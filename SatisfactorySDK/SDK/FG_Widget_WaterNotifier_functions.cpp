// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_WaterNotifier_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_WaterNotifier.Widget_WaterNotifier_C.SetTitleText
// ()
// Parameters:
// struct FText                   messageText                    (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_WaterNotifier_C::SetTitleText(const struct FText& messageText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_WaterNotifier.Widget_WaterNotifier_C.SetTitleText");

	UWidget_WaterNotifier_C_SetTitleText_Params params;
	params.messageText = messageText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_WaterNotifier.Widget_WaterNotifier_C.SetMessageText
// ()
// Parameters:
// struct FText                   messageText                    (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_WaterNotifier_C::SetMessageText(const struct FText& messageText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_WaterNotifier.Widget_WaterNotifier_C.SetMessageText");

	UWidget_WaterNotifier_C_SetMessageText_Params params;
	params.messageText = messageText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_WaterNotifier.Widget_WaterNotifier_C.Construct
// ()

void UWidget_WaterNotifier_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_WaterNotifier.Widget_WaterNotifier_C.Construct");

	UWidget_WaterNotifier_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_WaterNotifier.Widget_WaterNotifier_C.RemoveNotifier
// ()

void UWidget_WaterNotifier_C::RemoveNotifier()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_WaterNotifier.Widget_WaterNotifier_C.RemoveNotifier");

	UWidget_WaterNotifier_C_RemoveNotifier_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_WaterNotifier.Widget_WaterNotifier_C.ExecuteUbergraph_Widget_WaterNotifier
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_WaterNotifier_C::ExecuteUbergraph_Widget_WaterNotifier(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_WaterNotifier.Widget_WaterNotifier_C.ExecuteUbergraph_Widget_WaterNotifier");

	UWidget_WaterNotifier_C_ExecuteUbergraph_Widget_WaterNotifier_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
