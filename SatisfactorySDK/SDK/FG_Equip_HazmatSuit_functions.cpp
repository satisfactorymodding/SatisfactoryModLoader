// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_HazmatSuit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_HazmatSuit.Equip_HazmatSuit_C.EnablePostProcessing
// ()
// Parameters:
// bool                           Enabled                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_HazmatSuit_C::EnablePostProcessing(bool Enabled)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.EnablePostProcessing");

	AEquip_HazmatSuit_C_EnablePostProcessing_Params params;
	params.Enabled = Enabled;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_HazmatSuit.Equip_HazmatSuit_C.AdjustDamage
// ()
// Parameters:
// float*                         damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float AEquip_HazmatSuit_C::AdjustDamage(float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.AdjustDamage");

	AEquip_HazmatSuit_C_AdjustDamage_Params params;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Equip_HazmatSuit.Equip_HazmatSuit_C.UserConstructionScript
// ()

void AEquip_HazmatSuit_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.UserConstructionScript");

	AEquip_HazmatSuit_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_HazmatSuit.Equip_HazmatSuit_C.WasUnEquipped
// ()

void AEquip_HazmatSuit_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.WasUnEquipped");

	AEquip_HazmatSuit_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_HazmatSuit.Equip_HazmatSuit_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_HazmatSuit_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.ReceiveTick");

	AEquip_HazmatSuit_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_HazmatSuit.Equip_HazmatSuit_C.WasEquipped
// ()

void AEquip_HazmatSuit_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.WasEquipped");

	AEquip_HazmatSuit_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_HazmatSuit.Equip_HazmatSuit_C.ExecuteUbergraph_Equip_HazmatSuit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_HazmatSuit_C::ExecuteUbergraph_Equip_HazmatSuit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_HazmatSuit.Equip_HazmatSuit_C.ExecuteUbergraph_Equip_HazmatSuit");

	AEquip_HazmatSuit_C_ExecuteUbergraph_Equip_HazmatSuit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
