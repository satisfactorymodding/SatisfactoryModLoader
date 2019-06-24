// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Chainsaw_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_Chainsaw.Attach_Chainsaw_C.UserConstructionScript
// ()

void AAttach_Chainsaw_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Chainsaw.Attach_Chainsaw_C.UserConstructionScript");

	AAttach_Chainsaw_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Chainsaw.Attach_Chainsaw_C.OnAttachmentUseStateUpdated
// ()
// Parameters:
// int*                           newUseState                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_Chainsaw_C::OnAttachmentUseStateUpdated(int* newUseState)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Chainsaw.Attach_Chainsaw_C.OnAttachmentUseStateUpdated");

	AAttach_Chainsaw_C_OnAttachmentUseStateUpdated_Params params;
	params.newUseState = newUseState;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Chainsaw.Attach_Chainsaw_C.PlayAttachEffects3P
// ()

void AAttach_Chainsaw_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Chainsaw.Attach_Chainsaw_C.PlayAttachEffects3P");

	AAttach_Chainsaw_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Chainsaw.Attach_Chainsaw_C.PlayDetachEffects3P
// ()

void AAttach_Chainsaw_C::PlayDetachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Chainsaw.Attach_Chainsaw_C.PlayDetachEffects3P");

	AAttach_Chainsaw_C_PlayDetachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Chainsaw.Attach_Chainsaw_C.ExecuteUbergraph_Attach_Chainsaw
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_Chainsaw_C::ExecuteUbergraph_Attach_Chainsaw(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Chainsaw.Attach_Chainsaw_C.ExecuteUbergraph_Attach_Chainsaw");

	AAttach_Chainsaw_C_ExecuteUbergraph_Attach_Chainsaw_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
