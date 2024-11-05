// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AkGameplayTypes.h"
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "FGBoomboxListenerInterface.h"
#include "FGCharacterPlayer.h"
#include "FGRemoteCallObject.h"
#include "FGSaveInterface.h"
#include "GameFramework/Info.h"
#include "Resources/FGTapeData.h"
#include "FGBoomBoxPlayer.generated.h"

UENUM( BlueprintType )
enum class EBoomBoxPickupButtonState: uint8
{
	EHideButton,			/** Never show the button - it's already equipped */
	EEquipBoomBox,			/** A hand slot is available and the boom box can be picked up */
	EPickUpBoomBox,			/** A hand slot is not available but an inventory slot is so it can be picked up. Interrupts playback. */
	ENoRoomForBoomBox		/** There's no room anywhere, in the inventory or a hand slot available so can't perform either action */
};


class AFGCharacterPlayer;
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

	UPROPERTY( SaveGame, meta = (Bitmask, BitmaskEnum = "/Script/FactoryGame.EBoomBoxPlaybackStateBitfield") )
	int32 mPlaybackState = 0;
};

/** Item state for the boombox. Shared by the equipment and the actor itself. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGBoomBoxItemState
{
	GENERATED_BODY()

	/** The tape currently loaded into the boombox */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "BoomBox" )
	TSubclassOf<UFGTapeData> CurrentTape;

	/** Index of the current song on the tape */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "BoomBox" )
	int32 CurrentSongIndex = -1;

	/** Current offset of the song in the milliseconds */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "BoomBox" )
	int32 SongOffsetMS = 0;

	/** Volume of the boombox */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "BoomBox" )
	float Volume = 1.0f;

	/** The currently selected repeat mode on the boombox */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "BoomBox" )
	EBoomBoxRepeatMode RepeatMode = EBoomBoxRepeatMode::RepeatTape;
};

UCLASS()
class FACTORYGAME_API UFGBoomBoxRemoteCallObject: public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	void SyncPlayerStateReqest( class AFGBoomBoxPlayer* player );

	/** Changes the active tape in this boombox. May be called from client or server. */
	UFUNCTION( Server, Reliable )
	void Server_BeginChangeTapeSequence( AFGBoomBoxPlayer* player, TSubclassOf< class UFGTapeData > newTape );

	/** Changes to the next song. May be called from client or server. */
	UFUNCTION( Server, Reliable )
	void Server_BeginNextSongSequence( AFGBoomBoxPlayer* player );

	/** Changes to the previous song. May be called from client or server. */
	UFUNCTION( Server, Reliable )
	void Server_BeginPreviousSongSequence( AFGBoomBoxPlayer* player );

	/** If the boombox has an active tape and isn't already playing, this will resume playback at the last known playback position. May be called from client or server. */
	UFUNCTION( Server, Reliable )
	void Server_BeginPlaySequence( AFGBoomBoxPlayer* player );

	/** If the boombox has an active tape and is currently playing, this will remember it's current position and stop playback. May be called from client or server. */
	UFUNCTION( Server, Reliable )
	void Server_BeginStopSequence( AFGBoomBoxPlayer* player );

	/**  Triggers turbo bass, if it is at all possible. */
	UFUNCTION( Server, Reliable )
	void Server_BeginTurboBassSequence( AFGBoomBoxPlayer* player );

	/** Changes the boombox volume. Value should be in 0..1 range and will be clamped to it. May be called from client or server. */
	UFUNCTION( Server, Reliable )
	void Server_SetVolumeNormalized( AFGBoomBoxPlayer* player, float volume );

	/** Puts the boombox down at the player's location, if used as an equipment. */
	UFUNCTION( Server, Reliable )
	void Server_PutBoomBoxDown( AFGBoomBoxPlayer* player, const FTransform& transform );

	UFUNCTION( Server, Reliable )
	void Server_LoadTapeNow( AFGBoomBoxPlayer* player );
	
	UFUNCTION( Server, Reliable )
	void Server_EjectTapeNow( AFGBoomBoxPlayer* player );

	UFUNCTION( Server, Reliable )
	void Server_PlayNow( AFGBoomBoxPlayer* player );

	UFUNCTION( Server, Reliable )
	void Server_StopNow( AFGBoomBoxPlayer* player );

	UFUNCTION( Server, Reliable )
	void Server_NextNow( AFGBoomBoxPlayer* player );

	UFUNCTION( Server, Reliable )
	void Server_PrevNow( AFGBoomBoxPlayer* player );

	UFUNCTION( Server, Reliable )
	void Server_FireTurboBassNow( AFGBoomBoxPlayer* player );

	UFUNCTION( Server, Reliable )
	void Server_SetRepeatMode( AFGBoomBoxPlayer* player, EBoomBoxRepeatMode repeatMode );

protected:
	UFUNCTION( Server, Reliable )
	void Server_SyncPlayerStateRequest( class AFGBoomBoxPlayer* player, float clientTimestamp );

	UFUNCTION( Client, Reliable )
	void Client_SyncPlayerState( class AFGBoomBoxPlayer* player, FBoomBoxPlayerState state, float timestamp );
private:
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGBoomBoxRemoteCallObject = false;
};

UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API AFGBoomBoxPlayer : public AActor, public IFGSaveInterface, public IFGUseableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFGBoomBoxPlayer();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	void LoadFromItemState( const FFGDynamicStruct& itemState );
	FFGDynamicStruct SaveToItemState() const;
	void FlushItemState() const;
	
	/** Changes the active tape in this boombox. May be called from client or server. */
	UFUNCTION( BlueprintCallable )
	void BeginChangeTapeSequence( TSubclassOf< class UFGTapeData > newTape, AFGCharacterPlayer* instigatorCharacter );

	/** Changes to the next song. May be called from client or server. */
	UFUNCTION( BlueprintCallable )
	void BeginNextSongSequence( AFGCharacterPlayer* instigatorCharacter );

	/** Changes to the previous song. May be called from client or server. */
	UFUNCTION( BlueprintCallable )
	void BeginPreviousSongSequence( AFGCharacterPlayer* instigatorCharacter );

	/** If the boombox has an active tape and isn't already playing, this will resume playback at the last known playback position. May be called from client or server. */
	UFUNCTION( BlueprintCallable )
	void BeginPlaySequence( AFGCharacterPlayer* instigatorCharacter );

	/** If the boombox has an active tape and is currently playing, this will remember it's current position and stop playback. May be called from client or server. */
	UFUNCTION( BlueprintCallable )
	void BeginStopSequence( AFGCharacterPlayer* instigatorCharacter );

	/**  Triggers turbo bass, if it is at all possible. Returns true if turbobass was triggered. */
	UFUNCTION( BlueprintCallable )
	void BeginTurboBassSequence( AFGCharacterPlayer* instigatorCharacter );

	/** Changes the boombox volume. Value should be in 0..1 range and will be clamped to it. May be called from client or server. */
	UFUNCTION( BlueprintCallable )
	void SetVolumeNormalized( float volume, AFGCharacterPlayer* instigatorCharacter );

	/** Puts the boombox down at the player's location, if used as an equipment. */
	UFUNCTION( BlueprintCallable )
	void PutDown( const FTransform& transform );

	UFUNCTION( BlueprintCallable )
	void SetRepeatMode( EBoomBoxRepeatMode repeatMode, AFGCharacterPlayer* instigatorCharacter );

	UFUNCTION( BlueprintPure )
	EBoomBoxRepeatMode GetRepeatMode() const;

	UFUNCTION( BlueprintCallable )
	bool GetCharacterLookAtTransform( FTransform& out_Transform ) const;

	UFUNCTION( BlueprintCallable )
	bool GetCharacterNearbyTransform( FTransform& out_Transform ) const;

	/** Register a new state listener. The state listener will be notified of any state changes in the boombox. */
	UFUNCTION( BlueprintCallable )
	void RegisterStateListener( TScriptInterface<class IFGBoomboxListenerInterface> stateListener );

	/** Unregister a state listener. This state listener will not receive any further notifications from this boombox. */
	UFUNCTION( BlueprintCallable )
	void UnregisterStateListener( TScriptInterface<IFGBoomboxListenerInterface > stateListener );

	/** Returns true if this boombox is currently playing music, false otherwise. */
	UFUNCTION( BlueprintPure )
	bool IsCurrentlyPlaying() const;

	/** Returns the tape that this boombox currently has loaded. */
	UFUNCTION( BlueprintPure )
	TSubclassOf< class UFGTapeData > GetCurrentTape() const;

	/** Return true if this boombox is currently used as an equipment, whether it is currently equipped or not */
	UFUNCTION( BlueprintPure )
	bool IsInEquipmentMode() const;

	/** Return true if this boombox is not currently used as an equipment and the player trying to pick it up has room in their inventory. */
	UFUNCTION( BlueprintPure )
	bool CanBePickedUp( class AFGCharacterPlayer* byPlayer ) const;

	UFUNCTION( BlueprintPure )
	EBoomBoxPickupButtonState GetPickupButtonState( AFGCharacterPlayer* player );
	
	// Called every frame
	virtual void Tick( float DeltaTime ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	UFUNCTION( BlueprintNativeEvent )
	void OnModeChanged();

	UFUNCTION()
	void OnRep_RepeatMode();
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_SetAudioVolume( float normalizedVolume );

	void SetPlaybackAllowedByEquipStatus( bool allowed );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PutDown( const FTransform& transform );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_ApplyState( const FBoomBoxPlayerState& boomBoxState );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_FireTurboBassNow( class AFGCharacterPlayer* character );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayTurboBassEffects( class AFGCharacterPlayer* character );

	UFUNCTION( BlueprintPure )
	bool IsPlaybackEnabled() const;

	UFUNCTION( BlueprintPure )
	bool IsPlaybackAllowedByEquippedStatus() const;

	UFUNCTION( BlueprintPure )
	bool IsPlaybackAllowedByPossessedStatus() const;

	UFUNCTION( BlueprintPure )
	bool IsPlaybackEffectivelyAllowed() const;
	
	bool IsEffectivelyPlaying() const;
	FSongData GetCurrentSong();
	
	bool CanFireTurboBass() const;

	UFUNCTION( BlueprintCallable )
	void SwitchToNextTapeTexture();
	
	/**
	 * Clears the current state of the boombox (ie stops playing any music) and then applies the new state. Not check are made wrt to the
	 * equivalence of the new and old state. This is always a hard reset.
	 */ 
	void ApplyStateLocally( const FBoomBoxPlayerState& state );
	FBoomBoxPlayerState GetState();

	void SetEquipmentActor( class AFGEquipmentBoomBox* equipmentActor );

	void SetMode( EBoomBoxMode mode );

	/** Loads the next queued tape in the boombox immediately. Only produces effects if called on server. Intended to be triggered by anim notifies. */
	UFUNCTION( BlueprintCallable )
	void LoadTapeNow( class AFGCharacterPlayer* character );

	/** Removes the currently loaded tape from the boombox. Only produces effects if called on server. Intended to be triggered by anim notifies. */
	UFUNCTION( BlueprintCallable )
	void EjectTapeNow( AFGCharacterPlayer* character );

	/** Starts playback immediately, without starting any animations. Intended to be triggered by anim notifies. */
	UFUNCTION( BlueprintCallable )
	void PlayNow( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintCallable )
	void StopNow( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintCallable )
	void NextNow( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintCallable )
	void PrevNow( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintCallable )
	void FireTurboBassNow( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintCallable )
	void TogglePlaybackNow( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayStingerEffects( AFGCharacterPlayer* character );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayEquipEffects( AFGCharacterPlayer* character );

	/** Updates materials based on the camera mode */
	void UpdateMaterialsFromCameraMode();
	
protected:
	void SetPlaybackStateFlag( EBoomBoxPlaybackStateBitfield flag, bool set );
	
	void ApplyTurboBassGameplayEffects( class AFGCharacterPlayer* character );
	
	/** Stops playback */
	void SetAudioVolumeLocally( float normalizedVolume, bool notifyListeners = true );
	UMaterialInterface* GetDefaultTapeMaterial();

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnPawnPossessed( class APawn* pawn, class AController* controller );

	UFUNCTION()
	void OnceClientSubsystemsAreReady();

	UFUNCTION()
	void SongFinished( EAkCallbackType cbType, UAkCallbackInfo* cbInfo );

	UFUNCTION()
	void TapeTextureLoadedAsync( UTexture2D *texture );

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

	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	FName mTapeTextureParameter = "Albedo";
	
	UPROPERTY( EditDefaultsOnly, Category = BoomBox )
	int32 mTapeMaterialIndex = 0;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	class UAkComponent* mAkComponent = nullptr;

	/** Boombox mesh */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	USkeletalMeshComponent* mMesh = nullptr;

	/** Separate scene root component, needed to allow the mesh transform to be changed in editor */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	USceneComponent* mSceneRoot = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	UBoxComponent* mBoxCollision = nullptr;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	FTransform mBaseTransformEquipped = FTransform::Identity;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Boombox" )
	FTransform mBaseTransformFreeActor = FTransform::Identity;
	
	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mImpulseRadius = 3000.f;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mImpulseStrength = 500.f;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mVerticalImpulseStrength = 250.f;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mTurboBassBaseDamage = 1.f;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	TSubclassOf< class UFGPointDamageType > mImpulseDamageType;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	TSubclassOf< class UFGNoise > mTurboBassNoise;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mBoostJumpMultiplier = 5.f;

	UPROPERTY( EditDefaultsOnly, Category = "Boombox" )
	float mBoostJumpVelocityRange = 100.f;

	UPROPERTY( EditDefaultsOnly, Category="Equipment" )
	UMaterialInstance* mFirstPersonTapeMaterial;
	
	/** Each Mesh Component should have an entry here to remap its materials to the First person material (one with the panini switch enabled) */
	UPROPERTY( EditDefaultsOnly, Category = "Equipment")
	TMap< FName, FFirstPersonMaterialArray > mComponentNameToFirstPersonMaterials;

	/** Backup of each material in the event that the boombox is dropped we can undo the panini projectiion materials*/
	UPROPERTY()
	TMap< FName, FFirstPersonMaterialArray > mOriginalMaterials;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* mCachedMaterialInstance = nullptr;

	UPROPERTY()
	class UMaterialInstanceDynamic* mCachedMaterialInstance1p = nullptr;
	
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

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayLoadTapeSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlaySwitchTapeSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayPlaySequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayStopSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayNextSongSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayPrevSongSequence( AFGCharacterPlayer* instigatorPlayer );
	
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic )
	void PlayTurboBassSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( BlueprintImplementableEvent )
	void OnPlaybackStateChanged( UPARAM(meta = (Bitmask, BitmaskEnum = "/Script/FactoryGame.EBoomBoxPlaybackStateBitfield")) int32 PlaybackState );

	void SetOwningCharacter( class AFGCharacterPlayer* character );
	AFGCharacterPlayer* GetOwningCharacter() const { return mOwningCharacter; }
private:
	friend class AFGEquipmentBoomBox;
	friend class UFGBoomBoxRemoteCallObject;
	
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginPlaySequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginStopSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginLoadTapeSequence( TSubclassOf< UFGTapeData > newTape, AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginSwitchTapeSequence( TSubclassOf< UFGTapeData > newTape, AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginNextSongSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginPreviousSongSequence( AFGCharacterPlayer* instigatorPlayer );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginTurboBassSequence( AFGCharacterPlayer* instigatorPlayer );
	
	float GetAudioVolume();
	void GetCurrentPlaybackPosition( float& out_currentPosition, float& out_maxDuration );
	void FetchCurrentSongOffsetMS();
	void UpdateTickFunction();
	void SanitizeListeners();
	void StopPlayingNoNotify();
	void StartPlayingNoNotify( int32 song, int32 offsetMs );
	void FullyNotifyListeners();
	void UpdatePlaybackAllowedByPossessedStatus();
	void SetPlaybackAllowedByPossessedStatus( bool allowed );
	
	USkeletalMeshComponent* GetMesh() const { return mMesh; }

	// On Dedicated Servers, WWise does not play back sounds at all, not even virtualized so we need to keep track of playback position
	// on our own, using timers and relying on the properties of the audio events. This is of course required to be able to keep clients
	// reasonably synchronized to one another
	FTimerHandle mPlaybackEndTimerHandle = {};

	float mOffsetInSecondsWhenPlaybackStarted = 0.f;

	UPROPERTY( SaveGame )
	FBoomBoxPlayerState mState;

	UPROPERTY( SaveGame, ReplicatedUsing=OnModeChanged )
	EBoomBoxMode mMode = EBoomBoxMode::Undefined;
	
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_RepeatMode )
	EBoomBoxRepeatMode mRepeatMode = EBoomBoxRepeatMode::RepeatTape;

	UPROPERTY( SaveGame, Replicated )
	class AFGCharacterPlayer* mOwningCharacter = nullptr;

	UPROPERTY()
	AFGEquipmentBoomBox* mEquipmentActor = nullptr;

	UPROPERTY()
	TSubclassOf< UFGTapeData > mNextTape;
};
