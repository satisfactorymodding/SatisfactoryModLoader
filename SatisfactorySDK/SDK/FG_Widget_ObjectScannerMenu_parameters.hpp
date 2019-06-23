#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ObjectScannerMenu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.GetScannableIcon
struct UWidget_ObjectScannerMenu_C_GetScannableIcon_Params
{
	struct FScannableDetails                           ScannableDetails;                                         // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UTexture*                                    Texture;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Get_RingHighlighter_Visibility_1
struct UWidget_ObjectScannerMenu_C_Get_RingHighlighter_Visibility_1_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.GetPositionInCircle
struct UWidget_ObjectScannerMenu_C_GetPositionInCircle_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Translation;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.OnAnimationFinished
struct UWidget_ObjectScannerMenu_C_OnAnimationFinished_Params
{
	class UWidgetAnimation**                           Animation;                                                // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.OnItemSelected
struct UWidget_ObjectScannerMenu_C_OnItemSelected_Params
{
	class UClass*                                      scannedActorClass;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Destruct
struct UWidget_ObjectScannerMenu_C_Destruct_Params
{
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Construct
struct UWidget_ObjectScannerMenu_C_Construct_Params
{
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.Tick
struct UWidget_ObjectScannerMenu_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ObjectScannerMenu.Widget_ObjectScannerMenu_C.ExecuteUbergraph_Widget_ObjectScannerMenu
struct UWidget_ObjectScannerMenu_C_ExecuteUbergraph_Widget_ObjectScannerMenu_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
