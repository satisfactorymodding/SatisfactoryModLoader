// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "FGPlatformFunctions.generated.h"

UENUM( BlueprintType )
enum class EFGPlatformScreenshotResult : uint8
{
	Success = 0,
	UnknownError = 1,
	Busy = 2,
	NoSpace = 3
};

UENUM( BlueprintType )
enum class EFGPlatformFeature : uint8
{
	Screenshot = 0,
	HiResScreenshot = 1
};

DECLARE_DYNAMIC_DELEGATE_OneParam( FFGPlatformScreenshotDone, EFGPlatformScreenshotResult, result );

UCLASS()
class UFGPlatformFunctionsSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
public:
	//~UEngineSubsystem interface
	virtual void Initialize( FSubsystemCollectionBase& Collection ) override;
	virtual void Deinitialize() override;
	//~End of UEngineSubsystem interface

	UFUNCTION( BlueprintCallable )
	static void CreatePlatformScreenshot( bool bHiRes, FFGPlatformScreenshotDone DoneDelegate );

	UFUNCTION( BlueprintPure )
	static float GetPlatformScreenshotCooldown();

	UFUNCTION( BlueprintPure )
	static bool PlatformHasFeature( EFGPlatformFeature Feature );

	UFUNCTION( BlueprintPure )
	static int GetPlatformMaxSavegames();

	UFUNCTION( BlueprintPure )
	static bool PlatformSupportsCommunityTranslations();

	UFUNCTION( BlueprintPure )
	static bool HasPlatform120HzEnabled(int32& RefreshRate);
};
