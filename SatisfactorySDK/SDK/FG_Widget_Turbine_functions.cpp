// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Turbine_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Turbine.Widget_Turbine_C.TurnTurbine
// ()
// Parameters:
// class UPanelWidget*            Container                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_Turbine_C::TurnTurbine(class UPanelWidget* Container)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Turbine.Widget_Turbine_C.TurnTurbine");

	UWidget_Turbine_C_TurnTurbine_Params params;
	params.Container = Container;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Turbine.Widget_Turbine_C.TurnEvent
// ()

void UWidget_Turbine_C::TurnEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Turbine.Widget_Turbine_C.TurnEvent");

	UWidget_Turbine_C_TurnEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Turbine.Widget_Turbine_C.Destruct
// ()

void UWidget_Turbine_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Turbine.Widget_Turbine_C.Destruct");

	UWidget_Turbine_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Turbine.Widget_Turbine_C.Construct
// ()

void UWidget_Turbine_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Turbine.Widget_Turbine_C.Construct");

	UWidget_Turbine_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Turbine.Widget_Turbine_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Turbine_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Turbine.Widget_Turbine_C.PreConstruct");

	UWidget_Turbine_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Turbine.Widget_Turbine_C.ExecuteUbergraph_Widget_Turbine
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Turbine_C::ExecuteUbergraph_Widget_Turbine(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Turbine.Widget_Turbine_C.ExecuteUbergraph_Widget_Turbine");

	UWidget_Turbine_C_ExecuteUbergraph_Widget_Turbine_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
