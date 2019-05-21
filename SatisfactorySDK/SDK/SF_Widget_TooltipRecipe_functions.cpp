// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_TooltipRecipe_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.OnUnhovered
// ()

void UWidget_TooltipRecipe_C::OnUnhovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.OnUnhovered");

	UWidget_TooltipRecipe_C_OnUnhovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.OnHovered
// ()

void UWidget_TooltipRecipe_C::OnHovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.OnHovered");

	UWidget_TooltipRecipe_C_OnHovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.Construct
// ()

void UWidget_TooltipRecipe_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.Construct");

	UWidget_TooltipRecipe_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.ExecuteUbergraph_Widget_TooltipRecipe
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_TooltipRecipe_C::ExecuteUbergraph_Widget_TooltipRecipe(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TooltipRecipe.Widget_TooltipRecipe_C.ExecuteUbergraph_Widget_TooltipRecipe");

	UWidget_TooltipRecipe_C_ExecuteUbergraph_Widget_TooltipRecipe_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
