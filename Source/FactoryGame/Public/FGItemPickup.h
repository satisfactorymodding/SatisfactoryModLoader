#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGUseableInterface.h"
#include "FGSaveInterface.h"
#include "FGInventoryComponent.h"
#include "FGSignificanceInterface.h"
#include "FGItemPickup.generated.h"

/**
 * Use state when inventory of player looking at the item has a full inventory
 */
UCLASS()
class FACTORYGAME_API UFGUseState_FullInventory : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_FullInventory() : Super() { mIsUsableState = false; }

public:
	FORCEINLINE ~UFGUseState_FullInventory() = default;
};

/**
* Use state when the item is being collected but takes time
*/
UCLASS()
class FACTORYGAME_API UFGUseState_Collecting : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_Collecting() : Super() { mIsUsableState = true; }

public:
	FORCEINLINE ~UFGUseState_Collecting() = default;
};

//State that an item pickup can be in
UENUM( BlueprintType )
enum class EItemState :uint8
{
	ES_SEED			UMETA( DisplayName = "Seed" ),
	ES_NORMAL		UMETA( DisplayName = "Normal" ),
	ES_MAX			UMETA( Hidden )
};

/**
 * @todo: This looks like it should be a subclass of FGInteractActor
 */
UCLASS(abstract)
class FACTORYGAME_API AFGItemPickup : public AActor, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGItemPickup();

	//~ Begin UObject interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason) override;
	//~ End UObject interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End
	
	//~ Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override {};
	//~ End IFGUseableInterface

	/** SERVER and CLIENT picking up: Handles regular pick up logic. Only to be called from the Character when they are picking up the item from PickUpItem(). */
	UFUNCTION( BlueprintCallable )
	void PickUpByCharacter( class AFGCharacterPlayer* byCharacter );

	/** Pickup functionality so that we can pickup x amount of items and can be used by other than character 
	 * 
	 * @return true if there was enough items for pickup
	 */
	UFUNCTION( BlueprintCallable )
	bool PickupByAmount( int32 amount = 1 );
	
	/** Multicast to everyone so picking up clients can see effects */
	UFUNCTION( BlueprintImplementableEvent,BlueprintCosmetic )
	void PlayPickupEffect();

	/** Multicast to everyone so picking up clients can see effects */
	UFUNCTION( Unreliable, NetMulticast )
	void Multicast_PlayPickupEffect();

	/** Returns the normalized progress until collection is complete */
	UFUNCTION( BlueprintCallable, Category = "Pickup" )
	float GetNormalizedCollectionProgress();

	/** Get if the item is picked up */
	UFUNCTION(BlueprintPure,Category="Pickup")
	bool IsPickedUp() const{ return !mPickupItems.HasItems(); }

	/** Get the pickup items*/
	UFUNCTION( BlueprintPure, Category = "Pickup" )
	FORCEINLINE FInventoryStack GetPickupItems() const{ return mPickupItems; }

	FORCEINLINE const TSubclassOf< class UFGItemDescriptor >& GetPickupItemClass() const { return mPickupItems.Item.ItemClass; }

	/** Get the respawn time in days*/
	UFUNCTION( BlueprintPure, Category = "Pickup" )
	FORCEINLINE int32 GetRespawnTimeInDays() const{ return mRespawnTimeInDays; }

	/** Sets new items */
	void RespawnItems();

	/** Clears any items this pickup has */
	UFUNCTION( BlueprintCallable, Category = "Pickup" )
	void ClearPickup();

	/** Plants this pickup */
	UFUNCTION( BlueprintCallable, Category = "Pickup" )
	void PlantPickup();

	/** Updates the state of the item  */
	void Grow();

	/** Returns the state of this item pickup */
	UFUNCTION( BlueprintPure, Category = "Pickup" )
	FORCEINLINE EItemState GetItemState() const{ return mItemState; }

	/** Returns amount of items we have saved that this pickup should give */
	UFUNCTION( BlueprintPure, Category = "Pickup" )
	FORCEINLINE int32 GetSavedNumItems() const{ return mSavedNumItems; }
	
	/** Called when whe have changed something and want to do a visual update */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Pickup" )
	void UpdateVisuals();

	/** Should this item be destroyed on pickup b*/
	UFUNCTION( BlueprintPure, Category = "Pickup" )
	FORCEINLINE bool GetDestroyOnPickup() const{ return mDestroyOnPickup; }
protected:
	/**
	* SERVER and Client picking up: Called right after this item is added to the players inventory, for GameplayEffects.
	* If you want to do something only on the picking up client, check if byCharacter is locally controlled
	*/
	UFUNCTION( BlueprintImplementableEvent )
	void OnPickup( class AFGCharacterPlayer* byCharacter );

	/** Set the number of items */
	UFUNCTION( BlueprintCallable, BlueprintAuthorityOnly, Category = "Pickup" )
	void SetNumItems( int32 numItems );

	/** Get the number of items the pickup have */
	UFUNCTION( BlueprintPure, Category = "Pickup" )
	FORCEINLINE int32 GetNumItems() const{ return mPickupItems.NumItems; }

	/** Called when the collection timer expires */
	void OnCollectTimerComplete();

private:
	/** Add the item to the player inventory */
	void AddToPlayerInventory( class AFGCharacterPlayer* character );

	/** Replicated and set when we are picked up */
	UFUNCTION()
	void OnRep_PickedUp();

	/** Replicated and set when we are picked up */
	UFUNCTION()
	void OnRep_StateUpdated();

	// Handle any radioactive materials.
	void UpdateRadioactivity();

protected:
	//** The amount of time required to pickup < 0 == instant */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	float mTimeToPickUp;

	//** The player collecting the item */
	UPROPERTY( Replicated )
	AFGCharacterPlayer* mCollector;

	//** Timer handler for item being picked up */
	UPROPERTY()
	FTimerHandle mCollectingTimerHandle;
	
	// The items we want to be able to pickup
	UPROPERTY( SaveGame, EditAnywhere, Category = "Item", ReplicatedUsing = OnRep_PickedUp )
	FInventoryStack mPickupItems;

	/** If set to true, then we destroy the item when it's pickup:ed */
	UPROPERTY( EditAnywhere, Category = "Item" )
	bool mDestroyOnPickup;

	/** ak component that plays sound */
	UPROPERTY( VisibleDefaultsOnly, Category = "Audio" )
	class UAkComponent* mSoundComponent;

	/** The ak event to post for the sound  */
	UPROPERTY( EditDefaultsOnly, Category = "AkComponent" )
	class UAkAudioEvent* mAudioEvent;
private:
	/** How many days before item can respawn */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	int32 mRespawnTimeInDays;

	/** What day count was the item last updated */
	UPROPERTY( SaveGame )
	int32 mUpdatedOnDayNr;

	/** Current state for this item */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_StateUpdated )
	EItemState mItemState;

	/** How many days before item has grown from seed */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	int32 mGrowTimeInDays;

	/** Current state for this item */
	UPROPERTY( SaveGame )
	int32 mSavedNumItems;

	/** How many respawns are allowed on this item */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	int32 mMaxRespawns;

	/** How many respawns are allowed on this item */
	UPROPERTY( SaveGame )
	int32 mNumRespawns;

public:
	FORCEINLINE ~AFGItemPickup() = default;
};