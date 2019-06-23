// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MantaAnim_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MantaAnim.BP_MantaAnim_C.ExecuteUbergraph_BP_MantaAnim
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MantaAnim_C::ExecuteUbergraph_BP_MantaAnim(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MantaAnim.BP_MantaAnim_C.ExecuteUbergraph_BP_MantaAnim");

	UBP_MantaAnim_C_ExecuteUbergraph_BP_MantaAnim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
