#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Machinegun_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_Machinegun.Attach_Machinegun_C.UserConstructionScript
struct AAttach_Machinegun_C_UserConstructionScript_Params
{
};

// Function Attach_Machinegun.Attach_Machinegun_C.PlayFireEffect
struct AAttach_Machinegun_C_PlayFireEffect_Params
{
	struct FVector*                                    flashLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Attach_Machinegun.Attach_Machinegun_C.ClientPlayReloadEffect
struct AAttach_Machinegun_C_ClientPlayReloadEffect_Params
{
};

// Function Attach_Machinegun.Attach_Machinegun_C.ExecuteUbergraph_Attach_Machinegun
struct AAttach_Machinegun_C_ExecuteUbergraph_Attach_Machinegun_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
