// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CostSlot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_CostSlot.Widget_CostSlot_C.GetDividerTopVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_CostSlot_C::GetDividerTopVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CostSlot.Widget_CostSlot_C.GetDividerTopVisibility");

	UWidget_CostSlot_C_GetDividerTopVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CostSlot.Widget_CostSlot_C.GetItemName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_CostSlot_C::GetItemName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CostSlot.Widget_CostSlot_C.GetItemName");

	UWidget_CostSlot_C_GetItemName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_CostSlot.Widget_CostSlot_C.SetCostSlot
// ()
// Parameters:
// int                            SlotIdx                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CostSlot_C::SetCostSlot(int SlotIdx)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CostSlot.Widget_CostSlot_C.SetCostSlot");

	UWidget_CostSlot_C_SetCostSlot_Params params;
	params.SlotIdx = SlotIdx;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CostSlot.Widget_CostSlot_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CostSlot_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CostSlot.Widget_CostSlot_C.Tick");

	UWidget_CostSlot_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_CostSlot.Widget_CostSlot_C.ExecuteUbergraph_Widget_CostSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_CostSlot_C::ExecuteUbergraph_Widget_CostSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_CostSlot.Widget_CostSlot_C.ExecuteUbergraph_Widget_CostSlot");

	UWidget_CostSlot_C_ExecuteUbergraph_Widget_CostSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
