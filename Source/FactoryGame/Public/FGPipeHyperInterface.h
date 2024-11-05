// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGPipeHyperInterface.generated.h"

class AFGBuildablePipeBase;
class UFGPipeConnectionComponentBase;
class UFGCharacterMovementComponent;
class AFGCharacterPlayer;
struct FPlayerPipeHyperData;

/** Base struct to be used as a parent for all pipe data structs used by the implementers of IFGPipeHyperInterface */
USTRUCT(BlueprintType)
struct FFGPipeHyperBasePipeData
{
	GENERATED_BODY()

	UPROPERTY()
	bool bDummy;
};

UINTERFACE( meta = (CannotImplementInterfaceInBlueprint) )
class FACTORYGAME_API UFGPipeHyperInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

enum class EPipeHyperEnterResult
{
	/** Pipe should be entered normally */
	PHR_Success,
	/** Pipe could not be entered, the player should turn back */
	PHR_TurnBack,
	/** Pipe could not be entered, the player should be ejected as if nothing was connected to the pipe */
	PHR_Eject,
	/** Pipe could not be entered, player should be ragdolled and exited through ForcePipeHyperExit */
	PHR_ForceExit,
};

class FACTORYGAME_API IFGPipeHyperInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	/**
	 * Returns a list of all possible connections that can serve as exits if the player has entered through the provided connection
	 * Used for traversing the pipe network when searching for valid junctions ahead of character
	 */
	virtual TArray<TPair<UFGPipeConnectionComponentBase*, float>> GetPossibleConnectionsToTransitionThrough(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough) const = 0;
	
	/**
	 * Called when the pipe is actually being entered and becomes the current hypertube. Note that it's called *earlier* than the interpolation actually moves the player into that pipe
	 * Keep in mind that the system will *not* save connectionEnteredThrough for you! If you need to access it later, you need to
	 * use the pipe data struct and save it there by yourself.
	 *
	 * @param outPipeData custom data that you can use to persist any state on the player, valid as long as the player is in the tube
	 * @param predictionPipeData custom data that was derived from FindDistanceClosestToWorldLocation when we are simulating the movement for simulated proxies, empty otherwise
	 * @return true if player is allowed to enter the pipe, false if he should be turned back
	 */
	virtual EPipeHyperEnterResult OnPipeEnterReal(AFGCharacterPlayer* charPlayer, UFGPipeConnectionComponentBase* connectionEnteredThrough, TStructOnScope<FFGPipeHyperBasePipeData>& outPipeData, const TStructOnScope<FFGPipeHyperBasePipeData>& predictionPipeData ) = 0;

	/**
	 * Called when the pipe has been entered during the sub-step interpolation
	 * This would always happen after OnPipeEnterReal has been called.
	 **/
	virtual void OnPipeEnterInterpolated(AFGCharacterPlayer* charPlayer, TStructOnScope<FFGPipeHyperBasePipeData>& pipeData) {}

	/** Returns the length of the pipe spline, serves as maximum valid value for distance passed to GetLocationAndRotationAlongPipe and GetConnectionToTransitThrough */
	virtual float GetLengthAlongPipe(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData) = 0;

	/**
	 * Called every hyper pipe movement logic simulation step right after the normal velocity calculations are applied
	 * Gives the pipe part the additional opportunity to directly influence the travel velocity and minimum speed
	 * FPlayerPipeHyperData provided here is only for information querying purpose and is never intended to be modified directly outside of the player movement component
	 * Note! Not called when traveling outside of pipe boundaries during the pending eject
	 * 
	 * @param stepLength length of the simulation step
	 */
	virtual void OnPipeMoveStep(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float stepLength, const FPlayerPipeHyperData& pipeTravelData, float& pipeVelocityReal, float& pipeTempMinSpeed ) { }
	
	/** Retrieves location and rotation when travelling along the pipe at the particular distance (0 - <PipeLength>) */
	virtual void GetLocationAndRotationAlongPipe(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, FVector& outLocation, FVector& outDirection ) = 0;

	/**
	 * This function attempts to find the closest point inside of this pipe to the world location provided,
	 * and also potentially synthesize the pipe data struct matching to the player moving inside of this pipe at the specified location with specified velocity
	 * @return true if the approximation was successful
	 */
	virtual bool FindDistanceClosestToWorldLocation(AFGCharacterPlayer* charPlayer, const FVector& worldLocation, const FVector& velocity, TStructOnScope<FFGPipeHyperBasePipeData>& out_pipeData, float& out_distance) const = 0;
	
	/**
	 * Returns the exit connection that the player must transit through when passing the provided distance.
	 * Only called at the ends of the pipe, e.g. when travel distance exceeds pipe length of goes below zero
	 */
	virtual UFGPipeConnectionComponentBase* GetConnectionToTransitThrough(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData, float distance, float& outExitOffset ) = 0;

	/**
	 * Called when the pipe has actually been exited, but can still get interpolated during sub-step interpolation later on
	 * That means the pipe data will be still kept around until OnPipeExitInterpolated has been called
	 * Keep in mind that because of that, the player can still visually be in the pipe when this function is called.
	 */
	virtual void OnPipeExitReal(AFGCharacterPlayer* charPlayer, TStructOnScope<FFGPipeHyperBasePipeData>& pipeData) {}
	
	/**
	 * Called when pipe has been fully exited by the sub-step interpolation
	 * Will always be called after OnPipeExitReal has been called.
	 * After this function is called, the pipe data struct for this pipe will be thrashed.
	 */
	virtual void OnPipeExitInterpolated(AFGCharacterPlayer* charPlayer, const TStructOnScope<FFGPipeHyperBasePipeData>& pipeData ) {}
};
