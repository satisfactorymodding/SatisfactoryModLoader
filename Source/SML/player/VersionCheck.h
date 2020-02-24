#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/GameMode.h"
#include "VersionCheck.generated.h"

UCLASS()
class UKickReasonAttachment : public UActorComponent {
	GENERATED_BODY()
public:
	FString PlayerKickReason;
	static UKickReasonAttachment* Get(AGameModeBase* actor);
};

namespace SML {
	void registerVersionCheckHooks();
}