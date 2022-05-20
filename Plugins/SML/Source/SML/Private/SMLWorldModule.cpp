#include "SMLWorldModule.h"

#include "FGGameState.h"
#include "FGSaveSession.h"
#include "SatisfactoryModLoader.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Patching/Patch/SaveMetadataPatch.h"

USMLWorldModule::USMLWorldModule()
{
#if !WITH_EDITOR
	this->bRootModule = true;
#endif
}

void USMLWorldModule::DispatchLifecycleEvent(ELifecyclePhase Phase)
{
	Super::DispatchLifecycleEvent(Phase);
	if (Phase == ELifecyclePhase::POST_INITIALIZATION)
	{
		AGameStateBase* State = GetWorld()->GetGameState();
		if (State && State->HasAuthority())
		{
			WriteModMetadataToSave();
		}
	}
}

void USMLWorldModule::WriteModMetadataToSave()
{
	TArray<FModInfo> LoadedMods = GEngine->GetEngineSubsystem<UModLoadingLibrary>()->GetLoadedMods();
	TSharedRef<FJsonObject> Metadata = MakeShareable(new FJsonObject());
	TArray<TSharedPtr<FJsonValue>> Versions;
		
	for (int i = 0; i < LoadedMods.Num(); ++i)
	{
		FModInfo Mod = LoadedMods[i];
		if (IgnoredModReferences.Contains(Mod.Name))
		{
			continue;
		}
		FModMetadata VersionInfo = FModMetadata::FromModInfo(Mod);
		Versions.Push(VersionInfo.ToJson());
	}
	Metadata->SetArrayField("Mods", Versions);
		
	FString Out;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
	FJsonSerializer::Serialize(Metadata, Writer);
		
	UFGSaveSession* Session = UFGSaveSession::Get(this);
	Session->SetModMetadata(Out);
}
