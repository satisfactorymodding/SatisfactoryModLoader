// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGRepDetailActor_Extractor.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGRepDetailActor_Extractor : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()
public:
	AFGRepDetailActor_Extractor();
	
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void RemoveDetailActorFromOwner() override;
	virtual void FlushReplicationActorStateToOwner() override;

	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE class UFGInventoryComponent* GetOutputInventory() const { return mOutputInventory; };

protected:
	using AFGReplicationDetailActor_BuildableFactory::OnRep_Inventory;

	UPROPERTY( ReplicatedUsing = OnRep_Inventory )
	class UFGInventoryComponent* mOutputInventory;
	
};