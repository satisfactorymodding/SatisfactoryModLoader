#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_NobeliskDetonator_R_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.UserConstructionScript
struct AAttach_NobeliskDetonator_R_C_UserConstructionScript_Params
{
};

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnIsLoadedSet
struct AAttach_NobeliskDetonator_R_C_OnIsLoadedSet_Params
{
};

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.PlayFireEffect
struct AAttach_NobeliskDetonator_R_C_PlayFireEffect_Params
{
	struct FVector*                                    flashLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnBeginFireEffect
struct AAttach_NobeliskDetonator_R_C_OnBeginFireEffect_Params
{
	struct FVector*                                    Location;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.ClientPlayReloadEffect
struct AAttach_NobeliskDetonator_R_C_ClientPlayReloadEffect_Params
{
};

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnAttach
struct AAttach_NobeliskDetonator_R_C_OnAttach_Params
{
};

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.ExecuteUbergraph_Attach_NobeliskDetonator_R
struct AAttach_NobeliskDetonator_R_C_ExecuteUbergraph_Attach_NobeliskDetonator_R_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
