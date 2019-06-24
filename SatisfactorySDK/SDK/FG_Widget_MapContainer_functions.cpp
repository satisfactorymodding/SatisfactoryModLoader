// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapContainer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MapContainer.Widget_MapContainer_C.NormalizedValueToZoomValue
// ()
// Parameters:
// float                          NormalizedValue                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ZoomValue                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::NormalizedValueToZoomValue(float NormalizedValue, struct FVector2D* ZoomValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.NormalizedValueToZoomValue");

	UWidget_MapContainer_C_NormalizedValueToZoomValue_Params params;
	params.NormalizedValue = NormalizedValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ZoomValue != nullptr)
		*ZoomValue = params.ZoomValue;
}


// Function Widget_MapContainer.Widget_MapContainer_C.UpdateZoomSlider
// ()

void UWidget_MapContainer_C::UpdateZoomSlider()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.UpdateZoomSlider");

	UWidget_MapContainer_C_UpdateZoomSlider_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetOpenMap
// ()
// Parameters:
// bool                           OpenMap                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::SetOpenMap(bool OpenMap)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetOpenMap");

	UWidget_MapContainer_C_SetOpenMap_Params params;
	params.OpenMap = OpenMap;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.Construct
// ()

void UWidget_MapContainer_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.Construct");

	UWidget_MapContainer_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.CloseMap
// ()

void UWidget_MapContainer_C::CloseMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.CloseMap");

	UWidget_MapContainer_C_CloseMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.OnEscapePressed
// ()

void UWidget_MapContainer_C::OnEscapePressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.OnEscapePressed");

	UWidget_MapContainer_C_OnEscapePressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.Destruct
// ()

void UWidget_MapContainer_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.Destruct");

	UWidget_MapContainer_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_MapContainer_C_BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.SetInputMode
// ()

void UWidget_MapContainer_C::SetInputMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.SetInputMode");

	UWidget_MapContainer_C_SetInputMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapContainer.Widget_MapContainer_C.ExecuteUbergraph_Widget_MapContainer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapContainer_C::ExecuteUbergraph_Widget_MapContainer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapContainer.Widget_MapContainer_C.ExecuteUbergraph_Widget_MapContainer");

	UWidget_MapContainer_C_ExecuteUbergraph_Widget_MapContainer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
