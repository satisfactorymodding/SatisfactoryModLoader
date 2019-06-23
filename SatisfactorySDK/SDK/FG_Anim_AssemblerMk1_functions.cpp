// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_AssemblerMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_AssemblerMk1.Anim_AssemblerMk1_C.ExecuteUbergraph_Anim_AssemblerMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_AssemblerMk1_C::ExecuteUbergraph_Anim_AssemblerMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_AssemblerMk1.Anim_AssemblerMk1_C.ExecuteUbergraph_Anim_AssemblerMk1");

	UAnim_AssemblerMk1_C_ExecuteUbergraph_Anim_AssemblerMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
