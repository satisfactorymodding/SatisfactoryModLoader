// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "../FGFluidIntegrantInterface.h"
#include "FGBuildableCheatFluidSpawner.generated.h"

/**
 * Base for cheat building that spawns an infinite amount of fluid.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCheatFluidSpawner : public AFGBuildableFactory, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	// Begin AActor
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor

	// Begin FluidIntegrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End FluidIntegrant Interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

	/** Allow blueprint to set the resource type. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	void SetResourceType( TSubclassOf< UFGItemDescriptor > type );

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface

protected:
	/** Resource type to spawn. */
	UPROPERTY( SaveGame, BlueprintReadOnly )
	TSubclassOf< UFGItemDescriptor > mResourceType;

	/** Spawn rate of the fluid, 0 means unlimited. [m3/s] */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float mSpawnRate;

	/** Actual spawn rate of the fluid. [m3/s] */
	UPROPERTY( BlueprintReadWrite )
	float mMeasuredSpawnRate;

	/** Pressure from this output, 0 no added pressure. [meters] */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float mPressure;

private:
	/** Connection fetched from blueprint. */
	UPROPERTY()
	class UFGPipeConnectionComponent* mOutputConnection;

	/** Simulation data for this fluid integrant. */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;

public:
	FORCEINLINE ~AFGBuildableCheatFluidSpawner() = default;
};
