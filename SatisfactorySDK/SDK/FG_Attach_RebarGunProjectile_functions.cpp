// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_RebarGunProjectile_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.UserConstructionScript
// ()

void AAttach_RebarGunProjectile_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.UserConstructionScript");

	AAttach_RebarGunProjectile_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.PlayFireEffect
// ()
// Parameters:
// struct FVector*                flashLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_RebarGunProjectile_C::PlayFireEffect(struct FVector* flashLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.PlayFireEffect");

	AAttach_RebarGunProjectile_C_PlayFireEffect_Params params;
	params.flashLocation = flashLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.ClientPlayReloadEffect
// ()

void AAttach_RebarGunProjectile_C::ClientPlayReloadEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.ClientPlayReloadEffect");

	AAttach_RebarGunProjectile_C_ClientPlayReloadEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.PlayAttachEffects3P
// ()

void AAttach_RebarGunProjectile_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.PlayAttachEffects3P");

	AAttach_RebarGunProjectile_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.ExecuteUbergraph_Attach_RebarGunProjectile
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_RebarGunProjectile_C::ExecuteUbergraph_Attach_RebarGunProjectile(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_RebarGunProjectile.Attach_RebarGunProjectile_C.ExecuteUbergraph_Attach_RebarGunProjectile");

	AAttach_RebarGunProjectile_C_ExecuteUbergraph_Attach_RebarGunProjectile_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
