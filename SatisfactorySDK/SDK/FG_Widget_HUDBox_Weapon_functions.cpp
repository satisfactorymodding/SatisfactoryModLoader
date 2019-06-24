// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Weapon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.UpdateAmmoSlot
// ()

void UWidget_HUDBox_Weapon_C::UpdateAmmoSlot()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.UpdateAmmoSlot");

	UWidget_HUDBox_Weapon_C_UpdateAmmoSlot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.UpdateContent
// ()

void UWidget_HUDBox_Weapon_C::UpdateContent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.UpdateContent");

	UWidget_HUDBox_Weapon_C_UpdateContent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Weapon_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.Tick");

	UWidget_HUDBox_Weapon_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.Construct
// ()

void UWidget_HUDBox_Weapon_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.Construct");

	UWidget_HUDBox_Weapon_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.ExecuteUbergraph_Widget_HUDBox_Weapon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Weapon_C::ExecuteUbergraph_Widget_HUDBox_Weapon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Weapon.Widget_HUDBox_Weapon_C.ExecuteUbergraph_Widget_HUDBox_Weapon");

	UWidget_HUDBox_Weapon_C_ExecuteUbergraph_Widget_HUDBox_Weapon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
