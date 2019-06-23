// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_SpaceGiraffe_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.GetLookAtDecription
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText AChar_SpaceGiraffe_C::GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.GetLookAtDecription");

	AChar_SpaceGiraffe_C_GetLookAtDecription_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.IsUseable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_SpaceGiraffe_C::IsUseable()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.IsUseable");

	AChar_SpaceGiraffe_C_IsUseable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UpdateUseState
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 atLocation                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class UPrimitiveComponent*     componentHit                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FUseState               out_useState                   (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceGiraffe_C::UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UpdateUseState");

	AChar_SpaceGiraffe_C_UpdateUseState_Params params;
	params.byCharacter = byCharacter;
	params.atLocation = atLocation;
	params.componentHit = componentHit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_useState != nullptr)
		*out_useState = params.out_useState;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnRep_mDoPanic
// ()

void AChar_SpaceGiraffe_C::OnRep_mDoPanic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnRep_mDoPanic");

	AChar_SpaceGiraffe_C_OnRep_mDoPanic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UserConstructionScript
// ()

void AChar_SpaceGiraffe_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UserConstructionScript");

	AChar_SpaceGiraffe_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnUseStop
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceGiraffe_C::OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnUseStop");

	AChar_SpaceGiraffe_C_OnUseStop_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.RegisterInteractingPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::RegisterInteractingPlayer(class AFGCharacterPlayer* Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.RegisterInteractingPlayer");

	AChar_SpaceGiraffe_C_RegisterInteractingPlayer_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StartIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceGiraffe_C::StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StartIsLookedAt");

	AChar_SpaceGiraffe_C_StartIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StopIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceGiraffe_C::StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StopIsLookedAt");

	AChar_SpaceGiraffe_C_StopIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UnregisterInteractingPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::UnregisterInteractingPlayer(class AFGCharacterPlayer* Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.UnregisterInteractingPlayer");

	AChar_SpaceGiraffe_C_UnregisterInteractingPlayer_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveTick");

	AChar_SpaceGiraffe_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.NotifyOnTakeDamage
// ()
// Parameters:
// class AActor**                 damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType**            DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController**            instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor**                 damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::NotifyOnTakeDamage(class AActor** damagedActor, float* damageAmount, class UDamageType** DamageType, class AController** instigatedBy, class AActor** damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.NotifyOnTakeDamage");

	AChar_SpaceGiraffe_C_NotifyOnTakeDamage_Params params;
	params.damagedActor = damagedActor;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StartRotationMovement
// ()
// Parameters:
// struct FRotator*               TargetRotation                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::StartRotationMovement(struct FRotator* TargetRotation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.StartRotationMovement");

	AChar_SpaceGiraffe_C_StartRotationMovement_Params params;
	params.TargetRotation = TargetRotation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1
// ()
// Parameters:
// float                          AxisValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1(float AxisValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1");

	AChar_SpaceGiraffe_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1_Params params;
	params.AxisValue = AxisValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10
// ()
// Parameters:
// float                          AxisValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10(float AxisValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10");

	AChar_SpaceGiraffe_C_InpAxisEvt_MoveRight_K2Node_InputAxisEvent_10_Params params;
	params.AxisValue = AxisValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceivePossessed
// ()
// Parameters:
// class AController**            NewController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::ReceivePossessed(class AController** NewController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceivePossessed");

	AChar_SpaceGiraffe_C_ReceivePossessed_Params params;
	params.NewController = NewController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ClientSetupHUD
// ()
// Parameters:
// class AFGPlayerController*     Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::ClientSetupHUD(class AFGPlayerController* Controller)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ClientSetupHUD");

	AChar_SpaceGiraffe_C_ClientSetupHUD_Params params;
	params.Controller = Controller;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveUnpossessed
// ()
// Parameters:
// class AController**            OldController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::ReceiveUnpossessed(class AController** OldController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveUnpossessed");

	AChar_SpaceGiraffe_C_ReceiveUnpossessed_Params params;
	params.OldController = OldController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnUse
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_SpaceGiraffe_C::OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.OnUse");

	AChar_SpaceGiraffe_C_OnUse_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void AChar_SpaceGiraffe_C::BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	AChar_SpaceGiraffe_C_BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;
	params.bFromSweep = bFromSweep;
	params.SweepResult = SweepResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveDied
// ()

void AChar_SpaceGiraffe_C::ReceiveDied()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ReceiveDied");

	AChar_SpaceGiraffe_C_ReceiveDied_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ExecuteUbergraph_Char_SpaceGiraffe
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_SpaceGiraffe_C::ExecuteUbergraph_Char_SpaceGiraffe(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_SpaceGiraffe.Char_SpaceGiraffe_C.ExecuteUbergraph_Char_SpaceGiraffe");

	AChar_SpaceGiraffe_C_ExecuteUbergraph_Char_SpaceGiraffe_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
