// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Object.h"
#include "ItemAmount.h"
#include "AssetBundleData.h"
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
	EST_Milestone			UMETA( DisplayName = "Milestone" ),
	EST_Alternate			UMETA( DisplayName = "Alternate" ),
	EST_Story				UMETA( DisplayName = "Story" ),
	EST_MAM					UMETA( DisplayName = "MAM" ),
	EST_ResourceSink		UMETA( DisplayName = "Resource Sink" ),
	EST_HardDrive			UMETA( DisplayName = "Hard Drive" ),
	EST_Prototype			UMETA( DisplayName = "Prototype" )
};

/** Holds info about a schematic cost. */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FMultipleItemStruct
{
	GENERATED_BODY()

	/** Cost of schematic if there are more than once item in this array the true cost will be randomly selected. */
	UPROPERTY( EditDefaultsOnly )
	TArray< FItemAmount > ItemCost;

public:
	FORCEINLINE ~FMultipleItemStruct() = default;
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
	static TSubclassOf< class UFGSchematicCategory > GetSchematicCategory( TSubclassOf< UFGSchematic > inClass );

	/** Returns the sub categories of this schematic */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	static void GetSubCategories( TSubclassOf< UFGSchematic > inClass, UPARAM( ref ) TArray< TSubclassOf< class UFGSchematicCategory > >& out_subCategories );

	/** Returns the cost of this schematic*/
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< FItemAmount > GetCost( TSubclassOf< UFGSchematic > inClass );

	/** Returns the unlocks granted by this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< UFGUnlock* > GetUnlocks( TSubclassOf< UFGSchematic > inClass );

	/** Returns mTechOnionTier */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static int32 GetTechTier( TSubclassOf< UFGSchematic > inClass );

	/** Returns how long this schematics takes to complete its actions when we acquire it */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static float GetTimeToComplete( TSubclassOf< UFGSchematic > inClass );
	
	/** The icon to be used in UI. */
	UFUNCTION( BlueprintPure, Category = "Item" )
	static FSlateBrush GetItemIcon( TSubclassOf< UFGSchematic > inClass );

	/** Returns true if the dependencies for this schematic are met and are available for purchase */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool AreSchematicDependenciesMet( TSubclassOf< UFGSchematic > inClass, UObject* worldContext );

	/** Returns true if the dependencies for this schematic are met and are available for purchase */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	static void GetSchematicDependencies( TSubclassOf< UFGSchematic > inClass, TArray< class UFGAvailabilityDependency* >& out_schematicDependencies );

	/** Returns true if this schematic is allowed to be purchased more than once */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool IsRepeatPurchasesAllowed( TSubclassOf< UFGSchematic > inClass );

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
	/** Add a recipe to this schematic. Only for editor use */
	UFUNCTION( BlueprintCallable, Category = "Editor|Schematic" )
	static void AddRecipe( TSubclassOf< UFGSchematic > inClass, TSubclassOf< class UFGRecipe > recipe );

	/** This migrates the old schematic dependencies to the new dependency system */
	void MigrateDataToNewDependencySystem();

#endif

	//~ Begin AssetInterface
#if WITH_EDITOR
	/** This scans the class for AssetBundles metadata on asset properties and initializes the AssetBundleData with InitializeAssetBundlesFromMetadata */
	void UpdateAssetBundleData();
#endif
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	//~ End AssetInterface

#if WITH_EDITORONLY_DATA
	/** This uses the old schematic category enum to add the new object based type category */
	void MigrateDataToNewSchematicCategory();
#endif

public: // MODDING EDIT: protected -> public
	/** What type of schematic is this. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	ESchematicType mType;

	/** The name to be displayed to the player */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	FText mDisplayName;

	/** The category this schematic belongs to. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TSubclassOf< class UFGSchematicCategory > mSchematicCategory;

	/** The sub categories this schematic belongs to. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TArray< TSubclassOf< class UFGSchematicCategory > > mSubCategories;

	/** The tech tier that this Schematic belongs to. [0...N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Schematic", AssetRegistrySearchable )
	int32 mTechTier;

	/** The cost of this schematic. */
	UPROPERTY( EditDefaultsOnly, Category = "Cost" )
	TArray< FItemAmount > mCost;

	/** When we acquire this schematic how long does it take for it to complete its actions */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	float mTimeToComplete;

	/** The unlocks you get when purchasing */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Unlocks" )
	TArray< class UFGUnlock* > mUnlocks;

	/** Icon used when displaying this schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic", meta = (NoAutoJson = true) )
	FSlateBrush mSchematicIcon;

	/** Is this schematic dependant on anything to be available for purchase? */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Dependencies" )
	TArray< class UFGAvailabilityDependency* > mSchematicDependencies;

	// Begin Deprecated
	/** Is this schematic dependant on any other for being unlocked? */
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = ( DeprecatedProperty, DeprecationMessage = "Use availability dependencies instead", NoAutoJson = true ) )
	TSubclassOf< UFGSchematic > mDependsOnSchematic;

	/** Additional list of schematics for more specific dependency checking */
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = ( DeprecatedProperty, DeprecationMessage = "Use availability dependencies instead", NoAutoJson = true ) )
	TArray< TSubclassOf< UFGSchematic > > mAdditionalSchematicDependencies;
	
	/** The category this schematic belongs to. */
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = ( DeprecatedProperty, DeprecationMessage = "Use new schematic category object instead", NoAutoJson = true ) )
	ESchematicCategory mSchematicCategoryDeprecated;
	// End Deprecated

private:
	/** Asset Bundle data computed at save time. In cooked builds this is accessible from AssetRegistry */
	UPROPERTY( meta = ( NoAutoJson = true ) )
	FAssetBundleData mAssetBundleData;

#if WITH_EDITORONLY_DATA
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category="Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif


public:
	FORCEINLINE ~UFGSchematic() = default;
};
