// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_VolumeFogSmall_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.UpdateBrightness
// ()

void ABP_VolumeFogSmall_C::UpdateBrightness()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.UpdateBrightness");

	ABP_VolumeFogSmall_C_UpdateBrightness_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.UserConstructionScript
// ()

void ABP_VolumeFogSmall_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.UserConstructionScript");

	ABP_VolumeFogSmall_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.LostSignificance
// ()

void ABP_VolumeFogSmall_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.LostSignificance");

	ABP_VolumeFogSmall_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.GainedSignificance
// ()

void ABP_VolumeFogSmall_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.GainedSignificance");

	ABP_VolumeFogSmall_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_VolumeFogSmall_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveEndPlay");

	ABP_VolumeFogSmall_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_VolumeFogSmall_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveTick");

	ABP_VolumeFogSmall_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveBeginPlay
// ()

void ABP_VolumeFogSmall_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ReceiveBeginPlay");

	ABP_VolumeFogSmall_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ExecuteUbergraph_BP_VolumeFogSmall
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_VolumeFogSmall_C::ExecuteUbergraph_BP_VolumeFogSmall(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFogSmall.BP_VolumeFogSmall_C.ExecuteUbergraph_BP_VolumeFogSmall");

	ABP_VolumeFogSmall_C_ExecuteUbergraph_BP_VolumeFogSmall_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
