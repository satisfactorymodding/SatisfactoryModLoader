// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	/** Loop de loop */
	void CycleEquipment( int32 dir );

	/** Sets @index to be active if it is a valid index */
	void SetActiveIndex( int32 index );

	/** Checks whether this contains any items of item type and whether they have room for inventory item */
	bool ContainsItemTypeAndHasEnoughSpaceForItem( FInventoryItem item );

	/** Subscribes for active equipment changed notifications */
	FDelegateHandle BindOnActiveEquipmentChanged( const FOnActiveEquipmentChanged::FDelegate &Delegate );
protected:
	/** Decide on what properties to replicate */
	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin UFGInventoryComponent interface
	virtual void OnItemsAdded( int32 idx, int32 num ) override;
	virtual void OnItemsRemoved( int32 index, int32 num, FInventoryItem item ) override;
	// End UFGInventoryComponent interface

	
	void ActivateEquipment();
	void RemoveEquipment( FInventoryItem item );
private:
	/** @copydoc UFGInventoryComponent::FilterEquipmentClasses */
	bool FilterEquipmentClasses( TSubclassOf< UObject > object, int32 idx ) const;

	/** Finds and returns the cached character */
	class AFGCharacterPlayer* GetOwningCharacter();

	UFUNCTION()
	void OnRep_ActiveEquipmentIndex();

	UFUNCTION()
	void OnRep_ActiveEquipment();
private:
	friend class AFGCharacterPlayer;

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
