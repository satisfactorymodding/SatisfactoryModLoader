#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "WheeledVehicleMovementComponent4W.h"
#include "PhysicsPublic.h"
#include "PhysXPublic.h"
#include "FGWheeledVehicle.h"
#include "FGWheeledVehicleMovementComponent4W.generated.h"

UCLASS(meta = (BlueprintSpawnableComponent))
class FACTORYGAME_API UFGWheeledVehicleMovementComponent4W : public UWheeledVehicleMovementComponent4W
{
	GENERATED_BODY()
public:

	UFGWheeledVehicleMovementComponent4W(const FObjectInitializer& ObjectInitializer);

	/** Use Jace's super awesome custom gearbox or not */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (DisplayName = "Use Jace's special gearbox"))
	bool mUseDSOLGearbox;

	/** Max slope Angle Limit (in degrees) in order to use all of SlopeShiftRatio */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (ClampMin = "0.001"))
	float mDSOLMaxSlopeAngleLimit;

	/** Amount of ADDITIONAL required gear ratio in order to shift up or down, given a slope. The result is that on steep slopes, the vehicle will shift up at a higher ratio and shift down at a higher ratio. */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float mSlopeShiftRatio;

	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float mDownShiftLatency;

	/** Returns true if we have pulled the handbreak of the vehicle */
	bool GetHandbreakInput() const;

	/** Overrided update simulation to trigger DSOL gearbox if necessary */
	virtual void UpdateSimulation(float DeltaTime) override;

	/** Overridden so we can take advantage of camber */
	virtual void GenerateTireForces(class UVehicleWheel* Wheel, const FTireShaderInput& Input, FTireShaderOutput& Output) override;

	/** Overridden so we can take advantage of camber */
	virtual void SetupWheelMassProperties_AssumesLocked(const uint32 NumWheels, physx::PxVehicleWheelsSimData* PWheelsSimData, physx::PxRigidBody* PVehicleActor) override;

	virtual void SetupWheels(physx::PxVehicleWheelsSimData* PWheelsSimData) override;

	virtual void PreTick( float DeltaTime ) override;

protected:
	virtual void SetupVehicleShapes() override;

	/** returns the current largest tire load of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	float GetLargestTireLoadValue();

	/** returns the current largest lat slip of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	float GetLargestLateralSlip();

	/** returns the current largest long slip of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	float GetLargestLongitudinalSlip();

private:
	/** Gearbox data that is tracked during simulation */
	DSOLDynGearboxData mDSOLDynGearboxData;

	/** Gearbox setup data */
	DSOLSetupData mDSOLSetupData;

	/** Array of PhysX User defineable data that are passed to the shader */
	TArray<FPhysxUserData> mPhysxUserData;

	/** Array of PhysXWheel User defineable data that are passed to the shader */
	TArray<FPhysxWheelUserData> mPhysxWheelUserData;

public:
	FORCEINLINE ~UFGWheeledVehicleMovementComponent4W() = default;
};

