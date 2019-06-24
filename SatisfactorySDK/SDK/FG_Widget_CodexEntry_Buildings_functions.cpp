// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CodexEntry_Buildings_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CodexEntry_Buildings.Widget_CodexEntry_Buildings_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CodexEntry_Buildings_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexEntry_Buildings.Widget_CodexEntry_Buildings_C.PreConstruct");

	UWidget_CodexEntry_Buildings_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CodexEntry_Buildings.Widget_CodexEntry_Buildings_C.ExecuteUbergraph_Widget_CodexEntry_Buildings
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CodexEntry_Buildings_C::ExecuteUbergraph_Widget_CodexEntry_Buildings(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CodexEntry_Buildings.Widget_CodexEntry_Buildings_C.ExecuteUbergraph_Widget_CodexEntry_Buildings");

	UWidget_CodexEntry_Buildings_C_ExecuteUbergraph_Widget_CodexEntry_Buildings_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
