// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_Manufacturing.generated.h"

UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_Manufacturing : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()

public:
	AFGReplicationDetailActor_Manufacturing();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void UpdateInternalReplicatedValues() override;
	virtual void RemoveDetailActorFromOwner() override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetInputInventory() { return mInputInventory; }
	FORCEINLINE UFGInventoryComponent* GetOutputInventory() { return mOutputInventory; }
	FORCEINLINE float GetCurrentManufacturingProgress() const { return mCurrentManufacturingProgress; }

protected:
	using AFGReplicationDetailActor_BuildableFactory::OnRep_Inventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mInputInventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mOutputInventory;

	UPROPERTY( Replicated )
	float mCurrentManufacturingProgress;
};
