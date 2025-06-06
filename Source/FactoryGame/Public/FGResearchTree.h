// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "CoreMinimal.h"
#include "FGEventSubsystem.h"
#include "FGResearchTreeNode.h"
#include "IncludeInBuild.h"
#include "Misc/DataValidation.h"
#include "Styling/SlateBrush.h"
#include "UObject/NoExportTypes.h"
#include "FGResearchTree.generated.h"

UENUM( BlueprintType )
enum EResearchTreeStatus
{
	ERTS_Locked					= 0 UMETA( DisplayName = "Locked" ),
	ERTS_Unlocked				= 1 UMETA( DisplayName = "Unlocked" ),
	ERTS_StartedResearch		= 2 UMETA( DisplayName = "Started Research" ),
	ERTS_FinishedAllResearch	= 3 UMETA( DisplayName = "Finished All Research" ),
};

/**
 * 
 */
UCLASS( Blueprintable, abstract )
class FACTORYGAME_API UFGResearchTree : public UObject
{
	GENERATED_BODY()

public:
	// Begin UObject interface
	void PostLoad() override;
#if WITH_EDITOR
	virtual void PreSave( FObjectPreSaveContext SaveContext ) override;
	virtual EDataValidationResult IsDataValid( FDataValidationContext& validationContext ) const override;
#endif
	// End UObject interface

	// Begin AssetInterface
#if WITH_EDITOR
	/** This scans the class for AssetBundles metadata on asset properties and initializes the AssetBundleData with InitializeAssetBundlesFromMetadata */
	void UpdateAssetBundleData();
#endif
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	// End AssetInterface

	/** Returns the research tree name that should be displayed to the player before the tree is unlocked */
	UFUNCTION( BlueprintPure, Category = "Research Tree" )
	static FText GetPreUnlockDisplayName( TSubclassOf< UFGResearchTree > inClass );

	/** Returns the research tree name that should be displayed to the player after the tree is unlocked */
	UFUNCTION( BlueprintPure, Category = "Research Tree" )
	static FText GetDisplayName( TSubclassOf< UFGResearchTree > inClass );

	/** Returns the research tree description that should be displayed to the player before the three is unlocked */
	UFUNCTION( BlueprintPure, Category = "Research Tree" )
	static FText GetPreUnlockDescription( TSubclassOf< UFGResearchTree > inClass );

	/** Returns the research tree description that should be displayed to the player after the three is unlocked */
	UFUNCTION( BlueprintPure, Category = "Research Tree" )
	static FText GetPostUnlockDescription( TSubclassOf< UFGResearchTree > inClass );

	/** Get the icon for a research tree */
	UFUNCTION( BlueprintPure, Category = "Research Tree" )
	static FSlateBrush GetResearchTreeIcon( TSubclassOf< UFGResearchTree > inClass );

	UFUNCTION( BlueprintCallable, Category = "Research Tree" )
	static void SetNodes( TSubclassOf <UFGResearchTree> inClass, TArray< class UFGResearchTreeNode* > nodes );

	UFUNCTION( BlueprintCallable, Category = "Research Tree" )
	static TArray< class UFGResearchTreeNode* > GetNodes( TSubclassOf <UFGResearchTree> inClass );

	UFUNCTION( BlueprintPure, Category = "Research Tree" )
	static TArray<class UFGAvailabilityDependency *> GetUnlockDependencies( TSubclassOf <UFGResearchTree> inClass );

	/** Returns the relevant events this schematic is present in. */
	UFUNCTION( BlueprintPure, Category = "Research Tree" )
    static TArray< EEvents > GetRelevantEvents( TSubclassOf< UFGResearchTree > inClass );

	static EResearchTreeStatus GetResearchTreeStatus( TSubclassOf< UFGResearchTree > inClass, UObject* worldContext );

	bool GetIsEventTree() const { return mIsEventTree; }
	
protected:
	/** The name to be displayed to the player before the tree is unlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Research Tree" )
	FText mPreUnlockDisplayName;

	/** The name to be displayed to the player after the tree is unlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Research Tree" )
	FText mDisplayName;

	/** The description to be displayed to the player before the tree is unlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Research Tree" )
	FText mPreUnlockDescription;

	/** The description to be displayed to the player after the tree is unlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Research Tree" )
	FText mPostUnlockDescription;

	/** Icon used when displaying this research tree */
	UPROPERTY( EditDefaultsOnly, Category = "Research Tree" )
	FSlateBrush mResearchTreeIcon;

	/** The dependencies that needs to be satisfied before the player can use the tree */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Research Tree" )
	TArray< class UFGAvailabilityDependency* > mUnlockDependencies;

	/** The dependencies that needs to be satisfied before the player can see the tree */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Research Tree" )
	TArray< class UFGAvailabilityDependency* > mVisibilityDependencies;

	/** The events this schematic are present in */
	UPROPERTY( EditDefaultsOnly, Category = "Events" )
	TArray< EEvents > mRelevantEvents;
	
	/** The nodes that this tree is made up of */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Research Tree" )
	TArray< class UFGResearchTreeNode* > mNodes;

	/** True if tree is related to event. Will not give achievement if researched. */
	UPROPERTY( EditDefaultsOnly, Category = "Research Tree" )
	bool mIsEventTree = false;
	
private:
	/** Asset Bundle data computed at save time. In cooked builds this is accessible from AssetRegistry */
	UPROPERTY()
	FAssetBundleData mAssetBundleData;

#if WITH_EDITORONLY_DATA
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category = "Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif

};
