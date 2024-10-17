#include "SMLWorldModule.h"
#include "FGGameState.h"
#include "FGResearchManager.h"
#include "FGSaveSession.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Patching/Patch/SaveMetadataPatch.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

void USMLWorldModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
	Super::DispatchLifecycleEvent(Phase);

	if (Phase == ELifecyclePhase::POST_INITIALIZATION) {
		AGameStateBase* State = GetWorld()->GetGameState();
		if (State && State->HasAuthority()) {
			WriteModMetadataToSave();
		}
		// Update research trees in case dependencies were already unlocked.
		// After adding mods to an existing save, newly-added research trees
		// stay locked, even though their dependencies are already unlocked.
		AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);
		if (ResearchManager != NULL && ResearchManager->HasAuthority()) {
			ResearchManager->UpdateUnlockedResearchTrees();
		}
	}
}

void USMLWorldModule::WriteModMetadataToSave() {
	FModMetadata ModMetadata;
	
	TArray<FModInfo> LoadedMods = GetWorld()->GetGameInstance()->GetSubsystem<UModLoadingLibrary>()->GetLoadedMods();
	for (const FModInfo& Mod : LoadedMods) {
		if (IgnoredModReferences.Contains(Mod.Name)) {
			continue;
		}
		ModMetadata.Mods.Add(FSavedModInfo::FromModInfo(Mod));
	}
	ModMetadata.FullMapName = GetWorld()->GetPathName();

	TSharedRef<FJsonObject> Metadata = MakeShared<FJsonObject>();
	ModMetadata.Write(Metadata);

	FString Out;
	auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out);
	FJsonSerializer::Serialize(Metadata, Writer);

	UFGSaveSession* Session = UFGSaveSession::Get(this);
	Session->SetModMetadata(Out);
}
