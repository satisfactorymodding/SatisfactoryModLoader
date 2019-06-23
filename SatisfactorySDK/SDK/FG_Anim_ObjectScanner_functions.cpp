// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_ObjectScanner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_ObjectScanner.Anim_ObjectScanner_C.ExecuteUbergraph_Anim_ObjectScanner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_ObjectScanner_C::ExecuteUbergraph_Anim_ObjectScanner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_ObjectScanner.Anim_ObjectScanner_C.ExecuteUbergraph_Anim_ObjectScanner");

	UAnim_ObjectScanner_C_ExecuteUbergraph_Anim_ObjectScanner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
