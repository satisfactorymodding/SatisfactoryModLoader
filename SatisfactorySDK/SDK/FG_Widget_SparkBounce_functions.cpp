// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SparkBounce_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SparkBounce.Widget_SparkBounce_C.Construct
// ()

void UWidget_SparkBounce_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SparkBounce.Widget_SparkBounce_C.Construct");

	UWidget_SparkBounce_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SparkBounce.Widget_SparkBounce_C.OnAnimFinished
// ()

void UWidget_SparkBounce_C::OnAnimFinished()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SparkBounce.Widget_SparkBounce_C.OnAnimFinished");

	UWidget_SparkBounce_C_OnAnimFinished_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SparkBounce.Widget_SparkBounce_C.ExecuteUbergraph_Widget_SparkBounce
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SparkBounce_C::ExecuteUbergraph_Widget_SparkBounce(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SparkBounce.Widget_SparkBounce_C.ExecuteUbergraph_Widget_SparkBounce");

	UWidget_SparkBounce_C_ExecuteUbergraph_Widget_SparkBounce_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
