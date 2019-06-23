// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexContent_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CodexContent.Widget_CodexContent_C.Habada
// ()
// Parameters:
// bool                           NewParam                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_CodexContent_C::Habada(bool* NewParam)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexContent.Widget_CodexContent_C.Habada");

	UWidget_CodexContent_C_Habada_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewParam != nullptr)
		*NewParam = params.NewParam;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
