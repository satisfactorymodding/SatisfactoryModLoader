// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGGameMode.h"
#include "FGGameModeDSComponent.generated.h"

enum class EPrivilegeLevel : uint8;
class UFGSchematic;
class UFGGamePhase;

class FDSGameModeComponentPreLoginData : public FDedicatedServerGameModeComponentPreLoginDataInterface
{
public:
	EPrivilegeLevel PlayerPrivilegeLevel{};
};

/**
 * Dedicated Server game mode component implementation
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGGameModeDSComponent : public UFGDedicatedServerGameModeComponentInterface
{
	GENERATED_BODY()
public:
	UFGGameModeDSComponent();

	// Begin UFGDedicatedServerGameModeComponent interface
	virtual void NotifyBeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool PreLogin(UPlayer* NewPlayer, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage, TSharedPtr<FDedicatedServerGameModeComponentPreLoginDataInterface>& OutPreLoginData) override;
	virtual void PostLogin(APlayerController* PlayerController, const TSharedPtr<FDedicatedServerGameModeComponentPreLoginDataInterface>& PreLoginData) override;
	virtual void NotifyPlayerLogout(AController* ExitingController) override;
	virtual TSubclassOf<AFGGameSession> OverrideGameSessionClass(TSubclassOf<AFGGameSession> InGameSessionClass) const override;
	virtual bool IsPaused(bool bGameModePaused) const override;
	virtual void NotifyInitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual bool AllowCheats(APlayerController* PlayerController) const override;
	virtual bool ShouldSkipOnboarding(bool bGameModeSkipOnboarding) const override;
	// End UFGDedicatedServerGameModeComponent interface

	FORCEINLINE bool IsAllowedToReclaimSocket() const { return mAllowedToReclaimSocket; }

	/** Amount of time to delay the auto-pause for to allow the level streaming and factory logic to complete initialization */
	float ServerAutoPauseStartupTimeDelay;
protected:
	void OnAutoSaveOnPlayerDisconnectChanged( FString OptionName, FVariant OptionValue );
	void OnAutoPauseChanged( FString OptionName, FVariant OptionValue );
	void OnAdvancedGameSettingChanged( FString OptionName, FVariant OptionValue );

	UFUNCTION()
	void OnCurrentGamePhaseUpdated( UFGGamePhase* NewCurrentGamePhase );
	UFUNCTION()
	void OnActiveSchematicChanged( TSubclassOf<UFGSchematic> NewActiveSchematic );
	
	/** True if we want to save when the player disconnects from the game */
	uint8 mAutoSaveOnPlayerDisconnect : 1;
	/** True if we want to auto pause when there are no players on the server */
	uint8 mAutoPause : 1;
	/** True if we are allowed to auto pause. That means no level streaming is pending and a fixed amount of time has passed since the server has started */
	uint8 mAllowedToAutoPause : 1;
	/** True if we are allowed to re-claim the server socket */
	uint8 mAllowedToReclaimSocket: 1;
	/** Amount of time passed since the server started */
	float TimeSinceServerStarted;
};
