// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ProfileSpline_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ProfileSpline.BP_ProfileSpline_C.CheckDoneRespawning
// ()
// Parameters:
// bool                           bDoneSpawning                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_ProfileSpline_C::CheckDoneRespawning(bool* bDoneSpawning)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.CheckDoneRespawning");

	ABP_ProfileSpline_C_CheckDoneRespawning_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (bDoneSpawning != nullptr)
		*bDoneSpawning = params.bDoneSpawning;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.GetPlayerController
// ()
// Parameters:
// bool                           bIsValid                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// class APlayerController*       PlayerController               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_ProfileSpline_C::GetPlayerController(bool* bIsValid, class APlayerController** PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.GetPlayerController");

	ABP_ProfileSpline_C_GetPlayerController_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (bIsValid != nullptr)
		*bIsValid = params.bIsValid;
	if (PlayerController != nullptr)
		*PlayerController = params.PlayerController;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.UserConstructionScript
// ()

void ABP_ProfileSpline_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.UserConstructionScript");

	ABP_ProfileSpline_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ProfileSpline_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.ReceiveTick");

	ABP_ProfileSpline_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.FetchPlayerPawn
// ()

void ABP_ProfileSpline_C::FetchPlayerPawn()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.FetchPlayerPawn");

	ABP_ProfileSpline_C_FetchPlayerPawn_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.StartProfile
// ()

void ABP_ProfileSpline_C::StartProfile()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.StartProfile");

	ABP_ProfileSpline_C_StartProfile_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.EnsurePlayerDoneSpawning
// ()

void ABP_ProfileSpline_C::EnsurePlayerDoneSpawning()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.EnsurePlayerDoneSpawning");

	ABP_ProfileSpline_C_EnsurePlayerDoneSpawning_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ProfileSpline.BP_ProfileSpline_C.ExecuteUbergraph_BP_ProfileSpline
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ProfileSpline_C::ExecuteUbergraph_BP_ProfileSpline(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ProfileSpline.BP_ProfileSpline_C.ExecuteUbergraph_BP_ProfileSpline");

	ABP_ProfileSpline_C_ExecuteUbergraph_BP_ProfileSpline_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
