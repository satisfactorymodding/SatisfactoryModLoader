// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "AkGameplayTypes.h"
#include "AkAudioDevice.h"
#include "FGMusicManager.generated.h"

/**
 * Handles playing the music in game, this is created really early and is available across loading screens.
 * [ZolotukhinN:21/07/2025] Note: this cannot be a game instance subsystem because it is a global blueprint logic driven object
 */
UCLASS(Blueprintable,Config=Engine)
class FACTORYGAME_API UFGMusicManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UFGMusicManager();

	/** Create a music manager from the specified class in a config */
	static class UFGMusicManager* CreateMusicManager( class UFGGameInstance* gameInstance );

	/** Get the music manager, can return null if world context is invalid or no music manager is spawned. */
	static UFGMusicManager* Get( UWorld* world );

	/** Get the music manager, can return null if world context is invalid or no music manager is spawned. */
	UFUNCTION( BlueprintPure, Category = "Audio|MusicManager", DisplayName = "GetMusicManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static UFGMusicManager* Get( UObject* worldContext );

	// Begin UObject interface
	virtual void BeginDestroy() override;
	virtual UWorld* GetWorld() const override;
	// End UObject interface

	// Begin FTickableGameObject interface
	virtual bool IsTickableWhenPaused() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual TStatId GetStatId() const override;
	virtual bool IsTickable() const override;
	virtual void Tick(float DeltaTime) override;
	// End FTickableGameObject interface

	/** Start/Continue music playback. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Audio|MusicManager" )
	void Play();

	/** Pause music playback. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Audio|MusicManager" )
	void Pause();

	/** Stop music playback. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Audio|MusicManager" )
	void Stop();

	/** Checks combat status */
	UFUNCTION( BlueprintPure, Category = "Audio|MusicManager" )
	FORCEINLINE bool IsInCombat() { return mIsInCombat; }

	/** Get the event to post when we start the current level */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Level|Audio" )
	UAkAudioEvent* GetLevelStartedAkEvent() const;
protected:
	/** Notify that music manager has been created */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio|MusicManager", DisplayName = "OnInit" )
	void NotifyInit( bool isMainMenuWorld );

	/** Called every game tick when the game is not paused (including main menu) to update the state of the music manager */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio|MusicManager", DisplayName = "Tick" )
	void NotifyTick( float deltaTime, bool isMainMenuWorld );

	/** Called whenever a player enters an area */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio|MusicManager" )
	void OnPlayerEnteredArea( class AFGPlayerControllerBase* playerController, TSubclassOf<class UFGMapArea> mapArea );

	/** Called whenever a player enters*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio|MusicManager" )
	void OnPlayerNearBaseChanged( bool isNear );
	
	/** Called when combat status has changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio|MusicManager" )
	void OnCombatStatusChanged( bool inCombat );

	/** Called to notify that the game is now paused or is no longer paused */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio|MusicManager" )
	void OnGamePausedChanged( bool isGamePaused );

	UFUNCTION( BlueprintCallable, Category = "Audio|MusicManager", meta = ( AdvancedDisplay = "2", AutoCreateRefTerm = "PostEventCallback" ) )
	void PostEvent( class UAkAudioEvent* akEvent, UPARAM( meta = ( Bitmask, BitmaskEnum = "/Script/AkAudio.EAkCallbackType" ) ) const int32 callbackMask, const FOnAkPostEventCallback& postEventCallback );

	UFUNCTION( BlueprintCallable, Category = "Audio|MusicManager" )
	void SetRTPCValue( const class UAkRtpc* rtpcValue, float value, int32 interpolationTimeMs, FString rtpc );

	UFUNCTION( BlueprintCallable, Category = "Audio|MusicManager" )
	void SetSwitch( const class UAkSwitchValue* switchValue, FString switchGroup, FString switchState );

	/** called on regular interval to update factory music */
	void UpdatePlayerNearBaseState( const APlayerController* localPlayerController );

	/** Called when a new level has been loaded. */
	void InitializeWithCurrentWorld();

	/** Separate across multiple game instances in PIE to allow separating audio from them */
	AkGameObjectID GetAkGameObjectID() const;
protected:
	/** How often (in seconds) we want to check if we are close to a factory */
	UPROPERTY( EditDefaultsOnly, Category = "Audio")
	float mIsPlayerNearBaseUpdateInterval;

	/** The distance that we considers a factory as close */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	float mFactoryCloseDistance;

	UPROPERTY( BlueprintReadOnly, Category = "Audio" )
	bool mHasPlayerAlreadyVisitedArea{false};
private:
	/** Music manager class name */
	UPROPERTY( GlobalConfig )
	FSoftClassPath mMusicManagerClassName;

	float mTimeUntilPlayerNearBaseUpdate{0.0f};

	/** If the player is in his factory. */
	uint8 mIsPlayerNearBase: 1;
	/** If the player is in combat mode. */
	uint8 mIsInCombat: 1;
	/** True if the game is currently paused */
	uint8 mIsGameCurrentlyPaused: 1;

	/** Map area the player is currently in */
	UPROPERTY()
	TSubclassOf<class UFGMapArea> mCurrentMapArea;

	/** Saved value of how many attackers the local player has currently */
	int32 mCachedNumAttackers;

	/** Last world we have initialized the music manager for */
	TWeakObjectPtr<const UWorld> mLastInitializedWorld;
};
