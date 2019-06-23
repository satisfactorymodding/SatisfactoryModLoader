// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ObjectScanner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_ObjectScanner.Attach_ObjectScanner_C.UserConstructionScript
// ()

void AAttach_ObjectScanner_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ObjectScanner.Attach_ObjectScanner_C.UserConstructionScript");

	AAttach_ObjectScanner_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ObjectScanner.Attach_ObjectScanner_C.ReceiveBeginPlay
// ()

void AAttach_ObjectScanner_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ObjectScanner.Attach_ObjectScanner_C.ReceiveBeginPlay");

	AAttach_ObjectScanner_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ObjectScanner.Attach_ObjectScanner_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_ObjectScanner_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ObjectScanner.Attach_ObjectScanner_C.ReceiveTick");

	AAttach_ObjectScanner_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ObjectScanner.Attach_ObjectScanner_C.UpdateScannerVisuals
// ()

void AAttach_ObjectScanner_C::UpdateScannerVisuals()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ObjectScanner.Attach_ObjectScanner_C.UpdateScannerVisuals");

	AAttach_ObjectScanner_C_UpdateScannerVisuals_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ObjectScanner.Attach_ObjectScanner_C.PlayAttachEffects3P
// ()

void AAttach_ObjectScanner_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ObjectScanner.Attach_ObjectScanner_C.PlayAttachEffects3P");

	AAttach_ObjectScanner_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ObjectScanner.Attach_ObjectScanner_C.ExecuteUbergraph_Attach_ObjectScanner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_ObjectScanner_C::ExecuteUbergraph_Attach_ObjectScanner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ObjectScanner.Attach_ObjectScanner_C.ExecuteUbergraph_Attach_ObjectScanner");

	AAttach_ObjectScanner_C_ExecuteUbergraph_Attach_ObjectScanner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
