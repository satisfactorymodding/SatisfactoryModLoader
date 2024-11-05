// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
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
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	// End AActor

	// Begin FluidIntegrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End FluidIntegrant Interface

	/** Set this sink enabled/disabled */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSink" )
	void SetEnabled( bool isEnabled );

	/** Updates the rate at which the fluid is sinked */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSink" )
	void SetSinkRate( float sinkRate );

	/** Updates the minimum fluid content of this sink before the sinking takes place */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSink" )
	void SetMinimumContent( float minimumContent );

	/** Updates the minimum pressure on this sink before the sinking takes place */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSink" )
	void SetMinimumPressure( float minimumPressure );
	
	/** true if this sink is enabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	FORCEINLINE bool IsEnabled() const { return mIsEnabled; }
	
	/** Get the maximum fluid content this building can hold. [m3] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	FORCEINLINE float GetMaxContent() const { return mFluidBox.MaxContent; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	FORCEINLINE float GetSinkRate() const { return mSinkRate; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	FORCEINLINE float GetMeasuredSinkRate() const { return mMeasuredSinkRate; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	FORCEINLINE float GetMinimumContent() const { return mMinimumContent; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSink" )
	FORCEINLINE float GetMinimumPressure() const { return mMinimumPressure; }
	
protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface

protected:
	/** Is the spawner outputting anything, useful for testing setups where multiple spawners are used. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	bool mIsEnabled = true;
	
	/** Sink rate of the fluid, 0 means sink everything. [m3/s] */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mSinkRate;

	/** Actual sink rate of the fluid. [m3/s] */
	UPROPERTY( meta = ( FGReplicated ) )
	float mMeasuredSinkRate;

	/** Sink only if the content is above this threshold. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mMinimumContent;

	/** Sink only if the pressure is above this threshold. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mMinimumPressure;

private:
	/** Cached input component from blueprint. */
	UPROPERTY()
	class UFGPipeConnectionComponent* mInputConnection;

	/** Simulation data for this fluid integrant. */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;
};
