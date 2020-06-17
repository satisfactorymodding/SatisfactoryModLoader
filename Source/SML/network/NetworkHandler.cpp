#include "NetworkHandler.h"
#include "DataChannel.h"
#include "FGGameInstance.h"
#include "FGGameMode.h"
#include "mod/hooking.h"
#include "Engine/NetConnection.h"
#include "Json.h"
#include "util/Logging.h"
//Type of NMT_GameSpecific used by SML messaging
#define SML_MESSAGE_TYPE 100

static UModNetworkHandler* GNetworkHandler = nullptr;

UModNetworkHandler* UModNetworkHandler::Get() {
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

void UModNetworkHandler::SendMessage(UNetConnection* Connection, const FMessageType& MessageType, const FString& Data) const {
    TSharedRef<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    JsonObject->SetStringField(TEXT("ModId"), MessageType.ModId);
    JsonObject->SetNumberField(TEXT("MsgId"), MessageType.MessageId);
    JsonObject->SetStringField(TEXT("Content"), Data);
    FJsonSerializer Serializer;
    FString ResultMessage{};
    const TSharedRef<TJsonWriter<>> Writer = TJsonStringWriter<>::Create(&ResultMessage);
    Serializer.Serialize(JsonObject, Writer);
    uint8 MessageId = SML_MESSAGE_TYPE;
    FNetControlMessage<NMT_GameSpecific>::Send(Connection,  MessageId, ResultMessage);
}

void UModNetworkHandler::ReceiveMessage(UNetConnection* Connection, const FString& RawMessageData) const {
    TSharedPtr<FJsonObject> ResultObject;
    FJsonSerializer Serializer;
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawMessageData);
    if (!Serializer.Deserialize(Reader, ResultObject)) {
        SML::Logging::warning(TEXT("Invalid SML control message received from "), *Connection->Describe());
        Connection->Close();
        return;
    }
    const FString ModId = ResultObject->GetStringField(TEXT("ModId"));
    const int32 MessageId = ResultObject->GetIntegerField(TEXT("MsgId"));
    const FString Content = ResultObject->GetStringField(TEXT("Content"));
    const TMap<int32, FMessageEntry>* Result = MessageHandlers.Find(ModId);
    if (Result != nullptr) {
        const FMessageEntry* MessageEntry = Result->Find(MessageId);
        if (MessageEntry != nullptr) {
            const bool bIsClientSide = Connection->ClientLoginState == EClientLoginState::Invalid;
            const bool bCanBeHandled = (bIsClientSide && MessageEntry->bClientHandled) || (!bIsClientSide && MessageEntry->bServerHandled);
            if (bCanBeHandled) {
                MessageEntry->MessageReceived.ExecuteIfBound(Content);
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
    check(!GNetworkHandler);
    GNetworkHandler = NewObject<UModNetworkHandler>();
    GNetworkHandler->AddToRoot();
    SUBSCRIBE_METHOD_AFTER(UNetConnection::CleanUp, [](UNetConnection* Connection) {
        GNetworkHandler->Metadata.Remove(Connection);
    });
    SUBSCRIBE_METHOD_AFTER(UWorld::WelcomePlayer, [](UWorld* ServerWorld, UNetConnection* Connection) {
        GNetworkHandler->OnWelcomePlayer().Broadcast(ServerWorld, Connection);
        Connection->FlushNet();
    });
    SUBSCRIBE_METHOD_AFTER(UPendingNetGame::SendInitialJoin, [](UPendingNetGame* NetGame) {
        if (NetGame->NetDriver != nullptr) {
            UNetConnection* ServerConnection = NetGame->NetDriver->ServerConnection;
            if (ServerConnection != nullptr) {
                GNetworkHandler->OnClientInitialJoin().Broadcast(ServerConnection);
                ServerConnection->FlushNet();
            }
        }
    });
    SUBSCRIBE_VIRTUAL_FUNCTION_AFTER(UFGGameInstance, UGameInstance::HandleGameNetControlMessage, [](UGameInstance* Self, class UNetConnection* Connection, uint8 MessageId, const FString& MessageStr) {
        const uint8 TargetMessageId = SML_MESSAGE_TYPE;
        if (MessageId == TargetMessageId) {
            GNetworkHandler->ReceiveMessage(Connection, MessageStr);
        }
    });
}
