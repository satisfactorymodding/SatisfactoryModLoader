#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ObjectScannerMenuItem_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.GetButtonFeedback
struct UWidget_ObjectScannerMenuItem_C_GetButtonFeedback_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.GetTextColor
struct UWidget_ObjectScannerMenuItem_C_GetTextColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ObjectScannerMenuItem.Widget_ObjectScannerMenuItem_C.OnItemSelected__DelegateSignature
struct UWidget_ObjectScannerMenuItem_C_OnItemSelected__DelegateSignature_Params
{
	class UClass*                                      scannedActorClass;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
