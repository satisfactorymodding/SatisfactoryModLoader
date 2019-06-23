// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AlphaInfoScreen_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.GetExperimentalVisibility
// ()

void UWidget_AlphaInfoScreen_C::GetExperimentalVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.GetExperimentalVisibility");

	UWidget_AlphaInfoScreen_C_GetExperimentalVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
// ()

void UWidget_AlphaInfoScreen_C::BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature");

	UWidget_AlphaInfoScreen_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.Construct
// ()

void UWidget_AlphaInfoScreen_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.Construct");

	UWidget_AlphaInfoScreen_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.ExecuteUbergraph_Widget_AlphaInfoScreen
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_AlphaInfoScreen_C::ExecuteUbergraph_Widget_AlphaInfoScreen(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_AlphaInfoScreen.Widget_AlphaInfoScreen_C.ExecuteUbergraph_Widget_AlphaInfoScreen");

	UWidget_AlphaInfoScreen_C_ExecuteUbergraph_Widget_AlphaInfoScreen_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
