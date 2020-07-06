// Copyright 2016-2020 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

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
	virtual void FlushReplicationActorStateToOwner() override;

	virtual bool HasCompletedInitialReplication() const override;

	FORCEINLINE class UFGInventoryComponent* GetOutputInventory() const { return mOutputInventory; };

protected:
	UPROPERTY( Replicated )
	class UFGInventoryComponent* mOutputInventory;
	

public:
	FORCEINLINE ~AFGRepDetailActor_Extractor() = default;
};