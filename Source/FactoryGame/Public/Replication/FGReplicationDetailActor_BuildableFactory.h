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

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mInventoryPotential;
};
