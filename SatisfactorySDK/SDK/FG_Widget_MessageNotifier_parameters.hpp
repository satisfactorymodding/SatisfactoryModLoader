#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MessageNotifier_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MessageNotifier.Widget_MessageNotifier_C.GetKeyForAction
struct UWidget_MessageNotifier_C_GetKeyForAction_Params
{
	struct FText                                       keyText;                                                  // (Parm, OutParm)
};

// Function Widget_MessageNotifier.Widget_MessageNotifier_C.PreConstruct
struct UWidget_MessageNotifier_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MessageNotifier.Widget_MessageNotifier_C.Construct
struct UWidget_MessageNotifier_C_Construct_Params
{
};

// Function Widget_MessageNotifier.Widget_MessageNotifier_C.RemoveNotifier
struct UWidget_MessageNotifier_C_RemoveNotifier_Params
{
};

// Function Widget_MessageNotifier.Widget_MessageNotifier_C.ExecuteUbergraph_Widget_MessageNotifier
struct UWidget_MessageNotifier_C_ExecuteUbergraph_Widget_MessageNotifier_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
