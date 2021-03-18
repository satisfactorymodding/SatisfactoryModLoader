// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGFluidIntegrantInterface.h"
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

	/** Set this sink enabled/disabled */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSink" )
	void SetEnabled( bool isEnabled );
	/** true if this sink is enabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	bool IsEnabled() const { return mIsEnabled; }
	
	/** Get the maximum fluid content this building can hold. [m3] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	float GetMaxContent() const { return mFluidBox.MaxContent; }

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_CollectInput_Implementation() override;
	// End AFGBuildableFactory interface

public:
	/** Is the spawner outputting anything, useful for testing setups where multiple spawners are used. */
	UPROPERTY( SaveGame )
	bool mIsEnabled = true;
	
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
};
