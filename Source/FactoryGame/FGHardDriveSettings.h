// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSettings.h"
#include "FGResearchManager.h"
#include "FGHardDriveSettings.generated.h"

USTRUCT( BlueprintType )
struct FHardDriveSchematicDrop
{
	GENERATED_BODY()

	FHardDriveSchematicDrop() : 
		Schematic( nullptr )
	{
		DropChance = 1.0f;
	}

	/** Get the schematic for this drop if it's loaded */
	TSubclassOf<class UFGSchematic> GetSchematic() const;

	/** Probability of this schematic showing up AFTER culling those that are not valid drops */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HardDriveSchematic" )
	float DropChance;
protected:
	/** @todonow: Remove BlueprintReadOnly on this and make a access function from BP for this Schematic that the hard drive might drop and it's drop chance. This might be null if the schematic isn't included in the build */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "HardDriveSchematic" )
	TSoftClassPtr<class UFGSchematic> Schematic;
};

/**
 * Settings for which schematics are returned from research
 */
UCLASS( abstract )
class FACTORYGAME_API UFGHardDriveSettings : public UFGSettings
{
	GENERATED_BODY()
	
public:
	/*
	* Called to fill in an array of research reward packages for storage and access from the MAM.
	* @note The research is assumed repeatable because of its inherent nature, thus the calledByResearch parameter is added back as a reward
	*/
	UFUNCTION( )
	static const TArray<FResearchRecipeReward> GetResearchRewardPackages( class UWorld* world, TSubclassOf<class UFGResearchRecipe> calledByResearch);

	FORCEINLINE FItemAmount GetFallbackReturnItem() const { return mFallbackReturnItem; }

protected:
	//** Gets the total sum of all potential drops */
	int32 GetTotalSchematicDropProbability( const TArray<FHardDriveSchematicDrop>& schematicDrops ) const;

	/** Helper for creating new rewards from recipes */
	FResearchRecipeReward ResearchRecipeRewardFactory( TSubclassOf<class UFGSchematic> schematic, TSubclassOf<class UFGResearchRecipe> calledByResearch ) const;

protected:
	/*
	* This is the total quantity of unique elements Schematics that will be added to the reward package
	* @note This is the number of options the player can pick from
	*/
	UPROPERTY( EditAnywhere, Category = "HardDrive" )
	int32 mUniqueItemCount;

	/** Schematics to fill hard drive reward package with */
	UPROPERTY( EditAnywhere, Category = "HardDrive" )
	TArray<FHardDriveSchematicDrop> mPotentialSchematicDrops;

	/** Fallback for returning hard drive if no research was available */
	UPROPERTY( EditAnywhere, Category = "HardDrive" )
	FItemAmount mFallbackReturnItem;

private:
	/** Called by GetResearchRewardPackages to get only relevant schematics from the drop list */
	void GetValidSchematicRewardDrops( class AFGSchematicManager* schematicManager, TArray<FHardDriveSchematicDrop>& out_validSchematics) const;

	/** The list of schematics after the valid list is weighed by probability */
	TArray<TSubclassOf<class UFGSchematic>> GetFinalSchematicRewards( const TArray<FHardDriveSchematicDrop>& allValidSchematicDrops ) const;

};
