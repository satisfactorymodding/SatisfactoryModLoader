#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_RebarGunProjectile_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.UserConstructionScript
struct AAttach_RebarGunProjectile_C_UserConstructionScript_Params
{
};

// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.PlayFireEffect
struct AAttach_RebarGunProjectile_C_PlayFireEffect_Params
{
	struct FVector*                                    flashLocation;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.ClientPlayReloadEffect
struct AAttach_RebarGunProjectile_C_ClientPlayReloadEffect_Params
{
};

// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.PlayAttachEffects3P
struct AAttach_RebarGunProjectile_C_PlayAttachEffects3P_Params
{
};

// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.ExecuteUbergraph_Attach_RebarGunProjectile
struct AAttach_RebarGunProjectile_C_ExecuteUbergraph_Attach_RebarGunProjectile_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
