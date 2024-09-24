#include "Patching/Patch/SaveMetadataPatch.h"

#include "FGPlayerController.h"
#include "FGSaveManagerInterface.h"
#include "SatisfactoryModLoader.h"
#include "Dom/JsonObject.h"
#include "Engine/GameInstance.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#define LOCTEXT_NAMESPACE "SML"

static TAutoConsoleVariable CVarSkipModCompatibilityCheck(
	TEXT("SML.SkipModCompatibilityCheck"),
	GIsEditor,
	TEXT("1 to skip mod compatibility check, 0 to enable it. Mod compatibility checks are disabled by default in the editor."),
	ECVF_Default
);

FSavedModInfo::FSavedModInfo(const FString& Reference, const FString& Name, const FVersion& Version) : Reference(Reference), Name(Name), Version(Version){}

bool FSavedModInfo::Read(const TSharedRef<FJsonObject>& Object, FString& OutError) {
	if(!Object->TryGetStringField("Reference", this->Reference))
	{
		OutError = TEXT("Missing Reference");
		return false;
	}
	if(!Object->TryGetStringField("Name", this->Name))
	{
		OutError = TEXT("Missing Name");
		return false;
	}
	FString VersionString;
	if(!Object->TryGetStringField("Version", VersionString))
	{
		OutError = TEXT("Missing Version");
		return false;
	}
	FString VersionError;
	if(!Version.ParseVersion(VersionString, VersionError))
	{
		OutError = FString::Printf(TEXT("Invalid Version: %s"), *VersionError);
		return false;
	}
	return true;
}


void FSavedModInfo::Write(const TSharedRef<FJsonObject>& Object) const {
	Object->SetStringField("Reference", this->Reference);
	Object->SetStringField("Name", this->Name);
	Object->SetStringField("Version", this->Version.ToString());
}

FSavedModInfo FSavedModInfo::FromModInfo(const FModInfo& ModInfo) 
{
	return FSavedModInfo(ModInfo.Name, ModInfo.FriendlyName, ModInfo.Version);
}

FString FModMismatch::ToString() const {
	if (this->IsMissing)
	{
		return FString::Printf(TEXT("%ls is missing"), *this->Was.Name);
	}
	return FString::Printf(TEXT("%ls (%ls -> %ls)"),
		*this->Is.FriendlyName,* this->Was.Version.ToString(), *this->Is.Version.ToString());
}

FText FModMismatch::ToText() const {
	if (this->IsMissing)
	{
		return FText::Format(LOCTEXT("MOD_MISSING", "{0} is missing"), FText::FromString(this->Was.Name));
	}
	return FText::Format(LOCTEXT("MOD_DOWNGRADE", "{0} was {1}, is {2})"),
		FText::FromString(this->Is.FriendlyName), FText::FromString(this->Was.Version.ToString()), FText::FromString(this->Is.Version.ToString()));
}

FModMismatch::FModMismatch(const FSavedModInfo& Was, const FModInfo& Is, const bool IsMissing) : Was(Was), Is(Is), IsMissing(IsMissing) {}

void FSaveMetadataPatch::Register() {
	UFGSaveSystem::CheckModdedSaveCompatibilityDelegate.BindStatic(CheckModdedSaveCompatibility);
}

ESaveModCheckResult FSaveMetadataPatch::CheckModdedSaveCompatibility(const FSaveHeader& SaveHeader, FText& OutMessage) {

	// Bail out early if we are asked to skip compatibility checking
	if ( CVarSkipModCompatibilityCheck.GetValueOnGameThread() )
	{
		return ESaveModCheckResult::MCR_Supported;
	}
	
	if(!SaveHeader.IsModdedSave) {
		return ESaveModCheckResult::MCR_Supported;
	}

	FModMetadata ModMetadata;
	if (!GetModMetadataFromHeader(SaveHeader, ModMetadata)) {
		OutMessage = LOCTEXT("MOD_METADATA_MISSING", "Could not read save mod metadata. Mod compatibility check was skipped.");
		return ESaveModCheckResult::MCR_Volatile;
	}

	// There is no game instance context here, so we have to use one for the first PIE/Game world currently available
	UGameInstance* GameInstance = nullptr;
	for ( const FWorldContext& WorldContext : GEngine->GetWorldContexts() )
	{
		if ( WorldContext.WorldType == EWorldType::PIE || WorldContext.WorldType == EWorldType::Game )
		{
			GameInstance = WorldContext.OwningGameInstance;
		}
	}

	if ( GameInstance )
	{
		// The save map must be present
		const ESaveModCheckResult MapCheckResult = CheckSaveMap(GameInstance, ModMetadata, SaveHeader, OutMessage);
		if (MapCheckResult != ESaveModCheckResult::MCR_Supported) {
			return MapCheckResult;
		}

		// Warn about missing/downgraded mods
		const ESaveModCheckResult ModMismatchesCheckResult = CheckModMismatches(GameInstance, ModMetadata, OutMessage);
		if (ModMismatchesCheckResult != ESaveModCheckResult::MCR_Supported) {
			return ModMismatchesCheckResult;
		}
	}
	return ESaveModCheckResult::MCR_Supported;
}

ESaveModCheckResult FSaveMetadataPatch::CheckModMismatches(UGameInstance* GameInstance, const FModMetadata& ModMetadata, FText& OutMessage)
{
	TArray<FModMismatch> ModMismatches = FindModMismatches( GameInstance, ModMetadata.Mods );
	if (ModMismatches.Num() > 0)
	{
		OutMessage = BuildModMismatchesText(ModMismatches);
		LogModMismatches(ModMismatches);
		return ESaveModCheckResult::MCR_Volatile;
	}
	return ESaveModCheckResult::MCR_Supported;
}

TArray<FModMismatch> FSaveMetadataPatch::FindModMismatches(UGameInstance* GameInstance, const TArray<FSavedModInfo>& ModMetadata)
{
	TArray<FModMismatch> ModMismatches;
	UModLoadingLibrary* ModLibrary = GameInstance->GetSubsystem<UModLoadingLibrary>();

	for (const FSavedModInfo& OldMod : ModMetadata) {
		FModInfo LoadedModInfo;
		if (!ModLibrary->GetLoadedModInfo(OldMod.Reference, LoadedModInfo)) {
			ModMismatches.Add(FModMismatch(OldMod, FModInfo(), true));
			continue;
		}
		if (LoadedModInfo.Version.Compare(OldMod.Version) < 0) {
			ModMismatches.Add(FModMismatch(OldMod, LoadedModInfo, false));
		}
	}
	return ModMismatches;
}

ESaveModCheckResult FSaveMetadataPatch::CheckSaveMap(UGameInstance* GameInstance, const FModMetadata& ModMetadata, const FSaveHeader& SaveHeader, FText& OutMessage)
{
	FString MapName = ModMetadata.FullMapName;
	if ( MapName.IsEmpty() )
	{
		MapName = SaveHeader.MapName;
		GEngine->MakeSureMapNameIsValid( MapName );
	}
	
	if ( !FPackageName::DoesPackageExist( MapName ) )
	{
		FString MapMountPoint = MapName;
		MapMountPoint.RemoveFromStart( TEXT("/") );

		int32 MountPointSeparatorIndex;
		if ( MapMountPoint.FindChar( TEXT('/'), MountPointSeparatorIndex ) )
		{
			MapMountPoint.RemoveAt( MountPointSeparatorIndex, MapMountPoint.Len() - MountPointSeparatorIndex );
		}
		
		const FSavedModInfo* ModInfo = ModMetadata.Mods.FindByPredicate([&MapMountPoint](const FSavedModInfo& Info) {
			return Info.Reference == MapMountPoint;
		});
		const FString ModName = ModInfo != nullptr ? ModInfo->Name : MapMountPoint;
		
		OutMessage = FText::Format(LOCTEXT("SAVE_MAP_MISSING", "This save file uses a custom map from mod '{0}' which could not be found. The save could not be loaded. Contact the mod developer for assistance. See the logs for more info."), FText::FromString( *ModName ));
		UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Save file uses custom map '%s' of mod '%s' which could not be found"), *ModMetadata.FullMapName, *ModName )
		return ESaveModCheckResult::MCR_Incompatible;
	}

	// Although we could check the version of the mod that the save map is part of,
	// the mod version will be checked later for a downgrade
	// and upgrading the mod version should be safe
	return ESaveModCheckResult::MCR_Supported;
}

inline FText FSaveMetadataPatch::BuildModMismatchesText(TArray<FModMismatch>& ModMismatches)
{
	int NumMods = ModMismatches.Num();
	int NumOverflowMods = 0;
	if (NumMods > 20)
	{
		NumOverflowMods = NumMods - 20;
		NumMods = 20;
	}

	TArray<FText> Lines;
	
	Lines.Add(LOCTEXT("MOD_MISMATCHES", "Some mods previously used in this save are missing or have lower versions:"));
	
	TArray<FText> ModMismatchTexts;
	for (int i = 0; i < NumMods; ++i)
	{
		ModMismatchTexts.Push(ModMismatches[i].ToText());
	}
	Lines.Add(FText::Join(INVTEXT("\n"), ModMismatchTexts));
	if (NumOverflowMods)
	{
		Lines.Add(FText::Format(LOCTEXT("MOD_MISMATCHES_OVERFLOW", "{0} missing mods were not shown in this list but written to the log"), NumOverflowMods));
	}
	Lines.Add(LOCTEXT("MOD_MISMATCH_EXPLANATION",
		"Missing mod content will disappear from your world.\n"
		"This includes things like machines & items but not more generic effects like moving a foundation.\n\n"
		"Press Confirm to load the save anyway or Cancel if you want to cancel"));
	
	return FText::Join(INVTEXT("\n"), Lines);
}

void FSaveMetadataPatch::LogModMismatches(TArray<FModMismatch>& ModMismatches)
{
	UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("%d missing mods found:"), ModMismatches.Num())
	for (int i = 0; i < ModMismatches.Num(); ++i)
	{
		UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("%ls"), *ModMismatches[i].ToString())
	}
}

bool FSaveMetadataPatch::GetModMetadataFromHeader(const FSaveHeader& SaveHeader, FModMetadata& OutMetadata) {
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(SaveHeader.ModMetadata);
	TSharedPtr<FJsonObject> Metadata = nullptr;
	FJsonSerializer::Deserialize(Reader, Metadata);

	if (!Metadata.IsValid()) {
		UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Invalid mod metadata format"));
		return false;
	}

	return OutMetadata.Read(Metadata.ToSharedRef());
}

bool FModMetadata::Read(const TSharedRef<FJsonObject>& MetadataObject) {
	uint8 RawVersion;
	if (!MetadataObject->TryGetNumberField(TEXT("Version"), RawVersion)) {
		// This is a save from before the version field was added
		RawVersion = 0;
	}

	Version = static_cast<EModMetadataVersion>(RawVersion);

	if (Version >= EModMetadataVersion::InitialVersion) {
		if (!MetadataObject->HasField(TEXT("Mods"))) {
			UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Mod metadata missing \"Mods\"."));
			return false;
		}
	
		TArray<TSharedPtr<FJsonValue>> MetadataMods = MetadataObject->GetArrayField(TEXT("Mods"));
		for (int i = 0; i < MetadataMods.Num(); ++i)
		{
			const TSharedPtr<FJsonObject> MetadataMod = MetadataMods[i]->AsObject();
			if(!MetadataMod.IsValid()) {
				UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Mod metadata item %d is not an object."), i);
				return false;
			}
			
			FSavedModInfo ModInfo;
			FString ModError;
			if (!ModInfo.Read(MetadataMod.ToSharedRef(), ModError)) {
				UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to read mod metadata item %d: %s"), i, *ModError);
				return false;
			}
		
			Mods.Push(ModInfo);
		}
	}

	if (Version >= EModMetadataVersion::AddFullMapName) {
		if (!MetadataObject->HasField(TEXT("FullMapName"))) {
			UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Mod metadata missing \"FullMapName\"."));
			return false;
		}
		FullMapName = MetadataObject->GetStringField(TEXT("FullMapName"));
	}

	return true;
}

void FModMetadata::Write(const TSharedRef<FJsonObject>& MetadataObject) const {
	MetadataObject->SetNumberField(TEXT("Version"), static_cast<uint8>(EModMetadataVersion::LatestVersion));

	TArray<TSharedPtr<FJsonValue>> MetadataMods;
	for (const FSavedModInfo& ModInfo : Mods)
	{
		TSharedRef<FJsonObject> MetadataMod = MakeShared<FJsonObject>();
		ModInfo.Write(MetadataMod);
		MetadataMods.Push(MakeShared<FJsonValueObject>(MetadataMod));
	}
	MetadataObject->SetArrayField(TEXT("Mods"), MetadataMods);

	MetadataObject->SetStringField(TEXT("FullMapName"), FullMapName);
}

#undef LOCTEXT_NAMESPACE
