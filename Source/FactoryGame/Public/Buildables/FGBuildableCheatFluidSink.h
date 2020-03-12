// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "../FGFluidIntegrantInterface.h"
#include "FGBuildableCheatFluidSink.generated.h"

/**
 * Base for cheat building that sinks an infinite amount of fluid.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCheatFluidSink : public AFGBuildableFactory, public IFGFluidIntegrantInterface
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

	/** Get the maximum fluid content this building can hold. [m3] */
	UFUNCTION( BlueprintPure )
	float GetMaxContent() const { return mFluidBox.MaxContent; }

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_CollectInput_Implementation() override;
	// End AFGBuildableFactory interface

public:
	/** Sink rate of the fluid, 0 means sink everything. [m3/s] */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float mSinkRate;

	/** Actual sink rate of the fluid. [m3/s] */
	UPROPERTY( BlueprintReadWrite )
	float mMeasuredSinkRate;

	/** Sink only if the content is above this threshold. */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float mMinimumContent;

	/** Sink only if the pressure is above this threshold. */
	UPROPERTY( SaveGame, BlueprintReadWrite )
	float mMinimumPressure;

private:
	/** Cached input component from blueprint. */
	UPROPERTY()
	class UFGPipeConnectionComponent* mInputConnection;

	/** Simulation data for this fluid integrant. */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;

public:
	FORCEINLINE ~AFGBuildableCheatFluidSink() = default;
};
