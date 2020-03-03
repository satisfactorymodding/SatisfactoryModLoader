// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGBuildDescriptor.h"
#include "FGVehicleDescriptor.generated.h"

/**
 * Build descriptor for vehicles.
 */
UCLASS()
class FACTORYGAME_API UFGVehicleDescriptor : public UFGBuildDescriptor
{
	GENERATED_BODY()
	
public:
	UFGVehicleDescriptor();

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

	/** Get the vehicle class for this descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Vehicle" )
	static TSubclassOf< class AFGVehicle > GetVehicleClass( TSubclassOf< UFGVehicleDescriptor > inClass );

protected:
	virtual FText GetItemNameInternal() const override;
	virtual FText GetItemDescriptionInternal() const override;

	virtual TSubclassOf< class AFGHologram > GetHologramClassInternal() const override;
	virtual TSubclassOf< AActor > GetBuildClassInternal() const override;

#if WITH_EDITOR
	virtual void SetupStage() override;
	virtual FVector GetCenterOfCollision() override;
#endif

public:
	/** Value to display instead of display name and description. */
	static FText mOverrideDisplayNameAndDescription;

	/** The vehicle this descriptor describes. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TSubclassOf< class AFGVehicle > mVehicleClass;

public:
	FORCEINLINE ~UFGVehicleDescriptor() = default;
};
