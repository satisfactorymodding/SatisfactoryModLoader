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
    if (Connection->GetDriver()->ServerConnection == Connection) {
        // We are a client. Nothing is listening for NMT_Failure on the remote
        // so we must "send" ourselves the message.
        // We cannot use GEngine->BroadcastNetworkFailure, followed by Connection->Close,
        // because UPendingNetGame will then call BroadcastNetworkFailure again with the generic "lost connection" message

        // Build a fake NMT_Failure bunch, only needs to contain a string.
        // We don't need to handle byte swapping, the Bunches handle that themselves.
        FControlChannelOutBunch Bunch(Connection->Channels[0], false);
        Bunch << MutableMessage;
        FInBunch InBunch(Connection, Bunch.GetData(), Bunch.GetNumBits());
        Connection->GetDriver()->Notify->NotifyControlMessage(Connection, NMT_Failure, InBunch);
    } else {
        // We are the server. Send NMT_Failure with the message to the client.
        FNetControlMessage<NMT_Failure>::Send(Connection, MutableMessage);
        Connection->FlushNet(true);
    }
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
 *                                                   Server                     Client
 *                                                     |        NMT_HELLO         |  UE initiates connection
 *               OnClientInitialJoin_Server is called  |<-------------------------|  OnClientInitialJoin is called
 *   SML intercepts the NMT_HELLO and sends SML_HELLO  |        SML_HELLO         |
 *                                                     |------------------------->|
 *                           UE responds to NMT_HELLO  |      NMT_CHALLENGE       |
 *                                                     |------------------------->|
 *                                                     |        SML_HELLO         |  SML receives SML_HELLO, responds with SML_HELLO
 *                                                     |<-------------------------|  SML sets bSupportsModMessageType = true
 *                                                     |   (queued SML messages)  |  SML sends all queued messages
 *                                                     |<-------------------------|
 *                                                     |        NMT_LOGIN         |  UE responds to NMT_CHALLENGE
 *                                                     |<-------------------------|
 *    SML receives SML_HELLO, responds with SML_HELLO  |        SML_HELLO         |
 *            SML sets bSupportsModMessageType = true  |------------------------->|
 *                      SML sends all queued messages  |   (queued SML messages)  |
 *                                                     |------------------------->|
 *                           UE responds to NMT_LOGIN  |       NMT_WELCOME        |
 *                          OnWelcomePlayer is called  |------------------------->|  OnWelcomePlayer_Client is called
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
        UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
        if (MessageType == NMT_Hello) {
            // NMT_Hello is only received on the server, sent by UPendingNetGame::SendInitialJoin
            // Initiate the SML handshake

            FNetControlMessage<NMT_DebugText>::Send(Connection, GSML_HELLO);
            Connection->FlushNet(true);

            NetworkHandler->OnClientInitialJoin_Server().Broadcast(Connection);
        }

        if (MessageType == NMT_Welcome) {
            // NMT_Welcome is only received on the client, sent by UWorld::WelcomePlayer

            NetworkHandler->OnWelcomePlayer_Client().Broadcast(Connection);
        }
        
        if (MessageType == NMT_DebugText) {
            // Part of the SML handshake, normally SML_HELLO is the only message ever sent on this channel.
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
