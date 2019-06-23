// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SproutAnim_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SproutAnim.BP_SproutAnim_C.BlueprintInitializeAnimation
// ()

void UBP_SproutAnim_C::BlueprintInitializeAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SproutAnim.BP_SproutAnim_C.BlueprintInitializeAnimation");

	UBP_SproutAnim_C_BlueprintInitializeAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SproutAnim.BP_SproutAnim_C.ExecuteUbergraph_BP_SproutAnim
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_SproutAnim_C::ExecuteUbergraph_BP_SproutAnim(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SproutAnim.BP_SproutAnim_C.ExecuteUbergraph_BP_SproutAnim");

	UBP_SproutAnim_C_ExecuteUbergraph_BP_SproutAnim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
