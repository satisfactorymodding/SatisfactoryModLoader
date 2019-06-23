// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CoffeeSplash_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_CoffeeSplash_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.OnKeyDown");

	UWidget_CoffeeSplash_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.Construct
// ()

void UWidget_CoffeeSplash_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.Construct");

	UWidget_CoffeeSplash_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_CoffeeSplash_C::BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_CoffeeSplash_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.HideSplash
// ()

void UWidget_CoffeeSplash_C::HideSplash()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.HideSplash");

	UWidget_CoffeeSplash_C_HideSplash_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.Cleanup
// ()

void UWidget_CoffeeSplash_C::Cleanup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.Cleanup");

	UWidget_CoffeeSplash_C_Cleanup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.ExecuteUbergraph_Widget_CoffeeSplash
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CoffeeSplash_C::ExecuteUbergraph_Widget_CoffeeSplash(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CoffeeSplash.Widget_CoffeeSplash_C.ExecuteUbergraph_Widget_CoffeeSplash");

	UWidget_CoffeeSplash_C_ExecuteUbergraph_Widget_CoffeeSplash_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
