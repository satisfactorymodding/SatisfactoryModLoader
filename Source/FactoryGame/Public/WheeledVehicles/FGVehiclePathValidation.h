// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBlueprintFunctionLibrary.h"
#include "FGVehiclePathValidation.generated.h"

class AFGWheeledVehicle;
class USplineComponent;

UENUM( BlueprintType )
enum class EVehiclePathValidationResult : uint8
{
	/** Path is valid and can be traversed by a vehicle */
	Valid,
	/** There is a turn that is too sharp for the vehicle to turn with the minimum speed possible */
	TurnTooSharp,
	/** Path is not close enough to the ground */
	NoFloor,
	/* Terrain is too steep to support the vehicle driving */
	TerrainTooSteep,
	/** There is a static obstacle in a vehicle driving path */
	StaticObstacle,
	/** Shape of the vehicle path is not valid according to the build mode. Only used by the hologram visualization logic */
	InvalidShape,
	/** Vehicle is submerged in water */
	SubmergedInWater,
};

/** Result of vehicle path validation checking */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FVehiclePathValidationInfo
{
	GENERATED_BODY()

	/** Result of path validation */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Path Validation" )
	EVehiclePathValidationResult Result{EVehiclePathValidationResult::Valid};

	/** Distance to the location on the spline where vehicle validation failed */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Path Validation" )
	float SplineValidationFailDistance{0.0f};

	/** Virtual path length is the length of the path with regards to the height difference. Moving uphill will contribute towards more "distance" travelled than going straight or downhill for fuel consumption calculation */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Path Validation" )
	float VirtualPathLength{0.0f};

	friend bool operator==( const FVehiclePathValidationInfo& A, const FVehiclePathValidationInfo& B )
	{
		return A.Result == B.Result && A.SplineValidationFailDistance == B.SplineValidationFailDistance && A.VirtualPathLength == B.VirtualPathLength;
	}
};

/** Settings for the vehicle path traversal modeling & validation. Path traversal validation checks if the particular vehicle can navigate the proposed path */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FVehiclePathValidationConfig
{
	GENERATED_BODY()

	/** Vehicle class to calculate the wheel simulation data from */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	TSoftClassPtr<AFGWheeledVehicle> VehicleClass;

	/** Collision of the vehicle main static mesh for the purposes of path validation. Should not include wheels or suspension. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	FBox VehicleCollisionBox{ForceInit};

	/** Maximum angle that the vehicle can climb uphill (in degrees) */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float VehicleMaxClimbAngle{40.0f};

	/** How long the path should be at minimum for the vehicle to make a full 90 degrees turn? Bigger vehicles generally have larger turn radii */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float VehicleTurnRadius{500.0f};

	/** Maximum amount (in cm) the suspension can raise from the idle position to help the vehicle overcome an ongoing obstacle when self-driving */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float SuspensionMaxRaise{100.0f};

	/** Maximum amount (in cm) the suspension can drop from the idle position to help the vehicle adjust to the terrain elevation difference between the wheels */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float SuspensionMaxDrop{200.0f};

	/** Maximum climb angle for individual wheels of the vehicle. This determines when the vehicle can roll over small obstacles and when it cannot */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float WheelMaxClimbAngle{60.0f};

	/** Elevation of the wheel sweep over the terrain. Allows vehicles to pass over small obstacles even if they are too steep for the wheels to climb */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float WheelSweepElevation{40.0f};

	/** Distance (in cm) over which vehicle suspension will smooth out the changes in the vehicle roll (banking) */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float VehicleSuspensionRollSmoothingDistance{200.0f};

	/** Maximum angle (in degrees) that the vehicle will be allowed to roll without toppling over. Keep in mind that other validation rules usually limit this to a much lower value than specified here */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	float MaximumVehicleBankingAngle{50.0f};

	/** A curve that, given climb angle in degrees in range [0;90), returns a multiplier that should be applied to a distance traveled by the vehicle for purposes of fuel consumption calculation */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Path Validation" )
	TObjectPtr<UCurveFloat> VehicleClimbAngleDistanceScaleCurve;
};

UCLASS( Config = "Game" )
class FACTORYGAME_API UFGVehiclePathValidation : public UFGBlueprintFunctionLibrary
{
	GENERATED_BODY()
protected:
	/** Step size to advance the vehicle movement/pathing simulation at a time */
	UPROPERTY( Config )
	float mVehicleSimulationStep{50.0f};
public:
	/**
	 * Validates that the vehicle can fully traverse the given spline from 0 to the spline length
	 * @param splineComponent spline component to evaluate as vehicle path
	 * @param pathValidationConfig vehicle configuration for path traversal
	 * @return result of path traversal validation
	 */
	UFUNCTION( BlueprintCallable, Category = "Path Validation" )
	static FVehiclePathValidationInfo ValidateVehiclePathSegment( const USplineComponent* splineComponent, const FVehiclePathValidationConfig& pathValidationConfig, float debugDrawLifetime );
};
