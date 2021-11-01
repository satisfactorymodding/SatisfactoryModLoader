// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGSequence.h"
#include "FGPlayerController.h"
#include "FGSubsystem.h"
#include "FGPhotoModeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSequencePlayStarted );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSequencePlayUpdated, float, sequenceTimer );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSequencePlayEnded );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPhotoModeManager : public AFGSubsystem
{
	GENERATED_BODY()

public:
	AFGPhotoModeManager();
	
	static AFGPhotoModeManager* Get( class UWorld* world );

	UFUNCTION( BlueprintPure, Category = "PhotoMode", DisplayName = "GetPhotoModeManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGPhotoModeManager* Get( class UObject* worldContext );

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
public:
	
	void ToggleAdvancedPhotoMode();

	UFUNCTION( BlueprintCallable )
	void AddCurrentPlayerLocation(FFrameTime frameTime );
	void AddPlayerLocation( FFrameTime frameTime, FVector location );

	UFUNCTION( BlueprintCallable )
	void AddCurrentPlayerRotation( FFrameTime frameTime );
	void AddPlayerRotation( FFrameTime frameTime, FRotator rotator );

	UFUNCTION( BlueprintCallable )
	void AddCurrentPlayerFOV( FFrameTime frameTime);
	void AddPlayerFOV( FFrameTime frameTime, float FOV  );

	UFUNCTION( BlueprintCallable )
	void AddCurrentPlayerLocAndRot( FFrameTime frameTime );

	UFUNCTION( BlueprintCallable )
	void AddCurrentPlayerAllValues( FFrameTime frameTime );

	UFUNCTION( BlueprintCallable )
	void RemovePlayerLocation( FFrameTime frameTime );

	UFUNCTION( BlueprintCallable )
	void RemovePlayerRotation( FFrameTime frameTime );

	UFUNCTION( BlueprintCallable )
	void RemovePlayerFOV( FFrameTime frameTime );

	UFUNCTION( BlueprintCallable )
	void PlaySequence();

	UFUNCTION( BlueprintCallable )
	void ClearSequence();

	UFUNCTION( BlueprintCallable )
	void EvaluateFrame( const FFrameTime& time, FVector& out_location, FRotator& out_rotation, float& out_FOV );

	UFUNCTION( BlueprintCallable )
	void EvaluateFrameDry( const FFrameTime& time, FVector& out_location, FRotator& out_rotation, float& out_FOV );

	UFUNCTION( BlueprintCallable )
	FVector GetLocationAtFrame( const FFrameTime& time );
	
	UFUNCTION( BlueprintCallable )
	FRotator GetRotationAtFrame( const FFrameTime& time );

	UFUNCTION( BlueprintCallable )
	float GetFOVAtFrame( const FFrameTime& time );

	UFUNCTION( BlueprintPure )
	FFGSequence GetCurrentSequence() const { return mCurrentSequence; }

	UFUNCTION( BlueprintPure )
	FFrameTime GetCurrentSequenceEnd() const { return mCurrentSequence.SequenceEnd; }
	UFUNCTION( BlueprintCallable )
	void SetCurrentSequenceEnd( FFrameTime newEnd ) { mCurrentSequence.SequenceEnd = newEnd; }
	UFUNCTION( BlueprintPure )
	FFrameTime GetCurrentSequenceStart() const { return mCurrentSequence.SequenceStart; }
	UFUNCTION( BlueprintCallable )
	void SetCurrentSequenceStart( FFrameTime newStart ) { mCurrentSequence.SequenceStart = newStart ;}

	UFUNCTION( BlueprintPure )
	bool IsAdvancedPhotoModeAvailable() const;

	void Debug_ToggleDebug();
	void Debug_ShowInfo();

	UPROPERTY( BlueprintAssignable, Category = "Sequencer" )
	FOnSequencePlayUpdated mOnSequencePlayUpdated;
	UPROPERTY( BlueprintAssignable, Category = "Sequencer" )
	FOnSequencePlayStarted mOnSequencePlayStarted;
	UPROPERTY( BlueprintAssignable, Category = "Sequencer" )
	FOnSequencePlayEnded mOnSequencePlayEnded;

	UPROPERTY()
	class AFGCharacterPlayer* mCachedPlayer;
	UPROPERTY()
	class AFGPlayerController* mCachedPlayerController;

	FFGSequence mCurrentSequence;

private:
	// Getters for the current player and controller. Will cache objects. Might return null.
	class AFGCharacterPlayer* GetPlayer();
	class AFGPlayerController* GetPlayerController();

	bool mShowDebug;

	//ULevelSequencePlayer::EnableCinematicMode //@todok2 add this
};
