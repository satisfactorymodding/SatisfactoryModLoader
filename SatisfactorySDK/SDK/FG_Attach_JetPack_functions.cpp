// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_JetPack_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_JetPack.Attach_JetPack_C.UserConstructionScript
// ()

void AAttach_JetPack_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_JetPack.Attach_JetPack_C.UserConstructionScript");

	AAttach_JetPack_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_JetPack.Attach_JetPack_C.OnStopThrusting
// ()

void AAttach_JetPack_C::OnStopThrusting()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_JetPack.Attach_JetPack_C.OnStopThrusting");

	AAttach_JetPack_C_OnStopThrusting_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_JetPack.Attach_JetPack_C.OnStartThrusting
// ()

void AAttach_JetPack_C::OnStartThrusting()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_JetPack.Attach_JetPack_C.OnStartThrusting");

	AAttach_JetPack_C_OnStartThrusting_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_JetPack.Attach_JetPack_C.ReceiveBeginPlay
// ()

void AAttach_JetPack_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_JetPack.Attach_JetPack_C.ReceiveBeginPlay");

	AAttach_JetPack_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_JetPack.Attach_JetPack_C.ExecuteUbergraph_Attach_JetPack
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_JetPack_C::ExecuteUbergraph_Attach_JetPack(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_JetPack.Attach_JetPack_C.ExecuteUbergraph_Attach_JetPack");

	AAttach_JetPack_C_ExecuteUbergraph_Attach_JetPack_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
