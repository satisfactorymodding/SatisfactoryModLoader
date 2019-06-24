// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ApexDestruction_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function ApexDestruction.DestructibleComponent.SetDestructibleMesh
// ()
// Parameters:
// class UDestructibleMesh*       NewMesh                        (Parm, ZeroConstructor, IsPlainOldData)

void UDestructibleComponent::SetDestructibleMesh(class UDestructibleMesh* NewMesh)
{
	static auto fn = UObject::FindObject<UFunction>("Function ApexDestruction.DestructibleComponent.SetDestructibleMesh");

	UDestructibleComponent_SetDestructibleMesh_Params params;
	params.NewMesh = NewMesh;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ApexDestruction.DestructibleComponent.GetDestructibleMesh
// ()
// Parameters:
// class UDestructibleMesh*       ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UDestructibleMesh* UDestructibleComponent::GetDestructibleMesh()
{
	static auto fn = UObject::FindObject<UFunction>("Function ApexDestruction.DestructibleComponent.GetDestructibleMesh");

	UDestructibleComponent_GetDestructibleMesh_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function ApexDestruction.DestructibleComponent.ApplyRadiusDamage
// ()
// Parameters:
// float                          BaseDamage                     (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 HurtOrigin                     (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// float                          DamageRadius                   (Parm, ZeroConstructor, IsPlainOldData)
// float                          ImpulseStrength                (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFullDamage                    (Parm, ZeroConstructor, IsPlainOldData)

void UDestructibleComponent::ApplyRadiusDamage(float BaseDamage, const struct FVector& HurtOrigin, float DamageRadius, float ImpulseStrength, bool bFullDamage)
{
	static auto fn = UObject::FindObject<UFunction>("Function ApexDestruction.DestructibleComponent.ApplyRadiusDamage");

	UDestructibleComponent_ApplyRadiusDamage_Params params;
	params.BaseDamage = BaseDamage;
	params.HurtOrigin = HurtOrigin;
	params.DamageRadius = DamageRadius;
	params.ImpulseStrength = ImpulseStrength;
	params.bFullDamage = bFullDamage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function ApexDestruction.DestructibleComponent.ApplyDamage
// ()
// Parameters:
// float                          damageAmount                   (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 HitLocation                    (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 ImpulseDir                     (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// float                          ImpulseStrength                (Parm, ZeroConstructor, IsPlainOldData)

void UDestructibleComponent::ApplyDamage(float damageAmount, const struct FVector& HitLocation, const struct FVector& ImpulseDir, float ImpulseStrength)
{
	static auto fn = UObject::FindObject<UFunction>("Function ApexDestruction.DestructibleComponent.ApplyDamage");

	UDestructibleComponent_ApplyDamage_Params params;
	params.damageAmount = damageAmount;
	params.HitLocation = HitLocation;
	params.ImpulseDir = ImpulseDir;
	params.ImpulseStrength = ImpulseStrength;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
