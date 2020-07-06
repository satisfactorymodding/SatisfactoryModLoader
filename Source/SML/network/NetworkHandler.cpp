#include "NetworkHandler.h"
#include "DataChannel.h"
#include "FGGameInstance.h"
#include "FGGameMode.h"
#include "mod/hooking.h"
#include "Engine/NetConnection.h"
#include "util/Logging.h"

DEFINE_CONTROL_CHANNEL_MESSAGE_THREEPARAM(ModMessage, 40, FString, int32, FString);
IMPLEMENT_CONTROL_CHANNEL_MESSAGE(ModMessage);

UModNetworkHandler* UModNetworkHandler::Get() {
    static UModNetworkHandler* GNetworkHandler = nullptr;
    if (!GNetworkHandler) GNetworkHandler = NewObject<UModNetworkHandler>();
    return GNetworkHandler;
}

FMessageEntry& UModNetworkHandler::RegisterMessageType(const FMessageType& MessageType) {
    TMap<int32, FMessageEntry>& ModEntries = MessageHandlers.FindOrAdd(MessageType.ModId);
    if (ModEntries.Contains(MessageType.MessageId)) {
        SML::Logging::fatal(TEXT("[ModNetworkHandler] Tried to register message with duplicate id "), MessageType.MessageId, TEXT(" for mod "), *MessageType.ModId);
    }
    return ModEntries.Add(MessageType.MessageId, FMessageEntry{});
}

void UModNetworkHandler::CloseWithFailureMessage(UNetConnection* Connection, const FString& Message) {
    FString DamnCopy = Message;
    FNetControlMessage<NMT_Failure>::Send(Connection, DamnCopy);
    Connection->FlushNet(true);
}

void UModNetworkHandler::SendMessage(UNetConnection* Connection, FMessageType MessageType, FString Data) {
    FNetControlMessage<NMT_ModMessage>::Send(Connection, MessageType.ModId, MessageType.MessageId, Data);
    Connection->FlushNet(true);
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

UObjectMetadata* UModNetworkHandler::GetMetadataForConnection(UNetConnection* Connection) {
    const TWeakObjectPtr<UNetConnection> Pointer = Connection;
    UObjectMetadata** ObjectMetadata = Metadata.Find(Pointer);
    if (ObjectMetadata == nullptr) {
        UObjectMetadata* NewMetadata = NewObject<UObjectMetadata>(this);
        Metadata.Add(Pointer, NewMetadata);
        return NewMetadata;
    }
    return *ObjectMetadata;
}

void UModNetworkHandler::Register() {
    UModNetworkHandler* GNetworkHandler = Get();
    GNetworkHandler->AddToRoot();
    SUBSCRIBE_METHOD_AFTER(UNetConnection::CleanUp, [=](UNetConnection* Connection) {
        GNetworkHandler->Metadata.Remove(Connection);
    });
    SUBSCRIBE_METHOD_AFTER(UWorld::WelcomePlayer, [=](UWorld* ServerWorld, UNetConnection* Connection) {
        GNetworkHandler->OnWelcomePlayer().Broadcast(ServerWorld, Connection);
    });
    SUBSCRIBE_METHOD_AFTER(UPendingNetGame::SendInitialJoin, [=](UPendingNetGame* NetGame) {
        if (NetGame->NetDriver != nullptr) {
            UNetConnection* ServerConnection = NetGame->NetDriver->ServerConnection;
            if (ServerConnection != nullptr) {
                GNetworkHandler->OnClientInitialJoin().Broadcast(ServerConnection);
            }
        }
    });
    auto MessageHandler = [=](auto& Call, void*, UNetConnection* Connection, uint8 MessageType, class FInBunch& Bunch) {
        if (MessageType == NMT_ModMessage) {
            FString ModId; int32 MessageId; FString Content;
            if (FNetControlMessage<NMT_ModMessage>::Receive(Bunch, ModId, MessageId, Content)) {
                GNetworkHandler->ReceiveMessage(Connection, ModId, MessageId, Content);
                Call.Cancel();
            }
        }
    };
    SUBSCRIBE_METHOD(UWorld::NotifyControlMessage, MessageHandler);
    SUBSCRIBE_METHOD(UPendingNetGame::NotifyControlMessage, MessageHandler);
}
