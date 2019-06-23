// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Hint_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Hint.Widget_Hint_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Hint_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Hint.Widget_Hint_C.PreConstruct");

	UWidget_Hint_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Hint.Widget_Hint_C.Construct
// ()

void UWidget_Hint_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Hint.Widget_Hint_C.Construct");

	UWidget_Hint_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Hint.Widget_Hint_C.ExecuteUbergraph_Widget_Hint
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Hint_C::ExecuteUbergraph_Widget_Hint(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Hint.Widget_Hint_C.ExecuteUbergraph_Widget_Hint");

	UWidget_Hint_C_ExecuteUbergraph_Widget_Hint_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
