// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildMenu.Widget_BuildMenu_C.HideSearchbar
// ()

void UWidget_BuildMenu_C::HideSearchbar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.HideSearchbar");

	UWidget_BuildMenu_C_HideSearchbar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.ShowSearchbar
// ()

void UWidget_BuildMenu_C::ShowSearchbar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.ShowSearchbar");

	UWidget_BuildMenu_C_ShowSearchbar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.IsShortcutSettingAllowed
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_BuildMenu_C::IsShortcutSettingAllowed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.IsShortcutSettingAllowed");

	UWidget_BuildMenu_C_IsShortcutSettingAllowed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.ClearAndHideSearchResults
// ()

void UWidget_BuildMenu_C::ClearAndHideSearchResults()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.ClearAndHideSearchResults");

	UWidget_BuildMenu_C_ClearAndHideSearchResults_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnSearchCreateResults
// ()
// Parameters:
// struct FText                   mText                          (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_BuildMenu_C::OnSearchCreateResults(const struct FText& mText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnSearchCreateResults");

	UWidget_BuildMenu_C_OnSearchCreateResults_Params params;
	params.mText = mText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_BuildMenu_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnKeyDown");

	UWidget_BuildMenu_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.SetVisibilityForSpecialCategory
// ()

void UWidget_BuildMenu_C::SetVisibilityForSpecialCategory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.SetVisibilityForSpecialCategory");

	UWidget_BuildMenu_C_SetVisibilityForSpecialCategory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.PopulateBuildings
// ()

void UWidget_BuildMenu_C::PopulateBuildings()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.PopulateBuildings");

	UWidget_BuildMenu_C_PopulateBuildings_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.UpdateShortcuts
// ()

void UWidget_BuildMenu_C::UpdateShortcuts()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.UpdateShortcuts");

	UWidget_BuildMenu_C_UpdateShortcuts_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.HandleShortcutPressed
// ()
// Parameters:
// int                            shortcutIndex                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           setupNewShortcut               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::HandleShortcutPressed(int shortcutIndex, bool* setupNewShortcut)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.HandleShortcutPressed");

	UWidget_BuildMenu_C_HandleShortcutPressed_Params params;
	params.shortcutIndex = shortcutIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (setupNewShortcut != nullptr)
		*setupNewShortcut = params.setupNewShortcut;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnStopHoveringRecipe
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_BuildMenuRecipeButton_C* RecipeButton                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_BuildMenu_C::OnStopHoveringRecipe(class UClass* Recipe, class UWidget_BuildMenuRecipeButton_C* RecipeButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnStopHoveringRecipe");

	UWidget_BuildMenu_C_OnStopHoveringRecipe_Params params;
	params.Recipe = Recipe;
	params.RecipeButton = RecipeButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnRecipeHovered
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_BuildMenuRecipeButton_C* RecipeButton                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_BuildMenu_C::OnRecipeHovered(class UClass* Recipe, class UWidget_BuildMenuRecipeButton_C* RecipeButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnRecipeHovered");

	UWidget_BuildMenu_C_OnRecipeHovered_Params params;
	params.Recipe = Recipe;
	params.RecipeButton = RecipeButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnKeyUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_BuildMenu_C::OnKeyUp(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnKeyUp");

	UWidget_BuildMenu_C_OnKeyUp_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.IsCentralStorageBuilt
// ()
// Parameters:
// bool                           IsBuilt                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::IsCentralStorageBuilt(bool* IsBuilt)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.IsCentralStorageBuilt");

	UWidget_BuildMenu_C_IsCentralStorageBuilt_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsBuilt != nullptr)
		*IsBuilt = params.IsBuilt;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.IsSpaceElevatorBuilt
// ()
// Parameters:
// bool                           IsBuilt                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::IsSpaceElevatorBuilt(bool* IsBuilt)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.IsSpaceElevatorBuilt");

	UWidget_BuildMenu_C_IsSpaceElevatorBuilt_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsBuilt != nullptr)
		*IsBuilt = params.IsBuilt;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.IsTradingPostBuilt
// ()
// Parameters:
// bool                           IsBuilt                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::IsTradingPostBuilt(bool* IsBuilt)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.IsTradingPostBuilt");

	UWidget_BuildMenu_C_IsTradingPostBuilt_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsBuilt != nullptr)
		*IsBuilt = params.IsBuilt;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.PonderAddingSpecialCategory
// ()

void UWidget_BuildMenu_C::PonderAddingSpecialCategory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.PonderAddingSpecialCategory");

	UWidget_BuildMenu_C_PonderAddingSpecialCategory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.GetInfoboxVisiblity
// ()

void UWidget_BuildMenu_C::GetInfoboxVisiblity()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.GetInfoboxVisiblity");

	UWidget_BuildMenu_C_GetInfoboxVisiblity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.SaveCategories
// ()

void UWidget_BuildMenu_C::SaveCategories()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.SaveCategories");

	UWidget_BuildMenu_C_SaveCategories_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnBuildCategoryClicked
// ()
// Parameters:
// class UClass*                  buildCategory                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::OnBuildCategoryClicked(class UClass* buildCategory)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnBuildCategoryClicked");

	UWidget_BuildMenu_C_OnBuildCategoryClicked_Params params;
	params.buildCategory = buildCategory;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.InitBuildMenu
// ()

void UWidget_BuildMenu_C::InitBuildMenu()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.InitBuildMenu");

	UWidget_BuildMenu_C_InitBuildMenu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnRecipeClicked
// ()
// Parameters:
// class UClass*                  InputPin                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::OnRecipeClicked(class UClass* InputPin)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnRecipeClicked");

	UWidget_BuildMenu_C_OnRecipeClicked_Params params;
	params.InputPin = InputPin;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.CreateInfoBox
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::CreateInfoBox(class UClass* Recipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.CreateInfoBox");

	UWidget_BuildMenu_C_CreateInfoBox_Params params;
	params.Recipe = Recipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.CreateCategoryButtons
// ()

void UWidget_BuildMenu_C::CreateCategoryButtons()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.CreateCategoryButtons");

	UWidget_BuildMenu_C_CreateCategoryButtons_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.CanAffordRecipe
// ()
// Parameters:
// class UClass*                  Recipe                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           CanAfford                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::CanAffordRecipe(class UClass* Recipe, bool* CanAfford)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.CanAffordRecipe");

	UWidget_BuildMenu_C_CanAffordRecipe_Params params;
	params.Recipe = Recipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (CanAfford != nullptr)
		*CanAfford = params.CanAfford;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnScroll
// ()
// Parameters:
// float                          ScrollPos                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::OnScroll(float ScrollPos)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnScroll");

	UWidget_BuildMenu_C_OnScroll_Params params;
	params.ScrollPos = ScrollPos;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.RemoveHotbarUpdateListener
// ()

void UWidget_BuildMenu_C::RemoveHotbarUpdateListener()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.RemoveHotbarUpdateListener");

	UWidget_BuildMenu_C_RemoveHotbarUpdateListener_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.ListenForHotbarUpdate
// ()

void UWidget_BuildMenu_C::ListenForHotbarUpdate()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.ListenForHotbarUpdate");

	UWidget_BuildMenu_C_ListenForHotbarUpdate_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.Destruct
// ()

void UWidget_BuildMenu_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.Destruct");

	UWidget_BuildMenu_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.Construct
// ()

void UWidget_BuildMenu_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.Construct");

	UWidget_BuildMenu_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnEscapePressed
// ()

void UWidget_BuildMenu_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnEscapePressed");

	UWidget_BuildMenu_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_BuildMenu_C::BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature");

	UWidget_BuildMenu_C_BndEvt__mSearchBar_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_2_OnTextComitted__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::BndEvt__mSearchBar_K2Node_ComponentBoundEvent_2_OnTextComitted__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__mSearchBar_K2Node_ComponentBoundEvent_2_OnTextComitted__DelegateSignature");

	UWidget_BuildMenu_C_BndEvt__mSearchBar_K2Node_ComponentBoundEvent_2_OnTextComitted__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.CheckSearchResultHover
// ()

void UWidget_BuildMenu_C::CheckSearchResultHover()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.CheckSearchResultHover");

	UWidget_BuildMenu_C_CheckSearchResultHover_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.UnBlockMouse
// ()

void UWidget_BuildMenu_C::UnBlockMouse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.UnBlockMouse");

	UWidget_BuildMenu_C_UnBlockMouse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__Widget_MouseMoveChecker_K2Node_ComponentBoundEvent_0_OnMouseMoved__DelegateSignature
// ()

void UWidget_BuildMenu_C::BndEvt__Widget_MouseMoveChecker_K2Node_ComponentBoundEvent_0_OnMouseMoved__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.BndEvt__Widget_MouseMoveChecker_K2Node_ComponentBoundEvent_0_OnMouseMoved__DelegateSignature");

	UWidget_BuildMenu_C_BndEvt__Widget_MouseMoveChecker_K2Node_ComponentBoundEvent_0_OnMouseMoved__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.BlockMouse
// ()

void UWidget_BuildMenu_C::BlockMouse()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.BlockMouse");

	UWidget_BuildMenu_C_BlockMouse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.ExecuteUbergraph_Widget_BuildMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_C::ExecuteUbergraph_Widget_BuildMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.ExecuteUbergraph_Widget_BuildMenu");

	UWidget_BuildMenu_C_ExecuteUbergraph_Widget_BuildMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu.Widget_BuildMenu_C.OnClicked__DelegateSignature
// ()

void UWidget_BuildMenu_C::OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu.Widget_BuildMenu_C.OnClicked__DelegateSignature");

	UWidget_BuildMenu_C_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
