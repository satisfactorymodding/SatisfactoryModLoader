#include "Patching/Patch/SaveMetadataPatch.h"

#include "FGAdminInterface.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGPlayerController.h"
#include "FGSaveManagerInterface.h"
#include "SatisfactoryModLoader.h"
#include "Patching/Patch/MainMenuPatch.h"
#include "Patching/BlueprintHookHelper.h"
#include "Patching/BlueprintHookManager.h"
#include "Reflection/ReflectionHelper.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/Engine.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "Patching/NativeHookManager.h"
#include "WebBrowser/Public/IWebBrowserDialog.h"

bool FSaveMetadataPatch::IsCallback = false;

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

FString FModMismatch::ToString()
{
	if (this->IsMissing)
	{
		return FString::Printf(TEXT("%ls is missing"), *this->Was.Name);
	}
	return FString::Printf(TEXT("%ls (%ls -> %ls)"),
		*this->Is.FriendlyName,* this->Was.Version.ToString(), *this->Is.Version.ToString());
}

FModMismatch::FModMismatch(FModMetadata Was, FModInfo Is, bool IsMissing) : Was(Was), Is(Is), IsMissing(IsMissing) {}

bool FSaveMetadataPatch::Patch(FSaveHeader Header, APlayerController* PlayerController)
{
	if (IsCallback) {
		return false;
	}
		
	UFGSaveSystem* System = UFGSaveSystem::Get(PlayerController);

	TArray<FModMismatch> ModMismatches = FindModMismatches(Header);

	USaveMetadataCallback* CallbackObject = USaveMetadataCallback::New(System, Header, PlayerController);
	if (ModMismatches.Num() > 0)
	{
#if !UE_SERVER
		PopupWarning(ModMismatches, CallbackObject);
#endif
		LogModMismatches(ModMismatches);
		return true;
	}
	return false;
}

void FSaveMetadataPatch::RegisterPatch() {
	UFGSaveSystem* Context = GetMutableDefault<UFGSaveSystem>();
	SUBSCRIBE_METHOD_VIRTUAL(UFGSaveSystem::LoadSaveFile, Context, [](auto& scope, UFGSaveSystem* self, const FSaveHeader& SaveGame, APlayerController* Player)
	{
		bool bAbort = Patch(SaveGame, Player);
		if (bAbort)
		{
			scope.Cancel();
		}
	});
	SUBSCRIBE_METHOD(AFGAdminInterface::LoadGame, [](auto& scope, AFGAdminInterface* self, bool locally, const FSaveHeader& save)
	{
		if (locally) {
			return;
		}
		APlayerController* Player = self->GetWorld()->GetFirstPlayerController();
		bool bAbort = Patch(save, Player);
		if (bAbort)
		{
			scope.Cancel();
		}
	});
}

void FSaveMetadataPatch::PopupWarning(TArray<FModMismatch> ModMismatches, USaveMetadataCallback* CallbackObject)
{
	FPopupClosed PopupClosedDelegate;
	
	PopupClosedDelegate.BindDynamic(CallbackObject, &USaveMetadataCallback::Callback);
	FString Body = BuildModMismatchesString(ModMismatches);
		
	UFGBlueprintFunctionLibrary::AddPopupWithCloseDelegate(CallbackObject->Player,
		FText::FromString(TEXT("Mod mismatch")), FText::FromString(Body),
		PopupClosedDelegate, PID_OK_CANCEL);
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

inline FString FSaveMetadataPatch::BuildModMismatchesString(TArray<FModMismatch>& ModMismatches)
{
	FString ExplanationMessage =
		"Missing mod content will disappear from your world.\n"
		"This includes things like machines & items but not more generic effects like moving a foundation.\n\n"
		"Press Confirm to load the save anyway or Cancel if you want to cancel";
	
	if (ModMismatches.Num() == 1)
	{
		FModMismatch ModMismatch = ModMismatches[0];
		FString Header = ModMismatch.Was.Name + " was previously used in this save and ";
		if (ModMismatch.IsMissing)
		{
			Header += "is missing";
		} else
		{
			Header += FString::Printf(TEXT("has a lower version than the previous one (%ls -> %ls)"),
				*ModMismatch.Was.Version.ToString(), *ModMismatch.Is.Version.ToString());
		}
		return FString::Printf(TEXT("%ls\n\n%ls"), *Header, *ExplanationMessage);
	}
	int NumMods = ModMismatches.Num();
	int NumOverflowMods = 0;
	if (NumMods > 20)
	{
		NumOverflowMods = NumMods - 20;
		NumMods = 20;
	}
	
	FString Out = "Some mods previously used in this save are missing or have lower versions:\n";
	for (int i = 0; i < NumMods; ++i)
	{
		Out += ModMismatches[i].ToString() + "\n";
	}
	if (NumOverflowMods)
	{
		Out += FString::Printf(TEXT("%d missing mods were not shown in this list but written to the log\n"), NumOverflowMods);
	}
	Out += "\n" + ExplanationMessage;
	
	return Out;
}

void FSaveMetadataPatch::LogModMismatches(TArray<FModMismatch>& ModMismatches)
{
	UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("%d missing mods found:"), ModMismatches.Num())
	for (int i = 0; i < ModMismatches.Num(); ++i)
	{
		UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("%ls"), *ModMismatches[i].ToString())
	}
}

void USaveMetadataCallback::Callback(bool Continue) 
{
	if (Continue)
	{
		FSaveMetadataPatch::IsCallback = true;
		System->LoadSaveFile(this->SaveGame, Player);
		FSaveMetadataPatch::IsCallback = false;
	}
	this->RemoveFromRoot();
}

USaveMetadataCallback* USaveMetadataCallback::New(UFGSaveSystem* System, FSaveHeader SaveGame, APlayerController* Player)
{
	USaveMetadataCallback* CallbackObject = NewObject<USaveMetadataCallback>();
	CallbackObject->AddToRoot();
	CallbackObject->System = System;
	CallbackObject->SaveGame = SaveGame;
	CallbackObject->Player = Player;
	return CallbackObject;
}