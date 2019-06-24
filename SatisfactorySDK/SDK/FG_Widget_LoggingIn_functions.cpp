// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LoggingIn_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_LoggingIn.Widget_LoggingIn_C.ExecuteUbergraph_Widget_LoggingIn
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_LoggingIn_C::ExecuteUbergraph_Widget_LoggingIn(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_LoggingIn.Widget_LoggingIn_C.ExecuteUbergraph_Widget_LoggingIn");

	UWidget_LoggingIn_C_ExecuteUbergraph_Widget_LoggingIn_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
