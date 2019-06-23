// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_IntroTutorial_Greeting_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function IntroTutorial_Greeting.IntroTutorial_Greeting_C.Destruct
// ()

void UIntroTutorial_Greeting_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function IntroTutorial_Greeting.IntroTutorial_Greeting_C.Destruct");

	UIntroTutorial_Greeting_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function IntroTutorial_Greeting.IntroTutorial_Greeting_C.ExecuteUbergraph_IntroTutorial_Greeting
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UIntroTutorial_Greeting_C::ExecuteUbergraph_IntroTutorial_Greeting(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function IntroTutorial_Greeting.IntroTutorial_Greeting_C.ExecuteUbergraph_IntroTutorial_Greeting");

	UIntroTutorial_Greeting_C_ExecuteUbergraph_IntroTutorial_Greeting_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
