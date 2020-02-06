// Copyright 2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_Storage.generated.h"


UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_Storage : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()

public:
	AFGReplicationDetailActor_Storage();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void FlushReplicationActorStateToOwner() override;

	FORCEINLINE UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mStorageInventory;
};