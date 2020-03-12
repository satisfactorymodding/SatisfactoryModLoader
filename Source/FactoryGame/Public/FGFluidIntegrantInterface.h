// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGFluidIntegrantInterface.generated.h"


/**
 * A fluid box is a simulation unit in the fluid system, it has a volume and keeps track of pressures, flow etc.
 *
 * @note ALL distance units in the fluid box is in meters.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFluidBox
{
	GENERATED_BODY()
public:
	bool Serialize( FArchive& ar );
	friend FArchive& operator<<( FArchive& ar, FFluidBox& box );
	bool operator==( const FFluidBox& other ) const;
	bool operator!=( const FFluidBox& other ) const;

public:
	static float constexpr DEFAULT_FLOW_LIMIT = 5.f;

	// The Z mid point for this box. [meters][world space]
	float Z = 0.f;
	// The lowest and highest point on the box. [meters][world space]
	float LowZ = 0.f;
	float HighZ = 0.f;
	// Height of this box, cannot be 0. [meters]
	float Height = 1.f;
	/**
	 * Height from the outflow at which this box can achieve laminar flow. [meters]
	 * Must be in range (0, Height]
	 */
	float LaminarHeight = 1.f;

	/** The current content of this fluid box. [m^3] */
	float Content = 0.f;
	/** The max content this fluid box can hold. [m^3] */
	float MaxContent = 5.f;
	/** The maximum overfill allowed in the range (0,1] normalized percent. */
	float MaxOverfillPct = 0.40f;
	/**
	 * Overfilling is what creates pressure in the pipes,
	 * How much of the overfill that contributes to the pressure is defined here.
	 * If the max over fill is 10 % and 50 % of that is contributing to pressure:
	 * Then we'll reach maximum pressure at 105 % content and are allowed to fill to 110 %.
	 *
	 * This value is in the range (0,1] normalized percent.
	 */
	static constexpr float OVERFILL_USED_FOR_PRESSURE_PCT = 0.75f;

	/**
	 * The following flow values are not used for any simulations only for feedback.
	 * For the simulation see the junction pairs in the network.
	 *
	 * Through flow is in [m^3/s] and both junction pairs are taken into account in the average.
	 *
	 * Fill and drain is how fast the box is filling up or emptying in [m^3/s].
	 */
	float FlowThrough = 0.f;
	float FlowFill = 0.f;
	float FlowDrain = 0.f;
	/** The flow direction relative to the first component on the pipe, either 1 or -1 if not pipe. */
	float FlowDirection;
	/** Maximum flow through this box. 0 is unlimited. [m^3/s] */
	float FlowLimit = DEFAULT_FLOW_LIMIT;

	/** See implementation */
	int32 PressureGroup = INDEX_NONE;
	/** The height of the pressure column at the bottom of this box. [meters] */
	float PressureColumn = 0.f;
	float ElevationPressureColumn = 0.f;

	/** The added pressure at this point in the simulation, pressure is added to the producer connection. [meters] */
	float AddedPressure = 0.f;
	/** Toggle to allow disabling added pressure ( currently used by pumps ) */
	float AddedPressureToggle = 1.f;

	//@todoPipes WITH_EDITORONLY_DATA maybe
	bool Debug_EnableVerboseLogging = false;
	int32 Debug_PressureGroup = INDEX_NONE;
	float Debug_DP = 0.f;
	float Debug_SmoothedFlow = 0.f;

	//** Call to get the current added pressure taking into account the pressure toggle. */
	float GetCurrentAddedPressure()
	{
		return AddedPressure * AddedPressureToggle;
	}

	// @todo - Move these helpers to a Blueprint Library
	/** The current content measured in Liters */
	int32 GetContentInLiters()
	{
		return FMath::FloorToInt( Content * 1000.f );
	}

	/** The Max content of this Fluid Box Rounded down in Liters */
	int32 GetAvailableSpaceInLiters()
	{
		return FMath::FloorToInt( ( ( MaxContent * ( 1.f + MaxOverfillPct ) ) - Content ) * 1000.f );
	}

	/** Adds a quantity of content supplied in Liters */
	void AddContentInLiters( int32 amountLiters )
	{
		Content += amountLiters * 0.001f;
	}

	/** Removes a quantity of content, supplied in Liters */
	void RemoveContentInLiters( int32 amountLiters )
	{
		Content -= amountLiters * 0.001f;
	}
	// endTodo for helper functions that should be in blueprint Library

	// Clear the set properties on this box ( Called when flushing a PipeNetwork )
	void Reset()
	{
		Content = 0.f;
		FlowThrough = 0.f;
		FlowFill = 0.f;
		FlowDrain = 0.f;
		PressureGroup = INDEX_NONE;
		PressureColumn = 0.f;

		Debug_PressureGroup = INDEX_NONE;
		Debug_DP = 0.f;
	}

public:
	FORCEINLINE ~FFluidBox() = default;
};

template<>
struct FACTORYGAME_API TStructOpsTypeTraits< FFluidBox > : public TStructOpsTypeTraitsBase2< FFluidBox >
{
	enum
	{
		WithSerializer = true,
		WithIdenticalViaEquality = true,
	};

public:
	FORCEINLINE ~TStructOpsTypeTraits< FFluidBox >() = default;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFGFluidIntegrantInterface : public UInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGFluidIntegrantInterface() = default;
};

/**
 * Interface for providing consistent access to all properties and components that will be needed to modify and update different aspects of fluid simulation across different buildables
 */
class FACTORYGAME_API IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	/** Returns a pointer the owners fluid box */
	virtual FFluidBox* GetFluidBox() = 0;

	/** Returns a TArray of pointers to all the owners pipe connections */
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() = 0;

	/** Notify that the network this fluid integrant belongs to has set its fluid descriptor */
	virtual void OnFluidDescriptorSet();

public:
	FORCEINLINE IFGFluidIntegrantInterface() = default;
};
