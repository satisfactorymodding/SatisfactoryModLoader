// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_CrabHatcher_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_CrabHatcher.Char_CrabHatcher_C.SpawnTimer
// ()

void AChar_CrabHatcher_C::SpawnTimer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.SpawnTimer");

	AChar_CrabHatcher_C_SpawnTimer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.PlaySpawnEffects
// ()

void AChar_CrabHatcher_C::PlaySpawnEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.PlaySpawnEffects");

	AChar_CrabHatcher_C_PlaySpawnEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.UserConstructionScript
// ()

void AChar_CrabHatcher_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.UserConstructionScript");

	AChar_CrabHatcher_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveBeginPlay
// ()

void AChar_CrabHatcher_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveBeginPlay");

	AChar_CrabHatcher_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.Damaged
// ()
// Parameters:
// class AActor*                  damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Damage                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType*             DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_CrabHatcher_C::Damaged(class AActor* damagedActor, float Damage, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.Damaged");

	AChar_CrabHatcher_C_Damaged_Params params;
	params.damagedActor = damagedActor;
	params.Damage = Damage;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.SpawnCrabs
// ()

void AChar_CrabHatcher_C::SpawnCrabs()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.SpawnCrabs");

	AChar_CrabHatcher_C_SpawnCrabs_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.StartExpanding
// ()

void AChar_CrabHatcher_C::StartExpanding()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.StartExpanding");

	AChar_CrabHatcher_C_StartExpanding_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveActorBeginOverlap
// ()
// Parameters:
// class AActor**                 OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_CrabHatcher_C::ReceiveActorBeginOverlap(class AActor** OtherActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveActorBeginOverlap");

	AChar_CrabHatcher_C_ReceiveActorBeginOverlap_Params params;
	params.OtherActor = OtherActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.ExecuteUbergraph_Char_CrabHatcher
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_CrabHatcher_C::ExecuteUbergraph_Char_CrabHatcher(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.ExecuteUbergraph_Char_CrabHatcher");

	AChar_CrabHatcher_C_ExecuteUbergraph_Char_CrabHatcher_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
