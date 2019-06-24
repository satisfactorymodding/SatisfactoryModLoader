// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Medkit_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Medkit.Anim_Medkit_C.ExecuteUbergraph_Anim_Medkit
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Medkit_C::ExecuteUbergraph_Anim_Medkit(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Medkit.Anim_Medkit_C.ExecuteUbergraph_Anim_Medkit");

	UAnim_Medkit_C_ExecuteUbergraph_Anim_Medkit_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
