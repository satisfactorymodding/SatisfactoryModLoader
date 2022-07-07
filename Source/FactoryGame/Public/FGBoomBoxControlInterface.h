// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGBoomBoxControlInterface.generated.h"

UENUM( BlueprintType )
enum class EBoomBoxPickupButtonState: uint8
{
	EHideButton,			/** Never show the button - it's already equipped */
	EEquipBoomBox,			/** A hand slot is available and the boom box can be picked up */
	EPickUpBoomBox,			/** A hand slot is not available but an inventory slot is so it can be picked up. Interrupts playback. */
	ENoRoomForBoomBox		/** There's no room anywhere, in the inventory or a hand slot available so can't perform either action */
};

/**
 * 
 */
UINTERFACE( BlueprintType, meta=( CannotImplementInterfaceInBlueprint ) )
class FACTORYGAME_API UFGBoomBoxControlInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGBoomBoxControlInterface
{
	GENERATED_BODY()

	/** Changes the active tape in this boombox */
	UFUNCTION( BlueprintCallable )
	virtual void ChangeTape( TSubclassOf< class UFGTapeData > newTape ) PURE_VIRTUAL( {} );

	/** Changes to the next song. Nothing should happen if no song is currently playing */
	UFUNCTION( BlueprintCallable )
	virtual void NextSong() PURE_VIRTUAL(,);

	/** Changes to the previous song. Nothing should happen if no song is currently playing */
	UFUNCTION( BlueprintCallable )
	virtual void PreviousSong() PURE_VIRTUAL(,);

	/** If the boombox has an active tape and isn't already playing, this will resume playback at the last known playback position. */
	UFUNCTION( BlueprintCallable )
	virtual void Play() PURE_VIRTUAL(,);

	/** If the boombox has an active tape and is currently playing, this will remember it's current position and stop playback. */
	UFUNCTION( BlueprintCallable )
	virtual void Stop() PURE_VIRTUAL(,);

	/**  */
	UFUNCTION( BlueprintCallable )
	virtual void FireTurboBass() PURE_VIRTUAL(,);

	/** Changes the boombox volume. Value should be in 0..1 range and will be clamped to it */
	UFUNCTION( BlueprintCallable )
	virtual void SetVolumeNormalized( float volume ) PURE_VIRTUAL(,);

	UFUNCTION( BlueprintCallable )
	virtual bool IsCurrentlyPlaying() PURE_VIRTUAL( , return false; );

	UFUNCTION( BlueprintCallable )
	virtual TSubclassOf< class UFGTapeData > GetCurrentTape( ) PURE_VIRTUAL( , return nullptr; );

	UFUNCTION( BlueprintCallable )
	virtual void RegisterStateListener( TScriptInterface<class IFGBoomboxListenerInterface> stateListener ) PURE_VIRTUAL(,);

	UFUNCTION( BlueprintCallable )
	virtual void UnregisterStateListener( TScriptInterface<IFGBoomboxListenerInterface > stateListener ) PURE_VIRTUAL(,);

	UFUNCTION( BlueprintCallable )
	virtual EBoomBoxPickupButtonState GetPickupButtonState( class AFGCharacterPlayer* player );

	UFUNCTION( BlueprintCallable )
	virtual void PickUp( class AFGCharacterPlayer* toPlayer ) PURE_VIRTUAL(,);

	UFUNCTION( BlueprintCallable )
	virtual void PutDownNearPlayer() PURE_VIRTUAL(,);
};
