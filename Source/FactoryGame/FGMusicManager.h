#pragma once
#include "Engine/World.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGMusicManager.generated.h"

UCLASS(Blueprintable,Config=Engine)
class UFGMusicManager : public UObject
{
	GENERATED_BODY()
public:
	/** Create a music manager from the specified class in a config */
	static class UFGMusicManager* CreateMusicManager( class UFGGameInstance* gameInstance );

	static UFGMusicManager* Get( UWorld* world );

	/** To easy access the music manager from anywhere, can return null if world context is invalid or no music manager is spawned. */
	UFUNCTION( BlueprintPure, Category = "Music", DisplayName = "GetMusicManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static UFGMusicManager* Get( UObject* worldContext );

	virtual UWorld* GetWorld() const override;

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

protected:
	/** Notify that a new map has been loaded. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio", DisplayName = "OnPostLoadMap" )
	void NotifyPostLoadMap( UWorld* loadedWorld, class AWorldSettings* worldSettings );

	/** Called whenever a player enters an area */
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio" )
	void OnPlayerEnteredArea( TSubclassOf< class UFGMapArea > mapArea );

	/** Called whenever a player enters*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Audio" )
	void OnPlayerNearBaseChanged( bool isNear );

private:
	UFGMusicManager();

	/** called on regular interval to update music */
	void Update();

	/** Called when a new level has been loaded. */
	void OnPostLoadMap( UWorld* loadedWorld );

protected:
	/** How often (in seconds) we want to check if we are close to a factory */
	UPROPERTY( EditDefaultsOnly, Category = "Audio")
	float mUpdateInterval;

	/** The distance that we considers a factory as close */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	float mFactoryCloseDistance;

	// MODDING EDIT
	///** Object we post event on, set RTPC on etc. */
	//UPROPERTY( BlueprintReadOnly, Transient )
	//class UAkObject* mAkObject;

private:
	/** Music manager class name */
	UPROPERTY( GlobalConfig )
	FSoftClassPath mMusicManagerClassName;

	/** Handle for the timer to check if a player i near a factory */
	FTimerHandle mUpdateHandle;

	/** If the player is in his factory. */
	uint8 mIsPlayerNearBase : 1;
};