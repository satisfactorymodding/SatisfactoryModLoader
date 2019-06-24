// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RecipeButton_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_RecipeButton.Widget_RecipeButton_C.ClearButtonSelection
// ()

void UWidget_RecipeButton_C::ClearButtonSelection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.ClearButtonSelection");

	UWidget_RecipeButton_C_ClearButtonSelection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetCustomTooltip
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_RecipeButton_C::GetCustomTooltip()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetCustomTooltip");

	UWidget_RecipeButton_C_GetCustomTooltip_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetRightClickMenuVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_RecipeButton_C::GetRightClickMenuVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetRightClickMenuVisibility");

	UWidget_RecipeButton_C_GetRightClickMenuVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.CreateRightClickMenu
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget_RecipeButton_C::CreateRightClickMenu()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.CreateRightClickMenu");

	UWidget_RecipeButton_C_CreateRightClickMenu_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetButtonHoverColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_RecipeButton_C::GetButtonHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetButtonHoverColor");

	UWidget_RecipeButton_C_GetButtonHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetTextHoverColor
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_RecipeButton_C::GetTextHoverColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetTextHoverColor");

	UWidget_RecipeButton_C_GetTextHoverColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.IsButtonEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget_RecipeButton_C::IsButtonEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.IsButtonEnabled");

	UWidget_RecipeButton_C_IsButtonEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduce
// ()
// Parameters:
// int                            Result                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_RecipeButton_C::GetNumCanProduce(int* Result)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduce");

	UWidget_RecipeButton_C_GetNumCanProduce_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Result != nullptr)
		*Result = params.Result;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduceVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_RecipeButton_C::GetNumCanProduceVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduceVisibility");

	UWidget_RecipeButton_C_GetNumCanProduceVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduceText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_RecipeButton_C::GetNumCanProduceText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetNumCanProduceText");

	UWidget_RecipeButton_C_GetNumCanProduceText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.CheckIngredients
// ()

void UWidget_RecipeButton_C::CheckIngredients()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.CheckIngredients");

	UWidget_RecipeButton_C_CheckIngredients_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetRecipeIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_RecipeButton_C::GetRecipeIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetRecipeIcon");

	UWidget_RecipeButton_C_GetRecipeIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetIconColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget_RecipeButton_C::GetIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetIconColor");

	UWidget_RecipeButton_C_GetIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.OnMouseButtonDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_RecipeButton_C::OnMouseButtonDown(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.OnMouseButtonDown");

	UWidget_RecipeButton_C_OnMouseButtonDown_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.GetRecipeDisplayName
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_RecipeButton_C::GetRecipeDisplayName()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.GetRecipeDisplayName");

	UWidget_RecipeButton_C_GetRecipeDisplayName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.Construct
// ()

void UWidget_RecipeButton_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.Construct");

	UWidget_RecipeButton_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RecipeButton_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.Tick");

	UWidget_RecipeButton_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.OnClicked
// ()

void UWidget_RecipeButton_C::OnClicked()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.OnClicked");

	UWidget_RecipeButton_C_OnClicked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.OnHovered
// ()

void UWidget_RecipeButton_C::OnHovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.OnHovered");

	UWidget_RecipeButton_C_OnHovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.OnPressed
// ()

void UWidget_RecipeButton_C::OnPressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.OnPressed");

	UWidget_RecipeButton_C_OnPressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.OnMouseLeave
// ()
// Parameters:
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_RecipeButton_C::OnMouseLeave(struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.OnMouseLeave");

	UWidget_RecipeButton_C_OnMouseLeave_Params params;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.UpdateWindowWidgetOffset_Event
// ()

void UWidget_RecipeButton_C::UpdateWindowWidgetOffset_Event()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.UpdateWindowWidgetOffset_Event");

	UWidget_RecipeButton_C_UpdateWindowWidgetOffset_Event_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_ListButton_C*    ListButton                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_RecipeButton_C::BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature(int Index, class UWidget_ListButton_C* ListButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature");

	UWidget_RecipeButton_C_BndEvt__Widget_ListButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params params;
	params.Index = Index;
	params.ListButton = ListButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.ExecuteUbergraph_Widget_RecipeButton
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_RecipeButton_C::ExecuteUbergraph_Widget_RecipeButton(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.ExecuteUbergraph_Widget_RecipeButton");

	UWidget_RecipeButton_C_ExecuteUbergraph_Widget_RecipeButton_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.OnRecipeButtonClicked__DelegateSignature
// ()
// Parameters:
// class UWidget_RecipeButton_C*  ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_RecipeButton_C::OnRecipeButtonClicked__DelegateSignature(class UWidget_RecipeButton_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.OnRecipeButtonClicked__DelegateSignature");

	UWidget_RecipeButton_C_OnRecipeButtonClicked__DelegateSignature_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_RecipeButton.Widget_RecipeButton_C.UpdateWindowWidgetOffset__DelegateSignature
// ()

void UWidget_RecipeButton_C::UpdateWindowWidgetOffset__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_RecipeButton.Widget_RecipeButton_C.UpdateWindowWidgetOffset__DelegateSignature");

	UWidget_RecipeButton_C_UpdateWindowWidgetOffset__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
