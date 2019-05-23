// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Machinegun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_Machinegun.Equip_Machinegun_C.UserConstructionScript
// ()

void AEquip_Machinegun_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.UserConstructionScript");

	AEquip_Machinegun_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.ReceiveBeginPlay
// ()

void AEquip_Machinegun_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.ReceiveBeginPlay");

	AEquip_Machinegun_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.PlayReloadEffects
// ()

void AEquip_Machinegun_C::PlayReloadEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.PlayReloadEffects");

	AEquip_Machinegun_C_PlayReloadEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Machinegun_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.ReceiveTick");

	AEquip_Machinegun_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.SwitchHUD
// ()
// Parameters:
// bool                           ShowHUD                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Machinegun_C::SwitchHUD(bool ShowHUD)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.SwitchHUD");

	AEquip_Machinegun_C_SwitchHUD_Params params;
	params.ShowHUD = ShowHUD;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.WasUnEquipped
// ()

void AEquip_Machinegun_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.WasUnEquipped");

	AEquip_Machinegun_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.WasEquipped
// ()

void AEquip_Machinegun_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.WasEquipped");

	AEquip_Machinegun_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.PlayFireEffect
// ()

void AEquip_Machinegun_C::PlayFireEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.PlayFireEffect");

	AEquip_Machinegun_C_PlayFireEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.ExecuteUbergraph_Equip_Machinegun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Machinegun_C::ExecuteUbergraph_Equip_Machinegun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.ExecuteUbergraph_Equip_Machinegun");

	AEquip_Machinegun_C_ExecuteUbergraph_Equip_Machinegun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Machinegun.Equip_Machinegun_C.Fire__DelegateSignature
// ()

void AEquip_Machinegun_C::Fire__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Machinegun.Equip_Machinegun_C.Fire__DelegateSignature");

	AEquip_Machinegun_C_Fire__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
