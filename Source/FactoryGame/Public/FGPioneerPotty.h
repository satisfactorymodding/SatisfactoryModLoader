// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
public:
	AFGPioneerPotty();

	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY( SaveGame )
	UFGInventoryComponent* mStorageInventory;
};
