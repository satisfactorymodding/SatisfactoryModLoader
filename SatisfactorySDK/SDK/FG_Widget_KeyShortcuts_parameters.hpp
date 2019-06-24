#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_KeyShortcuts_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.UpdateShortcutText
struct UWidget_KeyShortcuts_C_UpdateShortcutText_Params
{
};

// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.GetKeyForAction
struct UWidget_KeyShortcuts_C_GetKeyForAction_Params
{
	struct FName                                       ActionName;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       keyText;                                                  // (Parm, OutParm)
};

// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.Construct
struct UWidget_KeyShortcuts_C_Construct_Params
{
};

// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.UpdateShortcutAvilability
struct UWidget_KeyShortcuts_C_UpdateShortcutAvilability_Params
{
	class UClass*                                      Unused;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_KeyShortcuts.Widget_KeyShortcuts_C.ExecuteUbergraph_Widget_KeyShortcuts
struct UWidget_KeyShortcuts_C_ExecuteUbergraph_Widget_KeyShortcuts_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
