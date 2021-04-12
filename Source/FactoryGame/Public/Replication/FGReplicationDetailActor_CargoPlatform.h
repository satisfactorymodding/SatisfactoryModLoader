// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
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
	virtual void RemoveDetailActorFromOwner() override;
	virtual void FlushReplicationActorStateToOwner() override;
	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE UFGInventoryComponent* GetCargoInventory() const { return mCargoInventory; }

protected:
	using AFGReplicationDetailActor_BuildableFactory::OnRep_Inventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mCargoInventory;
	
};
