// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ManufacturerMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_ManufacturerMk1_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.BlueprintUpdateAnimation");

	UAnim_ManufacturerMk1_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.BlueprintInitializeAnimation
// ()

void UAnim_ManufacturerMk1_C::BlueprintInitializeAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.BlueprintInitializeAnimation");

	UAnim_ManufacturerMk1_C_BlueprintInitializeAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorComplexEnteredProducing
// ()

void UAnim_ManufacturerMk1_C::AnimNotify_ConstructorComplexEnteredProducing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorComplexEnteredProducing");

	UAnim_ManufacturerMk1_C_AnimNotify_ConstructorComplexEnteredProducing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorComplexLeftProducing
// ()

void UAnim_ManufacturerMk1_C::AnimNotify_ConstructorComplexLeftProducing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorComplexLeftProducing");

	UAnim_ManufacturerMk1_C_AnimNotify_ConstructorComplexLeftProducing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorComplexLeftOffline
// ()

void UAnim_ManufacturerMk1_C::AnimNotify_ConstructorComplexLeftOffline()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorComplexLeftOffline");

	UAnim_ManufacturerMk1_C_AnimNotify_ConstructorComplexLeftOffline_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorAdvEnteredOffline
// ()

void UAnim_ManufacturerMk1_C::AnimNotify_ConstructorAdvEnteredOffline()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.AnimNotify_ConstructorAdvEnteredOffline");

	UAnim_ManufacturerMk1_C_AnimNotify_ConstructorAdvEnteredOffline_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.HasPowerChanged
// ()
// Parameters:
// bool                           State                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_ManufacturerMk1_C::HasPowerChanged(bool State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.HasPowerChanged");

	UAnim_ManufacturerMk1_C_HasPowerChanged_Params params;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.ExecuteUbergraph_Anim_ManufacturerMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_ManufacturerMk1_C::ExecuteUbergraph_Anim_ManufacturerMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ManufacturerMk1.Anim_ManufacturerMk1_C.ExecuteUbergraph_Anim_ManufacturerMk1");

	UAnim_ManufacturerMk1_C_ExecuteUbergraph_Anim_ManufacturerMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
