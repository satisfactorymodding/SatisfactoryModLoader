// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "FGMusicManager.generated.h"

// MODDING EDIT
UCLASS()
class UAkObject : public UObject
{
	GENERATED_BODY()
};

/**
 * Handles playing the music in game, this is created really early and is available across loading screens.
 */
UCLASS(Blueprintable,Config=Engine)
class FACTORYGAME_API UFGMusicManager : public UObject
{
	GENERATED_BODY()
public:
	/** Create a music manager from the specified class in a config */
	static class UFGMusicManager* CreateMusicManager( class UFGGameInstance* gameInstance );

	/** Get the music manager, can return null if world context is invalid or no music manager is spawned. */
	static UFGMusicManager* Get( UWorld* world );
	/** Get the music manager, can return null if world context is invalid or no music manager is spawned. */
	UFUNCTION( BlueprintPure, Category = "Music", DisplayName = "GetMusicManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static UFGMusicManager* Get( UObject* worldContext );

	// Begin UObject interface
	virtual UWorld* GetWorld() const override;
	// End UObject interface

	/** Let us know when a player controller enters play. */
	void OnPlayerControllerBeginPlay( class AFGPlayerControllerBase* pc );

	/** Start/Continue music playback. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Audio" )
	void Play();

	/** Pause music playback. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Audio" )
	void Pause();

	/** Stop music playback. */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Audio" )
	void Stop();

	/** Called when combat status has changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio" )
	void OnCombatStatusChanged( bool inCombat );

	/** Called from the local character when attacker register/unregisters */
	void UpdateIncomingAttackers( int32 numAttackers );

	/** Checks combat status */
	UFUNCTION( BlueprintPure, Category = "Audio" )
	FORCEINLINE bool IsInCombat() { return mIsInCombat; }
protected:
	/** Notify that music manager has been created */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio", DisplayName = "OnInit" )
	void NotifyInit( UWorld* loadedWorld, class AWorldSettings* worldSettings );

	/** Called whenever a player enters an area */
	UFUNCTION( BlueprintNativeEvent, Category = "Audio" )
	void OnPlayerEnteredArea(AFGPlayerControllerBase* playerController, TSubclassOf< class UFGMapArea > mapArea );

	/** Called whenever a player enters*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio" )
	void OnPlayerNearBaseChanged( bool isNear );
private:
	UFGMusicManager();

	/** called on regular interval to update music */
	void Update();

	/** Called when a new level has been loaded. */
	void Init( UWorld* inWorld );

protected:
	/** How often (in seconds) we want to check if we are close to a factory */
	UPROPERTY( EditDefaultsOnly, Category = "Audio")
	float mUpdateInterval;

	/** The distance that we considers a factory as close */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	float mFactoryCloseDistance;

	/** Object we post event on, set RTPC on etc. */
	UPROPERTY( BlueprintReadOnly, Transient )
	class UAkObject* mAkObject;

	UPROPERTY(BlueprintReadOnly)
	bool mHasPlayerAlreadyVisitedArea = false;

private:
	/** Music manager class name */
	UPROPERTY( GlobalConfig )
	FSoftClassPath mMusicManagerClassName;

	/** Handle for the timer to check if a player i near a factory */
	FTimerHandle mUpdateHandle;

	/** If the player is in his factory. */
	uint8 mIsPlayerNearBase : 1;

	/** If the player is in combat mode. */
	uint8 mIsInCombat : 1;

	/** Saved value of how many attackers the local player has currently */
	int32 mCachedNumAttackers;
};
