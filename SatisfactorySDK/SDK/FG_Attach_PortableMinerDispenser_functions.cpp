// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_PortableMinerDispenser_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.UserConstructionScript
// ()

void AAttach_PortableMinerDispenser_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.UserConstructionScript");

	AAttach_PortableMinerDispenser_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.PlayAttachEffects3P
// ()

void AAttach_PortableMinerDispenser_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.PlayAttachEffects3P");

	AAttach_PortableMinerDispenser_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.PlayDetachEffects3P
// ()

void AAttach_PortableMinerDispenser_C::PlayDetachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.PlayDetachEffects3P");

	AAttach_PortableMinerDispenser_C_PlayDetachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.ExecuteUbergraph_Attach_PortableMinerDispenser
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_PortableMinerDispenser_C::ExecuteUbergraph_Attach_PortableMinerDispenser(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_PortableMinerDispenser.Attach_PortableMinerDispenser_C.ExecuteUbergraph_Attach_PortableMinerDispenser");

	AAttach_PortableMinerDispenser_C_ExecuteUbergraph_Attach_PortableMinerDispenser_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
