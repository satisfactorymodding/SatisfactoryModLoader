// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGReplicationDetailActor_BuildableFactory.h"
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
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetInputInventory() { return mInputInventory; }
	FORCEINLINE UFGInventoryComponent* GetOutputInventory() { return mOutputInventory; }
	FORCEINLINE float GetCurrentManufacturingProgress() const { return mCurrentManufacturingProgress; }

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mInputInventory;

	UPROPERTY( Replicated )
	class UFGInventoryComponent* mOutputInventory;

	UPROPERTY( Replicated )
	float mCurrentManufacturingProgress;

public:
	FORCEINLINE ~AFGReplicationDetailActor_Manufacturing() = default;
};