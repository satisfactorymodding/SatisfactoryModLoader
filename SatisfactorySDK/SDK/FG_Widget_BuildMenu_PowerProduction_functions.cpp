// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_PowerProduction_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C.GetStatText
// ()

void UWidget_BuildMenu_PowerProduction_C::GetStatText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C.GetStatText");

	UWidget_BuildMenu_PowerProduction_C_GetStatText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_PowerProduction_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C.PreConstruct");

	UWidget_BuildMenu_PowerProduction_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C.ExecuteUbergraph_Widget_BuildMenu_PowerProduction
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_BuildMenu_PowerProduction_C::ExecuteUbergraph_Widget_BuildMenu_PowerProduction(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C.ExecuteUbergraph_Widget_BuildMenu_PowerProduction");

	UWidget_BuildMenu_PowerProduction_C_ExecuteUbergraph_Widget_BuildMenu_PowerProduction_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
