// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceNode_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ResourceNode.BP_ResourceNode_C.UserConstructionScript
// ()

void ABP_ResourceNode_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNode.BP_ResourceNode_C.UserConstructionScript");

	ABP_ResourceNode_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNode.BP_ResourceNode_C.GainedSignificance
// ()

void ABP_ResourceNode_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNode.BP_ResourceNode_C.GainedSignificance");

	ABP_ResourceNode_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNode.BP_ResourceNode_C.LostSignificance
// ()

void ABP_ResourceNode_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNode.BP_ResourceNode_C.LostSignificance");

	ABP_ResourceNode_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNode.BP_ResourceNode_C.ExecuteUbergraph_BP_ResourceNode
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ResourceNode_C::ExecuteUbergraph_BP_ResourceNode(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNode.BP_ResourceNode_C.ExecuteUbergraph_BP_ResourceNode");

	ABP_ResourceNode_C_ExecuteUbergraph_BP_ResourceNode_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
