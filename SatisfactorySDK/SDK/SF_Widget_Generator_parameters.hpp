#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_Generator_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Generator.Widget_Generator_C.UpdateWarningWidget
struct UWidget_Generator_C_UpdateWarningWidget_Params
{
};

// Function Widget_Generator.Widget_Generator_C.DropInventorySlotStack
struct UWidget_Generator_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Generator.Widget_Generator_C.UpdateSlotStats
struct UWidget_Generator_C_UpdateSlotStats_Params
{
};

// Function Widget_Generator.Widget_Generator_C.GetFuseVisibility
struct UWidget_Generator_C_GetFuseVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Generator.Widget_Generator_C.UpdateSlotInfo
struct UWidget_Generator_C_UpdateSlotInfo_Params
{
};

// Function Widget_Generator.Widget_Generator_C.OnGetPowerCircuit
struct UWidget_Generator_C_OnGetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Generator.Widget_Generator_C.IsConnected
struct UWidget_Generator_C_IsConnected_Params
{
	bool                                               IsConnected;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Generator.Widget_Generator_C.Cleanup
struct UWidget_Generator_C_Cleanup_Params
{
};

// Function Widget_Generator.Widget_Generator_C.GetBurnProgressPercent
struct UWidget_Generator_C_GetBurnProgressPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Generator.Widget_Generator_C.Construct
struct UWidget_Generator_C_Construct_Params
{
};

// Function Widget_Generator.Widget_Generator_C.Destruct
struct UWidget_Generator_C_Destruct_Params
{
};

// Function Widget_Generator.Widget_Generator_C.Tick
struct UWidget_Generator_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Generator.Widget_Generator_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_1_OnStandbyClicked__DelegateSignature
struct UWidget_Generator_C_BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_1_OnStandbyClicked__DelegateSignature_Params
{
};

// Function Widget_Generator.Widget_Generator_C.Init
struct UWidget_Generator_C_Init_Params
{
};

// Function Widget_Generator.Widget_Generator_C.ResetFuse
struct UWidget_Generator_C_ResetFuse_Params
{
};

// Function Widget_Generator.Widget_Generator_C.WarningMessageCheck
struct UWidget_Generator_C_WarningMessageCheck_Params
{
};

// Function Widget_Generator.Widget_Generator_C.ExecuteUbergraph_Widget_Generator
struct UWidget_Generator_C_ExecuteUbergraph_Widget_Generator_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
