// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "GameFramework/Info.h"
#include "Resources/FGTapeData.h"
#include "AkGameplayTypes.h"
#include "FGBoomboxListenerInterface.h"
#include "FGBoomBoxPlayer.generated.h"

USTRUCT()
struct FBoomBoxPlayerState
{
	GENERATED_BODY() 

	UPROPERTY( SaveGame )
	TSubclassOf< UFGTapeData > mCurrentTape = nullptr;

	UPROPERTY( SaveGame )
	int32 mCurrentSongIx = -1;

	/** Only recorded for the purpose of serializing to save games, on the presave hook or in other cases on demand
	 *  During runtime, this member will most times hold an unreliable value. */
	UPROPERTY( SaveGame )
	int32 mSongOffsetMS = 0;

	UPROPERTY( SaveGame )
	float mVolume = 1.f;

	UPROPERTY( SaveGame )
	EBoomboxPlaybackState mPlaybackState = EBoomboxPlaybackState::EStopped;
};

UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API AFGBoomBoxPlayer : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFGBoomBoxPlayer();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	/** Start playback with the current tape at it's last known position (song+offset) */

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_Play();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_Stop();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_TogglePlayback();
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_NextSong();
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PreviousSong();
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_SetCurrentTape( TSubclassOf<class UFGTapeData> tape );
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_SetAudioVolume( float normalizedVolume );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_SuspendPlayback();
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_ResumePlayback();

	bool IsPlaying();
	bool IsEffectivelyPlaying();
	FSongData GetCurrentSong();
	
	void RegisterStateListener( TScriptInterface<class IFGBoomboxListenerInterface> stateListener );
	void UnregisterStateListener( TScriptInterface<class IFGBoomboxListenerInterface > stateListener );
	TSubclassOf<UFGTapeData> GetCurrentTape();
	class UAkComponent* GetAkComponent() const;
	void Play();
	void Stop();
	bool CanFireTurboBass() const;
	
	/**
	 * Clears the current state of the boombox (ie stops playing any music) and then applies the new state. Not check are made wrt to the
	 * equivalence of the new and old state. This is always a hard reset.
	 */ 
	void ResetState( FBoomBoxPlayerState state );
	FBoomBoxPlayerState GetState();

protected:
	/** Stops playback */
	void NextSong();
	void PreviousSong();
	void SetAudioVolume( float normalizedVolume, bool notifyListeners = true );

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPawnPossessed( class APawn* pawn, class AController* controller );

	UFUNCTION()
	void OnceClientSubsystemsAreReady();

	UFUNCTION()
	void SongFinished( EAkCallbackType cbType, UAkCallbackInfo* cbInfo );

	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	class UAkRtpc* mVolumeRtpc = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	class UAkRtpc* mTurboBassOutputRTPC = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	class UAkRtpc* mTurboBassRTPC = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	class UAkAudioEvent* mTurboBassAudioEvent = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	float mTurboBassBlockingThreshold = -48.f;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	class UAkComponent* mAkComponent = nullptr;

	/**
	 * State listeners subscribed to this boombox. 
	 */ 
	UPROPERTY()
	TArray<TScriptInterface<class IFGBoomboxListenerInterface>> mStateListeners;

	/**
	 * Current ak playing id. May be invalid even if playback state is playing, if for examnple the pawn we are attached to is not possessed.
	 * Generally, if this value != invalid playing id, then the boombox is really playing. Playback state is an outside facing state used
	 * for save game and replication purposes
	 */
	AkPlayingID mPlayingId = AK_INVALID_PLAYING_ID;

	template<typename funcT>
	void VisitListeners(funcT&& func)
	{
		SanitizeListeners();
		for(auto listener: mStateListeners)
		{
			func( listener );
		}
	}

private:
	void SetCurrentTape( TSubclassOf<class UFGTapeData> tape );
	float GetAudioVolume();
	void GetCurrentPlaybackPosition( float& out_currentPosition, float& out_maxDuration );
	void SetCurrentSong(int32 currentSong, int32 songOffsetMs);
	void FetchCurrentSongOffsetMS();
	void UpdateTickFunction();
	void SanitizeListeners();
	void SetPlaybackState(EBoomboxPlaybackState playbackState);
	void StopPlayingNoNotify();
	void StartPlayingNoNotify(int32 song, int32 offsetMs );
	void UpdatePostPlayerControllerChange();

	UPROPERTY( SaveGame )
	FBoomBoxPlayerState mState;
};
