// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMode_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildMode.Widget_BuildMode_C.CheckHologramState
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_BuildMode_C::CheckHologramState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.CheckHologramState");

	UWidget_BuildMode_C_CheckHologramState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMode.Widget_BuildMode_C.GetBuildDisqualifiersVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_BuildMode_C::GetBuildDisqualifiersVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.GetBuildDisqualifiersVisibility");

	UWidget_BuildMode_C_GetBuildDisqualifiersVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMode.Widget_BuildMode_C.GetBuildDisqualifiersText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_BuildMode_C::GetBuildDisqualifiersText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.GetBuildDisqualifiersText");

	UWidget_BuildMode_C_GetBuildDisqualifiersText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMode.Widget_BuildMode_C.UpdateCost
// ()

void UWidget_BuildMode_C::UpdateCost()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.UpdateCost");

	UWidget_BuildMode_C_UpdateCost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.CreateCostSlots
// ()

void UWidget_BuildMode_C::CreateCostSlots()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.CreateCostSlots");

	UWidget_BuildMode_C_CreateCostSlots_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.GetTextColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_BuildMode_C::GetTextColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.GetTextColor");

	UWidget_BuildMode_C_GetTextColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildMode.Widget_BuildMode_C.OnEscapePressed
// ()

void UWidget_BuildMode_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.OnEscapePressed");

	UWidget_BuildMode_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.Construct
// ()

void UWidget_BuildMode_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.Construct");

	UWidget_BuildMode_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMode_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.Tick");

	UWidget_BuildMode_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.PlayDismantleAnimation
// ()

void UWidget_BuildMode_C::PlayDismantleAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.PlayDismantleAnimation");

	UWidget_BuildMode_C_PlayDismantleAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.StopDismantleAnimation
// ()

void UWidget_BuildMode_C::StopDismantleAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.StopDismantleAnimation");

	UWidget_BuildMode_C_StopDismantleAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMode.Widget_BuildMode_C.ExecuteUbergraph_Widget_BuildMode
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMode_C::ExecuteUbergraph_Widget_BuildMode(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMode.Widget_BuildMode_C.ExecuteUbergraph_Widget_BuildMode");

	UWidget_BuildMode_C_ExecuteUbergraph_Widget_BuildMode_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
