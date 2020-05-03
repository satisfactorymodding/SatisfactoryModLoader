// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Resources/FGItemDescriptor.h"
#include "FGSaveInterface.h"
#include "FGFluidIntegrantInterface.h"
#include "FGPipeNetwork.generated.h"

// Draw text or boxes debug mode.
enum class EDebugPipeVisualization
{
	DPV_None,
	DPV_Text,
	DPV_Pressure,
	DPV_PressureGroup,
	DPV_DeltaPressure,
	DPV_Flow
};

/**
 * Contains all info needed to update a fluid box.
 */
struct FACTORYGAME_API PipeJunction
{
	PipeJunction( class UFGPipeConnectionComponent* previous, class UFGPipeConnectionComponent* current );

	struct FFluidBox* PreviousBox = nullptr;
	struct FFluidBox* CurrentBox = nullptr;

	// The Z height where the outflow is located in relation between the previous and current pipe. [meters]
	float PreviousOutflowZ = 0.f;
	float CurrentOutflowZ = 0.f;

	// Controls one way fluid movements, e.g. pumps and reservoirs.
	float PreviousOneWayModifier = 1.f;
	float CurrentOneWayModifier = 1.f;

	/**
	 * The flow and moved content from current to previous in this junction pair.
	 * A positive flow, and move, is from the previous box to into the current box.
	 * Units for the flow is m^3/s.
	 */
	float Flow = 0.f;
	float MovedContent = 0.f;

	//@todoPipes WITH_EDITORONLY_DATA
	FVector Debug_Location;
	FString Debug_Name;
	FString Debug_String;

public:
	FORCEINLINE ~PipeJunction() = default;
};

/**
 * A pipe network is responsible for a group of connected pipes and their fluid simulations.
 */
UCLASS()
class FACTORYGAME_API AFGPipeNetwork : public AInfo, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	// Begin AActor
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( EEndPlayReason::Type endPlayReason ) override;
	// End AActor

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Should the subsystem tick this network? */
	bool ShouldTickNetwork() const;
	
	/** Run the simulation on the networks junctions and fluid boxes */
	void UpdateSimulation( float dt );

	/** Get the id for this network. */
	int32 GetPipeNetworkID() const;
	void SetPipeNetworkID( int32 id );

	/** Get the type of fluid in this network. */
	TSubclassOf< UFGItemDescriptor > GetFluidDescriptor() const { return mFluidDescriptor; }

	/** Functions to manage this network, called by the subsystem. */
	void AddFluidIntegrant( class IFGFluidIntegrantInterface* fluidIntegrant );
	void RemoveFluidIntegrant( class IFGFluidIntegrantInterface* fluidIntegrant );
	int32 NumFluidIntegrants() const;
	void MergeNetworks( class AFGPipeNetwork* network );
	void RemoveAllFluidIntegrants();

	/** Get the first pipe in the pipeline, all other pipes should be reachable from this one. */
	class IFGFluidIntegrantInterface* GetFirstFluidIntegrant();

	/** 
	 * Assign a fluid descriptor to this network. Will fail if one is already specified.
	 * The effects of the change won't occur until the next tick when the network is rebuilt
	 */
	void TrySetFluidDescriptor( TSubclassOf< UFGItemDescriptor > newItemDescriptor );
	/** Propagate fluid descriptor from another network, does nothing if this network already have a descriptor. */
	void TryPropagateFluidDescriptorFrom( class AFGPipeNetwork* network );

	/**
	* Flush a single integrant in this network ( does not reset the fluid descriptor as that is per network )
	*/
	void FlushIntegrant( class IFGFluidIntegrantInterface* );

	/**
	 * Flush a network of all contents and remove its fluid descriptor
	 */
	void FlushNetwork();

	/** Manage rebuilding networks. */
	void MarkForFullRebuild();
	bool NeedFullRebuild() const;

	/** Callback for when this network has been rebuilt. */
	void OnFullRebuildCompleted();

	/** Debug */
	void Debug_DisplayDetails( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos, float indent );
	void Debug_PipeVisualization( EDebugPipeVisualization mode );
private:
	struct FPressureGroup
	{
		/** If valid, use the redirected groups values instead of this one. */
		int32 Redirect = INDEX_NONE;

		/** World Z values for different pressure points in meters, NOT unreal units. */
		float HighestPumpZ = -1000000.f;
		float HighestElevationZ = -1000000.f;
	};

	void RebuildUpdateList();

	void UpdateFluidDescriptor( TSubclassOf< UFGItemDescriptor > descriptor );

	int32 CreatePressureGroup();
	int32 FindTopMostPressureGroupIndex( int32 index );
	void UpdatePressureGroups( PipeJunction& junction, float dt );
	void UpdatePressure( PipeJunction& junction, float dt );
	void PostUpdatePressureGroups( PipeJunction& junction );
	void PreUpdateFlow( PipeJunction& junction );
	void UpdateFlow( PipeJunction& junction, float dt );
	void UpdateContent( PipeJunction& junction, float dt );

private:
	friend class UFGCheatManager;

	static constexpr float QUARTER_RULE = 0.25f;

	/**
	 * Unique id of this network, assigned at spawn.
	 * Note: This is not persistent between play sessions.
	 */
	UPROPERTY( SaveGame, Replicated )
	int32 mPipeNetworkID;

	/** The type of liquid in this network. */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf< UFGItemDescriptor > mFluidDescriptor;

	/** When a buildable attempts to move inventory to a pipe network as a fluid, it will first set the pending fluid descriptor
	*	On the next subsystem tick, this network will be marked for rebuild and will assign each connection this descriptor 
	*	The reason for not setting it directly is in case multiple buildables attempt to add different resource types in the same frame
	*/
	UPROPERTY()
	TSubclassOf< UFGItemDescriptor > mPendingFluidDescriptor;

	/** Cached constants for easy access. */
	float mFluidDensity;		// Around 1 is good for water,
	float mFluidViscosity;		// Around 1 is good for water, higher for oils, lower for gases.
	float mGravity;				// [m/s^2]
	float mFluidFriction;

	/** All Fluid Integrant Interfaces in this network */
	TArray< class IFGFluidIntegrantInterface* > mFluidIntegrants;

	/** Compiled during save, and Interface classes are extracted on load. Stores the mFluidIntegrants in a UPROPERTY type */
	UPROPERTY( SaveGame )
	TArray < TScriptInterface< class IFGFluidIntegrantInterface > > mFluidIntegrantScriptInterfaces;

	/**
	 * All Junctions we need to tick each frame
	 * A junction represents the point of connection between three FGPipeConnectionComponents
	 */
	TArray< PipeJunction > mUpdateList;

	/** If the update list is not up to date */
	bool mRebuildUpdateList;
	/** Does this pipe line needs a full rebuild. */
	bool mNeedFullRebuild;
	/** Does this network need to reassign its Fluid Desc to all connections ( needed after performing a rebuild ) */
	bool mForceFluidDescriptorUpdate;

	/**
	 * Intermediate products used to propagate the pressure. 
	 * See comments in implementation for details.
	 */
	TArray< FPressureGroup > mPressureGroups;

public:
	FORCEINLINE ~AFGPipeNetwork() = default;
};
