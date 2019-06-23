// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ResourceMiner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_MineComplete
// ()

void UAnim_ResourceMiner_C::AnimNotify_MineComplete()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_MineComplete");

	UAnim_ResourceMiner_C_AnimNotify_MineComplete_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_StopMining
// ()

void UAnim_ResourceMiner_C::AnimNotify_StopMining()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_StopMining");

	UAnim_ResourceMiner_C_AnimNotify_StopMining_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_MineVfx
// ()

void UAnim_ResourceMiner_C::AnimNotify_MineVfx()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_MineVfx");

	UAnim_ResourceMiner_C_AnimNotify_MineVfx_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_StartCameraShake
// ()

void UAnim_ResourceMiner_C::AnimNotify_StartCameraShake()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_StartCameraShake");

	UAnim_ResourceMiner_C_AnimNotify_StartCameraShake_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_PickRingSound
// ()

void UAnim_ResourceMiner_C::AnimNotify_PickRingSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_PickRingSound");

	UAnim_ResourceMiner_C_AnimNotify_PickRingSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_SecondMineVfx
// ()

void UAnim_ResourceMiner_C::AnimNotify_SecondMineVfx()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.AnimNotify_SecondMineVfx");

	UAnim_ResourceMiner_C_AnimNotify_SecondMineVfx_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_ResourceMiner.Anim_ResourceMiner_C.ExecuteUbergraph_Anim_ResourceMiner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_ResourceMiner_C::ExecuteUbergraph_Anim_ResourceMiner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ResourceMiner.Anim_ResourceMiner_C.ExecuteUbergraph_Anim_ResourceMiner");

	UAnim_ResourceMiner_C_ExecuteUbergraph_Anim_ResourceMiner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
