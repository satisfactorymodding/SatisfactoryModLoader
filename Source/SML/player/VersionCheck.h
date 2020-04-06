#pragma once

#include "GameFramework/GameMode.h"
#include "VersionCheck.generated.h"

UCLASS()
class UKickReasonAttachment : public UActorComponent {
	GENERATED_BODY()
public:
	FString PlayerKickReason;
	static UKickReasonAttachment* Get(AGameModeBase* Actor);
};

namespace SML {
	void RegisterVersionCheckHooks();
}