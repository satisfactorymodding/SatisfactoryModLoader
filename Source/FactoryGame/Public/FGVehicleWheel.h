// Copyright 2016 Coffee Stain Studios. All Rights Reserved.
#pragma once
#include "UObject/Class.h"
#include "PhysxUserData.h"
#include "VehicleWheel.h"
#include "FGVehicleWheel.generated.h"

#if WITH_PHYSX
#include "PhysXPublic.h"
#endif

UCLASS(BlueprintType, Blueprintable)
class FACTORYGAME_API UFGVehicleWheel : public UVehicleWheel
{
	GENERATED_BODY()

public:
	UFGVehicleWheel();

	/** Creates and cooks a cylinder wheel mesh */
	static PxConvexMesh* CreateWheelMesh(const PxF32 width, const PxF32 radius, PxPhysics& physics, PxCooking& cooking);

public:
	/** Set to true if a rear wheel. This can result in custom functionality for rear wheels. */
	UPROPERTY(EditDefaultsOnly, Category=Wheel)
	bool mInvertSteering;

	/** Automatically generates a perfect collision cylinder that matches the wheel's dimensions. */
	UPROPERTY(EditDefaultsOnly, Category = Wheel)
	bool mAutoGenerateCollisionCylinder;

	// MODDING EDIT
	///** PhysXWheel User defineable data that is passed to the shader */
	//FPhysxWheelUserData mPhysxWheelUserData;

	/** PhysX User defineable data that is passed to the shader */
	FPhysxUserData mPhysxUserData;

	/** Wheel camber angle IN DEGREES */
	UPROPERTY(EditDefaultsOnly, Category=Wheel)
	float mCamberAtRest;

	/** Wheel camber angle IN DEGREES */
	UPROPERTY(EditDefaultsOnly, Category = Wheel)
	float mCamberAtMaxCompression;

	/** Wheel camber angle IN DEGREES */
	UPROPERTY(EditDefaultsOnly, Category = Wheel)
	float mCamberAtMaxDroop;

	/** camber stiffness. measured in radians per kg... or something. */
	UPROPERTY(EditDefaultsOnly, Category = Wheel, meta=( ClampMin = "1.0", UIMin = "1.0" ))
	float mCamberStiffness;

	/** Taken from PxVehicleComputeTireForceDefault in WheeledVehicleMovementComponent.cpp */

	////////////////////////////////////////////////////////////////////////////
	//Default tire force shader function.
	//Taken from Michigan tire model.
	//Computes tire long and lat forces plus the aligning moment arising from 
	//the lat force and the torque to apply back to the wheel arising from the 
	//long force (application of Newton's 3rd law).
	////////////////////////////////////////////////////////////////////////////
	void ComputeTireForce
	(const void* tireShaderData,
		const PxF32 tireFriction,
		const PxF32 longSlip, const PxF32 latSlip, const PxF32 camber,
		const PxF32 wheelOmega, const PxF32 wheelRadius, const PxF32 recipWheelRadius,
		const PxF32 restTireLoad, const PxF32 normalisedTireLoad, const PxF32 tireLoad,
		const PxF32 gravity, const PxF32 recipGravity,
		PxF32& wheelTorque, PxF32& tireLongForceMag, PxF32& tireLatForceMag, PxF32& tireAlignMoment);

	static class UTireConfig* GetDefaultTireConfig();
};
