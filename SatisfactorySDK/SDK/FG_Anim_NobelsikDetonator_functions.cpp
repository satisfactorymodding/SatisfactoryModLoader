// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_NobelsikDetonator_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_NobelsikDetonator.Anim_NobelsikDetonator_C.AnimNotify_NobeliskDetonate
// ()

void UAnim_NobelsikDetonator_C::AnimNotify_NobeliskDetonate()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_NobelsikDetonator.Anim_NobelsikDetonator_C.AnimNotify_NobeliskDetonate");

	UAnim_NobelsikDetonator_C_AnimNotify_NobeliskDetonate_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_NobelsikDetonator.Anim_NobelsikDetonator_C.AnimNotify_NobeliskThrowRelease
// ()

void UAnim_NobelsikDetonator_C::AnimNotify_NobeliskThrowRelease()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_NobelsikDetonator.Anim_NobelsikDetonator_C.AnimNotify_NobeliskThrowRelease");

	UAnim_NobelsikDetonator_C_AnimNotify_NobeliskThrowRelease_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_NobelsikDetonator.Anim_NobelsikDetonator_C.ExecuteUbergraph_Anim_NobelsikDetonator
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_NobelsikDetonator_C::ExecuteUbergraph_Anim_NobelsikDetonator(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_NobelsikDetonator.Anim_NobelsikDetonator_C.ExecuteUbergraph_Anim_NobelsikDetonator");

	UAnim_NobelsikDetonator_C_ExecuteUbergraph_Anim_NobelsikDetonator_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
