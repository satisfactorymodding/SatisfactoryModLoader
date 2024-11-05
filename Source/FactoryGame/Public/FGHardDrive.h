// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "FGHardDrive.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSchematicsGenerated, const TArray<TSubclassOf<class UFGSchematic>>&, schematics );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSchematicClaimed, TSubclassOf<class UFGSchematic>, schematic );

/**
 * 
 */
UCLASS( BlueprintType )
class FACTORYGAME_API UFGHardDrive : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintPure, Category = "Research" )
	void GetSchematics( TArray<TSubclassOf<UFGSchematic>>& out_schematics ) const;

	/** Do we have any rerolls left for this hard drive */
	UFUNCTION( BlueprintPure, Category = "Research" )
	bool HasReroll() const;

	/** Do we have enough alternate schematics to reroll this hard drive */
	UFUNCTION( BlueprintPure, Category = "Research" )
	bool CanReroll() const;

	UFUNCTION( BlueprintCallable, Category = "Research" )
	void Reroll( class AFGPlayerController* controller );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	void ClaimSchematic( class AFGPlayerController* controller, TSubclassOf<class UFGSchematic> schematic);

	UPROPERTY( BlueprintAssignable, Category = "Research" )
	FOnSchematicsGenerated mOnSchematicsGenerated;
	
	UPROPERTY( BlueprintAssignable, Category = "Research" )
	FOnSchematicClaimed mOnSchematicClaimed;

private:
	friend class AFGResearchManager;
	
	int32 mHardDriveID = INDEX_NONE;
};
