// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PortableMiner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_PortableMiner.BP_PortableMiner_C.UserConstructionScript
// ()

void ABP_PortableMiner_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PortableMiner.BP_PortableMiner_C.UserConstructionScript");

	ABP_PortableMiner_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PortableMiner.BP_PortableMiner_C.ReceiveDestroyed
// ()

void ABP_PortableMiner_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PortableMiner.BP_PortableMiner_C.ReceiveDestroyed");

	ABP_PortableMiner_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PortableMiner.BP_PortableMiner_C.StartIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_PortableMiner_C::StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PortableMiner.BP_PortableMiner_C.StartIsLookedAt");

	ABP_PortableMiner_C_StartIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PortableMiner.BP_PortableMiner_C.StopIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_PortableMiner_C::StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PortableMiner.BP_PortableMiner_C.StopIsLookedAt");

	ABP_PortableMiner_C_StopIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PortableMiner.BP_PortableMiner_C.ReceiveBeginPlay
// ()

void ABP_PortableMiner_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PortableMiner.BP_PortableMiner_C.ReceiveBeginPlay");

	ABP_PortableMiner_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PortableMiner.BP_PortableMiner_C.ExecuteUbergraph_BP_PortableMiner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PortableMiner_C::ExecuteUbergraph_BP_PortableMiner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PortableMiner.BP_PortableMiner_C.ExecuteUbergraph_BP_PortableMiner");

	ABP_PortableMiner_C_ExecuteUbergraph_BP_PortableMiner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
