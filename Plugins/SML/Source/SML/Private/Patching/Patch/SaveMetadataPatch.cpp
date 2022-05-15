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

FString FMissingMod::ToString()
{
	if (this->Is == nullptr)
	{
		return FString::Printf(TEXT("%ls is missing"), *this->Was.Name);
	}
	return FString::Printf(TEXT("%ls (%ls -> %ls)"),
		*this->Is->FriendlyName,* this->Was.Version.ToString(), *this->Is->Version.ToString());
}

FMissingMod::FMissingMod(FModMetadata Was, FModInfo* Is) : Was(Was), Is(Is) {}

void FSaveMetadataPatch::RegisterPatch() {
	UFGSaveSystem* Context = GetMutableDefault<UFGSaveSystem>();
	SUBSCRIBE_METHOD_VIRTUAL(UFGSaveSystem::LoadSaveFile, Context, [](auto& scope, UFGSaveSystem* self, const FSaveHeader& SaveGame, APlayerController* Player)
	{
		if (IsCallback) {
			return;
		}
		
		self = UFGSaveSystem::Get(Player);

		TArray<FMissingMod> MissingMods = FindMissingMods(SaveGame);

		USaveMetadataCallback* CallbackObject = USaveMetadataCallback::New(self, SaveGame, Player);
		bool Missing = PopupWarningIfMissingMods(MissingMods, CallbackObject);
		LogMissingMods(MissingMods);
		if (Missing)
		{
			scope.Cancel();
		}
	});
}

bool FSaveMetadataPatch::PopupWarningIfMissingMods(TArray<FMissingMod> MissingMods, USaveMetadataCallback* CallbackObject)
{
	if (MissingMods.Num() < 1)
	{
		return false;
	}
	FPopupClosed PopupClosedDelegate;
	
	PopupClosedDelegate.BindUFunction(CallbackObject, TEXT("Callback"));
	FString Body = BuildMissingModString(MissingMods);
		
	UFGBlueprintFunctionLibrary::AddPopupWithCloseDelegate(CallbackObject->Player,
		FText::FromString(TEXT("Mod mismatch")), FText::FromString(Body),
		PopupClosedDelegate, PID_OK_CANCEL);
	return true;
}

bool FindModInArray(TArray<FModInfo>& Mods, FString ModReference, FModInfo* Out)
{
	for (int i = 0; i < Mods.Num(); ++i)
	{
		FModInfo Mod = Mods[i];
		if (Mod.Name == ModReference)
		{
			*Out = Mod;
			return true;
		}
	}
	return false;
}

TArray<FMissingMod> FSaveMetadataPatch::FindMissingMods(FSaveHeader Header)
{
	TArray<FMissingMod> MissingMods;
	UModLoadingLibrary* ModLibrary = GEngine->GetEngineSubsystem<UModLoadingLibrary>();
	TArray<FModInfo> LoadedMods = ModLibrary->GetLoadedMods();

	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Header.ModMetadata);
	TSharedPtr<FJsonObject> Metadata = nullptr;
	FJsonSerializer::Deserialize(Reader, Metadata);
	if (!(Metadata.IsValid() && Metadata->HasField("Mods"))) {
		return MissingMods;
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
			return MissingMods;
		}
		FVersion ModVersion;
		FString VersionConversionError;
		ModVersion.ParseVersion(ModVersionString, VersionConversionError);
		if (VersionConversionError != "")
		{
			UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Invalid mod metadata version format. Could not verify if there are missing mods."))
			return MissingMods;
		}
		
		FModInfo* Mod = new FModInfo;
		bool FoundMod = FindModInArray(LoadedMods, ModReference, Mod);
		if (!FoundMod)
		{
			Mod = nullptr;
		}
		
		if (!Mod || Mod->Version.Compare(ModVersion) < 0)
		{
			FModMetadata VersionInfo = FModMetadata(ModReference, ModName, ModVersion);
			MissingMods.Push(FMissingMod(VersionInfo, Mod));
		}
	}
	return MissingMods;
}

inline FString FSaveMetadataPatch::BuildMissingModString(TArray<FMissingMod>& MissingMods)
{
	if (MissingMods.Num() < 1)
	{
		return "";
	}
	FString ExplanationMessage =
		"Missing mod content will disappear from your world.\n"
		"This includes things like machines & items but not more generic effects like moving a foundation.\n\n"
		"Press Confirm to load the save anyway or Cancel if you want to cancel";
	
	if (MissingMods.Num() == 1)
	{
		FMissingMod MissingMod = MissingMods[0];
		FString Header = MissingMod.Was.Name + " was previously used in this save and ";
		if (MissingMod.Is == nullptr)
		{
			Header += "is missing";
		} else
		{
			Header += FString::Printf(TEXT("has a lower version than the previous one (%ls -> %ls)"),
				*MissingMod.Was.Version.ToString(), *MissingMod.Is->Version.ToString());
		}
		return FString::Printf(TEXT("%ls\n\n%ls"), *Header, *ExplanationMessage);
	}
	int NumMods = MissingMods.Num();
	int NumOverflowMods = 0;
	if (NumMods > 20)
	{
		NumOverflowMods = NumMods - 20;
		NumMods = 20;
	}
	
	FString Out = "Some mods previously used in this save are missing or have lower versions:\n";
	for (int i = 0; i < NumMods; ++i)
	{
		Out += MissingMods[i].ToString() + "\n";
	}
	if (NumOverflowMods)
	{
		Out += FString::Printf(TEXT("%d missing mods were not shown in this list but written to the log\n"), NumOverflowMods);
	}
	Out += "\n" + ExplanationMessage;
	
	return Out;
}

void FSaveMetadataPatch::LogMissingMods(TArray<FMissingMod>& MissingMods)
{
	UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("%d missing mods found:"), MissingMods.Num())
	for (int i = 0; i < MissingMods.Num(); ++i)
	{
		UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("%ls"), *MissingMods[i].ToString())
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
}

USaveMetadataCallback* USaveMetadataCallback::New(UFGSaveSystem* System, FSaveHeader SaveGame, APlayerController* Player)
{
	USaveMetadataCallback* obj = NewObject<USaveMetadataCallback>();
	obj->System = System;
	obj->SaveGame = SaveGame;
	obj->Player = Player;
	return obj;
}