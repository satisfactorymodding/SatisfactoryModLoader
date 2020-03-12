// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "FGPipeHyperInterface.generated.h"

class AFGBuildablePipeBase;
class UFGPipeConnectionComponentBase;
class UFGCharacterMovementComponent;

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGPipeHyperInterface : public UInterface
{
	
    GENERATED_BODY()
    UFGPipeHyperInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGPipeHyperInterface() = default;
};

/**
 * Actors attached that implement this interface will be considered by the chainsaw to be HyperTube.
 */
class FACTORYGAME_API IFGPipeHyperInterface
{
	GENERATED_IINTERFACE_BODY()

public:

/* @returns the progress along the pipe of the given connection (if the component is part of this obejct, otherwise the resturn value is undefined)*/
	UFUNCTION( BlueprintNativeEvent, Category = "Hyper Tube" )
	float GetPipeProgressOfConnection( const UFGPipeConnectionComponentBase* connectionEnteredThrough );


	/** OnPipeTransit
	* Called ever frame character is inside a pipe. Will be responsible for moving the character position and updating velocity and such.
	* Is responsible for handling transits to other hipes or similar things too.

	* @param	charMove - character movement component that is transiting
	* @param	connectionEnteredThrough - if transiting through a connection on this object, it will be here. Can be null if we transit from outside a pipe system (like and entrance)
	* @param	fromPipe - if we transited from a pipe, it will be sent here. Will be null otherwise
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "Hyper Tube" )
	void OnPipeMove( UFGCharacterMovementComponent* charMove, float deltaTime );



	/** OnPipeTransit
	* Called when entering a pipe object. Assumes if you are coming from a pipe that the movement components pipe progress and velocity represents traveling in the positive direction

	* @param	charMove - character movement component that is transiting
	* @param	connectionEnteredThrough - if transiting through a connection on this object, it will be here. Can be null if we transit from outside a pipe system (like and entrance)
	* @param	fromPipe - if we transited from a pipe, it will be sent here. Will be null otherwise
	*
	* @returns true if successful, otherwise the pipe is not a valid target to enter at the moment
	*/
	UFUNCTION(  BlueprintNativeEvent, Category = "Hyper Tube" )
	bool OnPipeEnter( UFGCharacterMovementComponent* charMove, const UFGPipeConnectionComponentBase* connectionEnteredThrough = nullptr, const AActor* fromPipe = nullptr );

public:
	FORCEINLINE IFGPipeHyperInterface() = default;
};
