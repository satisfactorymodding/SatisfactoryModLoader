// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_NonFlyingBird_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_NonFlyingBird.Char_NonFlyingBird_C.OnRep_mIsLuring
// ()

void AChar_NonFlyingBird_C::OnRep_mIsLuring()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.OnRep_mIsLuring");

	AChar_NonFlyingBird_C_OnRep_mIsLuring_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.SetLuring
// ()
// Parameters:
// bool                           isLuring                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_NonFlyingBird_C::SetLuring(bool isLuring)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.SetLuring");

	AChar_NonFlyingBird_C_SetLuring_Params params;
	params.isLuring = isLuring;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.UserConstructionScript
// ()

void AChar_NonFlyingBird_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.UserConstructionScript");

	AChar_NonFlyingBird_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_NonFlyingBird_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.ReceiveTick");

	AChar_NonFlyingBird_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.TryToJump
// ()

void AChar_NonFlyingBird_C::TryToJump()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.TryToJump");

	AChar_NonFlyingBird_C_TryToJump_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.OnLanded
// ()
// Parameters:
// struct FHitResult*             Hit                            (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void AChar_NonFlyingBird_C::OnLanded(struct FHitResult* Hit)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.OnLanded");

	AChar_NonFlyingBird_C_OnLanded_Params params;
	params.Hit = Hit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.ReceiveDied
// ()

void AChar_NonFlyingBird_C::ReceiveDied()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.ReceiveDied");

	AChar_NonFlyingBird_C_ReceiveDied_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.NotifyOnTakeDamage
// ()
// Parameters:
// class AActor**                 damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_NonFlyingBird_C::NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.NotifyOnTakeDamage");

	AChar_NonFlyingBird_C_NotifyOnTakeDamage_Params params;
	params.damagedActor = damagedActor;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.ExecuteUbergraph_Char_NonFlyingBird
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_NonFlyingBird_C::ExecuteUbergraph_Char_NonFlyingBird(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.ExecuteUbergraph_Char_NonFlyingBird");

	AChar_NonFlyingBird_C_ExecuteUbergraph_Char_NonFlyingBird_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_NonFlyingBird.Char_NonFlyingBird_C.OnLandedDelegate__DelegateSignature
// ()
// Parameters:
// class AChar_NonFlyingBird_C*   selfPawn                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_NonFlyingBird_C::OnLandedDelegate__DelegateSignature(class AChar_NonFlyingBird_C* selfPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_NonFlyingBird.Char_NonFlyingBird_C.OnLandedDelegate__DelegateSignature");

	AChar_NonFlyingBird_C_OnLandedDelegate__DelegateSignature_Params params;
	params.selfPawn = selfPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
