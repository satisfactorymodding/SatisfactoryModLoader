#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGun_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_BuildGun.BP_BuildGun_C.GetInstigatorPlayerController
struct ABP_BuildGun_C_GetInstigatorPlayerController_Params
{
	class APlayerController*                           PlayerController;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_BuildGun.BP_BuildGun_C.UserConstructionScript
struct ABP_BuildGun_C_UserConstructionScript_Params
{
};

// Function BP_BuildGun.BP_BuildGun_C.WasEquipped
struct ABP_BuildGun_C_WasEquipped_Params
{
};

// Function BP_BuildGun.BP_BuildGun_C.WasUnEquipped
struct ABP_BuildGun_C_WasUnEquipped_Params
{
};

// Function BP_BuildGun.BP_BuildGun_C.ExecuteUbergraph_BP_BuildGun
struct ABP_BuildGun_C_ExecuteUbergraph_BP_BuildGun_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
