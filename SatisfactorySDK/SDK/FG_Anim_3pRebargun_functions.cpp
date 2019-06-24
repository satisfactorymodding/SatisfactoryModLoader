// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_3pRebargun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_3pRebargun.Anim_3pRebargun_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_3pRebargun_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3pRebargun.Anim_3pRebargun_C.BlueprintUpdateAnimation");

	UAnim_3pRebargun_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_3pRebargun.Anim_3pRebargun_C.AnimNotify_RebarGunIsLoaded3p
// ()

void UAnim_3pRebargun_C::AnimNotify_RebarGunIsLoaded3p()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3pRebargun.Anim_3pRebargun_C.AnimNotify_RebarGunIsLoaded3p");

	UAnim_3pRebargun_C_AnimNotify_RebarGunIsLoaded3p_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_3pRebargun.Anim_3pRebargun_C.AnimNotify_RebarGunIsNotLoaded3p
// ()

void UAnim_3pRebargun_C::AnimNotify_RebarGunIsNotLoaded3p()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3pRebargun.Anim_3pRebargun_C.AnimNotify_RebarGunIsNotLoaded3p");

	UAnim_3pRebargun_C_AnimNotify_RebarGunIsNotLoaded3p_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_3pRebargun.Anim_3pRebargun_C.ExecuteUbergraph_Anim_3pRebargun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_3pRebargun_C::ExecuteUbergraph_Anim_3pRebargun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3pRebargun.Anim_3pRebargun_C.ExecuteUbergraph_Anim_3pRebargun");

	UAnim_3pRebargun_C_ExecuteUbergraph_Anim_3pRebargun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
