// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_IntroTutorial_Complete_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function IntroTutorial_Complete.IntroTutorial_Complete_C.Destruct
// ()

void UIntroTutorial_Complete_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function IntroTutorial_Complete.IntroTutorial_Complete_C.Destruct");

	UIntroTutorial_Complete_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function IntroTutorial_Complete.IntroTutorial_Complete_C.ExecuteUbergraph_IntroTutorial_Complete
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UIntroTutorial_Complete_C::ExecuteUbergraph_IntroTutorial_Complete(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function IntroTutorial_Complete.IntroTutorial_Complete_C.ExecuteUbergraph_IntroTutorial_Complete");

	UIntroTutorial_Complete_C_ExecuteUbergraph_IntroTutorial_Complete_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
