// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PassengerSeat_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PassengerSeat.Widget_PassengerSeat_C.Construct
// ()

void UWidget_PassengerSeat_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PassengerSeat.Widget_PassengerSeat_C.Construct");

	UWidget_PassengerSeat_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PassengerSeat.Widget_PassengerSeat_C.ExecuteUbergraph_Widget_PassengerSeat
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PassengerSeat_C::ExecuteUbergraph_Widget_PassengerSeat(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PassengerSeat.Widget_PassengerSeat_C.ExecuteUbergraph_Widget_PassengerSeat");

	UWidget_PassengerSeat_C_ExecuteUbergraph_Widget_PassengerSeat_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
