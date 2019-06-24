// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Equipment_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.SetEquipmentSlotText
// ()

void UWidget_HUDBox_Equipment_C::SetEquipmentSlotText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.SetEquipmentSlotText");

	UWidget_HUDBox_Equipment_C_SetEquipmentSlotText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentSlotVisibility
// ()

void UWidget_HUDBox_Equipment_C::GetEquipmentSlotVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentSlotVisibility");

	UWidget_HUDBox_Equipment_C_GetEquipmentSlotVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.SetContentWidgetClass
// ()

void UWidget_HUDBox_Equipment_C::SetContentWidgetClass()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.SetContentWidgetClass");

	UWidget_HUDBox_Equipment_C_SetContentWidgetClass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentInSlot
// ()
// Parameters:
// class AFGEquipment*            equipment                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Equipment_C::GetEquipmentInSlot(class AFGEquipment** equipment)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentInSlot");

	UWidget_HUDBox_Equipment_C_GetEquipmentInSlot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (equipment != nullptr)
		*equipment = params.equipment;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.UpdateTitle
// ()

void UWidget_HUDBox_Equipment_C::UpdateTitle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.UpdateTitle");

	UWidget_HUDBox_Equipment_C_UpdateTitle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.UpdateIcon
// ()

void UWidget_HUDBox_Equipment_C::UpdateIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.UpdateIcon");

	UWidget_HUDBox_Equipment_C_UpdateIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentItemClass
// ()
// Parameters:
// class UClass*                  Class                          (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Equipment_C::GetEquipmentItemClass(class UClass** Class)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentItemClass");

	UWidget_HUDBox_Equipment_C_GetEquipmentItemClass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Class != nullptr)
		*Class = params.Class;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Construct
// ()

void UWidget_HUDBox_Equipment_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Construct");

	UWidget_HUDBox_Equipment_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Equipment_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Tick");

	UWidget_HUDBox_Equipment_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.HideWidget
// ()

void UWidget_HUDBox_Equipment_C::HideWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.HideWidget");

	UWidget_HUDBox_Equipment_C_HideWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Destruct
// ()

void UWidget_HUDBox_Equipment_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Destruct");

	UWidget_HUDBox_Equipment_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.ExecuteUbergraph_Widget_HUDBox_Equipment
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_HUDBox_Equipment_C::ExecuteUbergraph_Widget_HUDBox_Equipment(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.ExecuteUbergraph_Widget_HUDBox_Equipment");

	UWidget_HUDBox_Equipment_C_ExecuteUbergraph_Widget_HUDBox_Equipment_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
