// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_SpaceRabbit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_SpaceRabbit.Char_SpaceRabbit_C.GetLookAtDecription
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText AChar_SpaceRabbit_C::GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.GetLookAtDecription");

	AChar_SpaceRabbit_C_GetLookAtDecription_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.IsUseable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_SpaceRabbit_C::IsUseable()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.IsUseable");

	AChar_SpaceRabbit_C_IsUseable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateUseState
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 atLocation                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class UPrimitiveComponent*     componentHit                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FUseState               out_useState                   (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceRabbit_C::UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateUseState");

	AChar_SpaceRabbit_C_UpdateUseState_Params params;
	params.byCharacter = byCharacter;
	params.atLocation = atLocation;
	params.componentHit = componentHit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_useState != nullptr)
		*out_useState = params.out_useState;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.SetupLootTimer
// ()

void AChar_SpaceRabbit_C::SetupLootTimer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.SetupLootTimer");

	AChar_SpaceRabbit_C_SetupLootTimer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnRep_mLootTableIndex
// ()

void AChar_SpaceRabbit_C::OnRep_mLootTableIndex()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnRep_mLootTableIndex");

	AChar_SpaceRabbit_C_OnRep_mLootTableIndex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.RollLoot
// ()

void AChar_SpaceRabbit_C::RollLoot()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.RollLoot");

	AChar_SpaceRabbit_C_RollLoot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.SetNewFriend
// ()
// Parameters:
// class AActor*                  newFriend                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::SetNewFriend(class AActor* newFriend)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.SetNewFriend");

	AChar_SpaceRabbit_C_SetNewFriend_Params params;
	params.newFriend = newFriend;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StopBackwardWalk
// ()

void AChar_SpaceRabbit_C::StopBackwardWalk()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.StopBackwardWalk");

	AChar_SpaceRabbit_C_StopBackwardWalk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateWalkBackMovement
// ()

void AChar_SpaceRabbit_C::UpdateWalkBackMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateWalkBackMovement");

	AChar_SpaceRabbit_C_UpdateWalkBackMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateWalkBackDirection
// ()

void AChar_SpaceRabbit_C::UpdateWalkBackDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.UpdateWalkBackDirection");

	AChar_SpaceRabbit_C_UpdateWalkBackDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StartWalkBack
// ()

void AChar_SpaceRabbit_C::StartWalkBack()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.StartWalkBack");

	AChar_SpaceRabbit_C_StartWalkBack_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UserConstructionScript
// ()

void AChar_SpaceRabbit_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.UserConstructionScript");

	AChar_SpaceRabbit_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnUseStop
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceRabbit_C::OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnUseStop");

	AChar_SpaceRabbit_C_OnUseStop_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.RegisterInteractingPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::RegisterInteractingPlayer(class AFGCharacterPlayer* Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.RegisterInteractingPlayer");

	AChar_SpaceRabbit_C_RegisterInteractingPlayer_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StartIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceRabbit_C::StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.StartIsLookedAt");

	AChar_SpaceRabbit_C_StartIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.StopIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceRabbit_C::StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.StopIsLookedAt");

	AChar_SpaceRabbit_C_StopIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.UnregisterInteractingPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::UnregisterInteractingPlayer(class AFGCharacterPlayer* Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.UnregisterInteractingPlayer");

	AChar_SpaceRabbit_C_UnregisterInteractingPlayer_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveTick");

	AChar_SpaceRabbit_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakeDamage
// ()
// Parameters:
// class AActor**                 damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakeDamage");

	AChar_SpaceRabbit_C_NotifyOnTakeDamage_Params params;
	params.damagedActor = damagedActor;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveDied
// ()

void AChar_SpaceRabbit_C::ReceiveDied()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveDied");

	AChar_SpaceRabbit_C_ReceiveDied_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakePointDamage
// ()
// Parameters:
// class AActor**                 damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         Damage                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                HitLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent**    HitComponent                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FName*                  BoneName                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                ShotFromDirection              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::NotifyOnTakePointDamage(class AActor** damagedActor, float* Damage, class AController** instigatedBy, struct FVector* HitLocation, class UPrimitiveComponent** HitComponent, struct FName* BoneName, struct FVector* ShotFromDirection, class UDamageType** DamageType, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakePointDamage");

	AChar_SpaceRabbit_C_NotifyOnTakePointDamage_Params params;
	params.damagedActor = damagedActor;
	params.Damage = Damage;
	params.instigatedBy = instigatedBy;
	params.HitLocation = HitLocation;
	params.HitComponent = HitComponent;
	params.BoneName = BoneName;
	params.ShotFromDirection = ShotFromDirection;
	params.DamageType = DamageType;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakeRadialDamage
// ()
// Parameters:
// class AActor**                 damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         Damage                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::NotifyOnTakeRadialDamage(class AActor** damagedActor, float* Damage, class AController** instigatedBy, class UDamageType** DamageType, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.NotifyOnTakeRadialDamage");

	AChar_SpaceRabbit_C_NotifyOnTakeRadialDamage_Params params;
	params.damagedActor = damagedActor;
	params.Damage = Damage;
	params.instigatedBy = instigatedBy;
	params.DamageType = DamageType;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveBeginPlay
// ()

void AChar_SpaceRabbit_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.ReceiveBeginPlay");

	AChar_SpaceRabbit_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.PlayConsumeItemEffect
// ()
// Parameters:
// class UClass**                 itemDescriptor                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int*                           amount                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::PlayConsumeItemEffect(class UClass** itemDescriptor, int* amount)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.PlayConsumeItemEffect");

	AChar_SpaceRabbit_C_PlayConsumeItemEffect_Params params;
	params.itemDescriptor = itemDescriptor;
	params.amount = amount;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnUse
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceRabbit_C::OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnUse");

	AChar_SpaceRabbit_C_OnUse_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.ExecuteUbergraph_Char_SpaceRabbit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceRabbit_C::ExecuteUbergraph_Char_SpaceRabbit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.ExecuteUbergraph_Char_SpaceRabbit");

	AChar_SpaceRabbit_C_ExecuteUbergraph_Char_SpaceRabbit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnWalkBackStopped__DelegateSignature
// ()

void AChar_SpaceRabbit_C::OnWalkBackStopped__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceRabbit.Char_SpaceRabbit_C.OnWalkBackStopped__DelegateSignature");

	AChar_SpaceRabbit_C_OnWalkBackStopped__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
