// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorSquare_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ColorSquare.Widget_ColorSquare_C.GetBorderColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_ColorSquare_C::GetBorderColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorSquare.Widget_ColorSquare_C.GetBorderColor");

	UWidget_ColorSquare_C_GetBorderColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ColorSquare.Widget_ColorSquare_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_ColorSquare_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorSquare.Widget_ColorSquare_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature");

	UWidget_ColorSquare_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ColorSquare.Widget_ColorSquare_C.ExecuteUbergraph_Widget_ColorSquare
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ColorSquare_C::ExecuteUbergraph_Widget_ColorSquare(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ColorSquare.Widget_ColorSquare_C.ExecuteUbergraph_Widget_ColorSquare");

	UWidget_ColorSquare_C_ExecuteUbergraph_Widget_ColorSquare_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
