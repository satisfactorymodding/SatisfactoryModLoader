// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Object.h"
#include "ItemAmount.h"
#include "AssetBundleData.h"
#include "FGGameState.h"
#include "IncludeInBuild.h"
#include "Styling/SlateBrush.h"
#include "FGSchematic.generated.h"

//@todo [MODSUPPORT] This should maybe be implemented the same way as UFGBuildCategories?
UENUM( BlueprintType )
enum class ESchematicCategory :uint8
{
	ESC_LOGISTICS		UMETA( DisplayName = "Logistics" ),
	ESC_PRODUCTION		UMETA( DisplayName = "Production" ),
	ESC_EQUIPMENT		UMETA( DisplayName = "Equipment" ),
	ESC_ORGANISATION	UMETA( DisplayName = "Organisation" )
};

//@todo [MODSUPPORT] This should maybe be implemented the same way as UFGBuildCategories?
UENUM( BlueprintType )
enum class ESchematicType :uint8
{
	EST_Custom				UMETA( DisplayName = "Custom" ),
	EST_Cheat				UMETA( DisplayName = "Cheat" ),
	EST_Tutorial			UMETA( DisplayName = "Tutorial" ),
	EST_Research			UMETA( DisplayName = "Research" ),
	EST_Alternate			UMETA( DisplayName = "Alternate" ),
	EST_Story				UMETA( DisplayName = "Story" ),
	EST_TradingPostUpgrade	UMETA( DisplayName = "Hub upgrade" ),
	EST_MAM					UMETA( DisplayName = "MAM unlocked" )
};

/** Holds info about a schematic cost. */
USTRUCT( BlueprintType )
struct FMultipleItemStruct
{
	GENERATED_BODY()

	/** Cost of schematic if there are more than once item in this array the true cost will be randomly selected. */
	UPROPERTY( EditDefaultsOnly )
	TArray< FItemAmount > ItemCost;
};

/**
 * This is a schematic. It is purchased in the trading post and grants the player resources and/or recipes.
 */
UCLASS( Blueprintable, Meta = (AutoJSON = true) )
class FACTORYGAME_API UFGSchematic : public UObject
{
	GENERATED_BODY()

public:
	UFGSchematic();

	/** Returns the type of schematic. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static ESchematicType GetType( TSubclassOf< UFGSchematic > inClass );

	/** Returns the display name of this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static FText GetSchematicDisplayName( TSubclassOf< UFGSchematic > inClass );

	/** Returns the category of this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static ESchematicCategory GetSchematicCategory( TSubclassOf< UFGSchematic > inClass );

	/** Returns the cost of this schematic*/
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< FItemAmount > GetCost( TSubclassOf< UFGSchematic > inClass );

	/** Returns the recipes granted by this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< TSubclassOf< class UFGRecipe > > GetRecipes( TSubclassOf< UFGSchematic > inClass );

	/** Returns mTechOnionTier */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static int32 GetTechTier( TSubclassOf< UFGSchematic > inClass );

	/** Returns mShipTravelTimeAfterPurchase */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static float GetShipTravelTimeAfterPurchase( TSubclassOf< UFGSchematic > inClass );
	
	/** Returns mResourcesToAddToScanner */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< TSubclassOf< class UFGResourceDescriptor > > GetResourceToAddToScanner( TSubclassOf< UFGSchematic > inClass );

	/** Does this schematic unlock the map */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetUnlocksMap( TSubclassOf< UFGSchematic > inClass );

	/** Does this schematic unlock any inventory slots */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetUnlocksInventorySlots( TSubclassOf< UFGSchematic > inClass );

	/** How many inventory slots are unlocked by schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static int32 GetNumInventorySlotsUnlocked( TSubclassOf< UFGSchematic > inClass );

	/** Does this schematic unlock any arm equipment slots */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetUnlocksArmEquipmentSlots( TSubclassOf< UFGSchematic > inClass );

	/** How many arm equipment slots are unlocked by schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static int32 GetNumArmEquipmentSlotsUnlocked( TSubclassOf< UFGSchematic > inClass );

	/** Does this schematic unlock the build efficiency display */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetUnlocksBuildEfficiencyDisplay( TSubclassOf< UFGSchematic > inClass );

	/** Does this schematic unlock the build overclock system */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetUnlocksBuildOverclock( TSubclassOf< UFGSchematic > inClass );	

	/** The icon to be used in UI. */
	UFUNCTION( BlueprintPure, Category = "Item" )
	static FSlateBrush GetItemIcon( TSubclassOf< UFGSchematic > inClass );

	/**Gets the schematic this is dependent on for being unlocked */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TSubclassOf< UFGSchematic > GetDependentOnSchematic( TSubclassOf< UFGSchematic > inClass );

	/**Gets an additional array of dependencies for this schematic to be available */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< TSubclassOf< UFGSchematic > > GetAdditionalSchematicDependencies( TSubclassOf< UFGSchematic > inClass );

	// Return true if we should include this schematic in the current build
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool IsIncludedInBuild( TSubclassOf< UFGSchematic > inClass );

	// Begin UObject interface
	virtual void PostLoad() override;
	virtual void Serialize( FArchive& ar ) override;
#if WITH_EDITOR
	virtual void PreSave( const class ITargetPlatform* targetPlatform ) override;
#endif
	// End UObject interface

#if WITH_EDITOR
	
#endif

	//~ Begin AssetInterface
#if WITH_EDITOR
	/** This scans the class for AssetBundles metadata on asset properties and initializes the AssetBundleData with InitializeAssetBundlesFromMetadata */
	void UpdateAssetBundleData();
#endif
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	//~ End AssetInterface
protected:
	/** What type of schematic is this. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	ESchematicType mType;

	/** The name to be displayed to the player */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	FText mDisplayName;

	/** The category this schematic belongs to. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	ESchematicCategory mSchematicCategory;

	/** The tech tier that this Schematic belongs to. [0...N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Schematic", AssetRegistrySearchable )
	int32 mTechTier;

	/** The cost of this schematic. */
	UPROPERTY( EditDefaultsOnly, Category = "Cost" )
	TArray< FItemAmount > mCost;

	/** When we purchase this schematic how long does it take the ship to come back? */
	UPROPERTY( EditDefaultsOnly, Category = "Cost" )
	float mShipTravelTimeAfterPurchase;

	/** The recipes you get when purchasing */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	TArray< TSubclassOf< UFGRecipe > > mRecipes;

	/**  These are the resources that are scannable */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	TArray< TSubclassOf< UFGResourceDescriptor > > mResourcesToAddToScanner;

	/** Does this schematic unlock the map? */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	bool mUnlocksMap;

	/** Does this schematic unlock the build efficiency display? */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	bool mUnlocksBuildEfficiency;

	/** Does this schematic unlock the build overclock functionality? */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	bool mUnlocksBuildOverclock;

	/** Number of inventory slots this schematic adds to the players inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	int32 mNumInventorySlotsToUnlock;

	/** Number of arm equipment slots this schematic adds to the players inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	int32 mNumArmEquipmentSlotsToUnlock;

	/** Icon used when displaying this schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic", meta = (NoAutoJson = true) )
	FSlateBrush mSchematicIcon;

	/** Is this schematic dependant on any other for being unlocked? */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TSubclassOf< UFGSchematic > mDependsOnSchematic;

	/** Additional list of schematics for more specific dependency checking */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TArray< TSubclassOf< UFGSchematic > > mAdditionalSchematicDependencies;
private:
	/** Asset Bundle data computed at save time. In cooked builds this is accessible from AssetRegistry */
	UPROPERTY()
	FAssetBundleData mAssetBundleData;

#if WITH_EDITORONLY_DATA
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category="Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif

};
