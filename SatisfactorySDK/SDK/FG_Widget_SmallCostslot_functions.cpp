// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SmallCostslot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SmallCostslot.Widget_SmallCostSlot_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SmallCostSlot_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SmallCostslot.Widget_SmallCostSlot_C.Tick");

	UWidget_SmallCostSlot_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SmallCostslot.Widget_SmallCostSlot_C.ExecuteUbergraph_Widget_SmallCostSlot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SmallCostSlot_C::ExecuteUbergraph_Widget_SmallCostSlot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SmallCostslot.Widget_SmallCostSlot_C.ExecuteUbergraph_Widget_SmallCostSlot");

	UWidget_SmallCostSlot_C_ExecuteUbergraph_Widget_SmallCostSlot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
