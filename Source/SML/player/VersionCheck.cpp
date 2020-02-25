#include "VersionCheck.h"
#include "mod/hooking.h"
#include "FGGameMode.h"
#include "UnrealEngine.h"
#include "util/Logging.h"
#include "mod/ModHandler.h"
#include "SatisfactoryModLoader.h"
#include "util/json.hpp"
#include "Base64.h"
#include "GameFramework/GameSession.h"
#include "Object.h"

UKickReasonAttachment* UKickReasonAttachment::Get(AGameModeBase* actor) {
	UKickReasonAttachment* attachment = actor->FindComponentByClass<UKickReasonAttachment>();
	if (attachment == nullptr) {
		attachment = NewObject<UKickReasonAttachment>(actor, TEXT("SML_KickAttachment"));
		attachment->RegisterComponent();
	}
	return attachment;
}

class FunctionProto {
public:
	EBrowseReturnVal::Type Browse(FWorldContext&, FURL&, const FString&) {
		return EBrowseReturnVal::Success;
	}
	void PreLogin(const FString&, const FString&, const FUniqueNetIdRepl&, FString* ErrorMessage) {
	}
};

FString CreateModListString() {
	//terribly inefficient due to multiple string copying and conversion, oh well.
	SML::Mod::FModHandler modHandler = SML::getModHandler();
	nlohmann::json resultJson;
	for (const std::wstring& modid : modHandler.getLoadedMods()) {
		const SML::Mod::FModInfo& info = modHandler.getLoadedMod(modid).modInfo;
		resultJson[convertStr(modid.c_str())] = convertStr(info.version.string().c_str());
	}
	return FString(nlohmann::to_string(resultJson).c_str());
}

void CheckModListString(const FString& modListString, FString& failureReason) {
	nlohmann::json resultJson = nlohmann::json::parse(convertStr(*modListString));
	SML::Mod::FModHandler modHandler = SML::getModHandler();
	TArray<FString> missingMods;
	for (const std::wstring& loadedModId : modHandler.getLoadedMods()) {
		std::string modIdStr = convertStr(loadedModId.c_str());
		if (!resultJson.contains(modIdStr)) {
			missingMods.Add(FString::Printf(TEXT("%s: missing"), loadedModId.c_str()));
		} else {
			const FVersion& modVersion = FVersion(convertStr(resultJson[modIdStr].get<std::string>().c_str()));
			const FVersion& minModVersion = modHandler.getLoadedMod(loadedModId).modInfo.version;
			if (modVersion.compare(minModVersion) < 0) {
				const FString& message = FString::Printf(TEXT("%s: required at least %s"), loadedModId.c_str(), minModVersion.string().c_str());
				missingMods.Add(message);
			}
		}
	}
	if (missingMods.Num() > 0) {
		failureReason = FString(TEXT("Missing Mods on Client: \n")) += FString::Join(missingMods, TEXT("\n"));
	}
}

bool Base64Decode(const FString& Source, FString& OutDest) {
	uint32 ExpectedLength = FBase64::GetDecodedDataSize(Source);

	TArray<ANSICHAR> TempDest;
	TempDest.AddZeroed(ExpectedLength + 1);
	if (!FBase64::Decode(*Source, Source.Len(), reinterpret_cast<uint8*>(TempDest.GetData()))) {
		return false;
	}
	OutDest = ANSI_TO_TCHAR(TempDest.GetData());
	return true;
}

void SML::registerVersionCheckHooks() {
	SUBSCRIBE_METHOD("?PreLogin@AGameModeBase@@UEAAXAEBVFString@@0AEBUFUniqueNetIdRepl@@AEAV2@@Z", FunctionProto::PreLogin, [](CallResult<void>, void* gm, const FString& Options, const FString&, const FUniqueNetIdRepl&, FString* ErrorMessage) {
		const int32 SmlModListIndex = Options.Find(TEXT("?SML_ModList="));
		FString disconnectReason;
		if (SmlModListIndex != INDEX_NONE) {
			FString subString = Options.Mid(SmlModListIndex + 13);
			int32 nextQuestionIndex;
			if (subString.FindChar('?', nextQuestionIndex)) {
				subString = subString.Mid(0, nextQuestionIndex);
			}
			FString decodedString;
			if (Base64Decode(subString, decodedString)) {
				CheckModListString(decodedString, disconnectReason);
			} else {
				disconnectReason = TEXT("Malformed Mod List Data");
			}
		} else {
			disconnectReason = TEXT("This server is running Satisfactory Mod Loader, and your client doesn't have it installed.");
		}
		AGameModeBase* gameMode = reinterpret_cast<AGameModeBase*>(gm);
		UKickReasonAttachment* attachment = UKickReasonAttachment::Get(gameMode);
		attachment->PlayerKickReason.Empty();
		if (!disconnectReason.IsEmpty()) {	
			attachment->PlayerKickReason = disconnectReason;
		}
	});
	FGameModeEvents::OnGameModePreLoginEvent().AddLambda([](AGameModeBase* gameMode, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) {
		UKickReasonAttachment* attachment = UKickReasonAttachment::Get(gameMode);
		if (!attachment->PlayerKickReason.IsEmpty()) {
			ErrorMessage = attachment->PlayerKickReason;
			SML::Logging::info(TEXT("Kicking player with ID "), *UniqueId.ToString(), TEXT(" due to mod incompatibility with reason: "), *ErrorMessage);
		}
	});
	
	SUBSCRIBE_METHOD("?Browse@UEngine@@UEAA?AW4Type@EBrowseReturnVal@@AEAUFWorldContext@@UFURL@@AEAVFString@@@Z", FunctionProto::Browse, [](CallResult<EBrowseReturnVal::Type>, void*, FWorldContext&, FURL& URL, const FString& Error) {
		SML::Logging::info(TEXT("Connecting to URL "), *URL.ToString());
		const FString& myModList = CreateModListString();
		const FString& encodedModList = FBase64::Encode(myModList);
		URL.AddOption(*(FString(TEXT("SML_ModList=")) += encodedModList));
	});
}
