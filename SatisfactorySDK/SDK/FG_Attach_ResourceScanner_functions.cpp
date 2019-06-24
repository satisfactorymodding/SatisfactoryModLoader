// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_ResourceScanner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Attach_ResourceScanner.Attach_ResourceScanner_C.UserConstructionScript
// ()

void AAttach_ResourceScanner_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ResourceScanner.Attach_ResourceScanner_C.UserConstructionScript");

	AAttach_ResourceScanner_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ResourceScanner.Attach_ResourceScanner_C.CustomEvent_1
// ()

void AAttach_ResourceScanner_C::CustomEvent_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ResourceScanner.Attach_ResourceScanner_C.CustomEvent_1");

	AAttach_ResourceScanner_C_CustomEvent_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ResourceScanner.Attach_ResourceScanner_C.PlayUseEffect
// ()
// Parameters:
// struct FVector*                UseLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_ResourceScanner_C::PlayUseEffect(struct FVector* UseLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ResourceScanner.Attach_ResourceScanner_C.PlayUseEffect");

	AAttach_ResourceScanner_C_PlayUseEffect_Params params;
	params.UseLocation = UseLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Attach_ResourceScanner.Attach_ResourceScanner_C.ExecuteUbergraph_Attach_ResourceScanner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AAttach_ResourceScanner_C::ExecuteUbergraph_Attach_ResourceScanner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Attach_ResourceScanner.Attach_ResourceScanner_C.ExecuteUbergraph_Attach_ResourceScanner");

	AAttach_ResourceScanner_C_ExecuteUbergraph_Attach_ResourceScanner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
