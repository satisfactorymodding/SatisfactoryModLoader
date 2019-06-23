// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateBuild_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.BeginState
// ()

void UBP_BuildGunStateBuild_C::BeginState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.BeginState");

	UBP_BuildGunStateBuild_C_BeginState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.EndState
// ()

void UBP_BuildGunStateBuild_C::EndState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.EndState");

	UBP_BuildGunStateBuild_C_EndState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.SecondaryFire
// ()

void UBP_BuildGunStateBuild_C::SecondaryFire()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.SecondaryFire");

	UBP_BuildGunStateBuild_C_SecondaryFire_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnActiveDescriptorChanged
// ()

void UBP_BuildGunStateBuild_C::OnActiveDescriptorChanged()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnActiveDescriptorChanged");

	UBP_BuildGunStateBuild_C_OnActiveDescriptorChanged_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnMultiStepPlacement
// ()
// Parameters:
// bool*                          isFinalStep                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildGunStateBuild_C::OnMultiStepPlacement(bool* isFinalStep)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnMultiStepPlacement");

	UBP_BuildGunStateBuild_C_OnMultiStepPlacement_Params params;
	params.isFinalStep = isFinalStep;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnResetHologram
// ()

void UBP_BuildGunStateBuild_C::OnResetHologram()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.OnResetHologram");

	UBP_BuildGunStateBuild_C_OnResetHologram_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.PrimaryFire
// ()

void UBP_BuildGunStateBuild_C::PrimaryFire()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.PrimaryFire");

	UBP_BuildGunStateBuild_C_PrimaryFire_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.ExecuteUbergraph_BP_BuildGunStateBuild
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildGunStateBuild_C::ExecuteUbergraph_BP_BuildGunStateBuild(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateBuild.BP_BuildGunStateBuild_C.ExecuteUbergraph_BP_BuildGunStateBuild");

	UBP_BuildGunStateBuild_C_ExecuteUbergraph_BP_BuildGunStateBuild_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
