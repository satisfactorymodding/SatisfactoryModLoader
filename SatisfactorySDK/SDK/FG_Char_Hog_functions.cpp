// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Hog_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_Hog.Char_Hog_C.OnRep_mIsThreatened
// ()

void AChar_Hog_C::OnRep_mIsThreatened()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.OnRep_mIsThreatened");

	AChar_Hog_C_OnRep_mIsThreatened_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.StartChargeMovement
// ()

void AChar_Hog_C::StartChargeMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.StartChargeMovement");

	AChar_Hog_C_StartChargeMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.UpdateChargeMovement
// ()

void AChar_Hog_C::UpdateChargeMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.UpdateChargeMovement");

	AChar_Hog_C_UpdateChargeMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.StopChargeMovement
// ()

void AChar_Hog_C::StopChargeMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.StopChargeMovement");

	AChar_Hog_C_StopChargeMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.UpdateChargeDirection
// ()

void AChar_Hog_C::UpdateChargeDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.UpdateChargeDirection");

	AChar_Hog_C_UpdateChargeDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.UserConstructionScript
// ()

void AChar_Hog_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.UserConstructionScript");

	AChar_Hog_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Hog_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.ReceiveTick");

	AChar_Hog_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.ReceiveHit
// ()
// Parameters:
// class UPrimitiveComponent**    MyComp                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor**                 Other                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent**    OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool*                          bSelfMoved                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                HitLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                HitNormal                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                NormalImpulse                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult*             Hit                            (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void AChar_Hog_C::ReceiveHit(class UPrimitiveComponent** MyComp, class AActor** Other, class UPrimitiveComponent** OtherComp, bool* bSelfMoved, struct FVector* HitLocation, struct FVector* HitNormal, struct FVector* NormalImpulse, struct FHitResult* Hit)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.ReceiveHit");

	AChar_Hog_C_ReceiveHit_Params params;
	params.MyComp = MyComp;
	params.Other = Other;
	params.OtherComp = OtherComp;
	params.bSelfMoved = bSelfMoved;
	params.HitLocation = HitLocation;
	params.HitNormal = HitNormal;
	params.NormalImpulse = NormalImpulse;
	params.Hit = Hit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.NotifyOnTakeDamage
// ()
// Parameters:
// class AActor**                 damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Hog_C::NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.NotifyOnTakeDamage");

	AChar_Hog_C_NotifyOnTakeDamage_Params params;
	params.damagedActor = damagedActor;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.CheckTargetHeight
// ()

void AChar_Hog_C::CheckTargetHeight()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.CheckTargetHeight");

	AChar_Hog_C_CheckTargetHeight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.circle
// ()

void AChar_Hog_C::circle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.circle");

	AChar_Hog_C_circle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.StartCircling
// ()
// Parameters:
// class UBTT_CircleMove_C*       BTTCircleMove                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Hog_C::StartCircling(class UBTT_CircleMove_C* BTTCircleMove)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.StartCircling");

	AChar_Hog_C_StartCircling_Params params;
	params.BTTCircleMove = BTTCircleMove;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.StopCircling
// ()

void AChar_Hog_C::StopCircling()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.StopCircling");

	AChar_Hog_C_StopCircling_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.ReceiveDied
// ()

void AChar_Hog_C::ReceiveDied()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.ReceiveDied");

	AChar_Hog_C_ReceiveDied_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.ExecuteUbergraph_Char_Hog
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Hog_C::ExecuteUbergraph_Char_Hog(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.ExecuteUbergraph_Char_Hog");

	AChar_Hog_C_ExecuteUbergraph_Char_Hog_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Hog.Char_Hog_C.OnChargeMovementStopped__DelegateSignature
// ()

void AChar_Hog_C::OnChargeMovementStopped__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Hog.Char_Hog_C.OnChargeMovementStopped__DelegateSignature");

	AChar_Hog_C_OnChargeMovementStopped__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
