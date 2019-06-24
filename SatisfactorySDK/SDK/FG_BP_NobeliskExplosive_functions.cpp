// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_NobeliskExplosive_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ShouldSave
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_NobeliskExplosive_C::ShouldSave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ShouldSave");

	ABP_NobeliskExplosive_C_ShouldSave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.GatherDependencies
// ()
// Parameters:
// TArray<class UObject*>         out_dependentObjects           (Parm, OutParm, ZeroConstructor)

void ABP_NobeliskExplosive_C::GatherDependencies(TArray<class UObject*>* out_dependentObjects)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.GatherDependencies");

	ABP_NobeliskExplosive_C_GatherDependencies_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_dependentObjects != nullptr)
		*out_dependentObjects = params.out_dependentObjects;
}


// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.NeedTransform
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_NobeliskExplosive_C::NeedTransform()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.NeedTransform");

	ABP_NobeliskExplosive_C_NeedTransform_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.UserConstructionScript
// ()

void ABP_NobeliskExplosive_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.UserConstructionScript");

	ABP_NobeliskExplosive_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.PlayExplosionEffects
// ()

void ABP_NobeliskExplosive_C::PlayExplosionEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.PlayExplosionEffects");

	ABP_NobeliskExplosive_C_PlayExplosionEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ReceiveHit
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

void ABP_NobeliskExplosive_C::ReceiveHit(class UPrimitiveComponent** MyComp, class AActor** Other, class UPrimitiveComponent** OtherComp, bool* bSelfMoved, struct FVector* HitLocation, struct FVector* HitNormal, struct FVector* NormalImpulse, struct FHitResult* Hit)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ReceiveHit");

	ABP_NobeliskExplosive_C_ReceiveHit_Params params;
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


// Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ExecuteUbergraph_BP_NobeliskExplosive
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_NobeliskExplosive_C::ExecuteUbergraph_BP_NobeliskExplosive(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_NobeliskExplosive.BP_NobeliskExplosive_C.ExecuteUbergraph_BP_NobeliskExplosive");

	ABP_NobeliskExplosive_C_ExecuteUbergraph_BP_NobeliskExplosive_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
