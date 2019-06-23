#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_NobeliskDetonator_L_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.UserConstructionScript
struct AAttach_NobeliskDetonator_L_C_UserConstructionScript_Params
{
};

// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.ClientPlayReloadEffect
struct AAttach_NobeliskDetonator_L_C_ClientPlayReloadEffect_Params
{
};

// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.PlayFireEffect
struct AAttach_NobeliskDetonator_L_C_PlayFireEffect_Params
{
	struct FVector*                                    flashLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.PlayAttachEffects3P
struct AAttach_NobeliskDetonator_L_C_PlayAttachEffects3P_Params
{
};

// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.ExecuteUbergraph_Attach_NobeliskDetonator_L
struct AAttach_NobeliskDetonator_L_C_ExecuteUbergraph_Attach_NobeliskDetonator_L_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
