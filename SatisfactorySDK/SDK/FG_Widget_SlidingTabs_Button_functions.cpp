// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SlidingTabs_Button_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetBackgroundVisibility
// ()
// Parameters:
// bool                           Visible                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::SetBackgroundVisibility(bool Visible)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetBackgroundVisibility");

	UWidget_SlidingTabs_Button_C_SetBackgroundVisibility_Params params;
	params.Visible = Visible;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetIcon
// ()
// Parameters:
// class UTexture*                Texture                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::SetIcon(class UTexture* Texture)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetIcon");

	UWidget_SlidingTabs_Button_C_SetIcon_Params params;
	params.Texture = Texture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetTitle
// ()
// Parameters:
// struct FText                   mTitle                         (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SlidingTabs_Button_C::SetTitle(const struct FText& mTitle)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetTitle");

	UWidget_SlidingTabs_Button_C_SetTitle_Params params;
	params.mTitle = mTitle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetActive
// ()
// Parameters:
// bool                           IsActive                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::SetActive(bool IsActive)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.SetActive");

	UWidget_SlidingTabs_Button_C_SetActive_Params params;
	params.IsActive = IsActive;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
// ()

void UWidget_SlidingTabs_Button_C::BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature");

	UWidget_SlidingTabs_Button_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.Construct
// ()

void UWidget_SlidingTabs_Button_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.Construct");

	UWidget_SlidingTabs_Button_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.PreConstruct");

	UWidget_SlidingTabs_Button_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SlidingTabs_Button_C::BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature");

	UWidget_SlidingTabs_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
// ()

void UWidget_SlidingTabs_Button_C::BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature");

	UWidget_SlidingTabs_Button_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.StartAutoScroll
// ()

void UWidget_SlidingTabs_Button_C::StartAutoScroll()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.StartAutoScroll");

	UWidget_SlidingTabs_Button_C_StartAutoScroll_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.ExecuteUbergraph_Widget_SlidingTabs_Button
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::ExecuteUbergraph_Widget_SlidingTabs_Button(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.ExecuteUbergraph_Widget_SlidingTabs_Button");

	UWidget_SlidingTabs_Button_C_ExecuteUbergraph_Widget_SlidingTabs_Button_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnUnhovered__DelegateSignature
// ()
// Parameters:
// class UWidget_SlidingTabs_Button_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::OnUnhovered__DelegateSignature(class UWidget_SlidingTabs_Button_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnUnhovered__DelegateSignature");

	UWidget_SlidingTabs_Button_C_OnUnhovered__DelegateSignature_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnHovered__DelegateSignature
// ()
// Parameters:
// class UWidget_SlidingTabs_Button_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::OnHovered__DelegateSignature(class UWidget_SlidingTabs_Button_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnHovered__DelegateSignature");

	UWidget_SlidingTabs_Button_C_OnHovered__DelegateSignature_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_SlidingTabs_Button_C* Instigator                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SlidingTabs_Button_C::OnClicked__DelegateSignature(class UWidget_SlidingTabs_Button_C* Instigator)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SlidingTabs_Button.Widget_SlidingTabs_Button_C.OnClicked__DelegateSignature");

	UWidget_SlidingTabs_Button_C_OnClicked__DelegateSignature_Params params;
	params.Instigator = Instigator;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
