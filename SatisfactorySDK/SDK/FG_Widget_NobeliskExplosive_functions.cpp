// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NobeliskExplosive_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_NobeliskExplosive.Widget_NobeliskExplosive_C.Get_mNobeliskThrowbar_Visibility_1
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_NobeliskExplosive_C::Get_mNobeliskThrowbar_Visibility_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NobeliskExplosive.Widget_NobeliskExplosive_C.Get_mNobeliskThrowbar_Visibility_1");

	UWidget_NobeliskExplosive_C_Get_mNobeliskThrowbar_Visibility_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_NobeliskExplosive.Widget_NobeliskExplosive_C.Get_mNobeliskThrowbar_FillColorAndOpacity_1
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_NobeliskExplosive_C::Get_mNobeliskThrowbar_FillColorAndOpacity_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NobeliskExplosive.Widget_NobeliskExplosive_C.Get_mNobeliskThrowbar_FillColorAndOpacity_1");

	UWidget_NobeliskExplosive_C_Get_mNobeliskThrowbar_FillColorAndOpacity_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_NobeliskExplosive.Widget_NobeliskExplosive_C.GetThrowPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_NobeliskExplosive_C::GetThrowPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_NobeliskExplosive.Widget_NobeliskExplosive_C.GetThrowPercent");

	UWidget_NobeliskExplosive_C_GetThrowPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
