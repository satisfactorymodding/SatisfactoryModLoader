#include "Patching/Patch/SaveMetadataPatch.h"

#include "FGPlayerController.h"
#include "FGSaveManagerInterface.h"
#include "SatisfactoryModLoader.h"
#include "Engine/Engine.h"
#include "ModLoading/ModLoadingLibrary.h"

#define LOCTEXT_NAMESPACE "SML"

FModMetadata::FModMetadata(FString Reference, FString Name, FVersion Version) : Reference(Reference), Name(Name), Version(Version){}

TSharedPtr<FJsonValue> FModMetadata::ToJson()
{
	TSharedPtr<FJsonObject> Object = MakeShareable(new FJsonObject());

	Object->SetStringField("Reference", this->Reference);
	Object->SetStringField("Name", this->Name);
	Object->SetStringField("Version", this->Version.ToString());
	
	return MakeShareable(new FJsonValueObject(Object));
}

FModMetadata FModMetadata::FromModInfo(FModInfo ModInfo) 
{
	return FModMetadata(ModInfo.Name, ModInfo.FriendlyName, ModInfo.Version);
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

FModMismatch::FModMismatch(FModMetadata Was, FModInfo Is, bool IsMissing) : Was(Was), Is(Is), IsMissing(IsMissing) {}

void FSaveMetadataPatch::Register() {
	UFGSaveSystem::CheckModdedSaveCompatibilityDelegate.BindStatic(CheckModdedSaveCompatibility);
}

ESaveModCheckResult FSaveMetadataPatch::CheckModdedSaveCompatibility(const FSaveHeader& SaveHeader, FText& OutMessage) {
	TArray<FModMismatch> ModMismatches = FindModMismatches(SaveHeader);
	if (ModMismatches.Num() > 0)
	{
		OutMessage = BuildModMismatchesText(ModMismatches);
		LogModMismatches(ModMismatches);
		return ESaveModCheckResult::MCR_Volatile;
	}
	return ESaveModCheckResult::MCR_Supported;
}

TArray<FModMismatch> FSaveMetadataPatch::FindModMismatches(FSaveHeader Header)
{
	TArray<FModMismatch> ModMismatches;
	UModLoadingLibrary* ModLibrary = GEngine->GetEngineSubsystem<UModLoadingLibrary>();
	TArray<FModInfo> LoadedMods = ModLibrary->GetLoadedMods();

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Header.ModMetadata);
	TSharedPtr<FJsonObject> Metadata = nullptr;
	FJsonSerializer::Deserialize(Reader, Metadata);
	if (!(Metadata.IsValid() && Metadata->HasField("Mods"))) {
		return ModMismatches;
	}
	
	TArray<TSharedPtr<FJsonValue>> MetadataMods = Metadata->GetArrayField("Mods");
	for (int i = 0; i < MetadataMods.Num(); ++i)
	{
		TSharedPtr<FJsonObject> MetadataMod = MetadataMods[i]->AsObject();
		FString ModReference;
		FString ModName;
		FString ModVersionString;
		bool bValidReference = MetadataMod->TryGetStringField("Reference", ModReference);
		bool bValidName = MetadataMod->TryGetStringField("Name",ModName);
		bool bValidVersion = MetadataMod->TryGetStringField("Version",ModVersionString);
		if (!(bValidReference && bValidVersion && bValidName))
		{
			UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Invalid mod metadata format. Could not verify if there are missing mods."))
			return ModMismatches;
		}
		FVersion ModVersion;
		FString VersionConversionError;
		ModVersion.ParseVersion(ModVersionString, VersionConversionError);
		if (VersionConversionError != "")
		{
			UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Invalid mod metadata version format. Could not verify if there are missing mods."))
			return ModMismatches;
		}
		
		FModInfo LoadedMod;
		bool bIsModLoaded = ModLibrary->GetLoadedModInfo(ModReference,LoadedMod);
		
		if (!bIsModLoaded || LoadedMod.Version.Compare(ModVersion) < 0)
		{
			FModMetadata OldVersionInfo = FModMetadata(ModReference, ModName, ModVersion);
			ModMismatches.Push(FModMismatch(OldVersionInfo, LoadedMod, !bIsModLoaded));
		}
	}
	return ModMismatches;
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

#undef LOCTEXT_NAMESPACE
