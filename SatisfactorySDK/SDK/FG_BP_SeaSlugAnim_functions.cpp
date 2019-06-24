// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SeaSlugAnim_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_SeaSlugAnim_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.BlueprintUpdateAnimation");

	UBP_SeaSlugAnim_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.AnimNotify_PlayRippleVfX_notify
// ()

void UBP_SeaSlugAnim_C::AnimNotify_PlayRippleVfX_notify()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.AnimNotify_PlayRippleVfX_notify");

	UBP_SeaSlugAnim_C_AnimNotify_PlayRippleVfX_notify_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.AnimNotify_PlayRippleVfx_02_notify
// ()

void UBP_SeaSlugAnim_C::AnimNotify_PlayRippleVfx_02_notify()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.AnimNotify_PlayRippleVfx_02_notify");

	UBP_SeaSlugAnim_C_AnimNotify_PlayRippleVfx_02_notify_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.AnimNotify_PlayRippleVfx_03_notify
// ()

void UBP_SeaSlugAnim_C::AnimNotify_PlayRippleVfx_03_notify()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.AnimNotify_PlayRippleVfx_03_notify");

	UBP_SeaSlugAnim_C_AnimNotify_PlayRippleVfx_03_notify_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.ExecuteUbergraph_BP_SeaSlugAnim
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_SeaSlugAnim_C::ExecuteUbergraph_BP_SeaSlugAnim(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlugAnim.BP_SeaSlugAnim_C.ExecuteUbergraph_BP_SeaSlugAnim");

	UBP_SeaSlugAnim_C_ExecuteUbergraph_BP_SeaSlugAnim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
