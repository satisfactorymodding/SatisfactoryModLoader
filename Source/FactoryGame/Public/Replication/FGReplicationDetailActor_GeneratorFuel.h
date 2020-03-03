// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_GeneratorFuel.generated.h"


UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_GeneratorFuel : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()

public:
	AFGReplicationDetailActor_GeneratorFuel();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mFuelInventory;

public:
	FORCEINLINE ~AFGReplicationDetailActor_GeneratorFuel() = default;
};