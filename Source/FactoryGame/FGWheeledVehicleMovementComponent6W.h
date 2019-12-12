// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

/*
* Base VehicleSim for the 6W PhysX vehicle class
*/
#pragma once
#include "Array.h"
#include "UObject/Class.h"
#include "WheeledVehicleMovementComponent.h"
#include "Curves/CurveFloat.h"
#include "PhysicsPublic.h"
#include "PhysXPublic.h"
#include "FGWheeledVehicle.h"
#include "FGWheeledVehicleMovementComponent6W.generated.h"


/** Described which axles are powered by the engine. True == Powered. */
USTRUCT()
struct FDifferentialSetup6W
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY( EditAnywhere, Category = Setup )
	bool Front;

	UPROPERTY(EditAnywhere, Category = Setup)
	bool Mid;

	UPROPERTY(EditAnywhere, Category = Setup)
	bool Rear;
};

UENUM()
enum EWheelOrder6W
{
	eFRONT_LEFT=0,
	eFRONT_RIGHT,
	eMID_LEFT,
	eMID_RIGHT,
	eREAR_LEFT,
	eREAR_RIGHT,
};

USTRUCT()
struct FVehicleDifferential6WData
{
	GENERATED_USTRUCT_BODY()

	/** Type of differential */
	UPROPERTY(EditAnywhere, Category = Setup)
	FDifferentialSetup6W DifferentialConfig;
};

USTRUCT()
struct FVehicleEngineData6W
{
	GENERATED_USTRUCT_BODY()

	/** Torque (Nm) at a given RPM*/
	UPROPERTY(EditAnywhere, Category = Setup)
	FRuntimeFloatCurve TorqueCurve;

	/** Maximum revolutions per minute of the engine */
	UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MaxRPM;

	/** Moment of inertia of the engine around the axis of rotation (Kgm^2). */
	UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.01", UIMin = "0.01"))
	float MOI;

	/** Damping rate of engine when full throttle is applied (Kgm^2/s) */
	UPROPERTY(EditAnywhere, Category = Setup, AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DampingRateFullThrottle;

	/** Damping rate of engine in at zero throttle when the clutch is engaged (Kgm^2/s)*/
	UPROPERTY(EditAnywhere, Category = Setup, AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DampingRateZeroThrottleClutchEngaged;

	/** Damping rate of engine in at zero throttle when the clutch is disengaged (in neutral gear) (Kgm^2/s)*/
	UPROPERTY(EditAnywhere, Category = Setup, AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DampingRateZeroThrottleClutchDisengaged;

	/** Find the peak torque produced by the TorqueCurve */
	float FindPeakTorque() const;
};


USTRUCT()
struct FVehicleGearData6W
{
	GENERATED_USTRUCT_BODY()

	/** Determines the amount of torque multiplication*/
	UPROPERTY(EditAnywhere, Category = Setup)
	float Ratio;

	/** Value of engineRevs/maxEngineRevs that is low enough to gear down*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"), Category = Setup)
	float DownRatio;

	/** Value of engineRevs/maxEngineRevs that is high enough to gear up*/
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"), Category = Setup)
	float UpRatio;
};

USTRUCT()
struct FVehicleTransmissionData6W
{
	GENERATED_USTRUCT_BODY()
	/** Whether to use automatic transmission */
	UPROPERTY(EditAnywhere, Category = VehicleSetup, meta = (DisplayName = "Automatic Transmission"))
	bool bUseGearAutoBox;

	/** Time it takes to switch gears (seconds) */
	UPROPERTY(EditAnywhere, Category = Setup, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float GearSwitchTime;

	/** Minimum time it takes the automatic transmission to initiate a gear change (seconds)*/
	UPROPERTY(EditAnywhere, Category = Setup, meta = (editcondition = "bUseGearAutoBox", ClampMin = "0.0", UIMin = "0.0"))
	float GearAutoBoxLatency;

	/** The final gear ratio multiplies the transmission gear ratios.*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Setup)
	float FinalRatio;

	/** Forward gear ratios (up to 30) */
	UPROPERTY(EditAnywhere, Category = Setup, AdvancedDisplay)
	TArray<FVehicleGearData6W> ForwardGears;

	/** Reverse gear ratio */
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Setup)
	float ReverseGearRatio;

	/** Value of engineRevs/maxEngineRevs that is high enough to increment gear*/
	UPROPERTY(EditAnywhere, AdvancedDisplay, Category = Setup, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float NeutralGearUpRatio;

	/** Strength of clutch (Kgm^2/s)*/
	UPROPERTY(EditAnywhere, Category = Setup, AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float ClutchStrength;
};

UCLASS(meta = (BlueprintSpawnableComponent))
class UFGWheeledVehicleMovementComponent6W : public UWheeledVehicleMovementComponent
{
	// MODDING EDIT
	GENERATED_BODY() 
	UFGWheeledVehicleMovementComponent6W(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

	/** Engine */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup)
	FVehicleEngineData6W EngineSetup;

	/** Differential */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup)
	FVehicleDifferential6WData DifferentialSetup;
	
	/** Use Jace's super awesome custom gearbox or not */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup,  meta = (DisplayName = "Use Jace's special gearbox") )
	bool mUseDSOLGearbox;

	/** Max slope Angle Limit (in degrees) in order to use all of SlopeShiftRatio */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (ClampMin = "0.001") )
	float mDSOLMaxSlopeAngleLimit;

	/** Amount of ADDITIONAL required gear ratio in order to shift up or down, given a slope. The result is that on steep slopes, the vehicle will shift up at a higher ratio and shift down at a higher ratio. */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float mSlopeShiftRatio;

	/** Transmission data */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup)
	FVehicleTransmissionData6W TransmissionSetup;

	/** Multiplier for down shifting latency. Eg. it may be better to have a faster latency when downshifting */
	UPROPERTY(EditAnywhere, Category = MechanicalSetup, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float mDownShiftLatency;

	/** Maximum steering versus forward speed (km/h) */
	UPROPERTY(EditAnywhere, Category = SteeringSetup)
	FRuntimeFloatCurve SteeringCurve;

	/** Accuracy of Ackermann steer calculation (range: 0..1) */
	UPROPERTY(EditAnywhere, Category = SteeringSetup, AdvancedDisplay, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
	float AckermannAccuracy;

	virtual void Serialize(FArchive & Ar) override;
	virtual void ComputeConstants() override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	/** Overridden so we can take advantage of camber */
	virtual void GenerateTireForces(class UVehicleWheel* Wheel, const FTireShaderInput& Input, FTireShaderOutput& Output) override;

	/** Overridden so we can take advantage of camber */
	virtual void SetupWheelMassProperties_AssumesLocked(const uint32 NumWheels, physx::PxVehicleWheelsSimData* PWheelsSimData, physx::PxRigidBody* PVehicleActor) override;

	virtual void SetupWheels(physx::PxVehicleWheelsSimData* PWheelsSimData) override;

	virtual void PreTick( float DeltaTime ) override;

protected:
	virtual void SetupVehicleShapes() override;

	/** Allocate and setup the PhysX vehicle */
	virtual void SetupVehicleDrive(physx::PxVehicleWheelsSimData* PWheelsSimData) override;

	virtual void UpdateSimulation(float DeltaTime) override;

	/** update simulation data: engine */
	void UpdateEngineSetup(const FVehicleEngineData6W& NewEngineSetup);

	/** update simulation data: differential */
	void UpdateDifferentialSetup(const FVehicleDifferential6WData& NewDifferentialSetup);

	/** update simulation data: transmission */
	void UpdateTransmissionSetup(const FVehicleTransmissionData6W& NewGearSetup);

	/** returns the current largest tire load of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	float GetLargestTireLoadValue();

	/** returns the current largest lat slip of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	float GetLargestLateralSlip();

	/** returns the current largest long slip of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	float GetLargestLongitudinalSlip();

public:
	/** Returns true if we have pulled the handbreak of the vehicle */
	bool GetHandbreakInput() const;

private:
	/** Sets up the differential for 6W vehicle */
	void GetVehicleDifferential6WSetup(const FVehicleDifferential6WData& Setup, PxVehicleDifferentialNWData& PxSetup);

	/** Helper functions from PhysX */
	void SetupDriveHelper(UFGWheeledVehicleMovementComponent6W* VehicleData, const PxVehicleWheelsSimData* PWheelsSimData, PxVehicleDriveSimDataNW& DriveData);
	void GetVehicleEngineSetup(const FVehicleEngineData6W& Setup, PxVehicleEngineData& PxSetup);
	void GetVehicleAutoBoxSetup(const FVehicleTransmissionData6W& Setup, PxVehicleAutoBoxData& PxSetup);
	void GetVehicleGearSetup(const FVehicleTransmissionData6W& Setup, PxVehicleGearsData& PxSetup);

	/////////////////////////////////////
	//Begin Ackermann Steering Correction
	/////////////////////////////////////

	/** The ackermann related settings. */
	PxVehicleAckermannGeometryData mAckermannData;

	/** Sets ackermann data */
	void SetAckermannData( PxVehicleAckermannGeometryData& data ) { mAckermannData = data; }

	/** Max front and rear steer angle that was set in the editor. These are needed as we mess with these values in the vehicle in-game 
	    to achieve ackermann steering. These variables will preserve the initial values so we can use them in calculations. */
	float mFrontWheelMaxSteer;
	float mMidWheelMaxSteer;
	float mRearWheelMaxSteer;

	/** width from front axle to mid axle */
	float mMidAxleSeparation;

	/** Width between mid wheels */
	float mMidWidth;

	/** Ackermann steering correction implementation */
	void ComputeAckermannSteerAngles(const float steer, const float steerGain, const float ackermannAccuracy, const float width, const float axleSeparation, float* leftAckermannSteerAngle, float* rightAckermannSteerAngle);
	void ComputeAckermannCorrectedSteerAngles(PxVehicleDriveSimDataNW& driveSimData, PxVehicleWheelsSimData& wheelsSimData, const float steer);

	/////////////////////////////////////
	//End Ackermann Steering Correction
	/////////////////////////////////////

	/** Gearbox data that is tracked during simulation */
	DSOLDynGearboxData mDSOLDynGearboxData;

	/** Gearbox setup data */
	DSOLSetupData mDSOLSetupData;

	/** Array of PhysX User defineable data that are passed to the shader */
	TArray<FPhysxUserData> mPhysxUserData;

	// MODDING EDIT: PhysX not working
	///** Array of PhysXWheel User defineable data that are passed to the shader */
	//TArray<FPhysxWheelUserData> mPhysxWheelUserData;
};

