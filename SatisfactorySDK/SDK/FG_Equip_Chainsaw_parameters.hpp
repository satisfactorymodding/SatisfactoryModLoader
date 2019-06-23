#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Chainsaw_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_Chainsaw.Equip_Chainsaw_C.CanStartSawing
struct AEquip_Chainsaw_C_CanStartSawing_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.UpdateAttachmentState
struct AEquip_Chainsaw_C_UpdateAttachmentState_Params
{
	TEnumAsByte<EChainsawUseState>                     ChainsawState;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ForceUpdate;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.InterpSawProgress
struct AEquip_Chainsaw_C_InterpSawProgress_Params
{
	float                                              DeltaTime;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.UserConstructionScript
struct AEquip_Chainsaw_C_UserConstructionScript_Params
{
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.ReceiveTick
struct AEquip_Chainsaw_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.WasEquipped
struct AEquip_Chainsaw_C_WasEquipped_Params
{
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.WasUnEquipped
struct AEquip_Chainsaw_C_WasUnEquipped_Params
{
};

// Function Equip_Chainsaw.Equip_Chainsaw_C.ExecuteUbergraph_Equip_Chainsaw
struct AEquip_Chainsaw_C_ExecuteUbergraph_Equip_Chainsaw_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
