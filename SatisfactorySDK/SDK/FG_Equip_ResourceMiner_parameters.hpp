#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_ResourceMiner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.UserConstructionScript
struct AEquip_ResourceMiner_C_UserConstructionScript_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.StopMining
struct AEquip_ResourceMiner_C_StopMining_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.StartMining
struct AEquip_ResourceMiner_C_StartMining_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.WasEquipped
struct AEquip_ResourceMiner_C_WasEquipped_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.PlayFinalEffects
struct AEquip_ResourceMiner_C_PlayFinalEffects_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.PlayMiningEffect
struct AEquip_ResourceMiner_C_PlayMiningEffect_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.StartCameraShake
struct AEquip_ResourceMiner_C_StartCameraShake_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.PlaySecondEffects
struct AEquip_ResourceMiner_C_PlaySecondEffects_Params
{
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.HitDeposit
struct AEquip_ResourceMiner_C_HitDeposit_Params
{
	class AActor*                                      Hit_Actor_Ref;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Hit_Location;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_ResourceMiner.Equip_ResourceMiner_C.ExecuteUbergraph_Equip_ResourceMiner
struct AEquip_ResourceMiner_C_ExecuteUbergraph_Equip_ResourceMiner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
