#include "Network/NetworkHandler.h"
#include "Engine/Engine.h"
#include "Net/DataChannel.h"
#include "Patching/NativeHookManager.h"
#include "Engine/NetConnection.h"
#include "Engine/World.h"
#include "UObject/UObjectAnnotation.h"

DEFINE_LOG_CATEGORY(LogModNetworkHandler);
DEFINE_CONTROL_CHANNEL_MESSAGE_THREEPARAM(ModMessage, 40, FString, int32, FString);
IMPLEMENT_CONTROL_CHANNEL_MESSAGE(ModMessage);

struct FConnectionSMLSupport {
    bool bSupportsModMessageType{false};
    TArray<TTuple<FMessageType, FString>> PendingMessages;

    FORCEINLINE bool IsDefault() const { return !bSupportsModMessageType && PendingMessages.IsEmpty(); }
};

static FUObjectAnnotationSparse<FConnectionSMLSupport, true> GConnectionMetadata;

static FString GSML_HELLO = TEXT("SML_HELLO");

FMessageEntry& UModNetworkHandler::RegisterMessageType(const FMessageType& MessageType) {
    UE_LOG(LogModNetworkHandler, Display, TEXT("Registering message type %s:%d"), *MessageType.ModReference, MessageType.MessageId);
    TMap<int32, FMessageEntry>& ModEntries = MessageHandlers.FindOrAdd(MessageType.ModReference);
    if (ModEntries.Contains(MessageType.MessageId)) {
        UE_LOG(LogModNetworkHandler, Fatal, TEXT("Tried to register mod message with duplicate identifier %d for mod %s"), MessageType.MessageId, *MessageType.ModReference);
        check(0);
    }
    return ModEntries.Add(MessageType.MessageId, FMessageEntry{});
}

void UModNetworkHandler::CloseWithFailureMessage(UNetConnection* Connection, const FString& Message) {
    FString MutableMessage = Message;
    FNetControlMessage<NMT_Failure>::Send(Connection, MutableMessage);
    Connection->FlushNet(true);
}

void UModNetworkHandler::SendMessage(UNetConnection* Connection, FMessageType MessageType, FString Data) {
    FConnectionSMLSupport ConnectionMetadata = GConnectionMetadata.GetAnnotation(Connection);
    if (ConnectionMetadata.bSupportsModMessageType) {
        FNetControlMessage<NMT_ModMessage>::Send(Connection, MessageType.ModReference, MessageType.MessageId, Data);
        Connection->FlushNet(true);
    } else {
        ConnectionMetadata.PendingMessages.Add({MessageType, Data});
        GConnectionMetadata.AddAnnotation(Connection, ConnectionMetadata);
    }
}

void UModNetworkHandler::SetConnectionSupportsModMessages(UNetConnection* Connection) {
    FConnectionSMLSupport ConnectionMetadata = GConnectionMetadata.GetAnnotation(Connection);

    if (ConnectionMetadata.bSupportsModMessageType) {
        return;
    }
    
    ConnectionMetadata.bSupportsModMessageType = true;

    // Let other side know we support mod messages
    FNetControlMessage<NMT_DebugText>::Send(Connection, GSML_HELLO);
    Connection->FlushNet(true);

    // Send all pending messages now that we know they are supported
    for (const TTuple<FMessageType, FString>& Message : ConnectionMetadata.PendingMessages) {
        FMessageType ModMessageType = Message.Get<0>();
        FString Data = Message.Get<1>();
        FNetControlMessage<NMT_ModMessage>::Send(Connection, ModMessageType.ModReference, ModMessageType.MessageId, Data);
    }

    Connection->FlushNet(true);
                    
    ConnectionMetadata.PendingMessages.Empty();
    GConnectionMetadata.AddAnnotation(Connection, ConnectionMetadata);
}

UGameInstance* UModNetworkHandler::GetGameInstanceFromNetDriver( const UNetDriver* NetDriver )
{
	if ( NetDriver )
	{
		if ( NetDriver->World != nullptr && NetDriver->World->GetGameInstance() != nullptr )
		{
			return NetDriver->World->GetGameInstance();
		}
		const FWorldContext* Context = GEngine->GetWorldContextFromPendingNetGameNetDriver( NetDriver );
		if ( Context != nullptr && Context->OwningGameInstance != nullptr )
		{
			return Context->OwningGameInstance;
		}
	}
	return nullptr;
}

void UModNetworkHandler::ReceiveMessage(UNetConnection* Connection, const FString& ModId, int32 MessageId, const FString& Content) const {
    const TMap<int32, FMessageEntry>* Result = MessageHandlers.Find(ModId);
    if (Result != nullptr) {
        const FMessageEntry* MessageEntry = Result->Find(MessageId);
        if (MessageEntry != nullptr) {
            const bool bIsClientSide = Connection->ClientLoginState == EClientLoginState::Invalid;
            const bool bCanBeHandled = (bIsClientSide && MessageEntry->bClientHandled) || (!bIsClientSide && MessageEntry->bServerHandled);
            if (bCanBeHandled) {
                MessageEntry->MessageReceived.ExecuteIfBound(Connection, Content);
            }
        }
    }
}

/**
 * SML handshake is done in the following way:
 *
 *                              Server                     Client
 *                                |        SML_HELLO         |
 *                                |------------------------->|
 *                                |        SML_HELLO         | bSupportsModMessageType = true
 *                                |<-------------------------|
 * bSupportsModMessageType = true |                          |
 *                                | any pending mod messages |
 *                                |<-------------------------|
 *                                |        SML_HELLO         |
 *                                |------------------------->|
 *                                | any pending mod messages |
 *                                |------------------------->|
 *   
 * If the client is not running SML, it will not respond to the SML_HELLO message,
 * so the server will not mark the connection as supporting mod messages, and never send any mod messages.
 *
 * If the server is not running SML, it will not send the initial SML_HELLO message,
 * so the client will not mark the connection as supporting mod messages, and never send any mod messages.
 *
 * We cannot simply send an SML_HELLO message from each side at the beginning of the connection,
 * because the server expects a specific message order from the client, up until the NMT_Welcome message,
 * and disconnects if that order is not followed.
 * So if the server is not running SML, nothing will intercept the SML_HELLO message, and it will reach
 * UWorld::NotifyControlMessage, which will disconnect the client.
 * 
 */
void UModNetworkHandler::InitializePatches() {
#if !WITH_EDITOR
    UWorld* WorldObjectInstance = GetMutableDefault<UWorld>();
    SUBSCRIBE_METHOD_VIRTUAL_AFTER(UWorld::WelcomePlayer, WorldObjectInstance, [=](UWorld* ServerWorld, UNetConnection* Connection) {
        UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
        NetworkHandler->OnWelcomePlayer().Broadcast(ServerWorld, Connection);
    });
	
    SUBSCRIBE_METHOD_AFTER(UPendingNetGame::SendInitialJoin, [=](UPendingNetGame* NetGame) {
        if (NetGame->NetDriver != nullptr) {
            UNetConnection* ServerConnection = NetGame->NetDriver->ServerConnection;
            if (ServerConnection != nullptr) {
                UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
                NetworkHandler->OnClientInitialJoin().Broadcast(ServerConnection);
            }
        }
    });
	
    auto MessageHandler = [=](auto& Call, void*, UNetConnection* Connection, uint8 MessageType, class FInBunch& Bunch) {
        if (MessageType == NMT_Hello) {
            // NMT_Hello is only received on the server, sent by UPendingNetGame::SendInitialJoin
            // Initiate the SML handshake

            FNetControlMessage<NMT_DebugText>::Send(Connection, GSML_HELLO);
            Connection->FlushNet(true);
        }
        
        if (MessageType == NMT_DebugText) {
            const int64 Pos = Bunch.GetPosBits();

            FString Text;
            if (FNetControlMessage<NMT_DebugText>::Receive(Bunch, Text)) {
                if(Text == GSML_HELLO) {
                    SetConnectionSupportsModMessages(Connection);
                }
            }

            // Only forward the message to the engine if it can be handled (see handshake explanation)
            if (Connection->IsClientMsgTypeValid(NMT_DebugText)) {
                Bunch.SetReadPosition(Pos);
            } else {
                Call.Cancel();
            }
        }
        
        if (MessageType == NMT_ModMessage) {
            FString ModId; int32 MessageId; FString Content;
            if (FNetControlMessage<NMT_ModMessage>::Receive(Bunch, ModId, MessageId, Content)) {
                UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
                NetworkHandler->ReceiveMessage(Connection, ModId, MessageId, Content);
                Call.Cancel();
            }
        }
    };

    SUBSCRIBE_METHOD_VIRTUAL(UWorld::NotifyControlMessage, WorldObjectInstance, MessageHandler);

    // Same for UPendingNetGame
    UPendingNetGame* PendingNetGame = static_cast<UPendingNetGame *>(FindObjectChecked<UClass>(NULL, TEXT("/Script/Engine.PendingNetGame"))->GetDefaultObject());
    SUBSCRIBE_METHOD_VIRTUAL(UPendingNetGame::NotifyControlMessage, PendingNetGame, MessageHandler);
#endif
}
