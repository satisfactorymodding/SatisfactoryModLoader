// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGNetSignificanceInterface.generated.h"


/**
 * Interface for actors and components that can be part of server-side significance octree
 * Net significance is handled by the server but is also simulated locally for clients, and objects receive
 * net significance when they are relevant to any player on the server in multiplayer,
 * or to the local player when playing as a client
 * Objects must be registered to the significance octree to receive net significance via UFGBlueprintFunctionLibrary::AddToServerSideSignificanceOctTree
 * and removed on EndPlay via UFGBlueprintFunctionLibrary::RemoveFromServerSideSignificanceOctTree
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGNetSignificanceInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGNetSignificanceInterface
{
	GENERATED_BODY()
public:
	/** Returns the range for net significance of this object */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	float GetNetSignificanceRange() const;
	
	/** Called when server-side significance of the object is gained, e.g. there is a local or remote player close by. Object needs to be registered to server side significance via UFGBlueprintFunctionLibrary::AddToServerSideSignificanceOctTree */
	UFUNCTION(BlueprintNativeEvent, Category="Significance")
	void GainedNetSignificance();

	/** Called when server-side significance of the object is lost, e.g. no players are close by to it in the networked game */
	UFUNCTION(BlueprintNativeEvent, Category="Significance")
	void LostNetSignificance();
};
