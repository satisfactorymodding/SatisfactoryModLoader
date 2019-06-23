// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Rifle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_Rifle.Attach_Rifle_C.UserConstructionScript
// ()

void AAttach_Rifle_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Rifle.Attach_Rifle_C.UserConstructionScript");

	AAttach_Rifle_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Rifle.Attach_Rifle_C.ClientPlayReloadEffect
// ()

void AAttach_Rifle_C::ClientPlayReloadEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Rifle.Attach_Rifle_C.ClientPlayReloadEffect");

	AAttach_Rifle_C_ClientPlayReloadEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Rifle.Attach_Rifle_C.PlayAttachEffects3P
// ()

void AAttach_Rifle_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Rifle.Attach_Rifle_C.PlayAttachEffects3P");

	AAttach_Rifle_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Rifle.Attach_Rifle_C.PlayFireEffect
// ()
// Parameters:
// struct FVector*                flashLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_Rifle_C::PlayFireEffect(struct FVector* flashLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Rifle.Attach_Rifle_C.PlayFireEffect");

	AAttach_Rifle_C_PlayFireEffect_Params params;
	params.flashLocation = flashLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Rifle.Attach_Rifle_C.ExecuteUbergraph_Attach_Rifle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_Rifle_C::ExecuteUbergraph_Attach_Rifle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Rifle.Attach_Rifle_C.ExecuteUbergraph_Attach_Rifle");

	AAttach_Rifle_C_ExecuteUbergraph_Attach_Rifle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
