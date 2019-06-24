#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_PhysXVehicles_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetUseAutoGears
struct UWheeledVehicleMovementComponent_SetUseAutoGears_Params
{
	bool                                               bUseAuto;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetThrottleInput
struct UWheeledVehicleMovementComponent_SetThrottleInput_Params
{
	float                                              Throttle;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetTargetGear
struct UWheeledVehicleMovementComponent_SetTargetGear_Params
{
	int                                                GearNum;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bImmediate;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetSteeringInput
struct UWheeledVehicleMovementComponent_SetSteeringInput_Params
{
	float                                              Steering;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetHandbrakeInput
struct UWheeledVehicleMovementComponent_SetHandbrakeInput_Params
{
	bool                                               bNewHandbrake;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetGroupsToIgnoreMask
struct UWheeledVehicleMovementComponent_SetGroupsToIgnoreMask_Params
{
	struct FNavAvoidanceMask                           GroupMask;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetGroupsToIgnore
struct UWheeledVehicleMovementComponent_SetGroupsToIgnore_Params
{
	int                                                GroupFlags;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetGroupsToAvoidMask
struct UWheeledVehicleMovementComponent_SetGroupsToAvoidMask_Params
{
	struct FNavAvoidanceMask                           GroupMask;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetGroupsToAvoid
struct UWheeledVehicleMovementComponent_SetGroupsToAvoid_Params
{
	int                                                GroupFlags;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetGearUp
struct UWheeledVehicleMovementComponent_SetGearUp_Params
{
	bool                                               bNewGearUp;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetGearDown
struct UWheeledVehicleMovementComponent_SetGearDown_Params
{
	bool                                               bNewGearDown;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetBrakeInput
struct UWheeledVehicleMovementComponent_SetBrakeInput_Params
{
	float                                              Brake;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetAvoidanceGroupMask
struct UWheeledVehicleMovementComponent_SetAvoidanceGroupMask_Params
{
	struct FNavAvoidanceMask                           GroupMask;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetAvoidanceGroup
struct UWheeledVehicleMovementComponent_SetAvoidanceGroup_Params
{
	int                                                GroupFlags;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.SetAvoidanceEnabled
struct UWheeledVehicleMovementComponent_SetAvoidanceEnabled_Params
{
	bool                                               bEnable;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.ServerUpdateState
struct UWheeledVehicleMovementComponent_ServerUpdateState_Params
{
	float                                              InSteeringInput;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              InThrottleInput;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              InBrakeInput;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              InHandbrakeInput;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                CurrentGear;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetUseAutoGears
struct UWheeledVehicleMovementComponent_GetUseAutoGears_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetThrottle
struct UWheeledVehicleMovementComponent_GetThrottle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetTargetGear
struct UWheeledVehicleMovementComponent_GetTargetGear_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetForwardSpeed
struct UWheeledVehicleMovementComponent_GetForwardSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetEngineRotationSpeed
struct UWheeledVehicleMovementComponent_GetEngineRotationSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetEngineMaxRotationSpeed
struct UWheeledVehicleMovementComponent_GetEngineMaxRotationSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.WheeledVehicleMovementComponent.GetCurrentGear
struct UWheeledVehicleMovementComponent_GetCurrentGear_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.SimpleWheeledVehicleMovementComponent.SetSteerAngle
struct USimpleWheeledVehicleMovementComponent_SetSteerAngle_Params
{
	float                                              SteerAngle;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                WheelIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.SimpleWheeledVehicleMovementComponent.SetDriveTorque
struct USimpleWheeledVehicleMovementComponent_SetDriveTorque_Params
{
	float                                              DriveTorque;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                WheelIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.SimpleWheeledVehicleMovementComponent.SetBrakeTorque
struct USimpleWheeledVehicleMovementComponent_SetBrakeTorque_Params
{
	float                                              BrakeTorque;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                WheelIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function PhysXVehicles.VehicleAnimInstance.GetVehicle
struct UVehicleAnimInstance_GetVehicle_Params
{
	class AWheeledVehicle*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.VehicleWheel.IsInAir
struct UVehicleWheel_IsInAir_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.VehicleWheel.GetSuspensionOffset
struct UVehicleWheel_GetSuspensionOffset_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.VehicleWheel.GetSteerAngle
struct UVehicleWheel_GetSteerAngle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function PhysXVehicles.VehicleWheel.GetRotationAngle
struct UVehicleWheel_GetRotationAngle_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
