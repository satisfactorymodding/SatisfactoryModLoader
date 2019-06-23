// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TakeDamageIndicator_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.SetRotation
// ()

void UWidget_TakeDamageIndicator_C::SetRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.SetRotation");

	UWidget_TakeDamageIndicator_C_SetRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.DestroySelf
// ()

void UWidget_TakeDamageIndicator_C::DestroySelf()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.DestroySelf");

	UWidget_TakeDamageIndicator_C_DestroySelf_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.Construct
// ()

void UWidget_TakeDamageIndicator_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.Construct");

	UWidget_TakeDamageIndicator_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TakeDamageIndicator_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.Tick");

	UWidget_TakeDamageIndicator_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.ExecuteUbergraph_Widget_TakeDamageIndicator
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TakeDamageIndicator_C::ExecuteUbergraph_Widget_TakeDamageIndicator(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TakeDamageIndicator.Widget_TakeDamageIndicator_C.ExecuteUbergraph_Widget_TakeDamageIndicator");

	UWidget_TakeDamageIndicator_C_ExecuteUbergraph_Widget_TakeDamageIndicator_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
