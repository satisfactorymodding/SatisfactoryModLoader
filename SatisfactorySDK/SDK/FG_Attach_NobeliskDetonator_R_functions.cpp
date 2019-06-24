// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_NobeliskDetonator_R_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.UserConstructionScript
// ()

void AAttach_NobeliskDetonator_R_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.UserConstructionScript");

	AAttach_NobeliskDetonator_R_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnIsLoadedSet
// ()

void AAttach_NobeliskDetonator_R_C::OnIsLoadedSet()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnIsLoadedSet");

	AAttach_NobeliskDetonator_R_C_OnIsLoadedSet_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.PlayFireEffect
// ()
// Parameters:
// struct FVector*                flashLocation                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_NobeliskDetonator_R_C::PlayFireEffect(struct FVector* flashLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.PlayFireEffect");

	AAttach_NobeliskDetonator_R_C_PlayFireEffect_Params params;
	params.flashLocation = flashLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnBeginFireEffect
// ()
// Parameters:
// struct FVector*                Location                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_NobeliskDetonator_R_C::OnBeginFireEffect(struct FVector* Location)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnBeginFireEffect");

	AAttach_NobeliskDetonator_R_C_OnBeginFireEffect_Params params;
	params.Location = Location;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.ClientPlayReloadEffect
// ()

void AAttach_NobeliskDetonator_R_C::ClientPlayReloadEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.ClientPlayReloadEffect");

	AAttach_NobeliskDetonator_R_C_ClientPlayReloadEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnAttach
// ()

void AAttach_NobeliskDetonator_R_C::OnAttach()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.OnAttach");

	AAttach_NobeliskDetonator_R_C_OnAttach_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.ExecuteUbergraph_Attach_NobeliskDetonator_R
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_NobeliskDetonator_R_C::ExecuteUbergraph_Attach_NobeliskDetonator_R(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_NobeliskDetonator_R.Attach_NobeliskDetonator_R_C.ExecuteUbergraph_Attach_NobeliskDetonator_R");

	AAttach_NobeliskDetonator_R_C_ExecuteUbergraph_Attach_NobeliskDetonator_R_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
