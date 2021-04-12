// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGReplicationDetailActor_PowerStorage.generated.h"

UCLASS()
class FACTORYGAME_API AFGReplicationDetailActor_PowerStorage : public AFGReplicationDetailActor_BuildableFactory
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	virtual void InitReplicationDetailActor( class AFGBuildable* owningActor ) override;
	virtual void UpdateInternalReplicatedValues() override;

	FORCEINLINE float GetPowerStore() const { return mPowerStore; }
	FORCEINLINE float GetPowerInput() const { return mPowerInput; }

protected:
	UPROPERTY( Replicated )
	float mPowerStore;
	
	UPROPERTY( Replicated )
	float mPowerInput;
};
