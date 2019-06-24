// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActiveSchematicCost_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.GetNumIngredientsPaidOff
// ()
// Parameters:
// int                            NumItems                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ActiveSchematicCost_C::GetNumIngredientsPaidOff(int* NumItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.GetNumIngredientsPaidOff");

	UWidget_ActiveSchematicCost_C_GetNumIngredientsPaidOff_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NumItems != nullptr)
		*NumItems = params.NumItems;
}


// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.GetIngredient
// ()
// Parameters:
// struct FItemAmount             ingredient                     (Parm, OutParm)

void UWidget_ActiveSchematicCost_C::GetIngredient(struct FItemAmount* ingredient)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.GetIngredient");

	UWidget_ActiveSchematicCost_C_GetIngredient_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ingredient != nullptr)
		*ingredient = params.ingredient;
}


// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.UpdateTimer
// ()

void UWidget_ActiveSchematicCost_C::UpdateTimer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.UpdateTimer");

	UWidget_ActiveSchematicCost_C_UpdateTimer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.Construct
// ()

void UWidget_ActiveSchematicCost_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.Construct");

	UWidget_ActiveSchematicCost_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.Destruct
// ()

void UWidget_ActiveSchematicCost_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.Destruct");

	UWidget_ActiveSchematicCost_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.ExecuteUbergraph_Widget_ActiveSchematicCost
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActiveSchematicCost_C::ExecuteUbergraph_Widget_ActiveSchematicCost(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicCost.Widget_ActiveSchematicCost_C.ExecuteUbergraph_Widget_ActiveSchematicCost");

	UWidget_ActiveSchematicCost_C_ExecuteUbergraph_Widget_ActiveSchematicCost_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
