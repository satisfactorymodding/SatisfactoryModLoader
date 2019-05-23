// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Machinegun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_Machinegun.Attach_Machinegun_C.UserConstructionScript
// ()

void AAttach_Machinegun_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Machinegun.Attach_Machinegun_C.UserConstructionScript");

	AAttach_Machinegun_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Machinegun.Attach_Machinegun_C.PlayFireEffect
// ()
// Parameters:
// struct FVector*                flashLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)

void AAttach_Machinegun_C::PlayFireEffect(struct FVector* flashLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Machinegun.Attach_Machinegun_C.PlayFireEffect");

	AAttach_Machinegun_C_PlayFireEffect_Params params;
	params.flashLocation = flashLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Machinegun.Attach_Machinegun_C.ClientPlayReloadEffect
// ()

void AAttach_Machinegun_C::ClientPlayReloadEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Machinegun.Attach_Machinegun_C.ClientPlayReloadEffect");

	AAttach_Machinegun_C_ClientPlayReloadEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Machinegun.Attach_Machinegun_C.ExecuteUbergraph_Attach_Machinegun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_Machinegun_C::ExecuteUbergraph_Attach_Machinegun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Machinegun.Attach_Machinegun_C.ExecuteUbergraph_Attach_Machinegun");

	AAttach_Machinegun_C_ExecuteUbergraph_Attach_Machinegun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
