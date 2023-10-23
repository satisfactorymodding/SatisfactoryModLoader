// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_ResourceSink.generated.h"

UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_ResourceSink : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()

public:
	AFGReplicationDetailActor_ResourceSink();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;
	
	FORCEINLINE UFGInventoryComponent* GetCouponInventory() const { return mCouponInventory; }

protected:
	using AFGReplicationDetailActor_BuildableFactory::OnRep_Inventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mCouponInventory;
};