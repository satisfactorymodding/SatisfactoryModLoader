// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGBuildableWall.h"
#include "FGBuildablePoweredWall.generated.h"

/**
 * A wall with a power socket, provides the whole building with power.
 * @todoG2 clean this out along with the foundation subsystem.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildablePoweredWall : public AFGBuildableWall
{
	GENERATED_BODY()
public:
	/** Adds a connection from a building to the walls internal (hidden) connection. */
	void AddConnection( class UFGPowerConnectionComponent* connection );

protected:
	/**
	 * @return The hidden connection all buildings are supposed to connect to; otherwise nullptr, e.g. if not set up correcly.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "PoweredWall" )
	class UFGPowerConnectionComponent* GetFoundationConnection() const;

public:
	FORCEINLINE ~AFGBuildablePoweredWall() = default;
};
