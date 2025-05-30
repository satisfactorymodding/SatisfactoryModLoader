// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "AssetRegistry/AssetBundleData.h"
#include "FGEventSubsystem.h"
#include "IncludeInBuild.h"
#include "ItemAmount.h"
#include "Styling/SlateBrush.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "Misc/DataValidation.h"
#include "FGSchematic.generated.h"

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
	EST_Prototype			UMETA( DisplayName = "Prototype" ),
	EST_Customization		UMETA( DisplayName = "Customization" )
};

UENUM( BlueprintType )
enum class ESchematicState :uint8
{
	ESS_Locked			UMETA( DisplayName = "Locked" ),
	ESS_Purchased		UMETA( DisplayName = "Purchased" ),
	ESS_Available		UMETA( DisplayName = "Available" ),
	ESS_Hidden			UMETA( DisplayName = "Hidden" )
};

UENUM( BlueprintType )
enum class ETechTierState :uint8
{
	ETTS_Locked				UMETA( DisplayName = "Locked" ),
	ETTS_Available			UMETA( DisplayName = "Available" ),
	ETTS_FullyPurchased		UMETA( DisplayName = "Fully Purchased" )
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

	// Begin UObject interface
	virtual void PostLoad() override;
	virtual void Serialize( FArchive& ar ) override;
#if WITH_EDITOR
	virtual void PreSave( FObjectPreSaveContext saveContext ) override;
	virtual EDataValidationResult IsDataValid( FDataValidationContext& validationContext ) const override;
#endif
	// End UObject interface

	//~ Begin AssetInterface
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
#if WITH_EDITOR
	/** This scans the class for AssetBundles metadata on asset properties and initializes the AssetBundleData with InitializeAssetBundlesFromMetadata */
	void UpdateAssetBundleData();
#endif
	//~ End AssetInterface

	/** Returns the type of schematic. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static ESchematicType GetType( TSubclassOf< UFGSchematic > inClass );

	/** Returns the display name of this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static FText GetSchematicDisplayName( TSubclassOf< UFGSchematic > inClass );

	/** Returns the description of this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static FText GetSchematicDescription( TSubclassOf< UFGSchematic > inClass );

	/** Gets the online statistic gameplay tag of this schematic. */
    UFUNCTION( BlueprintPure, Category = "Schematic" )
    static FGameplayTag GetStatisticGameplayTag( TSubclassOf< UFGSchematic > inClass );

	/** Returns the category of this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TSubclassOf< class UFGSchematicCategory > GetSchematicCategory( TSubclassOf< UFGSchematic > inClass );

	/** Returns the sub categories of this schematic */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	static void GetSubCategories( TSubclassOf< UFGSchematic > inClass, UPARAM( ref ) TArray< TSubclassOf< class UFGSchematicCategory > >& out_subCategories );

	/** The order we want schematics in menus, lower is earlier */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
    static float GetMenuPriority( TSubclassOf< UFGSchematic > inClass );

	/** Returns the cost of this schematic*/
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< FItemAmount > GetCost( TSubclassOf< UFGSchematic > inClass );

	/** Returns if this schematic is player specific */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetIsPlayerSpecific( TSubclassOf< UFGSchematic > inClass );

	/** Returns the unlocks granted by this schematic */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static TArray< class UFGUnlock* > GetUnlocks( TSubclassOf< UFGSchematic > inClass );

	/** Returns which tier this belongs to. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static int32 GetTechTier( TSubclassOf< UFGSchematic > inClass );

	/** Returns how long this schematics takes to complete its actions when we acquire it */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static float GetTimeToComplete( TSubclassOf< UFGSchematic > inClass );

	/** Returns other schematics that are unlocked and relevant to this schematic in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	static void GetRelevantUnlockedShopSchematics( UObject* worldContext, TSubclassOf< UFGSchematic > inClass, TArray< TSubclassOf< UFGSchematic > >& out_schematics );

	/** Returns other schematics that are relevant to this schematic in the awesome shop */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	static void GetRelevantShopSchematics( TSubclassOf< UFGSchematic > inClass, TArray< TSubclassOf< UFGSchematic > >& out_schematics );
	
	/** The icon to be used in UI. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static FSlateBrush GetItemIcon( TSubclassOf< UFGSchematic > inClass );

	/** The small version of the icon to be used in UI. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
    static UTexture2D* GetSmallIcon( TSubclassOf< UFGSchematic > inClass );

	/** Returns true if the dependencies for this schematic are met and are available for purchase */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool AreSchematicDependenciesMet( TSubclassOf< UFGSchematic > inClass, UObject* worldContext );

	/** Appends the dependencies for this schematic to the out_schematicDependencies */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
	static void GetSchematicDependencies( TSubclassOf< UFGSchematic > inClass, TArray< class UFGAvailabilityDependency* >& out_schematicDependencies );

	/** Returns if schematic should be hidden utnil dependencies are met. Used to filter out the visibilty of schematics when browsing them ingame */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool GetHiddenUntilDependenciesMet( TSubclassOf< UFGSchematic > inClass );
	
	/** Get the schematic state. Used to filter visibility when browsing schematics in game */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static ESchematicState GetSchematicState( TSubclassOf< UFGSchematic > inClass, UObject* worldContext );

	/** Returns true if we can give access to this schematic. Checks for events and if mDependenciesBlocksSchematicAccess is true we check that all dependencies are met as well. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool CanGiveAccessToSchematic( TSubclassOf< UFGSchematic > inClass, UObject* worldContext );

	/** Returns true if this schematic only contains unlocks that can be purchased more than once. If we have no unlocks we return false */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool IsRepeatPurchasesAllowed( TSubclassOf< UFGSchematic > inClass );

	/** Sort an array dependent on their menu priority. */
	UFUNCTION( BlueprintCallable, Category = "Schematic" )
    static void SortByMenuPriority( UPARAM( ref ) TArray< TSubclassOf< UFGSchematic > >& schematics );

	/** Returns the relevant events this schematic is present in. */
	UFUNCTION( BlueprintPure, Category = "Schematic" )
    static TArray< EEvents > GetRelevantEvents( TSubclassOf< UFGSchematic > inClass );

	// Return true if we should include this schematic in the current build
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static bool IsIncludedInBuild( TSubclassOf< UFGSchematic > inClass );
	
	UFUNCTION( BlueprintPure, Category = "Schematic" )
	static FGameplayTag GetSchematicUnlockTag( TSubclassOf< UFGSchematic > inClass );
	
#if WITH_EDITOR
	/** Add a recipe to this schematic. Only for editor use */
	UFUNCTION( BlueprintCallable, Category = "Editor|Schematic" )
	static void AddRecipe( TSubclassOf< UFGSchematic > inClass, TSubclassOf< class UFGRecipe > recipe );

	/** This migrates the old schematic dependencies to the new dependency system */
	void MigrateDataToNewDependencySystem();
#endif

protected:
	/** What type of schematic is this. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	ESchematicType mType;

	/** The name to be displayed to the player */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	FText mDisplayName;

	/** Readable description of the schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic", meta = ( MultiLine = true ) )
	FText mDescription;

	/** If assigned to an online stat gameplay tag, it will be incremented whenever this schematic is unlocked. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	FGameplayTag mStatisticGameplayTag;

	/** The category this schematic belongs to. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TSubclassOf< class UFGSchematicCategory > mSchematicCategory;

	/** The sub categories this schematic belongs to. */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TArray< TSubclassOf< class UFGSchematicCategory > > mSubCategories;

	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	float mMenuPriority;

	/** The tech tier that this Schematic belongs to. [0...N]*/
	UPROPERTY( EditDefaultsOnly, Category = "Schematic", AssetRegistrySearchable )
	int32 mTechTier;

	/** The cost of this schematic. */
	UPROPERTY( EditDefaultsOnly, Category = "Cost" )
	TArray< FItemAmount > mCost;

	/** When we acquire this schematic how long does it take for it to complete its actions */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	float mTimeToComplete;

	/** Other schematics that are relevant to this schematic in the awesome shop */
	UPROPERTY( EditDefaultsOnly, Category = "Schematic" )
	TArray< TSubclassOf<UFGSchematic> > mRelevantShopSchematics;

	/** If true this schematic is purchased per player rather than session wide. Only really applicable if type is EST_ResourceSink so we
	 *  do a check for that in IsDataValid */
	UPROPERTY( EditDefaultsOnly, Category = "Unlocks" )
	bool mIsPlayerSpecific;
	
	/** The unlocks you get when purchasing */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Unlocks" )
	TArray< class UFGUnlock* > mUnlocks;
	
	/** Icon used when displaying this schematic */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	FSlateBrush mSchematicIcon;
	
	/** Small version of the icon used when displaying this schematic  */
	UPROPERTY( EditDefaultsOnly, Category="UI", meta = ( AddAutoJSON = true ) )
	UTexture2D* mSmallSchematicIcon;

	/** Is this schematic dependant on anything to be available for purchase? */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Dependencies" )
	TArray< class UFGAvailabilityDependency* > mSchematicDependencies;

	/** Should schematic dependencies block the access to the schematic. This doesn't store the schematic and checks if dependencies are met later. You need to try and give access to it again. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependencies" )
	bool mDependenciesBlocksSchematicAccess;

	/** Should schematic be hidden until dependencies are met. Used to filter out the visibility of schematics when browsing them ingame */
	UPROPERTY( EditDefaultsOnly, Category = "Dependencies" )
	bool mHiddenUntilDependenciesMet;

	/** The events this schematic are present in */
	UPROPERTY( EditDefaultsOnly, Category = "Events" )
	TArray< EEvents > mRelevantEvents;

	// Begin Deprecated
	/** Is this schematic dependant on any other for being unlocked? */
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = ( DeprecatedProperty, DeprecationMessage = "Use availability dependencies instead", NoAutoJson = true ) )
	TSubclassOf< UFGSchematic > mDependsOnSchematic;

	/** Additional list of schematics for more specific dependency checking */
	UPROPERTY( VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = ( DeprecatedProperty, DeprecationMessage = "Use availability dependencies instead", NoAutoJson = true ) )
	TArray< TSubclassOf< UFGSchematic > > mAdditionalSchematicDependencies;
	
	// End Deprecated

	UPROPERTY( EditDefaultsOnly )
	FGameplayTag mSchematicUnlockTag;
	
private:
	/** Asset Bundle data computed at save time. In cooked builds this is accessible from AssetRegistry */
	UPROPERTY( meta = ( NoAutoJson = true ) )
	FAssetBundleData mAssetBundleData;

#if WITH_EDITORONLY_DATA
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category="Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif

};
