#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TradingPost.Widget_TradingPost_C.DropInventorySlotStack
struct UWidget_TradingPost_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetLowestNonFullyResearchedTier
struct UWidget_TradingPost_C_GetLowestNonFullyResearchedTier_Params
{
	int                                                tier;                                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	bool                                               FoundTier;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.CheckIfTierIsFullyResearched
struct UWidget_TradingPost_C_CheckIfTierIsFullyResearched_Params
{
	int                                                tier;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsResearched;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.SetTierAndDeafultSchematic
struct UWidget_TradingPost_C_SetTierAndDeafultSchematic_Params
{
	int                                                tier;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetSchematicHintTextVisibility
struct UWidget_TradingPost_C_GetSchematicHintTextVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetSchematicHintVisibility
struct UWidget_TradingPost_C_GetSchematicHintVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetTierHintVisibility
struct UWidget_TradingPost_C_GetTierHintVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GenerateTierList
struct UWidget_TradingPost_C_GenerateTierList_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.UpdateInventoryVisibility
struct UWidget_TradingPost_C_UpdateInventoryVisibility_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetRewardVisibility
struct UWidget_TradingPost_C_GetRewardVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetShipAwayFeedback
struct UWidget_TradingPost_C_GetShipAwayFeedback_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.SetRewardInformation
struct UWidget_TradingPost_C_SetRewardInformation_Params
{
	struct FText                                       inTitle;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       inDesc;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FSlateBrush                                 inIcon;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetActiveSchematicTabEnabled
struct UWidget_TradingPost_C_GetActiveSchematicTabEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.SetActiveTab
struct UWidget_TradingPost_C_SetActiveTab_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetShipInventoryVisibility
struct UWidget_TradingPost_C_GetShipInventoryVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.ActivateSelectedSchematic
struct UWidget_TradingPost_C_ActivateSelectedSchematic_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetSelectedRecipeBoxVisibility
struct UWidget_TradingPost_C_GetSelectedRecipeBoxVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.SetDefaultDescriptionText
struct UWidget_TradingPost_C_SetDefaultDescriptionText_Params
{
	class UClass*                                      mSchematicClass;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.UpdateRewardInfoFromProduct
struct UWidget_TradingPost_C_UpdateRewardInfoFromProduct_Params
{
	class UWidget_SchematicRewardItem_C*               Reward_Widget;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetTabFeedback
struct UWidget_TradingPost_C_GetTabFeedback_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.OnSchematicClicked
struct UWidget_TradingPost_C_OnSchematicClicked_Params
{
	class UClass*                                      Schematic;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.GetActiveSchematicInfoVisibility
struct UWidget_TradingPost_C_GetActiveSchematicInfoVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.SetActiveSchematicInfo
struct UWidget_TradingPost_C_SetActiveSchematicInfo_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPost.Widget_TradingPost_C.Cleanup
struct UWidget_TradingPost_C_Cleanup_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.Destruct
struct UWidget_TradingPost_C_Destruct_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.Init
struct UWidget_TradingPost_C_Init_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.Tick
struct UWidget_TradingPost_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.CloseTradepost
struct UWidget_TradingPost_C_CloseTradepost_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.OnActiveSchematicChanged
struct UWidget_TradingPost_C_OnActiveSchematicChanged_Params
{
	class UClass*                                      Schematic;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.Construct
struct UWidget_TradingPost_C_Construct_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.purchasedSchematic
struct UWidget_TradingPost_C_purchasedSchematic_Params
{
	class UClass*                                      purchasedSchematic;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.mShakeWindow
struct UWidget_TradingPost_C_mShakeWindow_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.BndEvt__mWindow_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
struct UWidget_TradingPost_C_BndEvt__mWindow_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.CreateSmoke
struct UWidget_TradingPost_C_CreateSmoke_Params
{
};

// Function Widget_TradingPost.Widget_TradingPost_C.BndEvt__mWindow_K2Node_ComponentBoundEvent_3_OnTabButtonClicked__DelegateSignature
struct UWidget_TradingPost_C_BndEvt__mWindow_K2Node_ComponentBoundEvent_3_OnTabButtonClicked__DelegateSignature_Params
{
	int                                                ButtonIndex;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPost.Widget_TradingPost_C.ExecuteUbergraph_Widget_TradingPost
struct UWidget_TradingPost_C_ExecuteUbergraph_Widget_TradingPost_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
