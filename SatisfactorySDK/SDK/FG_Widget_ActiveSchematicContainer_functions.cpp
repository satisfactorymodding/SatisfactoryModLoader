// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActiveSchematicContainer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.GetPodTimerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ActiveSchematicContainer_C::GetPodTimerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.GetPodTimerText");

	UWidget_ActiveSchematicContainer_C_GetPodTimerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShowPodTimerText
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ActiveSchematicContainer_C::ShowPodTimerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShowPodTimerText");

	UWidget_ActiveSchematicContainer_C_ShowPodTimerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.RemoveSchematicCostWidget
// ()

void UWidget_ActiveSchematicContainer_C::RemoveSchematicCostWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.RemoveSchematicCostWidget");

	UWidget_ActiveSchematicContainer_C_RemoveSchematicCostWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.AddSchematicCostWidget
// ()

void UWidget_ActiveSchematicContainer_C::AddSchematicCostWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.AddSchematicCostWidget");

	UWidget_ActiveSchematicContainer_C_AddSchematicCostWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.MatchWidgetWithSchematicCost
// ()

void UWidget_ActiveSchematicContainer_C::MatchWidgetWithSchematicCost()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.MatchWidgetWithSchematicCost");

	UWidget_ActiveSchematicContainer_C_MatchWidgetWithSchematicCost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShowSchematicWidget
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_ActiveSchematicContainer_C::ShowSchematicWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShowSchematicWidget");

	UWidget_ActiveSchematicContainer_C_ShowSchematicWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShouldShowSchematic
// ()
// Parameters:
// bool                           ShouldShow                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ActiveSchematicContainer_C::ShouldShowSchematic(bool* ShouldShow)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ShouldShowSchematic");

	UWidget_ActiveSchematicContainer_C_ShouldShowSchematic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ShouldShow != nullptr)
		*ShouldShow = params.ShouldShow;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.GetSchematicName
// ()

void UWidget_ActiveSchematicContainer_C::GetSchematicName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.GetSchematicName");

	UWidget_ActiveSchematicContainer_C_GetSchematicName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.Construct
// ()

void UWidget_ActiveSchematicContainer_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.Construct");

	UWidget_ActiveSchematicContainer_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.UpdateSchematic
// ()
// Parameters:
// class UClass*                  activeSchematic                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActiveSchematicContainer_C::UpdateSchematic(class UClass* activeSchematic)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.UpdateSchematic");

	UWidget_ActiveSchematicContainer_C_UpdateSchematic_Params params;
	params.activeSchematic = activeSchematic;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ExecuteUbergraph_Widget_ActiveSchematicContainer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActiveSchematicContainer_C::ExecuteUbergraph_Widget_ActiveSchematicContainer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActiveSchematicContainer.Widget_ActiveSchematicContainer_C.ExecuteUbergraph_Widget_ActiveSchematicContainer");

	UWidget_ActiveSchematicContainer_C_ExecuteUbergraph_Widget_ActiveSchematicContainer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
