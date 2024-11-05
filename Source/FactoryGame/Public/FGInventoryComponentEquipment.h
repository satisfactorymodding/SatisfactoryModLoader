// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Equipment/FGEquipment.h"
#include "FGInventoryComponent.h"
#include "FGInventoryComponentEquipment.generated.h"

class AFGEquipment;

DECLARE_MULTICAST_DELEGATE_OneParam( FOnActiveEquipmentChanged, EEquipmentSlot slot );

UCLASS()
class FACTORYGAME_API UFGInventoryComponentEquipment : public UFGInventoryComponent
{
	GENERATED_BODY()

public:
	/** Constructor */
	UFGInventoryComponentEquipment();

	/** Returns the equipment in this slot */
	class AFGEquipment* GetEquipmentInInventory() const;

	/** Returns the EEquipmentSlost for this inventory */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	EEquipmentSlot GetEquipmentSlotEnum() const;

	/** Sets the slot enum */
	void SetEquipmentSlotEnum( EEquipmentSlot inSlot );

	/**
	 * Override the equipment in the slot.
	 * If this is called twice the first override is unequipped and the new is equipped.
	 * This is to be called on both server and client (simulated).
	 * @param equipment		Equipment to override with, nullptr to unequip any overridden equipment.
	 */
	void SetOverrideEquipment( AFGEquipment* equipment );

	AFGEquipment* GetEquipmentInSlot() const { return mEquipmentInSlot; }

	/** Returns the EEquipmentSlost for this inventory */
	UFUNCTION( BlueprintPure, Category = "Equipment" )
	FORCEINLINE int32 GetActiveIndex() { return mActiveEquipmentIndex; }

	/** Returns the actor for the equipment in the slot, null if the slot is empty or does not contain an equipment, null if an invalid index is passed. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	class AFGEquipment* GetStackEquipmentActorAtIdx( const int32 index ) const;

	/** Returns the slot in which slotted in equipment is located, or INDEX_NONE */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	int32 FindSlotForSlottedInEquipment( const AFGEquipment* equipment ) const;

	/** Loop de loop */
	void CycleEquipment( int32 dir );

	// <FL> [KajtaziT] handheldselection radial menu can set the active equipment directly
	UFUNCTION( BlueprintCallable, Category = "Equipment" )
	void SetActiveIndexWithDefaultItem( int32 index );
	// </FL>

	/** Sets @index to be active if it is a valid index. If @itemAtCurrentIndex is set, it is assumed to be the item currently active in this
	 * equipment slot. This is useful when this function is called in response to the active item already having been removed from slot. 
	 */
	void SetActiveIndex( int32 index, TOptional< FInventoryItem > itemAtCurrentIndex = {} );

	/** Checks whether this contains any items of item type and whether they have room for inventory item */
	bool ContainsItemTypeAndHasEnoughSpaceForItem( FInventoryItem item );

	/** Subscribes for active equipment changed notifications */
	FDelegateHandle BindOnActiveEquipmentChanged( const FOnActiveEquipmentChanged::FDelegate &Delegate );

	/** Makes the provided equipment active either by changing the active slot or by making it an active override equipment */
	void SetActiveEquipment( AFGEquipment* equipment );
protected:
	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface
	
	// Begin UFGInventoryComponent interface
	virtual void OnItemsAdded( const int32 idx, const int32 num, UFGInventoryComponent* sourceInventory = nullptr ) override;
	virtual void OnItemsRemoved( int32 idx, int32 num, const FInventoryItem& item, UFGInventoryComponent* targetInventory = nullptr ) override;
	// End UFGInventoryComponent interface
	
	void ActivateEquipment();
	void RemoveActiveEquipment();
	
	void AdjustSlottedInEquipmentsSize();
	bool AttemptSpawnEquipmentForSlot( int32 slotIndex );
	bool AttemptRemoveEquipmentFromSlot( int32 slotIndex );
private:
	/** @copydoc UFGInventoryComponent::FilterEquipmentClasses */
	bool FilterEquipmentClasses( TSubclassOf< UObject > object, int32 idx ) const;

	/** Finds and returns the cached character */
	class AFGCharacterPlayer* GetOwningCharacter();

	UFUNCTION()
	void OnRep_ActiveEquipmentIndex();

	UFUNCTION()
	void OnRep_ActiveEquipment();

	UFUNCTION()
	void OnRep_SlottedInEquipments();
private:
	friend class AFGCharacterPlayer;

	/** Equipments that are slotted into the actual inventory slots. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_SlottedInEquipments )
	TArray<AFGEquipment*> mSlottedInEquipments;

	/** Local cache of slotted in equipments to be able to correctly dispatch WasSlottedIn/WasRemovedFromSlot on client */
	TArray<TWeakObjectPtr<AFGEquipment>> mLastSlottedInEquipments;

	/**
	 * If the equipment in the slot has been overridden, this is the equipment.
	 * No need to save this, the kinds of equipments that are placed here are not good candidates for saving (e.g. build gun)
	 * No need to replicate, this is simulated locally on the client.
	 */
	UPROPERTY()
	AFGEquipment* mOverrideEquipmentInSlot;

	/** This is the actual equipment in the slot */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ActiveEquipment )
	AFGEquipment* mEquipmentInSlot;

	/** This inventory will only accept equipments that are supposed to be on this slot */
	UPROPERTY( Replicated )
	EEquipmentSlot mEquipmentInventorySlot;

	/** Index of the active equipment*/
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ActiveEquipmentIndex )
	int32 mActiveEquipmentIndex;

	/**  Delegate fired when the active equipment index changes. The delegate works on both server and client */
	FOnActiveEquipmentChanged mOnActiveEquipmentChanged;
};
