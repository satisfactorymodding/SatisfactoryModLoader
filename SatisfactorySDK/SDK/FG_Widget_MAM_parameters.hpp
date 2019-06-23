#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MAM_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MAM.Widget_MAM_C.WidgetFactory
struct UWidget_MAM_C_WidgetFactory_Params
{
	class UClass*                                      PopupClass;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UUserWidget*>                         out_widgets;                                              // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_MAM.Widget_MAM_C.IsValidResearchReward
struct UWidget_MAM_C_IsValidResearchReward_Params
{
	struct FResearchRecipeReward                       researchReward;                                           // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               Valid;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.CheckResearchStatusOnStart
struct UWidget_MAM_C_CheckResearchStatusOnStart_Params
{
};

// Function Widget_MAM.Widget_MAM_C.CreatePopup
struct UWidget_MAM_C_CreatePopup_Params
{
	class UClass*                                      Research_Recipe;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.GetScreenTitle
struct UWidget_MAM_C_GetScreenTitle_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAM.Widget_MAM_C.GetPercentageText
struct UWidget_MAM_C_GetPercentageText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAM.Widget_MAM_C.GetResearchPercentage
struct UWidget_MAM_C_GetResearchPercentage_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.ScanEffect
struct UWidget_MAM_C_ScanEffect_Params
{
};

// Function Widget_MAM.Widget_MAM_C.OnResearchStateChange
struct UWidget_MAM_C_OnResearchStateChange_Params
{
	class UClass*                                      Research;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.OnResearchRewardsClaimed
struct UWidget_MAM_C_OnResearchRewardsClaimed_Params
{
	class UClass*                                      Research;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.UpdateButtonStates
struct UWidget_MAM_C_UpdateButtonStates_Params
{
};

// Function Widget_MAM.Widget_MAM_C.OnResearchCompleted
struct UWidget_MAM_C_OnResearchCompleted_Params
{
	class UClass*                                      Research;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.GetResearchTimeLeft
struct UWidget_MAM_C_GetResearchTimeLeft_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAM.Widget_MAM_C.CanStartAnalyzing
struct UWidget_MAM_C_CanStartAnalyzing_Params
{
	bool                                               Value;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.OnResearchPaidOff
struct UWidget_MAM_C_OnResearchPaidOff_Params
{
	class UClass*                                      Research;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.GetManufacturingInfoVisibility
struct UWidget_MAM_C_GetManufacturingInfoVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.GetInfoboxVisibility
struct UWidget_MAM_C_GetInfoboxVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.SetWorkingAtMAMOnServer
struct UWidget_MAM_C_SetWorkingAtMAMOnServer_Params
{
	class AFGPlayerController*                         FGPlayerController;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.CreateInfoBox
struct UWidget_MAM_C_CreateInfoBox_Params
{
	class UClass*                                      mRecipe;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.Cleanup
struct UWidget_MAM_C_Cleanup_Params
{
};

// Function Widget_MAM.Widget_MAM_C.GetAvailableResearch
struct UWidget_MAM_C_GetAvailableResearch_Params
{
	TArray<class UClass*>                              AvailableRecipes;                                         // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_MAM.Widget_MAM_C.SetSelectedRecipe
struct UWidget_MAM_C_SetSelectedRecipe_Params
{
	class UClass*                                      mRecipe;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.InitRecipeList
struct UWidget_MAM_C_InitRecipeList_Params
{
};

// Function Widget_MAM.Widget_MAM_C.Construct
struct UWidget_MAM_C_Construct_Params
{
};

// Function Widget_MAM.Widget_MAM_C.Tick
struct UWidget_MAM_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.OnButtonClicked
struct UWidget_MAM_C_OnButtonClicked_Params
{
};

// Function Widget_MAM.Widget_MAM_C.Destruct
struct UWidget_MAM_C_Destruct_Params
{
};

// Function Widget_MAM.Widget_MAM_C.Init
struct UWidget_MAM_C_Init_Params
{
};

// Function Widget_MAM.Widget_MAM_C.OnListbuttonClicked
struct UWidget_MAM_C_OnListbuttonClicked_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_ListButton_C*                        ListButton;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.OnPopupButtonClicked
struct UWidget_MAM_C_OnPopupButtonClicked_Params
{
	bool                                               Bool;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.OnAnalyseAnimStart
struct UWidget_MAM_C_OnAnalyseAnimStart_Params
{
};

// Function Widget_MAM.Widget_MAM_C.OnNewRecipeSet
struct UWidget_MAM_C_OnNewRecipeSet_Params
{
	class UClass*                                      mNewRecipe;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.NotifyPopupClosed
struct UWidget_MAM_C_NotifyPopupClosed_Params
{
	class UClass*                                      PopupClass;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                exitCode;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAM.Widget_MAM_C.ExecuteUbergraph_Widget_MAM
struct UWidget_MAM_C_ExecuteUbergraph_Widget_MAM_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
