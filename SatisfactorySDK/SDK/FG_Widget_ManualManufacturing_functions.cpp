// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManualManufacturing_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SpaceBarOverride
// ()

void UWidget_ManualManufacturing_C::SpaceBarOverride()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SpaceBarOverride");

	UWidget_ManualManufacturing_C_SpaceBarOverride_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StopCraftingOverride
// ()

void UWidget_ManualManufacturing_C::StopCraftingOverride()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StopCraftingOverride");

	UWidget_ManualManufacturing_C_StopCraftingOverride_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnPreviewKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_ManualManufacturing_C::OnPreviewKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnPreviewKeyDown");

	UWidget_ManualManufacturing_C_OnPreviewKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CreateCategoryHeader
// ()
// Parameters:
// class UPanelWidget*            InScrollbox                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FText                   Name                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_ManualManufacturing_C::CreateCategoryHeader(class UPanelWidget* InScrollbox, const struct FText& Name)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CreateCategoryHeader");

	UWidget_ManualManufacturing_C_CreateCategoryHeader_Params params;
	params.InScrollbox = InScrollbox;
	params.Name = Name;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateLeds
// ()

void UWidget_ManualManufacturing_C::UpdateLeds()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateLeds");

	UWidget_ManualManufacturing_C_UpdateLeds_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateWarningWidget
// ()

void UWidget_ManualManufacturing_C::UpdateWarningWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateWarningWidget");

	UWidget_ManualManufacturing_C_UpdateWarningWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCalculatedCurve
// ()
// Parameters:
// float                          Output                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::GetCalculatedCurve(float* Output)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCalculatedCurve");

	UWidget_ManualManufacturing_C_GetCalculatedCurve_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Output != nullptr)
		*Output = params.Output;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowCurrentOutput
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::ShowCurrentOutput()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowCurrentOutput");

	UWidget_ManualManufacturing_C_ShowCurrentOutput_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateProductionStats
// ()

void UWidget_ManualManufacturing_C::UpdateProductionStats()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateProductionStats");

	UWidget_ManualManufacturing_C_UpdateProductionStats_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateProgressBar
// ()

void UWidget_ManualManufacturing_C::UpdateProgressBar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.UpdateProgressBar");

	UWidget_ManualManufacturing_C_UpdateProgressBar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCraftButtonFeedback
// ()

void UWidget_ManualManufacturing_C::GetCraftButtonFeedback()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCraftButtonFeedback");

	UWidget_ManualManufacturing_C_GetCraftButtonFeedback_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitToShowSelectedRecipePhase
// ()

void UWidget_ManualManufacturing_C::InitToShowSelectedRecipePhase()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitToShowSelectedRecipePhase");

	UWidget_ManualManufacturing_C_InitToShowSelectedRecipePhase_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase2ButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetPhase2ButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase2ButtonVisibility");

	UWidget_ManualManufacturing_C_GetPhase2ButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase1ButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetPhase1ButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase1ButtonVisibility");

	UWidget_ManualManufacturing_C_GetPhase1ButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase2ButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_ManualManufacturing_C::GetPhase2ButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase2ButtonEnabled");

	UWidget_ManualManufacturing_C_GetPhase2ButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.IsPhaseUnlocked
// ()
// Parameters:
// TEnumAsByte<EGamePhase>        gamePhase                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           Unlocked                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::IsPhaseUnlocked(TEnumAsByte<EGamePhase> gamePhase, bool* Unlocked)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.IsPhaseUnlocked");

	UWidget_ManualManufacturing_C_IsPhaseUnlocked_Params params;
	params.gamePhase = gamePhase;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Unlocked != nullptr)
		*Unlocked = params.Unlocked;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase1ButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_ManualManufacturing_C::GetPhase1ButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase1ButtonEnabled");

	UWidget_ManualManufacturing_C_GetPhase1ButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase2Visibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetPhase2Visibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase2Visibility");

	UWidget_ManualManufacturing_C_GetPhase2Visibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase1Visibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetPhase1Visibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase1Visibility");

	UWidget_ManualManufacturing_C_GetPhase1Visibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitRecipeLists
// ()

void UWidget_ManualManufacturing_C::InitRecipeLists()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitRecipeLists");

	UWidget_ManualManufacturing_C_InitRecipeLists_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ToggleVisibilityOfPhase
// ()
// Parameters:
// int                            phase                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::ToggleVisibilityOfPhase(int phase)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ToggleVisibilityOfPhase");

	UWidget_ManualManufacturing_C_ToggleVisibilityOfPhase_Params params;
	params.phase = phase;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase0Visibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetPhase0Visibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetPhase0Visibility");

	UWidget_ManualManufacturing_C_GetPhase0Visibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CloseVehicle
// ()

void UWidget_ManualManufacturing_C::CloseVehicle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CloseVehicle");

	UWidget_ManualManufacturing_C_CloseVehicle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetInfoboxVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetInfoboxVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetInfoboxVisibility");

	UWidget_ManualManufacturing_C_GetInfoboxVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCraftingFeedbackVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ManualManufacturing_C::GetCraftingFeedbackVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetCraftingFeedbackVisibility");

	UWidget_ManualManufacturing_C_GetCraftingFeedbackVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetWorkingAtWorkbenchOnServer
// ()
// Parameters:
// class AFGPlayerController*     FGPlayerController             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::SetWorkingAtWorkbenchOnServer(class AFGPlayerController* FGPlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetWorkingAtWorkbenchOnServer");

	UWidget_ManualManufacturing_C_SetWorkingAtWorkbenchOnServer_Params params;
	params.FGPlayerController = FGPlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnCraftCompleted
// ()

void UWidget_ManualManufacturing_C::OnCraftCompleted()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnCraftCompleted");

	UWidget_ManualManufacturing_C_OnCraftCompleted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CreateInfoBox
// ()
// Parameters:
// class UClass*                  mRecipe                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::CreateInfoBox(class UClass* mRecipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.CreateInfoBox");

	UWidget_ManualManufacturing_C_CreateInfoBox_Params params;
	params.mRecipe = mRecipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Cleanup
// ()

void UWidget_ManualManufacturing_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Cleanup");

	UWidget_ManualManufacturing_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetAvailableRecipes
// ()
// Parameters:
// TEnumAsByte<EGamePhase>        ForPhase                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TArray<class UClass*>          AvailableRecipes               (Parm, OutParm, ZeroConstructor)

void UWidget_ManualManufacturing_C::GetAvailableRecipes(TEnumAsByte<EGamePhase> ForPhase, TArray<class UClass*>* AvailableRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.GetAvailableRecipes");

	UWidget_ManualManufacturing_C_GetAvailableRecipes_Params params;
	params.ForPhase = ForPhase;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (AvailableRecipes != nullptr)
		*AvailableRecipes = params.AvailableRecipes;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetSelectedRecipe
// ()
// Parameters:
// class UClass*                  mRecipe                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::SetSelectedRecipe(class UClass* mRecipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetSelectedRecipe");

	UWidget_ManualManufacturing_C_SetSelectedRecipe_Params params;
	params.mRecipe = mRecipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitRecipeList
// ()
// Parameters:
// TEnumAsByte<EGamePhase>        ForPhase                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UScrollBox*              InScrollbox                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_ManualManufacturing_C::InitRecipeList(TEnumAsByte<EGamePhase> ForPhase, class UScrollBox* InScrollbox)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.InitRecipeList");

	UWidget_ManualManufacturing_C_InitRecipeList_Params params;
	params.ForPhase = ForPhase;
	params.InScrollbox = InScrollbox;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Destruct
// ()

void UWidget_ManualManufacturing_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Destruct");

	UWidget_ManualManufacturing_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Construct
// ()

void UWidget_ManualManufacturing_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Construct");

	UWidget_ManualManufacturing_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetupProductionMode
// ()

void UWidget_ManualManufacturing_C::SetupProductionMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.SetupProductionMode");

	UWidget_ManualManufacturing_C_SetupProductionMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnNewRecipeSet
// ()
// Parameters:
// class UClass*                  mNewRecipe                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::OnNewRecipeSet(class UClass* mNewRecipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnNewRecipeSet");

	UWidget_ManualManufacturing_C_OnNewRecipeSet_Params params;
	params.mNewRecipe = mNewRecipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Init
// ()

void UWidget_ManualManufacturing_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Init");

	UWidget_ManualManufacturing_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mAccordionButtonPhase0_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()

void UWidget_ManualManufacturing_C::BndEvt__mAccordionButtonPhase0_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mAccordionButtonPhase0_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_ManualManufacturing_C_BndEvt__mAccordionButtonPhase0_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mAccordionButtonPhase1_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_ManualManufacturing_C::BndEvt__mAccordionButtonPhase1_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mAccordionButtonPhase1_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_ManualManufacturing_C_BndEvt__mAccordionButtonPhase1_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mAccordionButtonPhase2_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
// ()

void UWidget_ManualManufacturing_C::BndEvt__mAccordionButtonPhase2_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.BndEvt__mAccordionButtonPhase2_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature");

	UWidget_ManualManufacturing_C_BndEvt__mAccordionButtonPhase2_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartProducing
// ()
// Parameters:
// float                          produceSpeed                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::StartProducing(float produceSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartProducing");

	UWidget_ManualManufacturing_C_StartProducing_Params params;
	params.produceSpeed = produceSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.EndProducing
// ()

void UWidget_ManualManufacturing_C::EndProducing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.EndProducing");

	UWidget_ManualManufacturing_C_EndProducing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Tick");

	UWidget_ManualManufacturing_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnCraftingProgressbarAnimationLoop
// ()

void UWidget_ManualManufacturing_C::OnCraftingProgressbarAnimationLoop()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.OnCraftingProgressbarAnimationLoop");

	UWidget_ManualManufacturing_C_OnCraftingProgressbarAnimationLoop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartHold
// ()

void UWidget_ManualManufacturing_C::StartHold()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartHold");

	UWidget_ManualManufacturing_C_StartHold_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StopSuperClick
// ()

void UWidget_ManualManufacturing_C::StopSuperClick()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StopSuperClick");

	UWidget_ManualManufacturing_C_StopSuperClick_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartSuperClick
// ()

void UWidget_ManualManufacturing_C::StartSuperClick()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.StartSuperClick");

	UWidget_ManualManufacturing_C_StartSuperClick_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.IncreaseGlow
// ()

void UWidget_ManualManufacturing_C::IncreaseGlow()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.IncreaseGlow");

	UWidget_ManualManufacturing_C_IncreaseGlow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.DecreseGlow
// ()

void UWidget_ManualManufacturing_C::DecreseGlow()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.DecreseGlow");

	UWidget_ManualManufacturing_C_DecreseGlow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Shake
// ()

void UWidget_ManualManufacturing_C::Shake()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.Shake");

	UWidget_ManualManufacturing_C_Shake_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.EmptyBar
// ()

void UWidget_ManualManufacturing_C::EmptyBar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.EmptyBar");

	UWidget_ManualManufacturing_C_EmptyBar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.FadeBar
// ()

void UWidget_ManualManufacturing_C::FadeBar()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.FadeBar");

	UWidget_ManualManufacturing_C_FadeBar_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.WarningMessageCheck
// ()

void UWidget_ManualManufacturing_C::WarningMessageCheck()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.WarningMessageCheck");

	UWidget_ManualManufacturing_C_WarningMessageCheck_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ProductionStartupDelay
// ()
// Parameters:
// float                          produceSpeed                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::ProductionStartupDelay(float produceSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ProductionStartupDelay");

	UWidget_ManualManufacturing_C_ProductionStartupDelay_Params params;
	params.produceSpeed = produceSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.PlayLEDSound
// ()

void UWidget_ManualManufacturing_C::PlayLEDSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.PlayLEDSound");

	UWidget_ManualManufacturing_C_PlayLEDSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowAddedToInventory
// ()

void UWidget_ManualManufacturing_C::ShowAddedToInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ShowAddedToInventory");

	UWidget_ManualManufacturing_C_ShowAddedToInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.HideAddedToInventoryEvent
// ()

void UWidget_ManualManufacturing_C::HideAddedToInventoryEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.HideAddedToInventoryEvent");

	UWidget_ManualManufacturing_C_HideAddedToInventoryEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ExecuteUbergraph_Widget_ManualManufacturing
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManualManufacturing_C::ExecuteUbergraph_Widget_ManualManufacturing(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManualManufacturing.Widget_ManualManufacturing_C.ExecuteUbergraph_Widget_ManualManufacturing");

	UWidget_ManualManufacturing_C_ExecuteUbergraph_Widget_ManualManufacturing_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
