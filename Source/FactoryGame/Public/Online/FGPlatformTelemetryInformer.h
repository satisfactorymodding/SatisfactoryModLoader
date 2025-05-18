// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "CommonUserSubsystem.h"
#include "Engine/ObjectReferencer.h"
#include "UObject/NoExportTypes.h"

#include "FGPlatformTelemetryInformer.generated.h"
class UFGGameInstance;

/**
 *  <FL> [ZimmermannA] Used for certification.
 */
UCLASS()
class FACTORYGAME_API UFGPlatformTelemetryInformer : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// USubsystem
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// ~USubsystem

	UFUNCTION()
	void SetOnlineFeatureStatus(EOnlineSessionFeatureType sessionFeatureType);

private:

	bool bUsesMultiplayerFeature;
	UCommonUserSubsystem * pUserManager;
	UOnlineIntegrationSubsystem * pOnlineIntegrationSubsystem;
};
