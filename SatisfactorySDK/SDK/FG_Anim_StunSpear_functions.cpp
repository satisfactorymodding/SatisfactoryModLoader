// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_StunSpear_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_StunSpear.Anim_StunSpear_C.AnimNotify_Notify_StunSpearAttack
// ()

void UAnim_StunSpear_C::AnimNotify_Notify_StunSpearAttack()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_StunSpear.Anim_StunSpear_C.AnimNotify_Notify_StunSpearAttack");

	UAnim_StunSpear_C_AnimNotify_Notify_StunSpearAttack_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_StunSpear.Anim_StunSpear_C.ExecuteUbergraph_Anim_StunSpear
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_StunSpear_C::ExecuteUbergraph_Anim_StunSpear(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_StunSpear.Anim_StunSpear_C.ExecuteUbergraph_Anim_StunSpear");

	UAnim_StunSpear_C_ExecuteUbergraph_Anim_StunSpear_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
