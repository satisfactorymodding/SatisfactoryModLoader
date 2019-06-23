// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_3pChainsaw_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_3pChainsaw.Anim_3pChainsaw_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_3pChainsaw_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3pChainsaw.Anim_3pChainsaw_C.BlueprintUpdateAnimation");

	UAnim_3pChainsaw_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_3pChainsaw.Anim_3pChainsaw_C.ExecuteUbergraph_Anim_3pChainsaw
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_3pChainsaw_C::ExecuteUbergraph_Anim_3pChainsaw(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_3pChainsaw.Anim_3pChainsaw_C.ExecuteUbergraph_Anim_3pChainsaw");

	UAnim_3pChainsaw_C_ExecuteUbergraph_Anim_3pChainsaw_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
