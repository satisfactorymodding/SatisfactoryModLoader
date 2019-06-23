// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_DropPod_Door_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetHasBeenOpened
// ()
// Parameters:
// bool                           HasBeenOpened                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DropPod_Door_C::SetHasBeenOpened(bool HasBeenOpened)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetHasBeenOpened");

	UWidget_DropPod_Door_C_SetHasBeenOpened_Params params;
	params.HasBeenOpened = HasBeenOpened;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetLEDVisibility
// ()

void UWidget_DropPod_Door_C::SetLEDVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetLEDVisibility");

	UWidget_DropPod_Door_C_SetLEDVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetHandleAngle
// ()
// Parameters:
// float                          Angle                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DropPod_Door_C::SetHandleAngle(float Angle)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.SetHandleAngle");

	UWidget_DropPod_Door_C_SetHandleAngle_Params params;
	params.Angle = Angle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.Construct
// ()

void UWidget_DropPod_Door_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.Construct");

	UWidget_DropPod_Door_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DropPod_Door_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.Tick");

	UWidget_DropPod_Door_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          Value                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DropPod_Door_C::BndEvt__Slider_0_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature(float Value)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature");

	UWidget_DropPod_Door_C_BndEvt__Slider_0_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature_Params params;
	params.Value = Value;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__HandleSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature
// ()

void UWidget_DropPod_Door_C::BndEvt__HandleSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__HandleSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature");

	UWidget_DropPod_Door_C_BndEvt__HandleSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__HandleSlider_K2Node_ComponentBoundEvent_2_OnControllerCaptureEndEvent__DelegateSignature
// ()

void UWidget_DropPod_Door_C::BndEvt__HandleSlider_K2Node_ComponentBoundEvent_2_OnControllerCaptureEndEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.BndEvt__HandleSlider_K2Node_ComponentBoundEvent_2_OnControllerCaptureEndEvent__DelegateSignature");

	UWidget_DropPod_Door_C_BndEvt__HandleSlider_K2Node_ComponentBoundEvent_2_OnControllerCaptureEndEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.OnDoorOpen_Event
// ()

void UWidget_DropPod_Door_C::OnDoorOpen_Event()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.OnDoorOpen_Event");

	UWidget_DropPod_Door_C_OnDoorOpen_Event_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.Destruct
// ()

void UWidget_DropPod_Door_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.Destruct");

	UWidget_DropPod_Door_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.ExecuteUbergraph_Widget_DropPod_Door
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_DropPod_Door_C::ExecuteUbergraph_Widget_DropPod_Door(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.ExecuteUbergraph_Widget_DropPod_Door");

	UWidget_DropPod_Door_C_ExecuteUbergraph_Widget_DropPod_Door_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_DropPod_Door.Widget_DropPod_Door_C.OnDoorOpen__DelegateSignature
// ()

void UWidget_DropPod_Door_C::OnDoorOpen__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_DropPod_Door.Widget_DropPod_Door_C.OnDoorOpen__DelegateSignature");

	UWidget_DropPod_Door_C_OnDoorOpen__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
