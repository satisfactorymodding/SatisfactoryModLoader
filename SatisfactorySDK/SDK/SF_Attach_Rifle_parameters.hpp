#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Attach_Rifle_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_Rifle.Attach_Rifle_C.UserConstructionScript
struct AAttach_Rifle_C_UserConstructionScript_Params
{
};

// Function Attach_Rifle.Attach_Rifle_C.ClientPlayReloadEffect
struct AAttach_Rifle_C_ClientPlayReloadEffect_Params
{
};

// Function Attach_Rifle.Attach_Rifle_C.PlayFireEffect
struct AAttach_Rifle_C_PlayFireEffect_Params
{
	struct FVector*                                    flashLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
};

// Function Attach_Rifle.Attach_Rifle_C.PlayAttachEffects3P
struct AAttach_Rifle_C_PlayAttachEffects3P_Params
{
};

// Function Attach_Rifle.Attach_Rifle_C.ExecuteUbergraph_Attach_Rifle
struct AAttach_Rifle_C_ExecuteUbergraph_Attach_Rifle_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
