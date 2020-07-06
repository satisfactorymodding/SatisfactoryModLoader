#include "RemoteVersionChecker.h"
#include "mod/ModHandler.h"
#include "Json.h"
#include "SatisfactoryModLoader.h"
#include "NetworkHandler.h"
#include "player/component/SMLPlayerComponent.h"

void ValidateSMLInitData(UNetConnection* Connection, USMLConnectionMetadata* Metadata) {
    if (!Metadata->bIsInitialized) {
        UModNetworkHandler::CloseWithFailureMessage(Connection, TEXT("This server is running Satisfactory Mod Loader, and your client doesn't have it installed."));
        return;
    }
    FModHandler& ModHandler = SML::GetModHandler();
    TArray<FString> ClientMissingMods;
    for (const FString& Modid : ModHandler.GetLoadedMods()) {
        const FModInfo& Info = ModHandler.GetLoadedMod(Modid).ModInfo;
        if (Info.RemoteVersion.bAcceptAnyRemoteVersion)
            continue; //Server-side only mod
        FVersion* ClientVersion = Metadata->InstalledClientMods.Find(Modid);
        const FString ModName = FString::Printf(TEXT("%s (%s)"), *Info.Name, *Modid);
        if (ClientVersion == nullptr) {
            ClientMissingMods.Add(ModName);
            continue;
        }
        const FVersionRange& RemoteVersion = Info.RemoteVersion.RemoteVersion;
        if (!RemoteVersion.Matches(*ClientVersion)) {
            const FString VersionText = FString::Printf(TEXT("required: %s, client: %s"), *RemoteVersion.String(), *ClientVersion->String());
            ClientMissingMods.Add(FString::Printf(TEXT("%s: %s"), *ModName, *VersionText));
        }
    }
    if (ClientMissingMods.Num() > 0) {
        const FString JoinedModList = FString::Join(ClientMissingMods, TEXT("\n"));
        const FString Reason = FString::Printf(TEXT("Client missing mods: %s"), *JoinedModList);
        UModNetworkHandler::CloseWithFailureMessage(Connection, Reason);
    }
}

FString SerializeModInitData() {
    TSharedRef<FJsonObject> MetadataObject = MakeShareable(new FJsonObject());
    
    TSharedRef<FJsonObject> ModListObject = MakeShareable(new FJsonObject());
    FModHandler& ModHandler = SML::GetModHandler();
    for (const FString& Modid : ModHandler.GetLoadedMods()) {
        const FModInfo& Info = ModHandler.GetLoadedMod(Modid).ModInfo;
        ModListObject->SetStringField(Modid, Info.Version.String());
    }
    
    MetadataObject->SetObjectField(TEXT("ModList"), ModListObject);
    FString ResultString;
    const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ResultString);
    FJsonSerializer Serializer;
    Serializer.Serialize(MetadataObject, Writer);
    return ResultString;
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
        FVersion ModVersion = FVersion(Pair.Value->AsString());
        Metadata->InstalledClientMods.Add(Pair.Key, ModVersion);
    }
    return true;
}

//Metadata can be null if player is considered a local (host)
void CopyDataToPlayerComponent(USMLPlayerComponent* Component, USMLConnectionMetadata* Metadata) {
    Component->ClientInstalledMods.Empty();
    if (Metadata == nullptr) {
        //This is a local player, so installed mods are our local mod list
        FModHandler& ModHandler = SML::GetModHandler();
        for (const FString& Modid : ModHandler.GetLoadedMods()) {
            const FModInfo& Info = ModHandler.GetLoadedMod(Modid).ModInfo;
            Component->ClientInstalledMods.Add(Modid, Info.Version);
        }
    } else {
        //This is a remotely connected player, fetch list from connection metadata
        Component->ClientInstalledMods.Append(Metadata->InstalledClientMods);
    }
}

void FRemoteVersionChecker::Register() {
    const FMessageType MessageTypeSMLInit{TEXT("SML"), 1};
    UModNetworkHandler* NetworkHandler = UModNetworkHandler::Get();
    FMessageEntry& MessageEntry = NetworkHandler->RegisterMessageType(MessageTypeSMLInit);
    MessageEntry.bServerHandled = true;
    
    MessageEntry.MessageReceived.BindLambda([=](UNetConnection* Connection, const FString& Data){
        UObjectMetadata* Metadata = NetworkHandler->GetMetadataForConnection(Connection);
        USMLConnectionMetadata* SMLMetadata = Metadata->GetOrCreateSubObject<USMLConnectionMetadata>(TEXT("SML"));
        SMLMetadata->bIsInitialized = true;
        if (!HandleModInitData(SMLMetadata, Data))
            Connection->Close();
    });
    NetworkHandler->OnClientInitialJoin().AddLambda([=](UNetConnection* Connection){
        const FString InitialData = SerializeModInitData();
        NetworkHandler->SendMessage(Connection, MessageTypeSMLInit, InitialData);
    });
    NetworkHandler->OnWelcomePlayer().AddLambda([=](UWorld* Context, UNetConnection* Connection) {
        UObjectMetadata* Metadata = NetworkHandler->GetMetadataForConnection(Connection);
        USMLConnectionMetadata* SMLMetadata = Metadata->GetOrCreateSubObject<USMLConnectionMetadata>(TEXT("SML"));
        ValidateSMLInitData(Connection, SMLMetadata);
    });
    FGameModeEvents::GameModePostLoginEvent.AddLambda([=](AGameModeBase* GameMode, APlayerController* Controller){
        USMLPlayerComponent* PlayerComponent = USMLPlayerComponent::Get(Controller);
        UNetConnection* NetConnection = Cast<UNetConnection>(Controller->Player);
        if (PlayerComponent && Controller->Player) {
            USMLConnectionMetadata* SMLMetadata = NULL;
            if (NetConnection) {
                UObjectMetadata* Metadata = NetworkHandler->GetMetadataForConnection(NetConnection);
                SMLMetadata = Metadata->GetOrCreateSubObject<USMLConnectionMetadata>(TEXT("SML"));
            }
            CopyDataToPlayerComponent(PlayerComponent, SMLMetadata);
        }
    });
}
