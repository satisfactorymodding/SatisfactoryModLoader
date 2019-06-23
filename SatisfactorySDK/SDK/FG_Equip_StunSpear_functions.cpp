// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_StunSpear_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_StunSpear.Equip_StunSpear_C.UserConstructionScript
// ()

void AEquip_StunSpear_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.UserConstructionScript");

	AEquip_StunSpear_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_StunSpear_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.ReceiveTick");

	AEquip_StunSpear_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.SwordAttack
// ()

void AEquip_StunSpear_C::SwordAttack()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.SwordAttack");

	AEquip_StunSpear_C_SwordAttack_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.PlayStunEffects
// ()

void AEquip_StunSpear_C::PlayStunEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.PlayStunEffects");

	AEquip_StunSpear_C_PlayStunEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void AEquip_StunSpear_C::BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	AEquip_StunSpear_C_BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
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


// Function Equip_StunSpear.Equip_StunSpear_C.WasUnEquipped
// ()

void AEquip_StunSpear_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.WasUnEquipped");

	AEquip_StunSpear_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.WasEquipped
// ()

void AEquip_StunSpear_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.WasEquipped");

	AEquip_StunSpear_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.OnHitTarget
// ()

void AEquip_StunSpear_C::OnHitTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.OnHitTarget");

	AEquip_StunSpear_C_OnHitTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_StunSpear.Equip_StunSpear_C.ExecuteUbergraph_Equip_StunSpear
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_StunSpear_C::ExecuteUbergraph_Equip_StunSpear(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_StunSpear.Equip_StunSpear_C.ExecuteUbergraph_Equip_StunSpear");

	AEquip_StunSpear_C_ExecuteUbergraph_Equip_StunSpear_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
