// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGInventoryComponent.h"
#include "Equipment/FGEquipment.h"
#include "FGInventoryComponentEquipment.generated.h"

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

private:
	/**
	 * If the equipment in the slot has been overridden, this is the equipment.
	 * No need to save this, the kinds of equipments that are placed here are not good candidates for saving (e.g. build gun)
	 * No need to replicate, this is simulated locally on the client.
	 */
	UPROPERTY()
	AFGEquipment* mOverrideEquipmentInSlot;

	/** This is the actual equipment in the slot */
	UPROPERTY( SaveGame, Replicated )
	AFGEquipment* mEquipmentInSlot;

	/** This inventory will only accept equipments that are supposed to be on this slot */
	UPROPERTY( Replicated )
	EEquipmentSlot mEquipmentInventorySlot;

	/** Index of the active equipment*/
	UPROPERTY( SaveGame, Replicated )
	int32 mActiveEquipmentIndex;
};
