// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_ColorGun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDBox_ColorGun.Widget_HUDBox_ColorGun_C.Construct
// ()

void UWidget_HUDBox_ColorGun_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_ColorGun.Widget_HUDBox_ColorGun_C.Construct");

	UWidget_HUDBox_ColorGun_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_ColorGun.Widget_HUDBox_ColorGun_C.UpdateColors
// ()

void UWidget_HUDBox_ColorGun_C::UpdateColors()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_ColorGun.Widget_HUDBox_ColorGun_C.UpdateColors");

	UWidget_HUDBox_ColorGun_C_UpdateColors_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_ColorGun.Widget_HUDBox_ColorGun_C.ExecuteUbergraph_Widget_HUDBox_ColorGun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_ColorGun_C::ExecuteUbergraph_Widget_HUDBox_ColorGun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_ColorGun.Widget_HUDBox_ColorGun_C.ExecuteUbergraph_Widget_HUDBox_ColorGun");

	UWidget_HUDBox_ColorGun_C_ExecuteUbergraph_Widget_HUDBox_ColorGun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
