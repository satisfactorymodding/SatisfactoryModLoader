#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ClothingSystemRuntime_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function ClothingSystemRuntime.ClothingSimulationInteractorNv.SetAnimDriveSpringStiffness
struct UClothingSimulationInteractorNv_SetAnimDriveSpringStiffness_Params
{
	float                                              InStiffness;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ClothingSystemRuntime.ClothingSimulationInteractorNv.SetAnimDriveDamperStiffness
struct UClothingSimulationInteractorNv_SetAnimDriveDamperStiffness_Params
{
	float                                              InStiffness;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function ClothingSystemRuntime.ClothingSimulationInteractorNv.EnableGravityOverride
struct UClothingSimulationInteractorNv_EnableGravityOverride_Params
{
	struct FVector                                     InVector;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function ClothingSystemRuntime.ClothingSimulationInteractorNv.DisableGravityOverride
struct UClothingSimulationInteractorNv_DisableGravityOverride_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
