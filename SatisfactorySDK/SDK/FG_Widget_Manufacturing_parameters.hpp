#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Manufacturing_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Manufacturing.Widget_Manufacturing_C.ReconstructIOSlots
struct UWidget_Manufacturing_C_ReconstructIOSlots_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.DropInventorySlotStack
struct UWidget_Manufacturing_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.UpdateWindowText
struct UWidget_Manufacturing_C_UpdateWindowText_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.GetItemAmount
struct UWidget_Manufacturing_C_GetItemAmount_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FItemAmount                                 ItemAmount;                                               // (Parm, OutParm)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.GetManufacturingWarningVisibility
struct UWidget_Manufacturing_C_GetManufacturingWarningVisibility_Params
{
	class AFGBuildableManufacturer*                    buildableManufacturer;                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.UpdateProductionStats
struct UWidget_Manufacturing_C_UpdateProductionStats_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.UpdateOutputSlotInfo
struct UWidget_Manufacturing_C_UpdateOutputSlotInfo_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.UpdateProductivityPercentage
struct UWidget_Manufacturing_C_UpdateProductivityPercentage_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.GetPotentialButton
struct UWidget_Manufacturing_C_GetPotentialButton_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.CreateInfoBox
struct UWidget_Manufacturing_C_CreateInfoBox_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.OnManufacturingRecipeClicked
struct UWidget_Manufacturing_C_OnManufacturingRecipeClicked_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.OnStopHoveringManufacturingRecipe
struct UWidget_Manufacturing_C_OnStopHoveringManufacturingRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.OnManufacturingRecipeHovered
struct UWidget_Manufacturing_C_OnManufacturingRecipeHovered_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.GetIsInfoButtonTabEnabled
struct UWidget_Manufacturing_C_GetIsInfoButtonTabEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.RemoveInputSlot
struct UWidget_Manufacturing_C_RemoveInputSlot_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.AddInputSlot
struct UWidget_Manufacturing_C_AddInputSlot_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.UpdateIOSlots
struct UWidget_Manufacturing_C_UpdateIOSlots_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.SetSelectedRecipe
struct UWidget_Manufacturing_C_SetSelectedRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.InitRecipeList
struct UWidget_Manufacturing_C_InitRecipeList_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.OnNewRecipeSet
struct UWidget_Manufacturing_C_OnNewRecipeSet_Params
{
	class UClass*                                      newRecipe;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_12_OnStandbyClicked__DelegateSignature
struct UWidget_Manufacturing_C_BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_12_OnStandbyClicked__DelegateSignature_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.Init
struct UWidget_Manufacturing_C_Init_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.Tick
struct UWidget_Manufacturing_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.Construct
struct UWidget_Manufacturing_C_Construct_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.Destruct
struct UWidget_Manufacturing_C_Destruct_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
struct UWidget_Manufacturing_C_BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params
{
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_1_OnTabButtonClicked__DelegateSignature
struct UWidget_Manufacturing_C_BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_1_OnTabButtonClicked__DelegateSignature_Params
{
	int                                                ButtonIndex;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.OnReplicationDetailActorReplicated
struct UWidget_Manufacturing_C_OnReplicationDetailActorReplicated_Params
{
	class AActor*                                      replicationDetailActorOwner;                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Manufacturing.Widget_Manufacturing_C.ExecuteUbergraph_Widget_Manufacturing
struct UWidget_Manufacturing_C_ExecuteUbergraph_Widget_Manufacturing_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
