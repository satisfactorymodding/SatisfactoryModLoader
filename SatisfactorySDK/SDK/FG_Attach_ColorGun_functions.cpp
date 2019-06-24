// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ColorGun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_ColorGun.Attach_ColorGun_C.UserConstructionScript
// ()

void AAttach_ColorGun_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ColorGun.Attach_ColorGun_C.UserConstructionScript");

	AAttach_ColorGun_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ColorGun.Attach_ColorGun_C.ClientPlayReloadEffect
// ()

void AAttach_ColorGun_C::ClientPlayReloadEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ColorGun.Attach_ColorGun_C.ClientPlayReloadEffect");

	AAttach_ColorGun_C_ClientPlayReloadEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ColorGun.Attach_ColorGun_C.PlayFireEffect
// ()
// Parameters:
// struct FVector*                flashLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_ColorGun_C::PlayFireEffect(struct FVector* flashLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ColorGun.Attach_ColorGun_C.PlayFireEffect");

	AAttach_ColorGun_C_PlayFireEffect_Params params;
	params.flashLocation = flashLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ColorGun.Attach_ColorGun_C.PlayAttachEffects3P
// ()

void AAttach_ColorGun_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ColorGun.Attach_ColorGun_C.PlayAttachEffects3P");

	AAttach_ColorGun_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ColorGun.Attach_ColorGun_C.ExecuteUbergraph_Attach_ColorGun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_ColorGun_C::ExecuteUbergraph_Attach_ColorGun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ColorGun.Attach_ColorGun_C.ExecuteUbergraph_Attach_ColorGun");

	AAttach_ColorGun_C_ExecuteUbergraph_Attach_ColorGun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
