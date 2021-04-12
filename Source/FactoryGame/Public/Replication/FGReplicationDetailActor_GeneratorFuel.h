// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_GeneratorFuel.generated.h"


UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_GeneratorFuel : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()

public:
	AFGReplicationDetailActor_GeneratorFuel();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void RemoveDetailActorFromOwner() override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

protected:
	using AFGReplicationDetailActor_BuildableFactory::OnRep_Inventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mFuelInventory;
};
