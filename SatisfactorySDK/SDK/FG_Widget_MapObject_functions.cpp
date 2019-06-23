// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapObject_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_MapObject.Widget_MapObject_C.mShowActorDetails
// ()

void UWidget_MapObject_C::mShowActorDetails()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.mShowActorDetails");

	UWidget_MapObject_C_mShowActorDetails_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapObject_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.Tick");

	UWidget_MapObject_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.OnObjectFiltered
// ()
// Parameters:
// bool*                          FilteredIn                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapObject_C::OnObjectFiltered(bool* FilteredIn)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.OnObjectFiltered");

	UWidget_MapObject_C_OnObjectFiltered_Params params;
	params.FilteredIn = FilteredIn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.OnObjectMoved
// ()
// Parameters:
// struct FVector2D*              normalizedLocation             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapObject_C::OnObjectMoved(struct FVector2D* normalizedLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.OnObjectMoved");

	UWidget_MapObject_C_OnObjectMoved_Params params;
	params.normalizedLocation = normalizedLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.OnActorRepresentationUpdated
// ()

void UWidget_MapObject_C::OnActorRepresentationUpdated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.OnActorRepresentationUpdated");

	UWidget_MapObject_C_OnActorRepresentationUpdated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.Construct
// ()

void UWidget_MapObject_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.Construct");

	UWidget_MapObject_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.DestructionTimer
// ()
// Parameters:
// float                          Time                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapObject_C::DestructionTimer(float Time)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.DestructionTimer");

	UWidget_MapObject_C_DestructionTimer_Params params;
	params.Time = Time;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_0_OnUnhovered__DelegateSignature
// ()

void UWidget_MapObject_C::BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_0_OnUnhovered__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_0_OnUnhovered__DelegateSignature");

	UWidget_MapObject_C_BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_0_OnUnhovered__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_1_OnHovered__DelegateSignature
// ()

void UWidget_MapObject_C::BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_1_OnHovered__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_1_OnHovered__DelegateSignature");

	UWidget_MapObject_C_BndEvt__Widget_MapCompass_Icon_K2Node_ComponentBoundEvent_1_OnHovered__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.ShowActorDetailsEvent
// ()

void UWidget_MapObject_C::ShowActorDetailsEvent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.ShowActorDetailsEvent");

	UWidget_MapObject_C_ShowActorDetailsEvent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.ExecuteUbergraph_Widget_MapObject
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_MapObject_C::ExecuteUbergraph_Widget_MapObject(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.ExecuteUbergraph_Widget_MapObject");

	UWidget_MapObject_C_ExecuteUbergraph_Widget_MapObject_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.OnUnhovered__DelegateSignature
// ()
// Parameters:
// class UWidget_MapObject_C*     MapObject                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapObject_C::OnUnhovered__DelegateSignature(class UWidget_MapObject_C* MapObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.OnUnhovered__DelegateSignature");

	UWidget_MapObject_C_OnUnhovered__DelegateSignature_Params params;
	params.MapObject = MapObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_MapObject.Widget_MapObject_C.OnHovered__DelegateSignature
// ()
// Parameters:
// class UWidget_MapObject_C*     MapObject                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_MapObject_C::OnHovered__DelegateSignature(class UWidget_MapObject_C* MapObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_MapObject.Widget_MapObject_C.OnHovered__DelegateSignature");

	UWidget_MapObject_C_OnHovered__DelegateSignature_Params params;
	params.MapObject = MapObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
