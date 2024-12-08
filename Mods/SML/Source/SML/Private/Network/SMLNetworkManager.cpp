#include "Network/SMLConnection/SMLNetworkManager.h"
#include "FGPlayerController.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"
#include "Engine/NetConnection.h"
#include "Network/NetworkHandler.h"
#include "Player/SMLRemoteCallObject.h"
#include "GameFramework/GameModeBase.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "UObject/UObjectAnnotation.h"

static TAutoConsoleVariable CVarSkipRemoteModListCheck(
	TEXT("SML.SkipRemoteModListCheck"),
	GIsEditor,
	TEXT("1 to skip remote mod list check, 0 to enable it. Remote mod list checks are disabled by default in the editor."),
	ECVF_Default
);

static FUObjectAnnotationSparse<FConnectionMetadata, true> GModConnectionMetadata;

TSharedPtr<FMessageType> FSMLNetworkManager::MessageTypeModInit = NULL;

void FSMLNetworkManager::RegisterMessageTypeAndHandlers() {
    UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
    MessageTypeModInit = MakeShareable(new FMessageType{TEXT("SML"), 1});
    
    FMessageEntry& MessageEntry = NetworkHandler->RegisterMessageType(*MessageTypeModInit);
    MessageEntry.bServerHandled = true;
	MessageEntry.bClientHandled = true;
    
    MessageEntry.MessageReceived.BindStatic(FSMLNetworkManager::HandleMessageReceived);
    NetworkHandler->OnClientInitialJoin().AddStatic(FSMLNetworkManager::HandleInitialClientJoin);
	NetworkHandler->OnClientInitialJoin_Server().AddStatic(FSMLNetworkManager::HandleInitialClientJoin);
    NetworkHandler->OnWelcomePlayer().AddStatic(FSMLNetworkManager::HandleWelcomePlayer);
	NetworkHandler->OnWelcomePlayer_Client().AddStatic(FSMLNetworkManager::HandleWelcomePlayer_Client);
    FGameModeEvents::GameModePostLoginEvent.AddStatic(FSMLNetworkManager::HandleGameModePostLogin);
}

void FSMLNetworkManager::HandleMessageReceived(UNetConnection* Connection, FString Data) {
	FConnectionMetadata ConnectionMetadata{};
    ConnectionMetadata.bIsInitialized = true;
    if (!HandleModListObject(ConnectionMetadata, Data))
    {
        Connection->Close();
    }
	GModConnectionMetadata.AddAnnotation( Connection, ConnectionMetadata );
}

void FSMLNetworkManager::HandleInitialClientJoin(UNetConnection* Connection) {
    UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
    const FString LocalModList = SerializeLocalModList(Connection);
    NetworkHandler->SendMessage(Connection, *MessageTypeModInit, LocalModList);
}

void FSMLNetworkManager::HandleWelcomePlayer(UWorld* World, UNetConnection* Connection) {
    ValidateSMLConnectionData(Connection, true);
}

void FSMLNetworkManager::HandleWelcomePlayer_Client(UNetConnection* Connection) {
	ValidateSMLConnectionData(Connection, false);
}

void FSMLNetworkManager::HandleGameModePostLogin(AGameModeBase* GameMode, APlayerController* Controller) {

	UModNetworkHandler* NetworkHandler = GEngine->GetEngineSubsystem<UModNetworkHandler>();
    if (AFGPlayerController* CastedPlayerController = Cast<AFGPlayerController>(Controller)) {
        USMLRemoteCallObject* RemoteCallObject = CastedPlayerController->GetRemoteCallObjectOfClass<USMLRemoteCallObject>();

        if (CastedPlayerController->IsLocalController()) {
            //This is a local player, so installed mods are our local mod list
            UModLoadingLibrary* ModLoadingLibrary = GameMode->GetGameInstance()->GetSubsystem<UModLoadingLibrary>();
            const TArray<FModInfo> Mods = ModLoadingLibrary->GetLoadedMods();
            
            for (const FModInfo& ModInfo : Mods) {
                RemoteCallObject->ClientInstalledMods.Add(ModInfo.Name, ModInfo.Version);
            }
        } else {
            //This is remote player, retrieve installed mods from connection
            const UNetConnection* NetConnection = CastChecked<UNetConnection>(Controller->Player);
        	const FConnectionMetadata ConnectionMetadata = GModConnectionMetadata.GetAndRemoveAnnotation( NetConnection );
        	
            RemoteCallObject->ClientInstalledMods.Append(ConnectionMetadata.InstalledRemoteMods);
        }
    }
}

FString FSMLNetworkManager::SerializeLocalModList(UNetConnection* Connection)
{
	const TSharedRef<FJsonObject> ModListObject = MakeShareable(new FJsonObject());
	
	if (const UGameInstance* GameInstance = UModNetworkHandler::GetGameInstanceFromNetDriver( Connection->GetDriver() ) )
	{
		if ( UModLoadingLibrary* ModLoadingLibrary = GameInstance->GetSubsystem<UModLoadingLibrary>() )
		{
			const TArray<FModInfo> Mods = ModLoadingLibrary->GetLoadedMods();
    
			for (const FModInfo& ModInfo : Mods) {
				ModListObject->SetStringField(ModInfo.Name, ModInfo.Version.ToString());
			}
		}	
	}
	
	const TSharedRef<FJsonObject> MetadataObject = MakeShareable(new FJsonObject());
    MetadataObject->SetObjectField(TEXT("ModList"), ModListObject);
    
    FString ResultString;
    const auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&ResultString);
    FJsonSerializer::Serialize(MetadataObject, Writer);
    
    return ResultString;
}

bool FSMLNetworkManager::HandleModListObject( FConnectionMetadata& Metadata, const FString& ModListString) {
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ModListString);
    TSharedPtr<FJsonObject> MetadataObject;
    
    if (!FJsonSerializer::Deserialize(Reader, MetadataObject)) {
        return false;
    }
    
    if (!MetadataObject->HasTypedField<EJson::Object>(TEXT("ModList"))) {
        return false;
    }
    
    const TSharedPtr<FJsonObject>& ModList = MetadataObject->GetObjectField(TEXT("ModList"));
    
    for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : ModList->Values) {
        FVersion ModVersion = FVersion{};
        FString ErrorMessage;
        if ( ModVersion.ParseVersion(Pair.Value->AsString(), ErrorMessage) ) {
            Metadata.InstalledRemoteMods.Add(Pair.Key, ModVersion);
        } else {
            return false;
        }
    }
    
    return true;
}

void FSMLNetworkManager::ValidateSMLConnectionData(UNetConnection* Connection, bool IsServer)
{
	const bool bAllowMissingMods = CVarSkipRemoteModListCheck.GetValueOnGameThread();
	const FConnectionMetadata SMLMetadata = GModConnectionMetadata.GetAnnotation( Connection );
    TArray<FString> RemoteMissingMods;
    
    if (!SMLMetadata.bIsInitialized && !bAllowMissingMods && IsServer ) {
		// TODO: Is joining a modded server with a vanilla client safe?
        UModNetworkHandler::CloseWithFailureMessage(Connection, TEXT("This server is running Satisfactory Mod Loader, and your client doesn't have it installed."));
        return;
    }

	if (const UGameInstance* GameInstance = UModNetworkHandler::GetGameInstanceFromNetDriver( Connection->GetDriver() ) )
	{
		if ( UModLoadingLibrary* ModLoadingLibrary = GameInstance->GetSubsystem<UModLoadingLibrary>() )
		{
			const TArray<FModInfo> Mods = ModLoadingLibrary->GetLoadedMods();

			for (const FModInfo& ModInfo : Mods)
			{
				const FVersion* ClientVersion = SMLMetadata.InstalledRemoteMods.Find( ModInfo.Name );
				const FString ModName = FString::Printf( TEXT("%s (%s)"), *ModInfo.FriendlyName, *ModInfo.Name );
				if ( ClientVersion == nullptr )
				{
					// If the mod is not required on the remote, we don't care if it's missing
					// We also ignore SML in case we're joining a vanilla server with a modded client
					// TODO: Is joining a modded server with a vanilla client safe?
					if ( !ModInfo.bRequiredOnRemote || (ModInfo.Name == TEXT("SML") && !IsServer) )
					{
						continue; //Server-side only mod
					}
					RemoteMissingMods.Add( ModName );
					continue;
				}
				const FVersionRange& RemoteVersion = ModInfo.RemoteVersionRange;

				if ( !RemoteVersion.Matches(*ClientVersion) )
				{
					const FString VersionText = FString::Printf( TEXT("required: %s, %s: %s"), *RemoteVersion.ToString(), IsServer ? TEXT("client") : TEXT("server"), *ClientVersion->ToString() );
					RemoteMissingMods.Add( FString::Printf( TEXT("%s: %s"), *ModName, *VersionText ) );
				}
			}
		}	
	}
    
    if ( RemoteMissingMods.Num() > 0 && !bAllowMissingMods )
    {
        const FString JoinedModList = FString::Join( RemoteMissingMods, TEXT("\n") );
        const FString Reason = FString::Printf( TEXT("%s missing mods: %s"), IsServer ? TEXT("Client") : TEXT("Server"), *JoinedModList );
        UModNetworkHandler::CloseWithFailureMessage( Connection, Reason );
    }
}
