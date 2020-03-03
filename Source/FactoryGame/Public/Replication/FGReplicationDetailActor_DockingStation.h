// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_DockingStation.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_DockingStation : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetCargoInventory() const { return mCargoInventory; }
	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mCargoInventory;

	UPROPERTY( Replicated )
	class UFGInventoryComponent* mFuelInventory;

public:
	FORCEINLINE ~AFGReplicationDetailActor_DockingStation() = default;
};
