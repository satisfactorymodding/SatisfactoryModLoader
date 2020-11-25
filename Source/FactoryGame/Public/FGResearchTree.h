// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGResearchTreeNode.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "IncludeInBuild.h"
#include "Styling/SlateBrush.h"
#include "FGResearchTree.generated.h"

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
	virtual void PreSave( const class ITargetPlatform* targetPlatform ) override;
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

public: // MODDING EDIT: protected -> public
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
	
	/** The nodes that this tree is made up of */
	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Research Tree" )
	TArray< class UFGResearchTreeNode* > mNodes;

private:
	/** Asset Bundle data computed at save time. In cooked builds this is accessible from AssetRegistry */
	UPROPERTY()
	FAssetBundleData mAssetBundleData;

#if WITH_EDITORONLY_DATA
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category = "Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif


public:
	FORCEINLINE ~UFGResearchTree() = default;
};
