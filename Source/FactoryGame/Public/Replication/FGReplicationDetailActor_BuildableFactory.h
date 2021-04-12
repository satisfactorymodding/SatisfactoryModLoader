// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Replication/FGReplicationDetailActor.h"
#include "FGReplicationDetailActor_BuildableFactory.generated.h"

UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_BuildableFactory : public AFGReplicationDetailActor
{
	GENERATED_BODY()
public:
	AFGReplicationDetailActor_BuildableFactory();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void FlushReplicationActorStateToOwner() override;

	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE class UFGInventoryComponent* GetInventoryPotential() const { return mInventoryPotential; };

	/** Delegate that will fire (on clients) when mInventoryPotential has replicated */
	DECLARE_DELEGATE( FOnInventoryPotentialChanged )
	FOnInventoryPotentialChanged OnHasCompletedInitialReplicationDelegate;

protected:
	UFUNCTION()
	void OnRep_Inventory();

protected:
	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mInventoryPotential;
};
