// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Build_IngredientInfo_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Build_IngredientInfo.Widget_Build_IngredientInfo_C.Construct
// ()

void UWidget_Build_IngredientInfo_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Build_IngredientInfo.Widget_Build_IngredientInfo_C.Construct");

	UWidget_Build_IngredientInfo_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Build_IngredientInfo.Widget_Build_IngredientInfo_C.ExecuteUbergraph_Widget_Build_IngredientInfo
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Build_IngredientInfo_C::ExecuteUbergraph_Widget_Build_IngredientInfo(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Build_IngredientInfo.Widget_Build_IngredientInfo_C.ExecuteUbergraph_Widget_Build_IngredientInfo");

	UWidget_Build_IngredientInfo_C_ExecuteUbergraph_Widget_Build_IngredientInfo_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
