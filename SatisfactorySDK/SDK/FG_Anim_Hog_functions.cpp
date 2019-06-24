// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Hog_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Hog.Anim_Hog_C.CalculateAnimGraphVariables
// ()

void UAnim_Hog_C::CalculateAnimGraphVariables()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.CalculateAnimGraphVariables");

	UAnim_Hog_C_CalculateAnimGraphVariables_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Hog.Anim_Hog_C.OnPointDamageTaken
// ()
// Parameters:
// struct FVector*                shootDIrection                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Hog_C::OnPointDamageTaken(struct FVector* shootDIrection)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.OnPointDamageTaken");

	UAnim_Hog_C_OnPointDamageTaken_Params params;
	params.shootDIrection = shootDIrection;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Hog.Anim_Hog_C.OnAnyDamageTaken
// ()

void UAnim_Hog_C::OnAnyDamageTaken()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.OnAnyDamageTaken");

	UAnim_Hog_C_OnAnyDamageTaken_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Hog.Anim_Hog_C.OnRadialDamageTaken
// ()

void UAnim_Hog_C::OnRadialDamageTaken()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.OnRadialDamageTaken");

	UAnim_Hog_C_OnRadialDamageTaken_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Hog.Anim_Hog_C.AnimNotify_Notify_Hog_LeftIdle
// ()

void UAnim_Hog_C::AnimNotify_Notify_Hog_LeftIdle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.AnimNotify_Notify_Hog_LeftIdle");

	UAnim_Hog_C_AnimNotify_Notify_Hog_LeftIdle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Hog.Anim_Hog_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Hog_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.BlueprintUpdateAnimation");

	UAnim_Hog_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Hog.Anim_Hog_C.ExecuteUbergraph_Anim_Hog
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Hog_C::ExecuteUbergraph_Anim_Hog(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Hog.Anim_Hog_C.ExecuteUbergraph_Anim_Hog");

	UAnim_Hog_C_ExecuteUbergraph_Anim_Hog_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
