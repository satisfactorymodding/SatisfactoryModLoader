// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "../FGCircuitConnectionComponent.h"
#include "FGPowerPoleHologram.generated.h"

/**
* Hologram for power poles.
*/
UCLASS()
class FACTORYGAME_API AFGPowerPoleHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

private:
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;
};
