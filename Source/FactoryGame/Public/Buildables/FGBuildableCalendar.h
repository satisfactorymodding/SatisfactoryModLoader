// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGCalendarRewards.h"
#include "FGEventSubsystem.h"
#include "FGBuildableCalendar.generated.h"

USTRUCT()
struct FSlotIndextoRandomRewardMapping
{
	GENERATED_BODY()

	FSlotIndextoRandomRewardMapping(){};
	FSlotIndextoRandomRewardMapping( int32 slotIndex, int32 randomRewardIndex ) :
		SlotIndex( slotIndex ),
		RandomRewardIndex( randomRewardIndex )
	{}
	
	UPROPERTY()
	int32 SlotIndex = 0;
	UPROPERTY()
	int32 RandomRewardIndex = 0;
	
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCalendar : public AFGBuildable
{
	GENERATED_BODY()

public:
	AFGBuildableCalendar();
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	// End IFGDismantleInterface

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override { return false; }
	// End IFGSaveInterface
	
	/** Get the inventory for the christmas calendar. Each inventory slot represents one slot in the calendar */
	UFUNCTION( BlueprintPure, Category = "Calendar" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const { return mInventory; }

	/** Opens a slot on the calendar for the given day.  */
	UFUNCTION( BlueprintCallable, Category = "Calendar" )
	void OpenSlot( int32 dayNumber );

	/** Return the content of a slot on the calendar for the given day. Returns false if slot is not opened or it doesn't exists. dayNumber = 1 opens return the content of the first slot on the calendar, */
	UFUNCTION( BlueprintCallable, Category = "Calendar" )
    bool GetContentOnSlot( int32 dayNumber, FInventoryStack& out_slotContent);

	UFUNCTION( BlueprintCallable, Category = "Calendar" )
	UFGUnlock* GetUnlockOnSlot( int32 dayNumber );
	
	/** Returns true if the slot of the given day is opened, Returns false if slot is not opened or it doesn't exists. dayNumber = 1 will check if slot on the calendar is opened */
	UFUNCTION( BlueprintCallable, Category = "Calendar" )
	bool IsSlotOpened( int32 dayNumber ) const;
    
    /** Returns number of slots in the calendar */
    UFUNCTION( BlueprintCallable, Category = "Calendar" )
    int32 GetNumberOfSlotsInCalendar() const { return mNumberOfSlotsInCalendar; }

	UFUNCTION()
	void OnInventoryItemRemoved( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numRemoved, UFGInventoryComponent* targetInventory );

	void StoreDataToEventSubsystem();

protected:
	/** The inventory for the christmas calendar. Each slot is one slot in the calendar */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInventory;

	/** True if we have populated the calendar inventory with the initial rewards */
	UPROPERTY( SaveGame )
	bool mPopulatedInitialInventory;
	
	/** How many slots it should be in the calendar */
	UPROPERTY( EditDefaultsOnly, Category = "Calendar" )
	int32 mNumberOfSlotsInCalendar;

	/** The calendar rewards class we use to get rewards for slots in this calendar */
	UPROPERTY( EditDefaultsOnly, Category = "Calendar" )
	TSubclassOf< UFGCalendarRewards > mCalendarRewardsClass;

	/** This maps an inventory index to a random reward index in the calendar reward class */
	UPROPERTY()
	TMap< int32, int32 > mInventoryIndexToRandomRewardIndexMapping;

	/** Mirrors mInventoryIndexToRandomRewardIndexMapping for clients. Since TMaps can't be replciated. Can be used on server as well.
	 * Should be merged to only use this new one or something else entirely but didn't want to tackle that a day before release. */
	UPROPERTY( Replicated )
	TArray< FSlotIndextoRandomRewardMapping > mReplicatedIndexMapping;
	
	/** The day numbers ( not indexes ) of the opened slots in the calendar */
	UPROPERTY( Replicated )
	TArray<int32> mOpenedSlotsInCalendar;

	/** ONLY FOR TESTING PURPOSES - Fills out the calendar with this item, One item for day number so slot 1 = 1 item, slot 2 = 2 items and so on*/
	UPROPERTY( EditDefaultsOnly, Category = "Calendar - DEBUG" )
	TSubclassOf<UFGItemDescriptor> mSlotFillerItemClass;
	
};
