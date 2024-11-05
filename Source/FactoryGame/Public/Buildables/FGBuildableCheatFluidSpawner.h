// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "FGFluidIntegrantInterface.h"
#include "FGBuildableCheatFluidSpawner.generated.h"

/**
 * Base for cheat building that spawns an infinite amount of fluid.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCheatFluidSpawner : public AFGBuildableFactory, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	AFGBuildableCheatFluidSpawner();
	
	// Begin AActor
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	// End AActor

	// Begin FluidIntegrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End FluidIntegrant Interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

	/** Set this spawner enabled/disabled */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	void SetEnabled( bool isEnabled );

	/** Allow blueprint to set the resource type. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	void SetResourceType( TSubclassOf< UFGItemDescriptor > type );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	void SetSpawnRate( float spawnRate );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	void SetPressure( float pressure );
	
	/** true if this spawner is enabled. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
    FORCEINLINE bool IsEnabled() const { return mIsEnabled; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	FORCEINLINE float GetSpawnRate() const { return mSpawnRate; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	FORCEINLINE float GetMeasuredSpawnRate() const { return mMeasuredSpawnRate; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	FORCEINLINE float GetPressure() const { return mPressure; }
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat|CheatFluidSpawner" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetResourceType() const { return mResourceType; }

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface

protected:
	/** Is the spawner outputting anything, useful for testing setups where multiple spawners are used. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	bool mIsEnabled;
	
	/** Resource type to spawn. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< UFGItemDescriptor > mResourceType;

	/** Spawn rate of the fluid, 0 means unlimited. [m3/s] */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mSpawnRate;

	/** Actual spawn rate of the fluid. [m3/s] */
	UPROPERTY( meta = ( FGReplicated ) )
	float mMeasuredSpawnRate;

	/** Pressure from this output, 0 no added pressure. [meters] */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mPressure;

private:
	/** Connection fetched from blueprint. */
	UPROPERTY()
	class UFGPipeConnectionComponent* mOutputConnection;

	/** Simulation data for this fluid integrant. */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;
};
