// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MAM_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MAM.Widget_MAM_C.WidgetFactory
// ()
// Parameters:
// class UClass*                  PopupClass                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TArray<class UUserWidget*>     out_widgets                    (Parm, OutParm, ZeroConstructor)

void UWidget_MAM_C::WidgetFactory(class UClass* PopupClass, TArray<class UUserWidget*>* out_widgets)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.WidgetFactory");

	UWidget_MAM_C_WidgetFactory_Params params;
	params.PopupClass = PopupClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_widgets != nullptr)
		*out_widgets = params.out_widgets;
}


// Function Widget_MAM.Widget_MAM_C.IsValidResearchReward
// ()
// Parameters:
// struct FResearchRecipeReward   researchReward                 (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           Valid                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::IsValidResearchReward(const struct FResearchRecipeReward& researchReward, bool* Valid)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.IsValidResearchReward");

	UWidget_MAM_C_IsValidResearchReward_Params params;
	params.researchReward = researchReward;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Valid != nullptr)
		*Valid = params.Valid;
}


// Function Widget_MAM.Widget_MAM_C.CheckResearchStatusOnStart
// ()

void UWidget_MAM_C::CheckResearchStatusOnStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.CheckResearchStatusOnStart");

	UWidget_MAM_C_CheckResearchStatusOnStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.CreatePopup
// ()
// Parameters:
// class UClass*                  Research_Recipe                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::CreatePopup(class UClass* Research_Recipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.CreatePopup");

	UWidget_MAM_C_CreatePopup_Params params;
	params.Research_Recipe = Research_Recipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.GetScreenTitle
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_MAM_C::GetScreenTitle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetScreenTitle");

	UWidget_MAM_C_GetScreenTitle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAM.Widget_MAM_C.GetPercentageText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_MAM_C::GetPercentageText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetPercentageText");

	UWidget_MAM_C_GetPercentageText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAM.Widget_MAM_C.GetResearchPercentage
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_MAM_C::GetResearchPercentage()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetResearchPercentage");

	UWidget_MAM_C_GetResearchPercentage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAM.Widget_MAM_C.ScanEffect
// ()

void UWidget_MAM_C::ScanEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.ScanEffect");

	UWidget_MAM_C_ScanEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnResearchStateChange
// ()
// Parameters:
// class UClass*                  Research                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::OnResearchStateChange(class UClass* Research)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnResearchStateChange");

	UWidget_MAM_C_OnResearchStateChange_Params params;
	params.Research = Research;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnResearchRewardsClaimed
// ()
// Parameters:
// class UClass*                  Research                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::OnResearchRewardsClaimed(class UClass* Research)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnResearchRewardsClaimed");

	UWidget_MAM_C_OnResearchRewardsClaimed_Params params;
	params.Research = Research;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.UpdateButtonStates
// ()

void UWidget_MAM_C::UpdateButtonStates()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.UpdateButtonStates");

	UWidget_MAM_C_UpdateButtonStates_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnResearchCompleted
// ()
// Parameters:
// class UClass*                  Research                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::OnResearchCompleted(class UClass* Research)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnResearchCompleted");

	UWidget_MAM_C_OnResearchCompleted_Params params;
	params.Research = Research;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.GetResearchTimeLeft
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_MAM_C::GetResearchTimeLeft()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetResearchTimeLeft");

	UWidget_MAM_C_GetResearchTimeLeft_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAM.Widget_MAM_C.CanStartAnalyzing
// ()
// Parameters:
// bool                           Value                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::CanStartAnalyzing(bool* Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.CanStartAnalyzing");

	UWidget_MAM_C_CanStartAnalyzing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Value != nullptr)
		*Value = params.Value;
}


// Function Widget_MAM.Widget_MAM_C.OnResearchPaidOff
// ()
// Parameters:
// class UClass*                  Research                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::OnResearchPaidOff(class UClass* Research)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnResearchPaidOff");

	UWidget_MAM_C_OnResearchPaidOff_Params params;
	params.Research = Research;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.GetManufacturingInfoVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_MAM_C::GetManufacturingInfoVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetManufacturingInfoVisibility");

	UWidget_MAM_C_GetManufacturingInfoVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAM.Widget_MAM_C.GetInfoboxVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_MAM_C::GetInfoboxVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetInfoboxVisibility");

	UWidget_MAM_C_GetInfoboxVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_MAM.Widget_MAM_C.SetWorkingAtMAMOnServer
// ()
// Parameters:
// class AFGPlayerController*     FGPlayerController             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::SetWorkingAtMAMOnServer(class AFGPlayerController* FGPlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.SetWorkingAtMAMOnServer");

	UWidget_MAM_C_SetWorkingAtMAMOnServer_Params params;
	params.FGPlayerController = FGPlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.CreateInfoBox
// ()
// Parameters:
// class UClass*                  mRecipe                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::CreateInfoBox(class UClass* mRecipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.CreateInfoBox");

	UWidget_MAM_C_CreateInfoBox_Params params;
	params.mRecipe = mRecipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.Cleanup
// ()

void UWidget_MAM_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.Cleanup");

	UWidget_MAM_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.GetAvailableResearch
// ()
// Parameters:
// TArray<class UClass*>          AvailableRecipes               (Parm, OutParm, ZeroConstructor)

void UWidget_MAM_C::GetAvailableResearch(TArray<class UClass*>* AvailableRecipes)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.GetAvailableResearch");

	UWidget_MAM_C_GetAvailableResearch_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (AvailableRecipes != nullptr)
		*AvailableRecipes = params.AvailableRecipes;
}


// Function Widget_MAM.Widget_MAM_C.SetSelectedRecipe
// ()
// Parameters:
// class UClass*                  mRecipe                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::SetSelectedRecipe(class UClass* mRecipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.SetSelectedRecipe");

	UWidget_MAM_C_SetSelectedRecipe_Params params;
	params.mRecipe = mRecipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.InitRecipeList
// ()

void UWidget_MAM_C::InitRecipeList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.InitRecipeList");

	UWidget_MAM_C_InitRecipeList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.Construct
// ()

void UWidget_MAM_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.Construct");

	UWidget_MAM_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.Tick");

	UWidget_MAM_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnButtonClicked
// ()

void UWidget_MAM_C::OnButtonClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnButtonClicked");

	UWidget_MAM_C_OnButtonClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.Destruct
// ()

void UWidget_MAM_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.Destruct");

	UWidget_MAM_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.Init
// ()

void UWidget_MAM_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.Init");

	UWidget_MAM_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnListbuttonClicked
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_ListButton_C*    ListButton                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MAM_C::OnListbuttonClicked(int Index, class UWidget_ListButton_C* ListButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnListbuttonClicked");

	UWidget_MAM_C_OnListbuttonClicked_Params params;
	params.Index = Index;
	params.ListButton = ListButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnPopupButtonClicked
// ()
// Parameters:
// bool                           Bool                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::OnPopupButtonClicked(bool Bool)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnPopupButtonClicked");

	UWidget_MAM_C_OnPopupButtonClicked_Params params;
	params.Bool = Bool;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnAnalyseAnimStart
// ()

void UWidget_MAM_C::OnAnalyseAnimStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnAnalyseAnimStart");

	UWidget_MAM_C_OnAnalyseAnimStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.OnNewRecipeSet
// ()
// Parameters:
// class UClass*                  mNewRecipe                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::OnNewRecipeSet(class UClass* mNewRecipe)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.OnNewRecipeSet");

	UWidget_MAM_C_OnNewRecipeSet_Params params;
	params.mNewRecipe = mNewRecipe;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.NotifyPopupClosed
// ()
// Parameters:
// class UClass*                  PopupClass                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            exitCode                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::NotifyPopupClosed(class UClass* PopupClass, int exitCode)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.NotifyPopupClosed");

	UWidget_MAM_C_NotifyPopupClosed_Params params;
	params.PopupClass = PopupClass;
	params.exitCode = exitCode;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MAM.Widget_MAM_C.ExecuteUbergraph_Widget_MAM
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MAM_C::ExecuteUbergraph_Widget_MAM(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MAM.Widget_MAM_C.ExecuteUbergraph_Widget_MAM");

	UWidget_MAM_C_ExecuteUbergraph_Widget_MAM_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
