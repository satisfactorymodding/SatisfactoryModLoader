// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Beacon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Beacon.Widget_Beacon_C.SetBeaconColor
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Beacon_C::SetBeaconColor(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.SetBeaconColor");

	UWidget_Beacon_C_SetBeaconColor_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.SetBeaconText
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_Beacon_C::SetBeaconText(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.SetBeaconText");

	UWidget_Beacon_C_SetBeaconText_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.SetBeaconTexture
// ()
// Parameters:
// class UTexture2D*              Texture                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Beacon_C::SetBeaconTexture(class UTexture2D* Texture)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.SetBeaconTexture");

	UWidget_Beacon_C_SetBeaconTexture_Params params;
	params.Texture = Texture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.Construct
// ()

void UWidget_Beacon_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.Construct");

	UWidget_Beacon_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.BndEvt__mColorButton_K2Node_ComponentBoundEvent_115_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_Beacon_C::BndEvt__mColorButton_K2Node_ComponentBoundEvent_115_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.BndEvt__mColorButton_K2Node_ComponentBoundEvent_115_OnButtonClickedEvent__DelegateSignature");

	UWidget_Beacon_C_BndEvt__mColorButton_K2Node_ComponentBoundEvent_115_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.OnColorPicked
// ()
// Parameters:
// struct FLinearColor            Color                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Beacon_C::OnColorPicked(const struct FLinearColor& Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.OnColorPicked");

	UWidget_Beacon_C_OnColorPicked_Params params;
	params.Color = Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature
// ()

void UWidget_Beacon_C::BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature");

	UWidget_Beacon_C_BndEvt__Widget_Window_K2Node_ComponentBoundEvent_0_OnClose__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.OnPickup
// ()

void UWidget_Beacon_C::OnPickup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.OnPickup");

	UWidget_Beacon_C_OnPickup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.BndEvt__mTowerName_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Beacon_C::BndEvt__mTowerName_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.BndEvt__mTowerName_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature");

	UWidget_Beacon_C_BndEvt__mTowerName_K2Node_ComponentBoundEvent_1_OnEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.UpdateColor
// ()
// Parameters:
// struct FLinearColor            New_Color                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Beacon_C::UpdateColor(const struct FLinearColor& New_Color)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.UpdateColor");

	UWidget_Beacon_C_UpdateColor_Params params;
	params.New_Color = New_Color;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Beacon.Widget_Beacon_C.ExecuteUbergraph_Widget_Beacon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Beacon_C::ExecuteUbergraph_Widget_Beacon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Beacon.Widget_Beacon_C.ExecuteUbergraph_Widget_Beacon");

	UWidget_Beacon_C_ExecuteUbergraph_Widget_Beacon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
