// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Birds_01_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Birds_01.BP_Birds_01_C.UserConstructionScript
// ()

void ABP_Birds_01_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Birds_01.BP_Birds_01_C.UserConstructionScript");

	ABP_Birds_01_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Birds_01.BP_Birds_01_C.ReceiveBeginPlay
// ()

void ABP_Birds_01_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Birds_01.BP_Birds_01_C.ReceiveBeginPlay");

	ABP_Birds_01_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Birds_01.BP_Birds_01_C.ExecuteUbergraph_BP_Birds_01
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Birds_01_C::ExecuteUbergraph_BP_Birds_01(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Birds_01.BP_Birds_01_C.ExecuteUbergraph_BP_Birds_01");

	ABP_Birds_01_C_ExecuteUbergraph_BP_Birds_01_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
