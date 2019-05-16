#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attach_StunSpear_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_StunSpear.Attach_StunSpear_C.UserConstructionScript
struct AAttach_StunSpear_C_UserConstructionScript_Params
{
};

// Function Attach_StunSpear.Attach_StunSpear_C.PlayUseEffect
struct AAttach_StunSpear_C_PlayUseEffect_Params
{
	struct FVector*                                    UseLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Attach_StunSpear.Attach_StunSpear_C.PlayAttachEffects3P
struct AAttach_StunSpear_C_PlayAttachEffects3P_Params
{
};

// Function Attach_StunSpear.Attach_StunSpear_C.ExecuteUbergraph_Attach_StunSpear
struct AAttach_StunSpear_C_ExecuteUbergraph_Attach_StunSpear_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
