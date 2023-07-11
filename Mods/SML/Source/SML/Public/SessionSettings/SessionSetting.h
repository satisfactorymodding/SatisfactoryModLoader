#pragma once
#include "CoreMinimal.h"
#include "Settings/FGUserSetting.h"
#include "SessionSetting.generated.h"

/** Describes a single session setting */
UCLASS(NotBlueprintable)
class SML_API USMLSessionSetting : public UFGUserSetting {
	GENERATED_BODY()
public:
	USMLSessionSetting();

	virtual void PostLoad() override;
	
	/** A whitelist of maps on which this setting is relevant. If empty, it will be exposed on all available maps */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Session Setting")
	TArray<TSoftObjectPtr<UWorld>> MapNameWhitelist;
};
