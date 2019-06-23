#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TabsContainer_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TabsContainer.Widget_TabsContainer_C.SetActiveButton
struct UWidget_TabsContainer_C_SetActiveButton_Params
{
	class UWidget_SlidingTabs_Button_C*                ActiveButton;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.IfButtonClicked
struct UWidget_TabsContainer_C_IfButtonClicked_Params
{
	class UWidget_SlidingTabs_Button_C*                Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.IfButtonUnhovered
struct UWidget_TabsContainer_C_IfButtonUnhovered_Params
{
	class UWidget_SlidingTabs_Button_C*                Insitagor;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.IfButtonHovered
struct UWidget_TabsContainer_C_IfButtonHovered_Params
{
	class UWidget_SlidingTabs_Button_C*                Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.GenerateButtons
struct UWidget_TabsContainer_C_GenerateButtons_Params
{
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.PreConstruct
struct UWidget_TabsContainer_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.Init
struct UWidget_TabsContainer_C_Init_Params
{
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.Destruct
struct UWidget_TabsContainer_C_Destruct_Params
{
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.ExecuteUbergraph_Widget_TabsContainer
struct UWidget_TabsContainer_C_ExecuteUbergraph_Widget_TabsContainer_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.OnTabsGenerated__DelegateSignature
struct UWidget_TabsContainer_C_OnTabsGenerated__DelegateSignature_Params
{
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.OnNoTabsGenerated__DelegateSignature
struct UWidget_TabsContainer_C_OnNoTabsGenerated__DelegateSignature_Params
{
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.OnButtonClicked__DelegateSignature
struct UWidget_TabsContainer_C_OnButtonClicked__DelegateSignature_Params
{
	int                                                ButtonIndex;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.OnButtonUnhovered__DelegateSignature
struct UWidget_TabsContainer_C_OnButtonUnhovered__DelegateSignature_Params
{
	bool                                               IsActiveButton;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TabsContainer.Widget_TabsContainer_C.OnButtonHovered__DelegateSignature
struct UWidget_TabsContainer_C_OnButtonHovered__DelegateSignature_Params
{
	bool                                               IsActiveButton;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
