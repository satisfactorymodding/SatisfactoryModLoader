// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGSignificanceInterface.generated.h"

/**
 * Interface for actors that are handled by UFGSignificanceManager.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGSignificanceInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	/** Call when actor gained significance for the local player. Will not be fired for dedicated servers. Actor must be registered via USignificanceManagerAccelerated::RegisterStaticObject */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void GainedSignificance();

	/** Call when actor gained significance for the local players. Will not be fired for dedicated servers */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void LostSignificance();

	/** Will be called to update the object with the throttled tick rate and enable/disable tick based on the local player proximity and number of tick levels */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void UpdateSignificanceTickRate( float NewTickRate, bool bTickEnabled );

	/**
	 * Called before the object is added to the significance manager for local player. Only called when using significance functions in UFGBlueprintFunctionLibrary, such as AddGenericTickObjectToSignificanceManager.
	 * Can be used for bounding box setup, etc.
	 * TODO @Ben @Nick: Do we need this function as a separate API? Could we just move logic inside of it to BeginPlay?
	 */
	virtual void SetupForSignificance();

	/** Called to determine the object significance for local player. Range Defaults to 10000.0 if zero is provided in this function, or to the value provided to the registration functions in UFGBlueprintFunctionLibrary */
	virtual float GetSignificanceRange();

	/** Determines whenever the object needs UpdateSignificanceTickRate calls dispatched to it. As of now, never called, always assumed TRUE. TODO @Ben */
	virtual bool DoesReduceTick() const { return false; };

	/** Returns a number of tick levels this actor has for distance-based tick throttle. Each level exponentially reduces the tick rate */
	virtual int32 NumTickLevels() const { return 0; };
	/** Returns the exponent for the tick. As of right now, the value is NOT USED, and is always assumed to be 1.0f. TODO @Ben */
	virtual float GetTickExponent() const { return 1.0f; }

	/** Called when server-side significance of the object is gained, e.g. there is a local or remote player close by. Object needs to be registered to server side significance via UFGBlueprintFunctionLibrary::AddToServerSideSignificanceOctTree */
	UFUNCTION(BlueprintNativeEvent, Category="Significance")
	void GainedNetSignificance();

	/** Called when server-side significance of the object is lost, e.g. no players are close by to it in the networked game */
	UFUNCTION(BlueprintNativeEvent, Category="Significance")
	void LostNetSignificance();

	/** Called to notify the actor of the initial significance state it has after a call to USignificanceManagerAccelerated::RegisterStaticObject during BeginPlay */
	virtual void SetInitialState(bool bState) {}
};
