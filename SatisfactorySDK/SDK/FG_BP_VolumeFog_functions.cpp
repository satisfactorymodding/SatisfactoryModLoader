// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_VolumeFog_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_VolumeFog.BP_VolumeFog_C.UpdateBrightness
// ()

void ABP_VolumeFog_C::UpdateBrightness()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.UpdateBrightness");

	ABP_VolumeFog_C_UpdateBrightness_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.UserConstructionScript
// ()

void ABP_VolumeFog_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.UserConstructionScript");

	ABP_VolumeFog_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.LostSignificance
// ()

void ABP_VolumeFog_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.LostSignificance");

	ABP_VolumeFog_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.GainedSignificance
// ()

void ABP_VolumeFog_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.GainedSignificance");

	ABP_VolumeFog_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_VolumeFog_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.ReceiveEndPlay");

	ABP_VolumeFog_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_VolumeFog_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.ReceiveTick");

	ABP_VolumeFog_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.ReceiveBeginPlay
// ()

void ABP_VolumeFog_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.ReceiveBeginPlay");

	ABP_VolumeFog_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_VolumeFog.BP_VolumeFog_C.ExecuteUbergraph_BP_VolumeFog
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_VolumeFog_C::ExecuteUbergraph_BP_VolumeFog(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_VolumeFog.BP_VolumeFog_C.ExecuteUbergraph_BP_VolumeFog");

	ABP_VolumeFog_C_ExecuteUbergraph_BP_VolumeFog_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
