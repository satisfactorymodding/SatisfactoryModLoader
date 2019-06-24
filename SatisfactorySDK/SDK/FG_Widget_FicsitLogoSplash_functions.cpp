// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_FicsitLogoSplash_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_FicsitLogoSplash.Widget_FicsitLogoSplash_C.ShowLogo
// ()

void UWidget_FicsitLogoSplash_C::ShowLogo()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FicsitLogoSplash.Widget_FicsitLogoSplash_C.ShowLogo");

	UWidget_FicsitLogoSplash_C_ShowLogo_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_FicsitLogoSplash.Widget_FicsitLogoSplash_C.ExecuteUbergraph_Widget_FicsitLogoSplash
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_FicsitLogoSplash_C::ExecuteUbergraph_Widget_FicsitLogoSplash(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_FicsitLogoSplash.Widget_FicsitLogoSplash_C.ExecuteUbergraph_Widget_FicsitLogoSplash");

	UWidget_FicsitLogoSplash_C_ExecuteUbergraph_Widget_FicsitLogoSplash_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
