// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_DroneStation.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_DroneStation : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void RemoveDetailActorFromOwner() override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetInputInventory() const { return mInputInventory; }
	FORCEINLINE UFGInventoryComponent* GetOutputInventory() const { return mOutputInventory; }
	FORCEINLINE UFGInventoryComponent* GetBatteryInventory() const { return mBatteryInventory; }

protected:
	using AFGReplicationDetailActor_BuildableFactory::OnRep_Inventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mInputInventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mOutputInventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mBatteryInventory;
};
