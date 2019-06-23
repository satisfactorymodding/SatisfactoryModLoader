// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_DropPod_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_DropPod.Anim_DropPod_C.ExecuteUbergraph_Anim_DropPod
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_DropPod_C::ExecuteUbergraph_Anim_DropPod(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_DropPod.Anim_DropPod_C.ExecuteUbergraph_Anim_DropPod");

	UAnim_DropPod_C_ExecuteUbergraph_Anim_DropPod_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
