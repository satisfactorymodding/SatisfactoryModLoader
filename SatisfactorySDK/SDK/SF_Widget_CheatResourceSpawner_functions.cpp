// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CheatResourceSpawner_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.GetCountText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CheatResourceSpawner_C::GetCountText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.GetCountText");

	UWidget_CheatResourceSpawner_C_GetCountText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.Init
// ()

void UWidget_CheatResourceSpawner_C::Init()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.Init");

	UWidget_CheatResourceSpawner_C_Init_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.BndEvt__mDescriptorSelector_K2Node_ComponentBoundEvent_22_OnSelectionChangedEvent__DelegateSignature
// ()
// Parameters:
// class FString                  SelectedItem                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
// TEnumAsByte<ESelectInfo>       SelectionType                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatResourceSpawner_C::BndEvt__mDescriptorSelector_K2Node_ComponentBoundEvent_22_OnSelectionChangedEvent__DelegateSignature(const class FString& SelectedItem, TEnumAsByte<ESelectInfo> SelectionType)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.BndEvt__mDescriptorSelector_K2Node_ComponentBoundEvent_22_OnSelectionChangedEvent__DelegateSignature");

	UWidget_CheatResourceSpawner_C_BndEvt__mDescriptorSelector_K2Node_ComponentBoundEvent_22_OnSelectionChangedEvent__DelegateSignature_Params params;
	params.SelectedItem = SelectedItem;
	params.SelectionType = SelectionType;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.ExecuteUbergraph_Widget_CheatResourceSpawner
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CheatResourceSpawner_C::ExecuteUbergraph_Widget_CheatResourceSpawner(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CheatResourceSpawner.Widget_CheatResourceSpawner_C.ExecuteUbergraph_Widget_CheatResourceSpawner");

	UWidget_CheatResourceSpawner_C_ExecuteUbergraph_Widget_CheatResourceSpawner_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
