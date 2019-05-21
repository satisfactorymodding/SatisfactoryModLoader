#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CheatResourceSpawner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.GetCountText
struct UWidget_CheatResourceSpawner_C_GetCountText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.Init
struct UWidget_CheatResourceSpawner_C_Init_Params
{
};

// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.BndEvt__mDescriptorSelector_K2Node_ComponentBoundEvent_22_OnSelectionChangedEvent__DelegateSignature
struct UWidget_CheatResourceSpawner_C_BndEvt__mDescriptorSelector_K2Node_ComponentBoundEvent_22_OnSelectionChangedEvent__DelegateSignature_Params
{
	class FString                                      SelectedItem;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	TEnumAsByte<ESelectInfo>                           SelectionType;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.ExecuteUbergraph_Widget_CheatResourceSpawner
struct UWidget_CheatResourceSpawner_C_ExecuteUbergraph_Widget_CheatResourceSpawner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
