// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_CargoPlatform.generated.h"

/**
 * Inventory info replication actor for Train Cargo Platform.
 */
UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_CargoPlatform : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()
public:
	AFGReplicationDetailActor_CargoPlatform();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetCargoInventory() const { return mCargoInventory; }

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mCargoInventory;
	

public:
	FORCEINLINE ~AFGReplicationDetailActor_CargoPlatform() = default;
};
