#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Codex_Container_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Codex_Container.Widget_Codex_Container_C.PopulateSearchResults
struct UWidget_Codex_Container_C_PopulateSearchResults_Params
{
	struct FText                                       InText;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateItemInfo
struct UWidget_Codex_Container_C_UpdateItemInfo_Params
{
	class UClass*                                      product;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.SetAllItemsAndBuildings
struct UWidget_Codex_Container_C_SetAllItemsAndBuildings_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.GenerateReceipes
struct UWidget_Codex_Container_C_GenerateReceipes_Params
{
	TArray<class UClass*>                              InRecipes;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateNotifications
struct UWidget_Codex_Container_C_UpdateNotifications_Params
{
	class UWidget_CodexButton_C*                       forButton;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.OnFilterButtonPressed
struct UWidget_Codex_Container_C_OnFilterButtonPressed_Params
{
	class UWidget_CodexButton_C*                       ButtonPressed;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.SelectButtonWithMessage
struct UWidget_Codex_Container_C_SelectButtonWithMessage_Params
{
	class UClass*                                      inMessage;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.CheckShouldOpenMessage
struct UWidget_Codex_Container_C_CheckShouldOpenMessage_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.UpdateMessageText
struct UWidget_Codex_Container_C_UpdateMessageText_Params
{
	struct FText                                       senderMail;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       Sender;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.PopulateList
struct UWidget_Codex_Container_C_PopulateList_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.GetActiveTabFeedback
struct UWidget_Codex_Container_C_GetActiveTabFeedback_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.GetMessageVisiblity
struct UWidget_Codex_Container_C_GetMessageVisiblity_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.Construct
struct UWidget_Codex_Container_C_Construct_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.CloseCodex
struct UWidget_Codex_Container_C_CloseCodex_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.Tick
struct UWidget_Codex_Container_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.MarkAllAsRead
struct UWidget_Codex_Container_C_MarkAllAsRead_Params
{
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_0_OnTabButtonClicked__DelegateSignature
struct UWidget_Codex_Container_C_BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_0_OnTabButtonClicked__DelegateSignature_Params
{
	int                                                ButtonIndex;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.OnRecipeButtonClicked
struct UWidget_Codex_Container_C_OnRecipeButtonClicked_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature
struct UWidget_Codex_Container_C_BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.OnSearchResultClicked
struct UWidget_Codex_Container_C_OnSearchResultClicked_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
struct UWidget_Codex_Container_C_BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.BndEvt__Widget_ListButton_C_0_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UWidget_Codex_Container_C_BndEvt__Widget_ListButton_C_0_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.BndEvt__Widget_ListButton_C_1_K2Node_ComponentBoundEvent_4_OnClicked__DelegateSignature
struct UWidget_Codex_Container_C_BndEvt__Widget_ListButton_C_1_K2Node_ComponentBoundEvent_4_OnClicked__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Codex_Container.Widget_Codex_Container_C.ExecuteUbergraph_Widget_Codex_Container
struct UWidget_Codex_Container_C_ExecuteUbergraph_Widget_Codex_Container_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
