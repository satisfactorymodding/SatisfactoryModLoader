// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_NobeliskDetonator_L_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.UserConstructionScript
// ()

void AAttach_NobeliskDetonator_L_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.UserConstructionScript");

	AAttach_NobeliskDetonator_L_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.ClientPlayReloadEffect
// ()

void AAttach_NobeliskDetonator_L_C::ClientPlayReloadEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.ClientPlayReloadEffect");

	AAttach_NobeliskDetonator_L_C_ClientPlayReloadEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.PlayFireEffect
// ()
// Parameters:
// struct FVector*                flashLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_NobeliskDetonator_L_C::PlayFireEffect(struct FVector* flashLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.PlayFireEffect");

	AAttach_NobeliskDetonator_L_C_PlayFireEffect_Params params;
	params.flashLocation = flashLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.PlayAttachEffects3P
// ()

void AAttach_NobeliskDetonator_L_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.PlayAttachEffects3P");

	AAttach_NobeliskDetonator_L_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.ExecuteUbergraph_Attach_NobeliskDetonator_L
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_NobeliskDetonator_L_C::ExecuteUbergraph_Attach_NobeliskDetonator_L(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_L.Attach_NobeliskDetonator_L_C.ExecuteUbergraph_Attach_NobeliskDetonator_L");

	AAttach_NobeliskDetonator_L_C_ExecuteUbergraph_Attach_NobeliskDetonator_L_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
