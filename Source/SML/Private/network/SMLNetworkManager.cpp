#include "Network/SMLConnection/SMLNetworkManager.h"
#include "FGPlayerController.h"
#include "ModHandler.h"
#include "NetworkHandler.h"
#include "ObjectMetadata.h"
#include "SatisfactoryModLoader.h"
#include "SMLConnectionMetadata.h"
#include "SMLRemoteCallObject.h"
#include "GameFramework/GameModeBase.h"

TSharedPtr<FMessageType> FSMLNetworkManager::MessageTypeModInit = NULL;

void FSMLNetworkManager::RegisterMessageTypeAndHandlers() {
    UModNetworkHandler* NetworkHandler = UModNetworkHandler::Get();
    MessageTypeModInit = MakeShareable(new FMessageType{TEXT("SML"), 1});
    
    FMessageEntry& MessageEntry = NetworkHandler->RegisterMessageType(*MessageTypeModInit);
    MessageEntry.bServerHandled = true;
    
    MessageEntry.MessageReceived.BindStatic(FSMLNetworkManager::HandleMessageReceived);
    NetworkHandler->OnClientInitialJoin().AddStatic(FSMLNetworkManager::HandleInitialClientJoin);
    NetworkHandler->OnWelcomePlayer().AddStatic(FSMLNetworkManager::HandleWelcomePlayer);
    FGameModeEvents::GameModePostLoginEvent.AddStatic(FSMLNetworkManager::HandleGameModePostLogin);
}

void FSMLNetworkManager::HandleMessageReceived(UNetConnection* Connection, FString Data) {
    UModNetworkHandler* NetworkHandler = UModNetworkHandler::Get();
    UObjectMetadata* Metadata = NetworkHandler->GetMetadataForConnection(Connection);
    USMLConnectionMetadata* SMLMetadata = Metadata->GetOrCreateSubObject<USMLConnectionMetadata>(TEXT("SML"));
    SMLMetadata->bIsInitialized = true;
    if (!HandleModListObject(SMLMetadata, Data)) {
        Connection->Close();
    }
}

void FSMLNetworkManager::HandleInitialClientJoin(UNetConnection* Connection) {
    UModNetworkHandler* NetworkHandler = UModNetworkHandler::Get();
    const FString LocalModList = SerializeLocalModList();
    NetworkHandler->SendMessage(Connection, *MessageTypeModInit, LocalModList);
}

void FSMLNetworkManager::HandleWelcomePlayer(UWorld* World, UNetConnection* Connection) {
    ValidateSMLConnectionData(Connection);
}

void FSMLNetworkManager::HandleGameModePostLogin(AGameModeBase* GameMode, APlayerController* Controller) {
    UModNetworkHandler* NetworkHandler = UModNetworkHandler::Get();
    AFGPlayerController* FGPlayerController = Cast<AFGPlayerController>(Controller);
    if (FGPlayerController) {
        USMLRemoteCallObject* RemoteCallObject = FGPlayerController->GetRemoteCallObjectOfClass<USMLRemoteCallObject>();

        if (FGPlayerController->IsLocalController()) {
            //This is a local player, so installed mods are our local mod list
            FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
            for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
                RemoteCallObject->ClientInstalledMods.Add(ModContainer->ModInfo.ModReference, ModContainer->ModInfo.Version);
            }
        } else {
            //This is remote player, retrieve installed mods from connection
            UNetConnection* NetConnection = CastChecked<UNetConnection>(Controller->Player);
            UObjectMetadata* Metadata = NetworkHandler->GetMetadataForConnection(NetConnection);
            USMLConnectionMetadata* SMLMetadata = Metadata->GetOrCreateSubObject<USMLConnectionMetadata>(TEXT("SML"));
            RemoteCallObject->ClientInstalledMods.Append(SMLMetadata->InstalledClientMods);
        }
    }
}

FString FSMLNetworkManager::SerializeLocalModList() {
    TSharedRef<FJsonObject> ModListObject = MakeShareable(new FJsonObject());
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
        ModListObject->SetStringField(ModContainer->ModInfo.ModReference, ModContainer->ModInfo.Version.ToString());
    }

    TSharedRef<FJsonObject> MetadataObject = MakeShareable(new FJsonObject());
    MetadataObject->SetObjectField(TEXT("ModList"), ModListObject);
    FString ResultString;
    const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ResultString);
    FJsonSerializer Serializer;
    Serializer.Serialize(MetadataObject, Writer);
    return ResultString;
}

bool FSMLNetworkManager::HandleModListObject(USMLConnectionMetadata* Metadata, const FString& ModListString) {
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ModListString);
    FJsonSerializer Serializer;
    TSharedPtr<FJsonObject> MetadataObject;
    if (!Serializer.Deserialize(Reader, MetadataObject)) {
        return false;
    }
    if (!MetadataObject->HasTypedField<EJson::Object>(TEXT("ModList"))) {
        return false;
    }
    const TSharedPtr<FJsonObject>& ModList = MetadataObject->GetObjectField(TEXT("ModList"));
    for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : ModList->Values) {
        FVersion ModVersion = FVersion{};
        FString ErrorMessage;
        const bool bParseSuccess = ModVersion.ParseVersion(Pair.Value->AsString(), ErrorMessage);
        if (bParseSuccess) {
            Metadata->InstalledClientMods.Add(Pair.Key, ModVersion);
        } else {
            return false;
        }
    }
    return true;
}

void FSMLNetworkManager::ValidateSMLConnectionData(UNetConnection* Connection) {
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    UModNetworkHandler* NetworkHandler = UModNetworkHandler::Get();
    UObjectMetadata* Metadata = NetworkHandler->GetMetadataForConnection(Connection);
    USMLConnectionMetadata* SMLMetadata = Metadata->GetOrCreateSubObject<USMLConnectionMetadata>(TEXT("SML"));
    TArray<FString> ClientMissingMods;
    
    if (!SMLMetadata->bIsInitialized) {
        UModNetworkHandler::CloseWithFailureMessage(Connection, TEXT("This server is running Satisfactory Mod Loader, and your client doesn't have it installed."));
        return;
    }
    
    for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
        const FModInfo& ModInfo = ModContainer->ModInfo;
        if (ModInfo.RemoteVersion.bAcceptAnyRemoteVersion) {
            continue; //Server-side only mod
        }
        FVersion* ClientVersion = SMLMetadata->InstalledClientMods.Find(ModInfo.ModReference);
        const FString ModName = FString::Printf(TEXT("%s (%s)"), *ModInfo.Name, *ModInfo.ModReference);
        if (ClientVersion == nullptr) {
            ClientMissingMods.Add(ModName);
            continue;
        }
        const FVersionRange& RemoteVersion = ModInfo.RemoteVersion.RemoteVersion;
        if (!RemoteVersion.Matches(*ClientVersion)) {
            const FString VersionText = FString::Printf(TEXT("required: %s, client: %s"), *RemoteVersion.ToString(), *ClientVersion->ToString());
            ClientMissingMods.Add(FString::Printf(TEXT("%s: %s"), *ModName, *VersionText));
        }
    }
    
    if (ClientMissingMods.Num() > 0) {
        const FString JoinedModList = FString::Join(ClientMissingMods, TEXT("\n"));
        const FString Reason = FString::Printf(TEXT("Client missing mods: %s"), *JoinedModList);
        UModNetworkHandler::CloseWithFailureMessage(Connection, Reason);
    }
}

bool HandleModInitData(USMLConnectionMetadata* Metadata, const FString& Data) {
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Data);
    FJsonSerializer Serializer;
    TSharedPtr<FJsonObject> MetadataObject;
    if (!Serializer.Deserialize(Reader, MetadataObject)) {
        return false;
    }
    const TSharedPtr<FJsonObject>& ModList = MetadataObject->GetObjectField(TEXT("ModList"));
    for (const auto& Pair : ModList->Values) {
        FVersion ModVersion = FVersion{};
        FString ErrorMessage;
        const bool bParseSuccess = ModVersion.ParseVersion(Pair.Value->AsString(), ErrorMessage);
        if (bParseSuccess) {
            Metadata->InstalledClientMods.Add(Pair.Key, ModVersion);
        }
    }
    return true;
}
