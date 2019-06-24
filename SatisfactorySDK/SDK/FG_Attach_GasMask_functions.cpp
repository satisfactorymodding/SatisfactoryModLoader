// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_GasMask_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_GasMask.Attach_GasMask_C.UserConstructionScript
// ()

void AAttach_GasMask_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_GasMask.Attach_GasMask_C.UserConstructionScript");

	AAttach_GasMask_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_GasMask.Attach_GasMask_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_GasMask_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_GasMask.Attach_GasMask_C.ReceiveTick");

	AAttach_GasMask_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_GasMask.Attach_GasMask_C.PlayAttachEffects3P
// ()

void AAttach_GasMask_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_GasMask.Attach_GasMask_C.PlayAttachEffects3P");

	AAttach_GasMask_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_GasMask.Attach_GasMask_C.ExecuteUbergraph_Attach_GasMask
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_GasMask_C::ExecuteUbergraph_Attach_GasMask(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_GasMask.Attach_GasMask_C.ExecuteUbergraph_Attach_GasMask");

	AAttach_GasMask_C_ExecuteUbergraph_Attach_GasMask_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
