// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_MedKit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_MedKit.Attach_MedKit_C.UserConstructionScript
// ()

void AAttach_MedKit_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_MedKit.Attach_MedKit_C.UserConstructionScript");

	AAttach_MedKit_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_MedKit.Attach_MedKit_C.PlayUseEffect
// ()
// Parameters:
// struct FVector*                UseLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_MedKit_C::PlayUseEffect(struct FVector* UseLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_MedKit.Attach_MedKit_C.PlayUseEffect");

	AAttach_MedKit_C_PlayUseEffect_Params params;
	params.UseLocation = UseLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_MedKit.Attach_MedKit_C.PlayAttachEffects3P
// ()

void AAttach_MedKit_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_MedKit.Attach_MedKit_C.PlayAttachEffects3P");

	AAttach_MedKit_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_MedKit.Attach_MedKit_C.ExecuteUbergraph_Attach_MedKit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_MedKit_C::ExecuteUbergraph_Attach_MedKit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_MedKit.Attach_MedKit_C.ExecuteUbergraph_Attach_MedKit");

	AAttach_MedKit_C_ExecuteUbergraph_Attach_MedKit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
