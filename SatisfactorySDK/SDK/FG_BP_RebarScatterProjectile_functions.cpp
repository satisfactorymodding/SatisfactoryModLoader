// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_RebarScatterProjectile_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.UserConstructionScript
// ()

void ABP_RebarScatterProjectile_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.UserConstructionScript");

	ABP_RebarScatterProjectile_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveBeginPlay
// ()

void ABP_RebarScatterProjectile_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveBeginPlay");

	ABP_RebarScatterProjectile_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.PlayAttachEffect
// ()

void ABP_RebarScatterProjectile_C::PlayAttachEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.PlayAttachEffect");

	ABP_RebarScatterProjectile_C_PlayAttachEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_RebarScatterProjectile_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveTick");

	ABP_RebarScatterProjectile_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveDestroyed
// ()

void ABP_RebarScatterProjectile_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveDestroyed");

	ABP_RebarScatterProjectile_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveHit
// ()
// Parameters:
// class UPrimitiveComponent**    MyComp                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor**                 Other                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent**    OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool*                          bSelfMoved                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                HitLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FVector*                HitNormal                      (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FVector*                NormalImpulse                  (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FHitResult*             Hit                            (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABP_RebarScatterProjectile_C::ReceiveHit(class UPrimitiveComponent** MyComp, class AActor** Other, class UPrimitiveComponent** OtherComp, bool* bSelfMoved, struct FVector* HitLocation, struct FVector* HitNormal, struct FVector* NormalImpulse, struct FHitResult* Hit)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ReceiveHit");

	ABP_RebarScatterProjectile_C_ReceiveHit_Params params;
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


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.Shot Player
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 HitNormal                      (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)

void ABP_RebarScatterProjectile_C::Shot_Player(class AFGCharacterPlayer* Player, const struct FVector& HitNormal)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.Shot Player");

	ABP_RebarScatterProjectile_C_Shot_Player_Params params;
	params.Player = Player;
	params.HitNormal = HitNormal;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ExecuteUbergraph_BP_RebarScatterProjectile
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_RebarScatterProjectile_C::ExecuteUbergraph_BP_RebarScatterProjectile(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RebarScatterProjectile.BP_RebarScatterProjectile_C.ExecuteUbergraph_BP_RebarScatterProjectile");

	ABP_RebarScatterProjectile_C_ExecuteUbergraph_BP_RebarScatterProjectile_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
