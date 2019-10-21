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


// Function Char_CrabHatcher.Char_CrabHatcher_C.Damaged
// ()
// Parameters:
// class AActor*                  DamagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Damage                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType*             DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             InstigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  DamageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_CrabHatcher_C::Damaged(class AActor* DamagedActor, float Damage, class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.Damaged");

	AChar_CrabHatcher_C_Damaged_Params params;
	params.DamagedActor = DamagedActor;
	params.Damage = Damage;
	params.DamageType = DamageType;
	params.InstigatedBy = InstigatedBy;
	params.DamageCauser = DamageCauser;

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


// Function Char_CrabHatcher.Char_CrabHatcher_C.GainedSignificance
// ()

void AChar_CrabHatcher_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.GainedSignificance");

	AChar_CrabHatcher_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.LostSignificance
// ()

void AChar_CrabHatcher_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.LostSignificance");

	AChar_CrabHatcher_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_CrabHatcher_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveEndPlay");

	AChar_CrabHatcher_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

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
