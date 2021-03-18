// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableLightSource.h"
#include "FGBuildableFloodlight.generated.h"

/**
 * Base class for the wall- and pole mounted floodlight.
 * The fixture to be angled need to be named LightFixture in the component list.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableFloodlight : public AFGBuildableLightSource
{
	GENERATED_BODY()
public:
	// Begin Actor
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End Actor
	
	/**
	 * Sets the fixture angle, input will be clamped to match the allowed adjustability.
	 * Note: Must be called prior to BeginPlay.
	 */
	void SetFixtureAngle( int32 angle );

public:
	static const FName FIXTURE_COMPONENT_NAME;
	
	static constexpr int32 MAX_FIXTURE_ANGLE = 60;
	static constexpr int32 MIN_FIXTURE_ANGLE = 0;
	
private:
	friend class AFGFloodlightHologram;
	
	/** Angle of the light fixture.  */
	UPROPERTY( SaveGame, Replicated, EditDefaultsOnly, Category = "Light" )
	int32 mFixtureAngle = 30;
};
