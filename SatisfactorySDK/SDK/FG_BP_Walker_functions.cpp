// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Walker_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Walker.BP_Walker_C.UserConstructionScript
// ()

void ABP_Walker_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Walker.BP_Walker_C.UserConstructionScript");

	ABP_Walker_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Walker.BP_Walker_C.PlayConsumeItemEffect
// ()
// Parameters:
// class UClass**                 itemDescriptor                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int*                           amount                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Walker_C::PlayConsumeItemEffect(class UClass** itemDescriptor, int* amount)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Walker.BP_Walker_C.PlayConsumeItemEffect");

	ABP_Walker_C_PlayConsumeItemEffect_Params params;
	params.itemDescriptor = itemDescriptor;
	params.amount = amount;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Walker.BP_Walker_C.ExecuteUbergraph_BP_Walker
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Walker_C::ExecuteUbergraph_BP_Walker(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Walker.BP_Walker_C.ExecuteUbergraph_BP_Walker");

	ABP_Walker_C_ExecuteUbergraph_BP_Walker_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
