// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Beacon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_Beacon.Attach_Beacon_C.UserConstructionScript
// ()

void AAttach_Beacon_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Beacon.Attach_Beacon_C.UserConstructionScript");

	AAttach_Beacon_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Beacon.Attach_Beacon_C.PlayAttachEffects3P
// ()

void AAttach_Beacon_C::PlayAttachEffects3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Beacon.Attach_Beacon_C.PlayAttachEffects3P");

	AAttach_Beacon_C_PlayAttachEffects3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_Beacon.Attach_Beacon_C.ExecuteUbergraph_Attach_Beacon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_Beacon_C::ExecuteUbergraph_Attach_Beacon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_Beacon.Attach_Beacon_C.ExecuteUbergraph_Attach_Beacon");

	AAttach_Beacon_C_ExecuteUbergraph_Attach_Beacon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
