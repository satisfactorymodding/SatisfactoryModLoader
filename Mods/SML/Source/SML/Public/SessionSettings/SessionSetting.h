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
	
	/** A whitelist of map assets on which this setting is relevant. If empty, it will be exposed on all available maps */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Session Setting", meta=( DisplayName="Level Whitelist" ))
	TArray<TSoftObjectPtr<UWorld>> MapNameWhitelist;

#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
};
