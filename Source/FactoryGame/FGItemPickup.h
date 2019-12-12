#pragma once
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
class UFGUseState_FullInventory : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_FullInventory() : Super() { mIsUsableState = false; }
};

/**
* Use state when the item is being collected but takes time
*/
UCLASS()
class UFGUseState_Collecting : public UFGUseState
{
	GENERATED_BODY()

	UFGUseState_Collecting() : Super() { mIsUsableState = true; }
};

/**
 * @todo: This looks like it should be a subclass of FGInteractActor
 */
UCLASS(abstract)
class AFGItemPickup : public AActor, public IFGUseableInterface, public IFGSaveInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGItemPickup();

	//~ Begin UObject interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
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
	UFUNCTION(BlueprintImplementableEvent,BlueprintCosmetic)
	void PlayPickupEffect();

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
};