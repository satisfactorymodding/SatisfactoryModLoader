#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_JetPack_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_JetPack.Equip_JetPack_C.GetMaxFuel
struct AEquip_JetPack_C_GetMaxFuel_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.GetCurrentFuel
struct AEquip_JetPack_C_GetCurrentFuel_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.GetNewVelocityWhenThrusting
struct AEquip_JetPack_C_GetNewVelocityWhenThrusting_Params
{
	float*                                             Delta;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.CanThrust
struct AEquip_JetPack_C_CanThrust_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.UserConstructionScript
struct AEquip_JetPack_C_UserConstructionScript_Params
{
};

// Function Equip_JetPack.Equip_JetPack_C.OnStartThrusting
struct AEquip_JetPack_C_OnStartThrusting_Params
{
};

// Function Equip_JetPack.Equip_JetPack_C.OnStopThrusting
struct AEquip_JetPack_C_OnStopThrusting_Params
{
};

// Function Equip_JetPack.Equip_JetPack_C.ReceiveTick
struct AEquip_JetPack_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.ConsumeFuel
struct AEquip_JetPack_C_ConsumeFuel_Params
{
	float                                              Delta;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.RegenerateFuel
struct AEquip_JetPack_C_RegenerateFuel_Params
{
	float                                              Delta;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_JetPack.Equip_JetPack_C.ReceiveBeginPlay
struct AEquip_JetPack_C_ReceiveBeginPlay_Params
{
};

// Function Equip_JetPack.Equip_JetPack_C.WasEquipped
struct AEquip_JetPack_C_WasEquipped_Params
{
};

// Function Equip_JetPack.Equip_JetPack_C.WasUnEquipped
struct AEquip_JetPack_C_WasUnEquipped_Params
{
};

// Function Equip_JetPack.Equip_JetPack_C.ExecuteUbergraph_Equip_JetPack
struct AEquip_JetPack_C_ExecuteUbergraph_Equip_JetPack_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
