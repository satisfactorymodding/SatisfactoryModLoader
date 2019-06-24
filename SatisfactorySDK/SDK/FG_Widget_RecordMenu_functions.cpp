// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RecordMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RecordMenu.Widget_RecordMenu_C.SetNameAtIndex
// ()
// Parameters:
// struct FText                   Name                           (BlueprintVisible, BlueprintReadOnly, Parm)
// int                            Int                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RecordMenu_C::SetNameAtIndex(const struct FText& Name, int Int)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.SetNameAtIndex");

	UWidget_RecordMenu_C_SetNameAtIndex_Params params;
	params.Name = Name;
	params.Int = Int;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.UpdateLabels
// ()

void UWidget_RecordMenu_C::UpdateLabels()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.UpdateLabels");

	UWidget_RecordMenu_C_UpdateLabels_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.GetPositionInCircle
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               Translation                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_RecordMenu_C::GetPositionInCircle(int Index, struct FVector2D* Translation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.GetPositionInCircle");

	UWidget_RecordMenu_C_GetPositionInCircle_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Translation != nullptr)
		*Translation = params.Translation;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.GetPauseEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_RecordMenu_C::GetPauseEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.GetPauseEnabled");

	UWidget_RecordMenu_C_GetPauseEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.Construct
// ()

void UWidget_RecordMenu_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.Construct");

	UWidget_RecordMenu_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.ToggleRecording
// ()

void UWidget_RecordMenu_C::ToggleRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.ToggleRecording");

	UWidget_RecordMenu_C_ToggleRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.Destruct
// ()

void UWidget_RecordMenu_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.Destruct");

	UWidget_RecordMenu_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.ClearPathRecording
// ()

void UWidget_RecordMenu_C::ClearPathRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.ClearPathRecording");

	UWidget_RecordMenu_C_ClearPathRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.PauseClicked
// ()

void UWidget_RecordMenu_C::PauseClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.PauseClicked");

	UWidget_RecordMenu_C_PauseClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.AutoPilotClicked
// ()

void UWidget_RecordMenu_C::AutoPilotClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.AutoPilotClicked");

	UWidget_RecordMenu_C_AutoPilotClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.PathVisibilityClicked
// ()

void UWidget_RecordMenu_C::PathVisibilityClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.PathVisibilityClicked");

	UWidget_RecordMenu_C_PathVisibilityClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RecordMenu_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.Tick");

	UWidget_RecordMenu_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecordMenu.Widget_RecordMenu_C.ExecuteUbergraph_Widget_RecordMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RecordMenu_C::ExecuteUbergraph_Widget_RecordMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecordMenu.Widget_RecordMenu_C.ExecuteUbergraph_Widget_RecordMenu");

	UWidget_RecordMenu_C_ExecuteUbergraph_Widget_RecordMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
