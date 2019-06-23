// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MessageNotifier_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MessageNotifier.Widget_MessageNotifier_C.GetKeyForAction
// ()
// Parameters:
// struct FText                   keyText                        (Parm, OutParm)

void UWidget_MessageNotifier_C::GetKeyForAction(struct FText* keyText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MessageNotifier.Widget_MessageNotifier_C.GetKeyForAction");

	UWidget_MessageNotifier_C_GetKeyForAction_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (keyText != nullptr)
		*keyText = params.keyText;
}


// Function Widget_MessageNotifier.Widget_MessageNotifier_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MessageNotifier_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MessageNotifier.Widget_MessageNotifier_C.PreConstruct");

	UWidget_MessageNotifier_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MessageNotifier.Widget_MessageNotifier_C.Construct
// ()

void UWidget_MessageNotifier_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MessageNotifier.Widget_MessageNotifier_C.Construct");

	UWidget_MessageNotifier_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MessageNotifier.Widget_MessageNotifier_C.RemoveNotifier
// ()

void UWidget_MessageNotifier_C::RemoveNotifier()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MessageNotifier.Widget_MessageNotifier_C.RemoveNotifier");

	UWidget_MessageNotifier_C_RemoveNotifier_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MessageNotifier.Widget_MessageNotifier_C.ExecuteUbergraph_Widget_MessageNotifier
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MessageNotifier_C::ExecuteUbergraph_Widget_MessageNotifier(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MessageNotifier.Widget_MessageNotifier_C.ExecuteUbergraph_Widget_MessageNotifier");

	UWidget_MessageNotifier_C_ExecuteUbergraph_Widget_MessageNotifier_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
