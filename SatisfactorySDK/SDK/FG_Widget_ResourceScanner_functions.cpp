// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ResourceScanner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ResourceScanner.Widget_ResourceScanner_C.Construct
// ()

void UWidget_ResourceScanner_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceScanner.Widget_ResourceScanner_C.Construct");

	UWidget_ResourceScanner_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceScanner.Widget_ResourceScanner_C.Destruct
// ()

void UWidget_ResourceScanner_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceScanner.Widget_ResourceScanner_C.Destruct");

	UWidget_ResourceScanner_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ResourceScanner.Widget_ResourceScanner_C.ExecuteUbergraph_Widget_ResourceScanner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ResourceScanner_C::ExecuteUbergraph_Widget_ResourceScanner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ResourceScanner.Widget_ResourceScanner_C.ExecuteUbergraph_Widget_ResourceScanner");

	UWidget_ResourceScanner_C_ExecuteUbergraph_Widget_ResourceScanner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
