// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_ShockShank_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_ShockShank.Equip_ShockShank_C.UserConstructionScript
// ()

void AEquip_ShockShank_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ShockShank.Equip_ShockShank_C.UserConstructionScript");

	AEquip_ShockShank_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ShockShank.Equip_ShockShank_C.WasUnEquipped
// ()

void AEquip_ShockShank_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ShockShank.Equip_ShockShank_C.WasUnEquipped");

	AEquip_ShockShank_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ShockShank.Equip_ShockShank_C.PlayStunEffects
// ()

void AEquip_ShockShank_C::PlayStunEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ShockShank.Equip_ShockShank_C.PlayStunEffects");

	AEquip_ShockShank_C_PlayStunEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ShockShank.Equip_ShockShank_C.OnHitTarget
// ()

void AEquip_ShockShank_C::OnHitTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ShockShank.Equip_ShockShank_C.OnHitTarget");

	AEquip_ShockShank_C_OnHitTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ShockShank.Equip_ShockShank_C.WasEquipped
// ()

void AEquip_ShockShank_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ShockShank.Equip_ShockShank_C.WasEquipped");

	AEquip_ShockShank_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_ShockShank.Equip_ShockShank_C.ExecuteUbergraph_Equip_ShockShank
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_ShockShank_C::ExecuteUbergraph_Equip_ShockShank(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_ShockShank.Equip_ShockShank_C.ExecuteUbergraph_Equip_ShockShank");

	AEquip_ShockShank_C_ExecuteUbergraph_Equip_ShockShank_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
