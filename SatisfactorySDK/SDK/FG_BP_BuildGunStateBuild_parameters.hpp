#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateBuild_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.BeginState
struct UBP_BuildGunStateBuild_C_BeginState_Params
{
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.EndState
struct UBP_BuildGunStateBuild_C_EndState_Params
{
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.SecondaryFire
struct UBP_BuildGunStateBuild_C_SecondaryFire_Params
{
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnActiveDescriptorChanged
struct UBP_BuildGunStateBuild_C_OnActiveDescriptorChanged_Params
{
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnMultiStepPlacement
struct UBP_BuildGunStateBuild_C_OnMultiStepPlacement_Params
{
	bool*                                              isFinalStep;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnResetHologram
struct UBP_BuildGunStateBuild_C_OnResetHologram_Params
{
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.PrimaryFire
struct UBP_BuildGunStateBuild_C_PrimaryFire_Params
{
};

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.ExecuteUbergraph_BP_BuildGunStateBuild
struct UBP_BuildGunStateBuild_C_ExecuteUbergraph_BP_BuildGunStateBuild_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
