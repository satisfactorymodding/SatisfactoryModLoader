// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGPoleHologram.h"
#include "FGConveyorPoleHologram.generated.h"

/**
 * Hologram for conveyor poles.
 */
UCLASS()
class FACTORYGAME_API AFGConveyorPoleHologram : public AFGPoleHologram
{
	GENERATED_BODY()
public:
	AFGConveyorPoleHologram();
	virtual void BeginPlay() override;

	/** Get the connections the conveyors snap to. */
	FORCEINLINE UFGFactoryConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

	/** Snap this pole's snap connection to to the given connection. */
	void SnapToConnection( UFGFactoryConnectionComponent* connection, class AFGConveyorBeltHologram* parentConveyor );

	void SetSnappBuilding( class AFGBuildable* snappedBuilding );
private:
	/** The connection conveyors snap to, used when placing a pole automatically. */
	UPROPERTY( )
	UFGFactoryConnectionComponent* mSnapConnection;

public:
	FORCEINLINE ~AFGConveyorPoleHologram() = default;
};
