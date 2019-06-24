// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ShockShank_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_ShockShank.Anim_ShockShank_C.AnimNotify_Notify_ShockShankAttack
// ()

void UAnim_ShockShank_C::AnimNotify_Notify_ShockShankAttack()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ShockShank.Anim_ShockShank_C.AnimNotify_Notify_ShockShankAttack");

	UAnim_ShockShank_C_AnimNotify_Notify_ShockShankAttack_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ShockShank.Anim_ShockShank_C.ExecuteUbergraph_Anim_ShockShank
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_ShockShank_C::ExecuteUbergraph_Anim_ShockShank(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ShockShank.Anim_ShockShank_C.ExecuteUbergraph_Anim_ShockShank");

	UAnim_ShockShank_C_ExecuteUbergraph_Anim_ShockShank_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
