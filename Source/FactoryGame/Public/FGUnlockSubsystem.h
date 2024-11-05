// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGPlayerController.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "Resources/FGTapeData.h"
#include "Unlocks/FGUnlockCheckmark.h"
#include "Unlocks/FGUnlockScannableResource.h"
#include "FGUnlockSubsystem.generated.h"

class UFGPlayerCustomizationDesc;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FUnlockMoreInventorySlots, int32, newUnlockedSlots );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNewTapeUnlocked, TSubclassOf< UFGTapeData >, newTape );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNewScannableObjectUnlocked, TSubclassOf< class UFGItemDescriptor >, newItemDescriptor );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNewPlayerCustomizationUnlocked, TSubclassOf< class UFGPlayerCustomizationDesc >, customizationDesc );

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCentralStorageUploadSlotsUnlocked );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCentralStorageItemStackLimitUnlocked );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCentralStorageUploadSpeedUnlocked );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnFeatureUnlockedDelegate );

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
	void UnlockScannableResource( FScannableResourcePair newResource );
	void UnlockScannableObject( FScannableObjectData newScannableObject );
	void UnlockMap();
	void UnlockBlueprints();
	void UnlockCustomizer();
	void UnlockBuildEfficiency();
	void UnlockBuildOverclock();
	void UnlockBuildProductionBoost();
	void UnlockInventorySlots( int32 numSlotsToUnlock );
	void UnlockArmEquipmentSlots( int32 numSlotsToUnlock );
	void UnlockEmote( TSubclassOf< class UFGEmote > newEmote );
	void UnlockTape( TSubclassOf< UFGTapeData > newTape );
	void UnlockPlayerCustomization( TSubclassOf< UFGPlayerCustomizationDesc > newCustomizaton );
	void UnlockCentralStorageItemStackLimit( int32 itemStackLimitIncrease );
	// This will not save the value. Just for runtime debugging
	void Cheat_SetCentralStorageUploadSpeed( float seconds );
	void UnlockCentralStorageUploadSpeed( float uploadSpeedPercentageDecrease );
	void UnlockCentralStorageUploadSlots( int32 numSlotsToUnlock );
	void UnlockSAMIntensity( int32 newSamIntensity, bool forceSet = false );

	UFUNCTION( BlueprintCallable, Category = "Unlocks" )
	void UnlockCheckmark( FString playerName );

	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	TArray<TSubclassOf<class UFGResourceDescriptor>> GetScannableResources() const;
	
	FORCEINLINE TArray<FScannableResourcePair> GetScannableResourcePairs() const { return mScannableResourcesPairs; };

	/** Returns all scannable objects/items the given scanner object are allowed to scan for */
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	TArray<TSubclassOf<class UFGItemDescriptor>> GetScannableObjects( const UObject* scannerObject ) const;

	/** Can we scan for this resource class and node type? */
	bool IsNodeScannable( FScannableResourcePair scannableResourcePair );
	
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsMapUnlocked() const { return mIsMapUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsBlueprintsUnlocked() const { return mIsBlueprintsUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsCustomizerUnlocked() const { return mIsCustomizerUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsBuildingEfficiencyUnlocked() const { return mIsBuildingEfficiencyUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsBuildingOverclockUnlocked() const { return mIsBuildingOverclockUnlocked; }
	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool GetIsBuildingProductionBoostUnlocked() const { return mIsBuildingProductionBoostUnlocked; }
	

	/**
	 * This returns ALL customizations available, including ones that are not unlocked.
	 */
	UFUNCTION( BlueprintCallable )
	TArray< TSubclassOf< UFGPlayerCustomizationDesc > > GetAllCustomizationsAvailable() const;

	/**
	 * This lets us know if a customization is unlocked for the player. In addition to checking it from a game
	 * progression perspective, it also checks if the player has the entitlement for it, if the customization is backed by a DLC.
	 */
	UFUNCTION( BlueprintCallable )
	bool IsCustomizationUnlockedForPlayer( TSubclassOf< UFGPlayerCustomizationDesc > customizationDesc, AFGPlayerController* player ) const;

	UFUNCTION( BlueprintCallable, Category = "Resource Scanner" )
	void RemoveAllScannableResources() { mScannableResources.Empty(); }

	UFUNCTION()
	void OnSchematicPurchased( TSubclassOf< class UFGSchematic > newSchematic );

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = Unlocks )
	void OnSchematicPurchasedByPlayer( TSubclassOf< class UFGSchematic > newSchematic, class AFGCharacterPlayer* player );

	void SetTotalNumInventorySlots( int32 totalNumSlots );
	void SetTotalNumArmEquipmentSlots( int32 totalNumSlots );

	int32 GetNumTotalInventorySlots() const { return mNumTotalInventorySlots; }
	int32 GetNumTotalArmEquipmentSlots() const { return mNumTotalArmEquipmentSlots; }

	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	void GetUnlockedEmotes( TArray< TSubclassOf<class UFGEmote> >& out_unlockedEmotes ) const;

	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	void GetUnlockedTapes( TArray< TSubclassOf< class UFGTapeData > >& out_unlockedTapes ) const;

	/** Get the central storage item limit with unlock modifiers applied */
	int32 GetCentralStorageItemStackLimit() const;
	/** Get the central storage upload time with unlock modifiers applied */
	float GetCentralStorageTimeToUpload() const;
	/** Get the number of central storage upload slots for the player with unlock modifiers applied */
	int32 GetCentralStorageNumUploadSlots() const;

	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	void GetPlayersWithCheckmarks( TArray< FGCheckmarkUnlockData >& out_playersWithCheckmarks ) const;

	UFUNCTION( BlueprintPure, Category = "Unlocks" )
	FORCEINLINE bool DoesPlayerHaveCheckmarkUnlocked( FString playerName ) const
	{
		const FGCheckmarkUnlockData* data = mPlayersWithCheckmark.FindByPredicate( [playerName] (FGCheckmarkUnlockData unlockData)
		{
			return unlockData.PlayerName.Equals( playerName );
		} );
		
		return data != nullptr;
	}
	
	UFUNCTION( BlueprintPure, Category = "Narrative" )
	FORCEINLINE int32 GetSAMIntensity() const { return mSAMIntensity; } 

private:
	void SetNumOfAdditionalInventorySlots( int32 newNumSlots );
	void SetNumAdditionalArmEquipmentSlots( int32 newNumSlots );

	UFUNCTION()
	void OnRep_PlayerCheckmarks();
	UFUNCTION()
	void OnRep_CustomizerUnlocked();
	UFUNCTION()
	void OnRep_MapUnlocked();
	
	void UpdatePlayerWidgets();
	
public:
	/** SERVER ONLY: Called when we unlocked more inventory slots */
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FUnlockMoreInventorySlots mOnUnlockedMoreInventorySlots;

	/** SERVER ONLY: Called when we unlocked more arms slots */
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FUnlockMoreInventorySlots mOnUnlockedMoreArmsSlots;

	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnNewTapeUnlocked mOnNewTapeUnlocked;

	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnNewPlayerCustomizationUnlocked mOnNewPlayerCustomizationUnlocked;

	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnNewScannableObjectUnlocked mOnNewScannableObjectUnlocked;
	
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnCentralStorageUploadSlotsUnlocked mOnCentralStorageUploadSlotsUnlocked;
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnCentralStorageItemStackLimitUnlocked mOnCentralStorageItemStackLimitUnlocked;
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnCentralStorageUploadSpeedUnlocked mOnCentralStorageUploadSpeedUnlocked;

	/** Called when the customizer is unlocked */
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnFeatureUnlockedDelegate OnCustomizerUnlocked;

	/** Called when the map is unlocked */
	UPROPERTY( BlueprintAssignable, Category = "Unlocks" )
	FOnFeatureUnlockedDelegate OnMapUnlocked;
private:
	/** These are the resources the players can use their scanner to find */
	//@todok2 Deprecated Look into if we can remove this. Do we really need to save this or can we get away with removing it?
	UPROPERTY( SaveGame )
	TArray< TSubclassOf< class UFGResourceDescriptor > > mScannableResources;

	/** These are the resources the players can use their resource scanner to find */
	UPROPERTY( SaveGame, Replicated )
	TArray< FScannableResourcePair > mScannableResourcesPairs;

	/** These are the items the players can use their hand scanner or radar tower to find */
	UPROPERTY( SaveGame, Replicated )
	TArray< FScannableObjectData > mScannableObjectData;

	/** Did the player unlock the minimap? */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_MapUnlocked )
	bool mIsMapUnlocked;

	/** Is the building efficiency display unlocked */
	UPROPERTY( SaveGame, Replicated )
	bool mIsBuildingEfficiencyUnlocked;

	/** Is the building overclocking unlocked */
	UPROPERTY( SaveGame, Replicated )
	bool mIsBuildingOverclockUnlocked;
	
	UPROPERTY( SaveGame, Replicated )
	bool mIsBlueprintsUnlocked;
	
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CustomizerUnlocked )
	bool mIsCustomizerUnlocked;

	UPROPERTY( SaveGame, Replicated )
	bool mIsBuildingProductionBoostUnlocked;

	/** How many additional inventory slots have been unlocked for the players */
	int32 mNumAdditionalInventorySlots;

	/** The highest total number of inventory slots that any player have ever had, saved for save compatibility and rebalancing */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumTotalInventorySlots;

	/** How many additional arm equipment slots have been unlocked for the players */
	int32 mNumAdditionalArmEquipmentSlots;

	/** The highest total number of arm equipment slots that any player have ever had, saved for save compatibility and rebalancing */
	UPROPERTY( SaveGame, Replicated )
	int32 mNumTotalArmEquipmentSlots;

	/** The emotes that we have unlocked */
	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf<class UFGEmote> > mUnlockedEmotes;

	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class UFGTapeData > > mUnlockedTapes;

	UPROPERTY( SaveGame, Replicated )
	TArray< TSubclassOf< class UFGPlayerCustomizationDesc > > mUnlockedPlayerCustomizations;

	/** Increases the limit for how many item stacks we can store in the central storage. Added on top of UFGCentralStorageSettings::mDefaultItemLimit */
	int32 mUnlockedCentralStorageItemStackLimit;

	/**
	 * This will be a value between 0-100 and represent a percentage.
	 * We will then decrease UFGCentralStorageSettings::mDefaultTimeToUpload with that percentage.
	 * The maximum decrease will be limited by UFGCentralStorageSettings::mMaxTimeToUploadPercentageDecrease.
	 */
	UPROPERTY( Replicated )
	float mUnlockedCentralStorageTimeToUploadDecrease;

	/** How many extra upload slots the player will have where they can queue up uploads for central storage. Added on top of UFGPlayerSettings::mDefaultUploadSlots  */
	int32 mUnlockedCentralStorageUploadSlots;

	/** The names of the players that have unlocked the FICSIT Checkmark™ */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_PlayerCheckmarks )
	TArray< FGCheckmarkUnlockData > mPlayersWithCheckmark;

	/** How intense the effects like VO on the SAM nodes should be. Starts at 0 */ 
	UPROPERTY( SaveGame, Replicated )
	int32 mSAMIntensity = 0;
};
