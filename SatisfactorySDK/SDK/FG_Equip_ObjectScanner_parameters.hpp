#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_ObjectScanner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.UserConstructionScript
struct AEquip_ObjectScanner_C_UserConstructionScript_Params
{
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_3
struct AEquip_ObjectScanner_C_InpActEvt_PrimaryFire_K2Node_InputActionEvent_3_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_2
struct AEquip_ObjectScanner_C_InpActEvt_PrimaryFire_K2Node_InputActionEvent_2_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.InpActEvt_SecondaryFire_K2Node_InputActionEvent_1
struct AEquip_ObjectScanner_C_InpActEvt_SecondaryFire_K2Node_InputActionEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.PlayBeep
struct AEquip_ObjectScanner_C_PlayBeep_Params
{
	bool*                                              isObjectInRange;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.ReceiveTick
struct AEquip_ObjectScanner_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.UpdateScannerVisuals
struct AEquip_ObjectScanner_C_UpdateScannerVisuals_Params
{
	bool*                                              wasChange;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.WasEquipped
struct AEquip_ObjectScanner_C_WasEquipped_Params
{
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.WasUnEquipped
struct AEquip_ObjectScanner_C_WasUnEquipped_Params
{
};

// Function Equip_ObjectScanner.Equip_ObjectScanner_C.ExecuteUbergraph_Equip_ObjectScanner
struct AEquip_ObjectScanner_C_ExecuteUbergraph_Equip_ObjectScanner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
