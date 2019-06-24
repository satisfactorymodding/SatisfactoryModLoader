// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Stinger_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Stinger.Anim_Stinger_C.CalculateAnimGraphVariables
// ()

void UAnim_Stinger_C::CalculateAnimGraphVariables()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.CalculateAnimGraphVariables");

	UAnim_Stinger_C_CalculateAnimGraphVariables_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Stinger.Anim_Stinger_C.OnRadialDamageTaken
// ()

void UAnim_Stinger_C::OnRadialDamageTaken()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.OnRadialDamageTaken");

	UAnim_Stinger_C_OnRadialDamageTaken_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Stinger.Anim_Stinger_C.OnPointDamageTaken
// ()
// Parameters:
// struct FVector*                shootDIrection                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Stinger_C::OnPointDamageTaken(struct FVector* shootDIrection)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.OnPointDamageTaken");

	UAnim_Stinger_C_OnPointDamageTaken_Params params;
	params.shootDIrection = shootDIrection;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Stinger.Anim_Stinger_C.AnimNotify_Notify_Stinger_Entered_Idle
// ()

void UAnim_Stinger_C::AnimNotify_Notify_Stinger_Entered_Idle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.AnimNotify_Notify_Stinger_Entered_Idle");

	UAnim_Stinger_C_AnimNotify_Notify_Stinger_Entered_Idle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Stinger.Anim_Stinger_C.AnimNotify_Notify_Stinger_Entered_Walk
// ()

void UAnim_Stinger_C::AnimNotify_Notify_Stinger_Entered_Walk()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.AnimNotify_Notify_Stinger_Entered_Walk");

	UAnim_Stinger_C_AnimNotify_Notify_Stinger_Entered_Walk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Stinger.Anim_Stinger_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Stinger_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.BlueprintUpdateAnimation");

	UAnim_Stinger_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Stinger.Anim_Stinger_C.ExecuteUbergraph_Anim_Stinger
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Stinger_C::ExecuteUbergraph_Anim_Stinger(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Stinger.Anim_Stinger_C.ExecuteUbergraph_Anim_Stinger");

	UAnim_Stinger_C_ExecuteUbergraph_Anim_Stinger_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
