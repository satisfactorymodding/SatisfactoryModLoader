// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildableManufacturerVariablePower.h"
#include "FGBuildDescriptor.h"
#include "FGBuildingDescriptor.generated.h"

/**
 * Build descriptor for buildables.
 */
UCLASS( Abstract )
class FACTORYGAME_API UFGBuildingDescriptor : public UFGBuildDescriptor
{
	GENERATED_BODY()
public:
	UFGBuildingDescriptor();

	//~ Begin UObject Interface
	virtual void PostLoad() override;
	//~ End UObject Interface

	/** Get the buildable class for this building descriptor. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static TSubclassOf< class AFGBuildable > GetBuildableClass( TSubclassOf< UFGBuildingDescriptor > inClass );
	
	/** Whether or not the building uses distance when zooping instead of instances. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static bool GetUsesDistanceForZooping( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power consumption of buildable. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static float GetPowerConsumption( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power consumption of buildable. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static bool HasVariablePowerConsumption( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power consumption of buildable. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static float GetMinimumPowerConsumption( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power consumption of buildable. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static float GetMaximumPowerConsumption( TSubclassOf< UFGBuildingDescriptor > inClass );

	/** Get the the power production of buildable, 0 for non-producers. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Descriptor|Building" )
	static float GetPowerProduction( TSubclassOf< UFGBuildingDescriptor > inClass );

	template< float AFGBuildableManufacturerVariablePower::*Member >
	static float GetVariablePowerConsumptionLimit( TSubclassOf< UFGBuildingDescriptor > inClass );

protected:
	virtual FText GetItemNameInternal() const override;
	virtual FText GetItemDescriptionInternal() const override;

	virtual TSubclassOf< class AFGHologram > GetHologramClassInternal() const override;
	virtual TSubclassOf< AActor > GetBuildClassInternal() const override;

	FORCEINLINE virtual bool Internal_CanItemBePickedup() const override { return false; }

#if WITH_EDITOR
	/** Sets the class this building descriptor builds. Only for editor use */
	UFUNCTION( BlueprintCallable, Category = "Editor|Descriptor|Building" )
	static void SetBuildableClass( TSubclassOf< UFGBuildingDescriptor > inClass, TSubclassOf< class AFGBuildable > buildableClass );
#endif

protected:
	/** Value to display instead of display name and description. */
	static FText mOverrideDisplayNameAndDescription;

	/** The class to build. */
	UPROPERTY( EditDefaultsOnly, Category = "Building" )
	TSubclassOf< class AFGBuildable > mBuildableClass;

	/** Whether or not the building uses distance when zooping instead of instances. */
	UPROPERTY( EditDefaultsOnly, Category = "Item" )
	bool mUsesDistanceForZooping;
};

template< float AFGBuildableManufacturerVariablePower::*Member >
float UFGBuildingDescriptor::GetVariablePowerConsumptionLimit( TSubclassOf< UFGBuildingDescriptor > inClass )
{
	if( HasVariablePowerConsumption( inClass ) )
	{
		if( TSubclassOf < AFGBuildable > buildableClass = inClass->GetDefaultObject< UFGBuildingDescriptor >()->mBuildableClass )
		{
			AFGBuildableManufacturerVariablePower* buildable = CastChecked< AFGBuildableManufacturerVariablePower >( buildableClass->GetDefaultObject() );
			return buildable->*Member;
		}
	}
	return GetPowerConsumption( inClass );
}
