// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGBuildableSubsystem.h"
#include "Engine/NetConnection.h"
#include "FGConstructionMessageInterface.h"
#include "FGNetConstructionFunctionLibrary.generated.h"

/**
 * Function library for everything related to net construction
 */
UCLASS()
class FACTORYGAME_API UFGNetConstructionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FNetworkGUID GetNetworkGUID( const UNetDriver* netDriver, class UObject* netObject );
	static UObject* GetObjectFromNetGUID( const UNetDriver* netDriver, const FNetConstructionID& id, const FNetworkGUID& objectGUID );

	static bool IsClient( class UNetDriver* netDriver ) { return netDriver->ServerConnection != nullptr; }
};