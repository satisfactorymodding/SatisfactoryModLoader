#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ColorGun_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_ColorGun.Attach_ColorGun_C.UserConstructionScript
struct AAttach_ColorGun_C_UserConstructionScript_Params
{
};

// Function Attach_ColorGun.Attach_ColorGun_C.ClientPlayReloadEffect
struct AAttach_ColorGun_C_ClientPlayReloadEffect_Params
{
};

// Function Attach_ColorGun.Attach_ColorGun_C.PlayFireEffect
struct AAttach_ColorGun_C_PlayFireEffect_Params
{
	struct FVector*                                    flashLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_ColorGun.Attach_ColorGun_C.PlayAttachEffects3P
struct AAttach_ColorGun_C_PlayAttachEffects3P_Params
{
};

// Function Attach_ColorGun.Attach_ColorGun_C.ExecuteUbergraph_Attach_ColorGun
struct AAttach_ColorGun_C_ExecuteUbergraph_Attach_ColorGun_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
