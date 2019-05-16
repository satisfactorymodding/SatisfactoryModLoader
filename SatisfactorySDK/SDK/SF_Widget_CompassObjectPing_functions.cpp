// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CompassObjectPing_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CompassObjectPing.Widget_CompassObjectPing_C.Construct
// ()

void UWidget_CompassObjectPing_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectPing.Widget_CompassObjectPing_C.Construct");

	UWidget_CompassObjectPing_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CompassObjectPing.Widget_CompassObjectPing_C.ExecuteUbergraph_Widget_CompassObjectPing
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CompassObjectPing_C::ExecuteUbergraph_Widget_CompassObjectPing(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CompassObjectPing.Widget_CompassObjectPing_C.ExecuteUbergraph_Widget_CompassObjectPing");

	UWidget_CompassObjectPing_C_ExecuteUbergraph_Widget_CompassObjectPing_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
