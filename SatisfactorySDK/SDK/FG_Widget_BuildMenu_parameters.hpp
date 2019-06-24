#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_BuildMenu.Widget_BuildMenu_C.HideSearchbar
struct UWidget_BuildMenu_C_HideSearchbar_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.ShowSearchbar
struct UWidget_BuildMenu_C_ShowSearchbar_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.IsShortcutSettingAllowed
struct UWidget_BuildMenu_C_IsShortcutSettingAllowed_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.ClearAndHideSearchResults
struct UWidget_BuildMenu_C_ClearAndHideSearchResults_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnSearchCreateResults
struct UWidget_BuildMenu_C_OnSearchCreateResults_Params
{
	struct FText                                       mText;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnKeyDown
struct UWidget_BuildMenu_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.SetVisibilityForSpecialCategory
struct UWidget_BuildMenu_C_SetVisibilityForSpecialCategory_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.PopulateBuildings
struct UWidget_BuildMenu_C_PopulateBuildings_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.UpdateShortcuts
struct UWidget_BuildMenu_C_UpdateShortcuts_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.HandleShortcutPressed
struct UWidget_BuildMenu_C_HandleShortcutPressed_Params
{
	int                                                shortcutIndex;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               setupNewShortcut;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnStopHoveringRecipe
struct UWidget_BuildMenu_C_OnStopHoveringRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_BuildMenuRecipeButton_C*             RecipeButton;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnRecipeHovered
struct UWidget_BuildMenu_C_OnRecipeHovered_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_BuildMenuRecipeButton_C*             RecipeButton;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnKeyUp
struct UWidget_BuildMenu_C_OnKeyUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.IsCentralStorageBuilt
struct UWidget_BuildMenu_C_IsCentralStorageBuilt_Params
{
	bool                                               IsBuilt;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.IsSpaceElevatorBuilt
struct UWidget_BuildMenu_C_IsSpaceElevatorBuilt_Params
{
	bool                                               IsBuilt;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.IsTradingPostBuilt
struct UWidget_BuildMenu_C_IsTradingPostBuilt_Params
{
	bool                                               IsBuilt;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.PonderAddingSpecialCategory
struct UWidget_BuildMenu_C_PonderAddingSpecialCategory_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.GetInfoboxVisiblity
struct UWidget_BuildMenu_C_GetInfoboxVisiblity_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.SaveCategories
struct UWidget_BuildMenu_C_SaveCategories_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnBuildCategoryClicked
struct UWidget_BuildMenu_C_OnBuildCategoryClicked_Params
{
	class UClass*                                      buildCategory;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.InitBuildMenu
struct UWidget_BuildMenu_C_InitBuildMenu_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnRecipeClicked
struct UWidget_BuildMenu_C_OnRecipeClicked_Params
{
	class UClass*                                      InputPin;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.CreateInfoBox
struct UWidget_BuildMenu_C_CreateInfoBox_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.CreateCategoryButtons
struct UWidget_BuildMenu_C_CreateCategoryButtons_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.CanAffordRecipe
struct UWidget_BuildMenu_C_CanAffordRecipe_Params
{
	class UClass*                                      Recipe;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               CanAfford;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnScroll
struct UWidget_BuildMenu_C_OnScroll_Params
{
	float                                              ScrollPos;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.RemoveHotbarUpdateListener
struct UWidget_BuildMenu_C_RemoveHotbarUpdateListener_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.ListenForHotbarUpdate
struct UWidget_BuildMenu_C_ListenForHotbarUpdate_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.Destruct
struct UWidget_BuildMenu_C_Destruct_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.Construct
struct UWidget_BuildMenu_C_Construct_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnEscapePressed
struct UWidget_BuildMenu_C_OnEscapePressed_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature
struct UWidget_BuildMenu_C_BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_2_OnTextComitted__DelegateSignature
struct UWidget_BuildMenu_C_BndEvt__mSearchBar_K2Node_ComponentBoundEvent_2_OnTextComitted__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.CheckSearchResultHover
struct UWidget_BuildMenu_C_CheckSearchResultHover_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.UnBlockMouse
struct UWidget_BuildMenu_C_UnBlockMouse_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__Widget_MouseMoveChecker_K2Node_ComponentBoundEvent_0_OnMouseMoved__DelegateSignature
struct UWidget_BuildMenu_C_BndEvt__Widget_MouseMoveChecker_K2Node_ComponentBoundEvent_0_OnMouseMoved__DelegateSignature_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.BlockMouse
struct UWidget_BuildMenu_C_BlockMouse_Params
{
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.ExecuteUbergraph_Widget_BuildMenu
struct UWidget_BuildMenu_C_ExecuteUbergraph_Widget_BuildMenu_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BuildMenu.Widget_BuildMenu_C.OnClicked__DelegateSignature
struct UWidget_BuildMenu_C_OnClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
