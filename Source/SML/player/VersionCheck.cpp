#include "VersionCheck.h"
#include "mod/hooking.h"
#include "FGGameMode.h"
#include "util/Logging.h"
#include "mod/ModHandler.h"
#include "SatisfactoryModLoader.h"
#include "Base64.h"
#include "Json.h"
#include "util/FuncNames.h"

UKickReasonAttachment* UKickReasonAttachment::Get(AGameModeBase* Actor) {
	UKickReasonAttachment* Attachment = Actor->FindComponentByClass<UKickReasonAttachment>();
	if (Attachment == nullptr) {
		Attachment = NewObject<UKickReasonAttachment>(Actor, TEXT("SML_KickAttachment"));
		Attachment->RegisterComponent();
	}
	return Attachment;
}

class FunctionProto {
public:
	EBrowseReturnVal::Type Browse(FWorldContext&, FURL&, FString&) {
		return EBrowseReturnVal::Success;
	}
	void PreLogin(const FString&, const FString&, const FUniqueNetIdRepl&, FString* ErrorMessage) {
	}
};

FString CreateModListString() {
	SML::Mod::FModHandler& ModHandler = SML::getModHandler();
	FString ResultString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ResultString);
	FJsonSerializer Serializer;
	TSharedRef<FJsonObject> ModListObject = MakeShareable(new FJsonObject());
	for (const FString& Modid : ModHandler.getLoadedMods()) {
		const SML::Mod::FModInfo& Info = ModHandler.getLoadedMod(Modid).modInfo;
		ModListObject->SetStringField(Modid, Info.version.string());
	}
	Serializer.Serialize(ModListObject, Writer);
	return ResultString;
}

void CheckModListString(const FString& modListString, FString& failureReason) {
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(modListString);
	FJsonSerializer Serializer;
	TSharedPtr<FJsonObject> ModListObject;
	if (!Serializer.Deserialize(Reader, ModListObject)) {
		failureReason = TEXT("Failed to parse mod list info json");
		return;
	}
	SML::Mod::FModHandler& ModHandler = SML::getModHandler();
	TArray<FString> MissingMods;
	for (const FString& loadedModId : ModHandler.getLoadedMods()) {
		if (!ModListObject->HasField(loadedModId)) {
			MissingMods.Add(FString::Printf(TEXT("%s: missing"), *loadedModId));
		} else {
			const FVersion& ModVersion = FVersion(*ModListObject->GetStringField(loadedModId));
			const FVersion& MinModVersion = ModHandler.getLoadedMod(loadedModId).modInfo.version;
			if (ModVersion.compare(MinModVersion) < 0) {
				const FString& Message = FString::Printf(TEXT("%s: required at least %s"), *loadedModId, *MinModVersion.string());
				MissingMods.Add(Message);
			}
		}
	}
	if (MissingMods.Num() > 0) {
		failureReason = FString(TEXT("Missing Mods on Client: \n")) += FString::Join(MissingMods, TEXT("\n"));
	}
}

FString Base64Encode(const FString& Source) {
	return FBase64::Encode(Source);
}

bool Base64Decode(const FString& Source, FString& OutDest) {
	const uint32 ExpectedLength = FBase64::GetDecodedDataSize(Source);
	TArray<ANSICHAR> TempDest;
	TempDest.AddZeroed(ExpectedLength + 1);
	if (!FBase64::Decode(*Source, Source.Len(), reinterpret_cast<uint8*>(TempDest.GetData()))) {
		return false;
	}
	OutDest = ANSI_TO_TCHAR(TempDest.GetData());
	return true;
}

void AddOptionWithValue(FURL& URL, const FString& OptionName, const FString& OptionValue) {
	const FString OptionDesc = FString::Printf(TEXT("%s=%s"), *OptionName, *OptionValue);
	URL.AddOption(*OptionDesc);
}

FString FindOptionValue(const FString& Options, const FString& OptionName) {
	const FString SearchPrefix = FString::Printf(TEXT("?%s="), *OptionName);
	const int32 OptionIndex = Options.Find(*SearchPrefix);
	if (OptionIndex != INDEX_NONE) {
		FString SubString = Options.Mid(OptionIndex + SearchPrefix.Len());
		int32 NextQuestionIndex;
		if (SubString.FindChar('?', NextQuestionIndex)) {
			SubString = SubString.Mid(0, NextQuestionIndex);
		}
		return SubString;
	}
	return TEXT("");
}

void SML::RegisterVersionCheckHooks() {
	SUBSCRIBE_METHOD(GAME_MODE_PRE_LOGIN_FUNC_DESC, FunctionProto::PreLogin, [](auto& scope, FunctionProto* gm, const FString& Options, const FString& str, const FUniqueNetIdRepl& repl, FString* ErrorMessage) {
		const FString OptionValue = FindOptionValue(Options, TEXT("SML_ModList"));
		FString DisconnectReason;
		if (!OptionValue.IsEmpty()) {
			FString ModListJsonString;
			if (Base64Decode(OptionValue, ModListJsonString)) {
				CheckModListString(ModListJsonString, DisconnectReason);
			} else DisconnectReason = TEXT("Malformed Mod List Data");
		} else DisconnectReason = TEXT("This server is running Satisfactory Mod Loader, and your client doesn't have it installed.");
		
		AGameModeBase* gameMode = reinterpret_cast<AGameModeBase*>(gm);
		UKickReasonAttachment* attachment = UKickReasonAttachment::Get(gameMode);
		attachment->PlayerKickReason.Empty();
		if (!DisconnectReason.IsEmpty()) {
			attachment->PlayerKickReason = DisconnectReason;
		}
	});
	FGameModeEvents::OnGameModePreLoginEvent().AddLambda([](AGameModeBase* gameMode, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) {
		UKickReasonAttachment* attachment = UKickReasonAttachment::Get(gameMode);
		if (!attachment->PlayerKickReason.IsEmpty()) {
			ErrorMessage = attachment->PlayerKickReason;
			SML::Logging::info(TEXT("Kicking player with ID "), *UniqueId.ToString(), TEXT(" due to mod incompatibility with reason: "), *ErrorMessage);
		}
	});
	
	SUBSCRIBE_METHOD(ENGINE_BROWSE_MAP_FUNC_DESC, FunctionProto::Browse, [](auto& scope, FunctionProto* ptr, FWorldContext& world, FURL& URL, FString& Error) {
		SML::Logging::info(TEXT("Connecting to URL "), *URL.ToString());
		const FString MyModListJson = CreateModListString();
		const FString EncodedModList = Base64Encode(MyModListJson);
		AddOptionWithValue(URL, TEXT("SML_ModList"), EncodedModList);
	});
}
