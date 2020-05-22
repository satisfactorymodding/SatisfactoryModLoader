// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
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

	/** Constructor */
	AFGBuildableGenerator();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AACtor interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual bool HasPower() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

	/** Get the current load of this generator in the range [0,1]. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetLoadPercentage() const { return mLoadPercentage; }

	/** @return true if the fuse is triggered. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float IsFuseTriggered() const { return mIsFuseTriggered; }

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

public://MODDING EDIT
	/** Current load of this generator in the range [0,1]. */
	UPROPERTY( Replicated )
	float mLoadPercentage;

	/** Is the fuse triggered. */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	bool mIsFuseTriggered;

public:
	FORCEINLINE ~AFGBuildableGenerator() = default;
};
