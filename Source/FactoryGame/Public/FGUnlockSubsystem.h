// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGUnlockSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FUnlockMoreInventorySlots, int32, newUnlockedSlots );

/**
 * Subsystem responsible for handling unlocks that you get when purchasing/research a schematic
 */
UCLASS( abstract, Blueprintable, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGUnlockSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGUnlockSubsystem();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	/** Get the unlock subsystem, this should always return something unless you call it really early. */
	static AFGUnlockSubsystem* Get( UWorld* world );

	/** Get the unlock subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Unlocks", DisplayName = "GetUnlockSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGUnlockSubsystem* Get( UObject* worldContext );

	void Init();
	void UnlockRecipe( TSubclassOf< class UFGRecipe > recipe );
	void UnlockScannableResource( TSubclassOf< class UFGResourceDescriptor > newResource );
	void UnlockMap();
	void UnlockBuildEfficiency();
	void UnlockBuildOverclock();
	void UnlockInventorySlots( int32 numSlotsToUnlock );
	void UnlockArmEquipmentSlots( int32 numSlotsToUnlock );

	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE TArray< TSubclassOf< class UFGResourceDescriptor > > GetScannableResources() const{ return mScannableResources; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsMapUnlocked() const { return mIsMapUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsBuildingEfficiencyUnlocked() const { return mIsBuildingEfficiencyUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsBuildingOverclockUnlocked() const { return mIsBuildingOverclockUnlocked; }
	
	UFUNCTION( BlueprintCallable, Category = "Resource Scanner" )
	void RemoveAllScannableResources() { mScannableResources.Empty(); }

	UFUNCTION()
	void OnSchematicPurchased( TSubclassOf< class UFGSchematic > newSchematic );

	void SetTotalNumInventorySlots( int32 totalNumSlots );
	void SetTotalNumArmEquipmentSlots( int32 totalNumSlots );

	int32 GetNumTotalInventorySlots() const { return mNumTotalInventorySlots; }
	int32 GetNumTotalArmEquipmentSlots() const { return mNumTotalArmEquipmentSlots; }

private:
	void SetNumOfAdditionalInventorySlots( int32 newNumSlots );
	void SetNumAdditionalArmEquipmentSlots( int32 newNumSlots );
	void SendMessageToAllPlayers( TSubclassOf< class UFGMessageBase > inMessage );

public:
	/** SERVER ONLY: Called when we unlocked more inventory slots */
	UPROPERTY( BlueprintAssignable, Category = "Inventory" )
	FUnlockMoreInventorySlots mOnUnlockedMoreInventorySlots;

	/** SERVER ONLY: Called when we unlocked more arms slots */
	UPROPERTY( BlueprintAssignable, Category = "Inventory" )
	FUnlockMoreInventorySlots mOnUnlockedMoreArmsSlots;

protected:

	/** Message sent when the map is unlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mMapUnlockedMessage;

	/** Message sent when unlocking inventory slot */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mInventorySlotUnlockedMessage;

	/** Message sent when unlocking building efficiency display */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mBuildingEfficiencyUnlockedMessage;

	/** Message sent when unlocking overclocking of buildings */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mBuildingOverclockUnlockedMessage;

	/** Message sent when unlocking arm equipment slot */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mArmEquipmentSlotUnlockedMessage;

private:
	/** These are the resources the players can use their scanner to find */
	UPROPERTY( Savegame, Replicated )
	TArray< TSubclassOf< class UFGResourceDescriptor > > mScannableResources;

	/** Did the player unlock the minimap? */
	UPROPERTY( Savegame, Replicated )
	bool mIsMapUnlocked;

	/** Is the building efficiency display unlocked */
	UPROPERTY(Savegame, Replicated )
	bool mIsBuildingEfficiencyUnlocked;

	/** Is the building overclocking unlocked */
	UPROPERTY(Savegame, Replicated )
	bool mIsBuildingOverclockUnlocked;

	/** How many additional inventory slots have been unlocked for the players */
	int32 mNumAdditionalInventorySlots;

	/** The highest total number of inventory slots that any player have ever had, saved for save compatibility and rebalancing */
	UPROPERTY( Savegame, Replicated )
	int32 mNumTotalInventorySlots;

	/** How many additional arm equipment slots have been unlocked for the players */
	int32 mNumAdditionalArmEquipmentSlots;

	/** The highest total number of arm equipment slots that any player have ever had, saved for save compatibility and rebalancing */
	UPROPERTY( Savegame, Replicated )
	int32 mNumTotalArmEquipmentSlots;


public:
	FORCEINLINE ~AFGUnlockSubsystem() = default;
};
