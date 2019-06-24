#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ShockShank_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_ShockShank.Attach_ShockShank_C.UserConstructionScript
struct AAttach_ShockShank_C_UserConstructionScript_Params
{
};

// Function Attach_ShockShank.Attach_ShockShank_C.PlayUseEffect
struct AAttach_ShockShank_C_PlayUseEffect_Params
{
	struct FVector*                                    UseLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_ShockShank.Attach_ShockShank_C.PlayAttachEffects3P
struct AAttach_ShockShank_C_PlayAttachEffects3P_Params
{
};

// Function Attach_ShockShank.Attach_ShockShank_C.ExecuteUbergraph_Attach_ShockShank
struct AAttach_ShockShank_C_ExecuteUbergraph_Attach_ShockShank_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
