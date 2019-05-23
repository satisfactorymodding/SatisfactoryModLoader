// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_EliteCaveStinger_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.UserConstructionScript
// ()

void AChar_EliteCaveStinger_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.UserConstructionScript");

	AChar_EliteCaveStinger_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.ReceiveBeginPlay
// ()

void AChar_EliteCaveStinger_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.ReceiveBeginPlay");

	AChar_EliteCaveStinger_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.SpawnGas
// ()

void AChar_EliteCaveStinger_C::SpawnGas()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.SpawnGas");

	AChar_EliteCaveStinger_C_SpawnGas_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.OnTakeAnyDamage_Event_1
// ()
// Parameters:
// class AActor*                  damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Damage                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType*             DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_EliteCaveStinger_C::OnTakeAnyDamage_Event_1(class AActor* damagedActor, float Damage, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.OnTakeAnyDamage_Event_1");

	AChar_EliteCaveStinger_C_OnTakeAnyDamage_Event_1_Params params;
	params.damagedActor = damagedActor;
	params.Damage = Damage;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.ExecuteUbergraph_Char_EliteCaveStinger
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_EliteCaveStinger_C::ExecuteUbergraph_Char_EliteCaveStinger(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.ExecuteUbergraph_Char_EliteCaveStinger");

	AChar_EliteCaveStinger_C_ExecuteUbergraph_Char_EliteCaveStinger_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
