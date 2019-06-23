// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Spitter_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_Spitter.Char_Spitter_C.GetAttackLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector AChar_Spitter_C::GetAttackLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.GetAttackLocation");

	AChar_Spitter_C_GetAttackLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Spitter.Char_Spitter_C.UpdateStrafeDirection
// ()

void AChar_Spitter_C::UpdateStrafeDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.UpdateStrafeDirection");

	AChar_Spitter_C_UpdateStrafeDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.StopStrafe
// ()

void AChar_Spitter_C::StopStrafe()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.StopStrafe");

	AChar_Spitter_C_StopStrafe_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.DoStrafe
// ()

void AChar_Spitter_C::DoStrafe()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.DoStrafe");

	AChar_Spitter_C_DoStrafe_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.StartStrafe
// ()

void AChar_Spitter_C::StartStrafe()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.StartStrafe");

	AChar_Spitter_C_StartStrafe_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.UserConstructionScript
// ()

void AChar_Spitter_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.UserConstructionScript");

	AChar_Spitter_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Spitter_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.ReceiveTick");

	AChar_Spitter_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.OnCurrentAggroTargetReplicated
// ()

void AChar_Spitter_C::OnCurrentAggroTargetReplicated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.OnCurrentAggroTargetReplicated");

	AChar_Spitter_C_OnCurrentAggroTargetReplicated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void AChar_Spitter_C::BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	AChar_Spitter_C_BndEvt__Capsule_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
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


// Function Char_Spitter.Char_Spitter_C.ExecuteUbergraph_Char_Spitter
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Spitter_C::ExecuteUbergraph_Char_Spitter(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.ExecuteUbergraph_Char_Spitter");

	AChar_Spitter_C_ExecuteUbergraph_Char_Spitter_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter.Char_Spitter_C.OnStrafeEnded__DelegateSignature
// ()

void AChar_Spitter_C::OnStrafeEnded__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter.Char_Spitter_C.OnStrafeEnded__DelegateSignature");

	AChar_Spitter_C_OnStrafeEnded__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
