// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_GasMask_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_GasMask.Equip_GasMask_C.EnablePostProcessing
// ()
// Parameters:
// bool                           mEnabled                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_GasMask_C::EnablePostProcessing(bool mEnabled)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.EnablePostProcessing");

	AEquip_GasMask_C_EnablePostProcessing_Params params;
	params.mEnabled = mEnabled;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_GasMask.Equip_GasMask_C.AdjustDamage
// ()
// Parameters:
// float*                         damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float AEquip_GasMask_C::AdjustDamage(float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.AdjustDamage");

	AEquip_GasMask_C_AdjustDamage_Params params;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Equip_GasMask.Equip_GasMask_C.UserConstructionScript
// ()

void AEquip_GasMask_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.UserConstructionScript");

	AEquip_GasMask_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_GasMask.Equip_GasMask_C.WasUnEquipped
// ()

void AEquip_GasMask_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.WasUnEquipped");

	AEquip_GasMask_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_GasMask.Equip_GasMask_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_GasMask_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.ReceiveTick");

	AEquip_GasMask_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_GasMask.Equip_GasMask_C.WasEquipped
// ()

void AEquip_GasMask_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.WasEquipped");

	AEquip_GasMask_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_GasMask.Equip_GasMask_C.ExecuteUbergraph_Equip_GasMask
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_GasMask_C::ExecuteUbergraph_Equip_GasMask(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_GasMask.Equip_GasMask_C.ExecuteUbergraph_Equip_GasMask");

	AEquip_GasMask_C_ExecuteUbergraph_Equip_GasMask_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
