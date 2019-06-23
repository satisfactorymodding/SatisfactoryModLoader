#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManualManufacturing_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ClearAndHideSearchResults
struct UWidget_ManualManufacturing_C_ClearAndHideSearchResults_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnSearchCreateResults
struct UWidget_ManualManufacturing_C_OnSearchCreateResults_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowOnlyAffordableRecipes
struct UWidget_ManualManufacturing_C_ShowOnlyAffordableRecipes_Params
{
	bool                                               OnlyShowAffordable;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SpaceBarOverride
struct UWidget_ManualManufacturing_C_SpaceBarOverride_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StopCraftingOverride
struct UWidget_ManualManufacturing_C_StopCraftingOverride_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnPreviewKeyDown
struct UWidget_ManualManufacturing_C_OnPreviewKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CreateCategoryHeader
struct UWidget_ManualManufacturing_C_CreateCategoryHeader_Params
{
	class UPanelWidget*                                InScrollbox;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FText                                       Name;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateLeds
struct UWidget_ManualManufacturing_C_UpdateLeds_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateWarningWidget
struct UWidget_ManualManufacturing_C_UpdateWarningWidget_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCalculatedCurve
struct UWidget_ManualManufacturing_C_GetCalculatedCurve_Params
{
	float                                              Output;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowCurrentOutput
struct UWidget_ManualManufacturing_C_ShowCurrentOutput_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateProductionStats
struct UWidget_ManualManufacturing_C_UpdateProductionStats_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateProgressBar
struct UWidget_ManualManufacturing_C_UpdateProgressBar_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCraftButtonFeedback
struct UWidget_ManualManufacturing_C_GetCraftButtonFeedback_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CloseVehicle
struct UWidget_ManualManufacturing_C_CloseVehicle_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetInfoboxVisibility
struct UWidget_ManualManufacturing_C_GetInfoboxVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCraftingFeedbackVisibility
struct UWidget_ManualManufacturing_C_GetCraftingFeedbackVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetWorkingAtWorkbenchOnServer
struct UWidget_ManualManufacturing_C_SetWorkingAtWorkbenchOnServer_Params
{
	class AFGPlayerController*                         FGPlayerController;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnCraftCompleted
struct UWidget_ManualManufacturing_C_OnCraftCompleted_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CreateInfoBox
struct UWidget_ManualManufacturing_C_CreateInfoBox_Params
{
	class UClass*                                      mRecipe;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Cleanup
struct UWidget_ManualManufacturing_C_Cleanup_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetAvailableRecipes
struct UWidget_ManualManufacturing_C_GetAvailableRecipes_Params
{
	TArray<class UClass*>                              AvailableRecipes;                                         // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetSelectedRecipe
struct UWidget_ManualManufacturing_C_SetSelectedRecipe_Params
{
	class UClass*                                      mRecipe;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitRecipeList
struct UWidget_ManualManufacturing_C_InitRecipeList_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Destruct
struct UWidget_ManualManufacturing_C_Destruct_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Construct
struct UWidget_ManualManufacturing_C_Construct_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetupProductionMode
struct UWidget_ManualManufacturing_C_SetupProductionMode_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnNewRecipeSet
struct UWidget_ManualManufacturing_C_OnNewRecipeSet_Params
{
	class UClass*                                      mNewRecipe;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Init
struct UWidget_ManualManufacturing_C_Init_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartProducing
struct UWidget_ManualManufacturing_C_StartProducing_Params
{
	float                                              produceSpeed;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.EndProducing
struct UWidget_ManualManufacturing_C_EndProducing_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Tick
struct UWidget_ManualManufacturing_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnCraftingProgressbarAnimationLoop
struct UWidget_ManualManufacturing_C_OnCraftingProgressbarAnimationLoop_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartHold
struct UWidget_ManualManufacturing_C_StartHold_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StopSuperClick
struct UWidget_ManualManufacturing_C_StopSuperClick_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartSuperClick
struct UWidget_ManualManufacturing_C_StartSuperClick_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.IncreaseGlow
struct UWidget_ManualManufacturing_C_IncreaseGlow_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.DecreseGlow
struct UWidget_ManualManufacturing_C_DecreseGlow_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Shake
struct UWidget_ManualManufacturing_C_Shake_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.EmptyBar
struct UWidget_ManualManufacturing_C_EmptyBar_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.FadeBar
struct UWidget_ManualManufacturing_C_FadeBar_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.WarningMessageCheck
struct UWidget_ManualManufacturing_C_WarningMessageCheck_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ProductionStartupDelay
struct UWidget_ManualManufacturing_C_ProductionStartupDelay_Params
{
	float                                              produceSpeed;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.PlayLEDSound
struct UWidget_ManualManufacturing_C_PlayLEDSound_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowAddedToInventory
struct UWidget_ManualManufacturing_C_ShowAddedToInventory_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.HideAddedToInventoryEvent
struct UWidget_ManualManufacturing_C_HideAddedToInventoryEvent_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_ManualManufacturing_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mOnlyShowAffordableCheckbox_K2Node_ComponentBoundEvent_3_OnCheckChanged__DelegateSignature
struct UWidget_ManualManufacturing_C_BndEvt__mOnlyShowAffordableCheckbox_K2Node_ComponentBoundEvent_3_OnCheckChanged__DelegateSignature_Params
{
	bool                                               IsChecked;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mSearchbar_K2Node_ComponentBoundEvent_4_OnTextChanged__DelegateSignature
struct UWidget_ManualManufacturing_C_BndEvt__mSearchbar_K2Node_ComponentBoundEvent_4_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ExecuteUbergraph_Widget_ManualManufacturing
struct UWidget_ManualManufacturing_C_ExecuteUbergraph_Widget_ManualManufacturing_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
