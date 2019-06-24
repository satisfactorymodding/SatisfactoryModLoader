// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildGunDelay_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.GetWidgetVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_BuildGunDelay_C::GetWidgetVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.GetWidgetVisibility");

	UWidget_BuildGunDelay_C_GetWidgetVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildGunDelay_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.Tick");

	UWidget_BuildGunDelay_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.Construct
// ()

void UWidget_BuildGunDelay_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.Construct");

	UWidget_BuildGunDelay_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.ExecuteUbergraph_Widget_BuildGunDelay
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildGunDelay_C::ExecuteUbergraph_Widget_BuildGunDelay(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildGunDelay.Widget_BuildGunDelay_C.ExecuteUbergraph_Widget_BuildGunDelay");

	UWidget_BuildGunDelay_C_ExecuteUbergraph_Widget_BuildGunDelay_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
