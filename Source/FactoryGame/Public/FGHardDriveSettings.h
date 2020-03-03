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

/**
 * Settings for which schematics are returned from research
 */
UCLASS( abstract )
class FACTORYGAME_API UFGHardDriveSettings : public UFGSettings
{
	GENERATED_BODY()
	
public:
	/*
	* Called to fill in an array of research schematics for storage and access from the MAM.
	* @note The research is assumed repeatable because of its inherent nature, thus the calledByResearch parameter is added back as a reward
	*/
	UFUNCTION( )
	static const TArray<TSubclassOf<class UFGSchematic>> GetResearchRewardPackages( class UWorld* world );

	/** Get what we return back if we don't have any rewards to give for researching a hard drive */
	UFUNCTION( BlueprintPure, Category = "HardDrive" )
	FORCEINLINE FItemAmount GetFallbackReturnItem() const { return mFallbackReturnItem; }

	/** Get the schematic that is associated with hard drive research */
	UFUNCTION( BlueprintPure, Category = "HardDrive" )
	static TSubclassOf<class UFGSchematic> GetHardDriveResearchSchematic();

protected:
	/*
	* This is the total quantity of unique elements Schematics that will be added to the reward package
	* @note This is the number of options the player can pick from
	*/
	UPROPERTY( EditAnywhere, Category = "HardDrive" )
	int32 mUniqueItemCount;

	/** Fallback for returning hard drive if no research was available */
	UPROPERTY( EditAnywhere, Category = "HardDrive" )
	FItemAmount mFallbackReturnItem;

	/** The schematic which is used to research hard drives */
	UPROPERTY( EditAnywhere, Category = "HardDrive" )
	TSubclassOf<class UFGSchematic> mHardDriveResearchSchematic;

private:
	/** Called by GetResearchRewardPackages to get only relevant schematics from the drop list */
	void GetValidSchematicRewardDrops( class AFGSchematicManager* schematicManager, TArray<TSubclassOf<class UFGSchematic>>& out_validSchematics) const;

	/** The list of schematics after the valid list is weighed by probability */
	TArray<TSubclassOf<class UFGSchematic>> GetFinalSchematicRewards( const TArray<TSubclassOf<class UFGSchematic>>& allValidSchematicDrops ) const;


public:
	FORCEINLINE ~UFGHardDriveSettings() = default;
};
