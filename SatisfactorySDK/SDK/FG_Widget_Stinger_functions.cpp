// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Stinger_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Stinger.Widget_Stinger_C.ShowSmallIcons
// ()

void UWidget_Stinger_C::ShowSmallIcons()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Stinger.Widget_Stinger_C.ShowSmallIcons");

	UWidget_Stinger_C_ShowSmallIcons_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Stinger.Widget_Stinger_C.ExecuteUbergraph_Widget_Stinger
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Stinger_C::ExecuteUbergraph_Widget_Stinger(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Stinger.Widget_Stinger_C.ExecuteUbergraph_Widget_Stinger");

	UWidget_Stinger_C_ExecuteUbergraph_Widget_Stinger_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
