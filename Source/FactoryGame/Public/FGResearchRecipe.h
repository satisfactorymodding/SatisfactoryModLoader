// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGRecipe.h"
#include "Resources/FGItemDescriptor.h"
#include "Resources/FGItemDescriptor.h"
#include "UObject/NoExportTypes.h"
#include "AssetBundleData.h"
#include "IncludeInBuild.h"
#include "FGResearchRecipe.generated.h"

USTRUCT(Blueprintable)
struct FACTORYGAME_API FResearchRecipeReward
{
	GENERATED_BODY()

public:
	UPROPERTY( BlueprintReadOnly )
	TArray<FItemAmount> Products;
	
	UPROPERTY( BlueprintReadOnly )
	TArray<TSubclassOf<class UFGResearchRecipe>> ResearchRecipes;
	
	UPROPERTY( BlueprintReadOnly )
	TArray<TSubclassOf<class UFGSchematic>> Schematics;

	bool IsValid() const
	{
		return ( Products.Num() > 0 || ResearchRecipes.Num() > 0 || Schematics.Num() > 0 );
	}

	/** For debugging */
	FString ToString() const;

public:
	FORCEINLINE ~FResearchRecipeReward() = default;
};


/**
 *
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGResearchRecipe : public UFGRecipe
{
	GENERATED_BODY()

public:
	UFGResearchRecipe();

	UFUNCTION( BlueprintCallable, Category = "Research" )
	static FResearchRecipeReward GetResearcResults( TSubclassOf<UFGResearchRecipe> inClass/*, TArray<FItemAmount>& out_products, TArray<TSubclassOf<UFGResearchRecipe>>& out_recipes, TArray<TSubclassOf<class UFGSchematic>>& out_schematics */);

	UFUNCTION( BlueprintCallable, Category = "Research" )
	static float GetResearchTime( TSubclassOf<UFGResearchRecipe> inClass );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	static TArray<TSubclassOf<class UFGItemDescriptor>> GetResearchTriggerItems( TSubclassOf<UFGResearchRecipe> inClass );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	static bool IsResearchRepeatable( TSubclassOf<UFGResearchRecipe> inClass );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	static bool IsValidResearchRecipeReward( FResearchRecipeReward recipeReward ) { return recipeReward.IsValid(); }

	static bool IsExcludedFromBuild( TSubclassOf<UFGResearchRecipe> inClass );

	const TArray<TSubclassOf<class UFGResearchRecipe>> GetRewardedResearchRecipes() const;
	const TArray<TSubclassOf<class UFGSchematic>> GetRewardedSchematics() const;
	bool GetIsRepeatable() const { return mIsRepeatable; }

	/** Accessor to get the display name of the recipe */
	virtual FText GetDisplayName() const override;

	FORCEINLINE bool GetRewardIsDropPackage() { return mRewardUsesDropPackage; }

	/** Returns which items when entering inventory that will trigger the research to become available */
	FORCEINLINE TArray<TSubclassOf<class UFGItemDescriptor>> GetTriggerItems() const { return mTriggerItems; }

	virtual void Serialize( FArchive& ar ) override;
	virtual void PostLoad() override;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
#if WITH_EDITOR
	virtual void PreSave( const class ITargetPlatform* targetPlatform ) override;
	void UpdateAssetBundleData();
#endif

protected:
	// Items that make this research available once it enters the players inventory
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	TArray<TSubclassOf< class UFGItemDescriptor>> mTriggerItems;

	// Can this research be completed multiple times?
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	bool mIsRepeatable;

	UPROPERTY( EditDefaultsOnly, Category = "Rewards" )
	bool mRewardUsesDropPackage;

	// What research that will be unlocked in the research tree by completing this research
	UPROPERTY( EditDefaultsOnly, Category = "Rewards", meta = (EditCondition = "!mRewardUsesDropPackage") )
	TArray<TSoftClassPtr<UFGResearchRecipe>> mUnlockedResearch;

	// What schematics that will be purchased by completing this research
	UPROPERTY( EditDefaultsOnly, Category = "Rewards", meta = ( EditCondition = "!mRewardUsesDropPackage" ) )
	TArray<TSoftClassPtr<UFGSchematic>> mUnlockedSchematics;

	UPROPERTY( EditDefaultsOnly, Category = "Rewards", meta = ( ClampMin = "0", ClampMax = "9999", UIMin = "0", UIMax = "9999", EditCondition = "!mRewardUsesDropPackage" ) )
	int32 mDecorPoints;

	UPROPERTY( EditDefaultsOnly, Category = "Rewards", meta = ( ClampMin = "0", ClampMax = "9999", UIMin = "0", UIMax = "9999", EditCondition = "!mRewardUsesDropPackage" ) )
	int32 mStructurePoints;

#if WITH_EDITORONLY_DATA
	/** Slightly misleading name, as this doesn't only apply to builds. If set to Never, it won't show up in editor */
	UPROPERTY( EditDefaultsOnly, AssetRegistrySearchable, Category="Cooking" )
	EIncludeInBuilds mIncludeInBuilds;
#endif


	/** Old property for excluding from build, remove when all UFGResearchRecipe is resaved on main*/
	UPROPERTY()
	bool mExcludeFromBuild_DEPRECATED;

private:	
	/** Asset Bundle data computed at save time. In cooked builds this is accessible from AssetRegistry */
	UPROPERTY()
	FAssetBundleData mAssetBundleData;

public:
	FORCEINLINE ~UFGResearchRecipe() = default;
};
