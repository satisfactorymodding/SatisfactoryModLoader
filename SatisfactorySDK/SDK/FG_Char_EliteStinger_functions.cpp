// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_EliteStinger_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_EliteStinger.Char_EliteStinger_C.UserConstructionScript
// ()

void AChar_EliteStinger_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteStinger.Char_EliteStinger_C.UserConstructionScript");

	AChar_EliteStinger_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteStinger.Char_EliteStinger_C.ReceiveBeginPlay
// ()

void AChar_EliteStinger_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteStinger.Char_EliteStinger_C.ReceiveBeginPlay");

	AChar_EliteStinger_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteStinger.Char_EliteStinger_C.SpawnGas
// ()

void AChar_EliteStinger_C::SpawnGas()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteStinger.Char_EliteStinger_C.SpawnGas");

	AChar_EliteStinger_C_SpawnGas_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteStinger.Char_EliteStinger_C.OnTakeAnyDamage_Event_1
// ()
// Parameters:
// class AActor*                  DamagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Damage                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType*             DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             InstigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  DamageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_EliteStinger_C::OnTakeAnyDamage_Event_1(class AActor* DamagedActor, float Damage, class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteStinger.Char_EliteStinger_C.OnTakeAnyDamage_Event_1");

	AChar_EliteStinger_C_OnTakeAnyDamage_Event_1_Params params;
	params.DamagedActor = DamagedActor;
	params.Damage = Damage;
	params.DamageType = DamageType;
	params.InstigatedBy = InstigatedBy;
	params.DamageCauser = DamageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_EliteStinger.Char_EliteStinger_C.ExecuteUbergraph_Char_EliteStinger
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_EliteStinger_C::ExecuteUbergraph_Char_EliteStinger(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_EliteStinger.Char_EliteStinger_C.ExecuteUbergraph_Char_EliteStinger");

	AChar_EliteStinger_C_ExecuteUbergraph_Char_EliteStinger_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
