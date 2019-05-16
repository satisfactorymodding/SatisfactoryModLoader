#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attach_MedKit_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_MedKit.Attach_MedKit_C.UserConstructionScript
struct AAttach_MedKit_C_UserConstructionScript_Params
{
};

// Function Attach_MedKit.Attach_MedKit_C.PlayUseEffect
struct AAttach_MedKit_C_PlayUseEffect_Params
{
	struct FVector*                                    UseLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Attach_MedKit.Attach_MedKit_C.PlayAttachEffects3P
struct AAttach_MedKit_C_PlayAttachEffects3P_Params
{
};

// Function Attach_MedKit.Attach_MedKit_C.ExecuteUbergraph_Attach_MedKit
struct AAttach_MedKit_C_ExecuteUbergraph_Attach_MedKit_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
