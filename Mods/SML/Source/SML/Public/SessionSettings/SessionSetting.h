#pragma once
#include "CoreMinimal.h"
#include "Settings/FGUserSetting.h"
#include "SessionSetting.generated.h"

/** Describes a single session setting */
UCLASS(NotBlueprintable)
class SML_API USMLSessionSetting : public UDataAsset {
	GENERATED_BODY()
public:
	/** User setting properties for this object */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Session Setting", meta = (ShowInnerProperties))
	UFGUserSetting* UserSetting;

	/** A whitelist of maps on which this setting is relevant. If empty, it will be exposed on all available maps */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Session Setting")
	TArray<TSoftObjectPtr<UWorld>> MapNameWhitelist;

	/** True if the setting can be edited after the session creation, or only at the session start */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Session Setting")
	bool bCanEditAfterSessionCreation;

	// Not used for now but we want support for it later 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Session Setting")
	EOptionApplyType ApplyType;

	USMLSessionSetting();
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
