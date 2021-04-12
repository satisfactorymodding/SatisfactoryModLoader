// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableGenerator.generated.h"

/**
 * Base for all generators, i.e. coal, fuel, nuclear etc.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableGenerator : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

	/** Constructor */
	AFGBuildableGenerator();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AACtor interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual bool Factory_HasPower() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

	/** Get the current load of this generator in the range [0,1]. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetLoadPercentage() const { return mLoadPercentage; }

	/** The power this generator can produce. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerProductionCapacity() const;

	/** The default amount power this generator can produce. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetDefaultPowerProductionCapacity() const;

	/** Calculate the power this generator can produce with a given potential. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float CalcPowerProductionCapacityForPotential( float potential ) const;

	virtual void SetActorHiddenInGame( bool bNewHidden ) override;

	/** Called to check if power production can be started. */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "Generator" )
	bool CanStartPowerProduction() const;

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	// End AFGBuildableFactory interface

	/** Called when we start producing fuel. */
	UFUNCTION( BlueprintNativeEvent, Category = "Generator" )
	void Factory_StartPowerProduction();

	/** Called when we stop producing fuel. */
	UFUNCTION( BlueprintNativeEvent, Category = "Generator" )
	void Factory_StopPowerProduction();

	/**
	 * Tick the power production, consume any fuel, update base and dynamic production.
	 * @param dt - Time since last tick.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Generator" )
	void Factory_TickPowerProduction( float dt );

protected:
	/** Amount of power this generator produces in MW. */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mPowerProduction;

	/**
	 * Exponent used in power production calculations.
	 * To calculate maximum production: max = overclock ^ ( 1 / exponent )
	 * Example: 2.5 ^ ( 1 / 1.6 ) = 1.77      An exponent of 1.6 gives a maximum production of 177% at 2.5x overclock.
	 * If exponent is 1.0 the function becomes linear.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = "1.0", ClampMax = "4.0" ) )
	float mPowerProductionExponent;

public: //MODDING EDIT private -> public
	/** Current load of this generator in the range [0,1]. */
	UPROPERTY( Replicated )
	float mLoadPercentage;

};
