// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GeneratorFuelInventorySlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C.Init
// ()
// Parameters:
// class AFGBuildableGeneratorFuel* Generator                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_GeneratorFuelInventorySlot_C::Init(class AFGBuildableGeneratorFuel* Generator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C.Init");

	UWidget_GeneratorFuelInventorySlot_C_Init_Params params;
	params.Generator = Generator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C.GetFuelPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_GeneratorFuelInventorySlot_C::GetFuelPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C.GetFuelPercent");

	UWidget_GeneratorFuelInventorySlot_C_GetFuelPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
