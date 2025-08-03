// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGRailroadSwitchControlHologram.generated.h"

/**
 * Hologram for switch controls placed at junctions.
 *
 * Note: This is only intended to be used as a child hologram so no other functions than for that purpose is implemented.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadSwitchControlHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

	friend class FGBlueprintOpenRailroadConnectionManager;
public:
	/**
	 * This have the same responsibilities as SetHologramLocationAndRotation but is specific to this child hologram.
	 *
	 * @param controlledConnection    The connection that this switch will control,
	 *                                this is typically a connection we snap to that already have a connection.
	 *                                Cannot be null.
	 */
	void SetHologramLocationAndRotationFromConnection( class UFGRailroadTrackConnectionComponent* controlledConnection );

	/** The the controlled connection, might be null if SetHologramLocationAndRotationFromConnection has not been called. */
	class UFGRailroadTrackConnectionComponent* GetControlledConnection() const { return mControlledConnection; }
	
protected:
	// Begin AFGHologram
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void CheckClearance() override;
	virtual void CheckValidFloor() override;
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FTransform& hologramTransform ) const override;
	// End AFGHologram

private:
	UPROPERTY( CustomSerialization )
	class UFGRailroadTrackConnectionComponent* mControlledConnection;
};
