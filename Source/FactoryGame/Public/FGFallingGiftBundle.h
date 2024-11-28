// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGInventoryComponent.h"
#include "FGSaveInterface.h"
#include "FGSignificanceInterface.h"
#include "FGUseableInterface.h"
#include "GameFramework/Actor.h"
#include "FGFallingGiftBundle.generated.h"

/** Data for a randomly selected gift reward. */
USTRUCT( BlueprintType )
struct FFGRandomGiftReward
{
	GENERATED_BODY()

	/** The type of items to give to the player when picked up. */
	UPROPERTY( EditDefaultsOnly )
	TArray< FInventoryStack > mItemsToGive;

	/** The type of unlocks to give to the player when picked up. */
	UPROPERTY( EditDefaultsOnly, Instanced )
	TArray< class UFGUnlock* > mUnlocks;

	/** The chance of this reward being chosen. All weights are added up and the percentage chance of being selected is Weight / TotalWeight. Weight of <= 0 will never be selected.*/
	UPROPERTY( EditDefaultsOnly )
	int32 SelectionChanceWeight = 1;
};

/**
 * 
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGFallingGiftBundle : public AActor, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()

	friend class AFGGiftRainSpawner;
public:
	AFGFallingGiftBundle();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PostNetReceiveLocationAndRotation() override;
	// End AActor Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGSaveInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	// End IFGSaveInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	// End IFGUseableInterface

	UFUNCTION( BlueprintPure, Category = "Falling Gift Bundle|Movement" )
	virtual float GetFallingSpeed() const;

	UFUNCTION( BlueprintCallable, Category = "Falling Gift Bundle|Movement" )
	
	void SetIsFalling( bool isFalling );
	UFUNCTION( BlueprintPure, Category = "Falling Gift Bundle" )
	virtual bool CanBePickedUp( class AFGCharacterPlayer* byCharacter ) const;

	UFUNCTION( BlueprintCallable, Category = "Falling Gift Bundle" )
	void SelectNewRandomReward();

protected:
	virtual void HandleLanding( const FHitResult& sweepResult );
	
	UFUNCTION( BlueprintNativeEvent, Category = "Falling Gift Bundle|Movement" )
	void OnBeginFalling();

	UFUNCTION( BlueprintNativeEvent, Category = "Falling Gift Bundle|Movement" )
	void OnStopFalling();
	
	UFUNCTION( BlueprintNativeEvent, Category = "Falling Gift Bundle|Movement" )
	void OnLanded();

	UFUNCTION( BlueprintNativeEvent, Category = "Falling Gift Bundle" )
	void OnPickup( AFGCharacterPlayer* player );
	
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void OnGainedSignificance();

	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void OnLostSignificance();

	UFUNCTION( BlueprintImplementableEvent, Category = "Significance" )
	void RemoveParachute();
	
private:
	UFUNCTION()
	void OnRep_IsFalling();

	UFUNCTION()
	void OnRep_SelectedRandomRewardIndex();

	UFUNCTION()
	void OnRep_WasPickedUp();
	
	UFUNCTION()
	void OnRep_HasLanded();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PickedUpByPlayer( class AFGCharacterPlayer* player );
	void PickupByPlayer( class AFGCharacterPlayer* player );

	void CacheExpectedLandingZ();

protected:
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	class UStaticMeshComponent* mMeshComponent;
	
private:
	/** Localized name of this gift bundle. */
	UPROPERTY( EditDefaultsOnly, Category = "Falling Gift Bundle" )
	FText mGiftBundleName;

	/** The audio event to fire when picking up this bundle */
	UPROPERTY( EditDefaultsOnly, Category = "Falling Gift Bundle" )
	class UAkAudioEvent* mPickupAudioEvent;
	
	/** A list of random rewards of which one will be selected for this gift. */
	UPROPERTY( EditDefaultsOnly, Category = "Falling Gift Bundle" )
	TArray< FFGRandomGiftReward > mRandomRewardPool;
	
	/** How fast the item pickup should fall. */
	UPROPERTY( EditDefaultsOnly, Category = "Falling Gift Bundle|Movement")
	float mFallingSpeed;
	
	/** How fast the item pickup should rotate when falling. */
	UPROPERTY( EditDefaultsOnly, Category = "Falling Gift Bundle|Movement")
	float mFallingRotationSpeed;
	
	/** Whether or not the item pickup is currently falling. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsFalling )
	bool mIsFalling;
	
	/** Cached value representing the height we expect to land at. Used to force the present to land in case the player moves out of valid collision range. */
	UPROPERTY( SaveGame, Replicated )
	float mCachedExpectedLandingZ;

	UPROPERTY( EditDefaultsOnly, Category = "Significance")
	float mSignificanceRange;
	
	/** The gift spawner that spawned us. */
	UPROPERTY()
	class AFGGiftRainSpawner* mGiftSpawner;

	/** The currently selected random reward. */
	const FFGRandomGiftReward* mSelectedRandomReward;

	UPROPERTY( ReplicatedUsing = OnRep_SelectedRandomRewardIndex )
	int32 mSelectedRandomRewardIndex;
	
	FVector mServerLocation;
    FRotator mServerRotation;

	UPROPERTY( ReplicatedUsing = OnRep_WasPickedUp )
	bool mWasPickedUp;

	/** Bool used to flip the rotation direction when falling. */
	UPROPERTY( Replicated )
	bool mFlipRotationDirection;
	
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_HasLanded )
	bool mHasLanded;
	
};
