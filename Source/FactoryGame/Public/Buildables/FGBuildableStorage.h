// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGBuildableStorage.generated.h"

/**
 * Base class for all storage boxes, large and small. May have an arbitrary number of inputs and outputs.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableStorage : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	/** Constructor */
	AFGBuildableStorage();
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	//~ Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	//~ End IFGDismantleInterface
	
	/** Get the storage inventory from this storage box. */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetStorageInventory() { return mStorageInventory; }

protected:
#if WITH_EDITOR // Virtual should only exist in editor builds since its used for testing item throughput
	virtual void Factory_Tick(float dt) override;
#endif
	
	// Begin Factory_ interface
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface
public:
	/** How far apart in Z do multiple storages stack. */
	UPROPERTY( EditDefaultsOnly, Category = "Storage" )
	float mStackingHeight;
	
	/** The size of the inventory for this storage. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySizeX;
	
	/** The size of the inventory for this storage. */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mInventorySizeY;

private:
	/** The inventory to store everything in. Don't use this directly, use mStorageInventoryHandler->GetActiveInventoryComponent() */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mStorageInventory;
	
	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray<class UFGFactoryConnectionComponent*> mCachedInputConnections;

#if WITH_EDITOR
	bool mHasResolvedBeltSpeed = 0.f;
	TArray< float > mSpeedOfIncomingBelts;
	float mTimeStartThroughputCheck = 0.f;
	int32 mNumItemsThroughputCheck = 0;
#endif
};
