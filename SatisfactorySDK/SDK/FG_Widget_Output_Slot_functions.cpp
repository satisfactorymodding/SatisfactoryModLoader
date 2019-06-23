// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Output_Slot_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Output_Slot.Widget_Output_Slot_C.UpdateWasteSlotVisibility
// ()

void UWidget_Output_Slot_C::UpdateWasteSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.UpdateWasteSlotVisibility");

	UWidget_Output_Slot_C_UpdateWasteSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Output_Slot.Widget_Output_Slot_C.CreateEfficiencyToolTip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_Output_Slot_C::CreateEfficiencyToolTip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.CreateEfficiencyToolTip");

	UWidget_Output_Slot_C_CreateEfficiencyToolTip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Output_Slot.Widget_Output_Slot_C.CreatePowerConsumptionToolTip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_Output_Slot_C::CreatePowerConsumptionToolTip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.CreatePowerConsumptionToolTip");

	UWidget_Output_Slot_C_CreatePowerConsumptionToolTip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Output_Slot.Widget_Output_Slot_C.CreateCycleTimeTooltip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_Output_Slot_C::CreateCycleTimeTooltip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.CreateCycleTimeTooltip");

	UWidget_Output_Slot_C_CreateCycleTimeTooltip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Output_Slot.Widget_Output_Slot_C.Construct
// ()

void UWidget_Output_Slot_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.Construct");

	UWidget_Output_Slot_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Output_Slot.Widget_Output_Slot_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Output_Slot_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.PreConstruct");

	UWidget_Output_Slot_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Output_Slot.Widget_Output_Slot_C.ExecuteUbergraph_Widget_Output_Slot
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Output_Slot_C::ExecuteUbergraph_Widget_Output_Slot(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Output_Slot.Widget_Output_Slot_C.ExecuteUbergraph_Widget_Output_Slot");

	UWidget_Output_Slot_C_ExecuteUbergraph_Widget_Output_Slot_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
