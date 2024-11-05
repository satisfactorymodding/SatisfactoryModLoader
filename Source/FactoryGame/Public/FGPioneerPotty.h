// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"
#include "FGPioneerPotty.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPioneerPotty : public AFGBuildable
{
	GENERATED_BODY()
	
	AFGPioneerPotty();
protected:
	virtual void BeginPlay() override;

	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }

private:
	UPROPERTY( SaveGame )
	UFGInventoryComponent* mStorageInventory;
};
