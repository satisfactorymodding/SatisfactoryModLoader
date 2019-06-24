// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_ColorGun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_ColorGun.Equip_ColorGun_C.UserConstructionScript
// ()

void AEquip_ColorGun_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.UserConstructionScript");

	AEquip_ColorGun_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.ToggleColorPickerUI
// ()

void AEquip_ColorGun_C::ToggleColorPickerUI()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.ToggleColorPickerUI");

	AEquip_ColorGun_C_ToggleColorPickerUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.PlayFireEffect
// ()

void AEquip_ColorGun_C::PlayFireEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.PlayFireEffect");

	AEquip_ColorGun_C_PlayFireEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.PlayReloadEffects
// ()

void AEquip_ColorGun_C::PlayReloadEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.PlayReloadEffects");

	AEquip_ColorGun_C_PlayReloadEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.WasEquipped
// ()

void AEquip_ColorGun_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.WasEquipped");

	AEquip_ColorGun_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.Event Clear Color Picker UI
// ()

void AEquip_ColorGun_C::Event_Clear_Color_Picker_UI()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.Event Clear Color Picker UI");

	AEquip_ColorGun_C_Event_Clear_Color_Picker_UI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.WasUnEquipped
// ()

void AEquip_ColorGun_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.WasUnEquipped");

	AEquip_ColorGun_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ColorGun.Equip_ColorGun_C.ExecuteUbergraph_Equip_ColorGun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_ColorGun_C::ExecuteUbergraph_Equip_ColorGun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ColorGun.Equip_ColorGun_C.ExecuteUbergraph_Equip_ColorGun");

	AEquip_ColorGun_C_ExecuteUbergraph_Equip_ColorGun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
