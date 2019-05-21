#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_Window_DarkMode_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetDividerButtonSlotVisibility
struct UWidget_Window_DarkMode_C_GetDividerButtonSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetNavigationVisibiliy
struct UWidget_Window_DarkMode_C_GetNavigationVisibiliy_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetInventoryBodyVisibility
struct UWidget_Window_DarkMode_C_GetInventoryBodyVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.GetTopButtonSlotVisibility
struct UWidget_Window_DarkMode_C_GetTopButtonSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnDrop
struct UWidget_Window_DarkMode_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.SetTitle
struct UWidget_Window_DarkMode_C_SetTitle_Params
{
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Construct
struct UWidget_Window_DarkMode_C_Construct_Params
{
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnEscapePressed
struct UWidget_Window_DarkMode_C_OnEscapePressed_Params
{
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Destruct
struct UWidget_Window_DarkMode_C_Destruct_Params
{
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.Tick
struct UWidget_Window_DarkMode_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnConstructAnimFinished
struct UWidget_Window_DarkMode_C_OnConstructAnimFinished_Params
{
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.PreConstruct
struct UWidget_Window_DarkMode_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnCloseButtonClicked
struct UWidget_Window_DarkMode_C_OnCloseButtonClicked_Params
{
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.ExecuteUbergraph_Widget_Window_DarkMode
struct UWidget_Window_DarkMode_C_ExecuteUbergraph_Widget_Window_DarkMode_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Window_DarkMode.Widget_Window_DarkMode_C.OnClose__DelegateSignature
struct UWidget_Window_DarkMode_C_OnClose__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
