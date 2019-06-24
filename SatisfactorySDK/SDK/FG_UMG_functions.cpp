// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_UMG_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function UMG.Widget.SetVisibility
// ()
// Parameters:
// ESlateVisibility               InVisibility                   (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetVisibility(ESlateVisibility InVisibility)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetVisibility");

	UWidget_SetVisibility_Params params;
	params.InVisibility = InVisibility;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetUserFocus
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetUserFocus(class APlayerController* PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetUserFocus");

	UWidget_SetUserFocus_Params params;
	params.PlayerController = PlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetToolTipText
// ()
// Parameters:
// struct FText                   InToolTipText                  (ConstParm, Parm, OutParm, ReferenceParm)

void UWidget::SetToolTipText(const struct FText& InToolTipText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetToolTipText");

	UWidget_SetToolTipText_Params params;
	params.InToolTipText = InToolTipText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetToolTip
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget::SetToolTip(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetToolTip");

	UWidget_SetToolTip_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderTranslation
// ()
// Parameters:
// struct FVector2D               Translation                    (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetRenderTranslation(const struct FVector2D& Translation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderTranslation");

	UWidget_SetRenderTranslation_Params params;
	params.Translation = Translation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderTransformPivot
// ()
// Parameters:
// struct FVector2D               Pivot                          (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetRenderTransformPivot(const struct FVector2D& Pivot)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderTransformPivot");

	UWidget_SetRenderTransformPivot_Params params;
	params.Pivot = Pivot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderTransform
// ()
// Parameters:
// struct FWidgetTransform        InTransform                    (Parm)

void UWidget::SetRenderTransform(const struct FWidgetTransform& InTransform)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderTransform");

	UWidget_SetRenderTransform_Params params;
	params.InTransform = InTransform;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderShear
// ()
// Parameters:
// struct FVector2D               Shear                          (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetRenderShear(const struct FVector2D& Shear)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderShear");

	UWidget_SetRenderShear_Params params;
	params.Shear = Shear;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderScale
// ()
// Parameters:
// struct FVector2D               Scale                          (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetRenderScale(const struct FVector2D& Scale)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderScale");

	UWidget_SetRenderScale_Params params;
	params.Scale = Scale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderOpacity
// ()
// Parameters:
// float                          InOpacity                      (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetRenderOpacity(float InOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderOpacity");

	UWidget_SetRenderOpacity_Params params;
	params.InOpacity = InOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetRenderAngle
// ()
// Parameters:
// float                          Angle                          (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetRenderAngle(float Angle)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetRenderAngle");

	UWidget_SetRenderAngle_Params params;
	params.Angle = Angle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetNavigationRule
// ()
// Parameters:
// EUINavigation                  Direction                      (Parm, ZeroConstructor, IsPlainOldData)
// EUINavigationRule              Rule                           (Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   WidgetToFocus                  (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetNavigationRule(EUINavigation Direction, EUINavigationRule Rule, const struct FName& WidgetToFocus)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetNavigationRule");

	UWidget_SetNavigationRule_Params params;
	params.Direction = Direction;
	params.Rule = Rule;
	params.WidgetToFocus = WidgetToFocus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetKeyboardFocus
// ()

void UWidget::SetKeyboardFocus()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetKeyboardFocus");

	UWidget_SetKeyboardFocus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetIsEnabled
// ()
// Parameters:
// bool                           bInIsEnabled                   (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetIsEnabled(bool bInIsEnabled)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetIsEnabled");

	UWidget_SetIsEnabled_Params params;
	params.bInIsEnabled = bInIsEnabled;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetCursor
// ()
// Parameters:
// TEnumAsByte<EMouseCursor>      InCursor                       (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetCursor(TEnumAsByte<EMouseCursor> InCursor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetCursor");

	UWidget_SetCursor_Params params;
	params.InCursor = InCursor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetClipping
// ()
// Parameters:
// EWidgetClipping                InClipping                     (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetClipping(EWidgetClipping InClipping)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetClipping");

	UWidget_SetClipping_Params params;
	params.InClipping = InClipping;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.SetAllNavigationRules
// ()
// Parameters:
// EUINavigationRule              Rule                           (Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   WidgetToFocus                  (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::SetAllNavigationRules(EUINavigationRule Rule, const struct FName& WidgetToFocus)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.SetAllNavigationRules");

	UWidget_SetAllNavigationRules_Params params;
	params.Rule = Rule;
	params.WidgetToFocus = WidgetToFocus;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.ResetCursor
// ()

void UWidget::ResetCursor()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.ResetCursor");

	UWidget_ResetCursor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.RemoveFromParent
// ()

void UWidget::RemoveFromParent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.RemoveFromParent");

	UWidget_RemoveFromParent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.Widget.OnReply__DelegateSignature
// ()
// Parameters:
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget::OnReply__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.OnReply__DelegateSignature");

	UWidget_OnReply__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.OnPointerEvent__DelegateSignature
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget::OnPointerEvent__DelegateSignature(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.OnPointerEvent__DelegateSignature");

	UWidget_OnPointerEvent__DelegateSignature_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.IsVisible
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::IsVisible()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.IsVisible");

	UWidget_IsVisible_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.IsHovered
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::IsHovered()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.IsHovered");

	UWidget_IsHovered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.InvalidateLayoutAndVolatility
// ()

void UWidget::InvalidateLayoutAndVolatility()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.InvalidateLayoutAndVolatility");

	UWidget_InvalidateLayoutAndVolatility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.HasUserFocusedDescendants
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasUserFocusedDescendants(class APlayerController* PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasUserFocusedDescendants");

	UWidget_HasUserFocusedDescendants_Params params;
	params.PlayerController = PlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.HasUserFocus
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasUserFocus(class APlayerController* PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasUserFocus");

	UWidget_HasUserFocus_Params params;
	params.PlayerController = PlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.HasMouseCaptureByUser
// ()
// Parameters:
// int                            UserIndex                      (Parm, ZeroConstructor, IsPlainOldData)
// int                            PointerIndex                   (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasMouseCaptureByUser(int UserIndex, int PointerIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasMouseCaptureByUser");

	UWidget_HasMouseCaptureByUser_Params params;
	params.UserIndex = UserIndex;
	params.PointerIndex = PointerIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.HasMouseCapture
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasMouseCapture()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasMouseCapture");

	UWidget_HasMouseCapture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.HasKeyboardFocus
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasKeyboardFocus()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasKeyboardFocus");

	UWidget_HasKeyboardFocus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.HasFocusedDescendants
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasFocusedDescendants()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasFocusedDescendants");

	UWidget_HasFocusedDescendants_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.HasAnyUserFocus
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::HasAnyUserFocus()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.HasAnyUserFocus");

	UWidget_HasAnyUserFocus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetWidget__DelegateSignature
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget::GetWidget__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetWidget__DelegateSignature");

	UWidget_GetWidget__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget::GetVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetVisibility");

	UWidget_GetVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetText__DelegateSignature
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget::GetText__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetText__DelegateSignature");

	UWidget_GetText__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetSlateVisibility__DelegateSignature
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget::GetSlateVisibility__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetSlateVisibility__DelegateSignature");

	UWidget_GetSlateVisibility__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetSlateColor__DelegateSignature
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget::GetSlateColor__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetSlateColor__DelegateSignature");

	UWidget_GetSlateColor__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetSlateBrush__DelegateSignature
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget::GetSlateBrush__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetSlateBrush__DelegateSignature");

	UWidget_GetSlateBrush__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetRenderOpacity
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget::GetRenderOpacity()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetRenderOpacity");

	UWidget_GetRenderOpacity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetParent
// ()
// Parameters:
// class UPanelWidget*            ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UPanelWidget* UWidget::GetParent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetParent");

	UWidget_GetParent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetOwningPlayer
// ()
// Parameters:
// class APlayerController*       ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class APlayerController* UWidget::GetOwningPlayer()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetOwningPlayer");

	UWidget_GetOwningPlayer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetOwningLocalPlayer
// ()
// Parameters:
// class ULocalPlayer*            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class ULocalPlayer* UWidget::GetOwningLocalPlayer()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetOwningLocalPlayer");

	UWidget_GetOwningLocalPlayer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetMouseCursor__DelegateSignature
// ()
// Parameters:
// TEnumAsByte<EMouseCursor>      ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

TEnumAsByte<EMouseCursor> UWidget::GetMouseCursor__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetMouseCursor__DelegateSignature");

	UWidget_GetMouseCursor__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetLinearColor__DelegateSignature
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UWidget::GetLinearColor__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetLinearColor__DelegateSignature");

	UWidget_GetLinearColor__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetIsEnabled
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::GetIsEnabled()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetIsEnabled");

	UWidget_GetIsEnabled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetInt32__DelegateSignature
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidget::GetInt32__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetInt32__DelegateSignature");

	UWidget_GetInt32__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetFloat__DelegateSignature
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget::GetFloat__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetFloat__DelegateSignature");

	UWidget_GetFloat__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetDesiredSize
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UWidget::GetDesiredSize()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetDesiredSize");

	UWidget_GetDesiredSize_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetClipping
// ()
// Parameters:
// EWidgetClipping                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EWidgetClipping UWidget::GetClipping()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetClipping");

	UWidget_GetClipping_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetCheckBoxState__DelegateSignature
// ()
// Parameters:
// ECheckBoxState                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ECheckBoxState UWidget::GetCheckBoxState__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetCheckBoxState__DelegateSignature");

	UWidget_GetCheckBoxState__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.GetCachedGeometry
// ()
// Parameters:
// struct FGeometry               ReturnValue                    (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm, IsPlainOldData)

struct FGeometry UWidget::GetCachedGeometry()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.GetCachedGeometry");

	UWidget_GetCachedGeometry_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GetBool__DelegateSignature
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidget::GetBool__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GetBool__DelegateSignature");

	UWidget_GetBool__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GenerateWidgetForString__DelegateSignature
// ()
// Parameters:
// class FString                  Item                           (Parm, ZeroConstructor)
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget::GenerateWidgetForString__DelegateSignature(const class FString& Item)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GenerateWidgetForString__DelegateSignature");

	UWidget_GenerateWidgetForString__DelegateSignature_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// DelegateFunction UMG.Widget.GenerateWidgetForObject__DelegateSignature
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidget::GenerateWidgetForObject__DelegateSignature(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.Widget.GenerateWidgetForObject__DelegateSignature");

	UWidget_GenerateWidgetForObject__DelegateSignature_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Widget.ForceVolatile
// ()
// Parameters:
// bool                           bForce                         (Parm, ZeroConstructor, IsPlainOldData)

void UWidget::ForceVolatile(bool bForce)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.ForceVolatile");

	UWidget_ForceVolatile_Params params;
	params.bForce = bForce;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Widget.ForceLayoutPrepass
// ()

void UWidget::ForceLayoutPrepass()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Widget.ForceLayoutPrepass");

	UWidget_ForceLayoutPrepass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.PanelWidget.RemoveChildAt
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UPanelWidget::RemoveChildAt(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.RemoveChildAt");

	UPanelWidget_RemoveChildAt_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.RemoveChild
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UPanelWidget::RemoveChild(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.RemoveChild");

	UPanelWidget_RemoveChild_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.HasChild
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UPanelWidget::HasChild(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.HasChild");

	UPanelWidget_HasChild_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.HasAnyChildren
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UPanelWidget::HasAnyChildren()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.HasAnyChildren");

	UPanelWidget_HasAnyChildren_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.GetChildrenCount
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UPanelWidget::GetChildrenCount()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.GetChildrenCount");

	UPanelWidget_GetChildrenCount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.GetChildIndex
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UPanelWidget::GetChildIndex(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.GetChildIndex");

	UPanelWidget_GetChildIndex_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.GetChildAt
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UPanelWidget::GetChildAt(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.GetChildAt");

	UPanelWidget_GetChildAt_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.PanelWidget.ClearChildren
// ()

void UPanelWidget::ClearChildren()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.ClearChildren");

	UPanelWidget_ClearChildren_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.PanelWidget.AddChild
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UPanelSlot*              ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UPanelSlot* UPanelWidget::AddChild(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.PanelWidget.AddChild");

	UPanelWidget_AddChild_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ContentWidget.SetContent
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UPanelSlot*              ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UPanelSlot* UContentWidget::SetContent(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ContentWidget.SetContent");

	UContentWidget_SetContent_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ContentWidget.GetContentSlot
// ()
// Parameters:
// class UPanelSlot*              ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UPanelSlot* UContentWidget::GetContentSlot()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ContentWidget.GetContentSlot");

	UContentWidget_GetContentSlot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ContentWidget.GetContent
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UContentWidget::GetContent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ContentWidget.GetContent");

	UContentWidget_GetContent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.UnregisterInputComponent
// ()

void UUserWidget::UnregisterInputComponent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.UnregisterInputComponent");

	UUserWidget_UnregisterInputComponent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.Tick
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// float                          InDeltaTime                    (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::Tick(const struct FGeometry& MyGeometry, float InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.Tick");

	UUserWidget_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.StopListeningForInputAction
// ()
// Parameters:
// struct FName                   ActionName                     (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<EInputEvent>       EventType                      (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::StopListeningForInputAction(const struct FName& ActionName, TEnumAsByte<EInputEvent> EventType)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopListeningForInputAction");

	UUserWidget_StopListeningForInputAction_Params params;
	params.ActionName = ActionName;
	params.EventType = EventType;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.StopListeningForAllInputActions
// ()

void UUserWidget::StopListeningForAllInputActions()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopListeningForAllInputActions");

	UUserWidget_StopListeningForAllInputActions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.StopAnimationsAndLatentActions
// ()

void UUserWidget::StopAnimationsAndLatentActions()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopAnimationsAndLatentActions");

	UUserWidget_StopAnimationsAndLatentActions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.StopAnimation
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UUserWidget::StopAnimation(class UWidgetAnimation* InAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopAnimation");

	UUserWidget_StopAnimation_Params params;
	params.InAnimation = InAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.StopAllAnimations
// ()

void UUserWidget::StopAllAnimations()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.StopAllAnimations");

	UUserWidget_StopAllAnimations_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetPositionInViewport
// ()
// Parameters:
// struct FVector2D               Position                       (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bRemoveDPIScale                (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetPositionInViewport(const struct FVector2D& Position, bool bRemoveDPIScale)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetPositionInViewport");

	UUserWidget_SetPositionInViewport_Params params;
	params.Position = Position;
	params.bRemoveDPIScale = bRemoveDPIScale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetPlaybackSpeed
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// float                          PlaybackSpeed                  (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetPlaybackSpeed(class UWidgetAnimation* InAnimation, float PlaybackSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetPlaybackSpeed");

	UUserWidget_SetPlaybackSpeed_Params params;
	params.InAnimation = InAnimation;
	params.PlaybackSpeed = PlaybackSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetPadding");

	UUserWidget_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetOwningPlayer
// ()
// Parameters:
// class APlayerController*       LocalPlayerController          (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetOwningPlayer(class APlayerController* LocalPlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetOwningPlayer");

	UUserWidget_SetOwningPlayer_Params params;
	params.LocalPlayerController = LocalPlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetNumLoopsToPlay
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            NumLoopsToPlay                 (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetNumLoopsToPlay(class UWidgetAnimation* InAnimation, int NumLoopsToPlay)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetNumLoopsToPlay");

	UUserWidget_SetNumLoopsToPlay_Params params;
	params.InAnimation = InAnimation;
	params.NumLoopsToPlay = NumLoopsToPlay;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetInputActionPriority
// ()
// Parameters:
// int                            NewPriority                    (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetInputActionPriority(int NewPriority)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetInputActionPriority");

	UUserWidget_SetInputActionPriority_Params params;
	params.NewPriority = NewPriority;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetInputActionBlocking
// ()
// Parameters:
// bool                           bShouldBlock                   (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetInputActionBlocking(bool bShouldBlock)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetInputActionBlocking");

	UUserWidget_SetInputActionBlocking_Params params;
	params.bShouldBlock = bShouldBlock;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetForegroundColor
// ()
// Parameters:
// struct FSlateColor             InForegroundColor              (Parm)

void UUserWidget::SetForegroundColor(const struct FSlateColor& InForegroundColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetForegroundColor");

	UUserWidget_SetForegroundColor_Params params;
	params.InForegroundColor = InForegroundColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetDesiredSizeInViewport
// ()
// Parameters:
// struct FVector2D               Size                           (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetDesiredSizeInViewport(const struct FVector2D& Size)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetDesiredSizeInViewport");

	UUserWidget_SetDesiredSizeInViewport_Params params;
	params.Size = Size;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            InColorAndOpacity              (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetColorAndOpacity(const struct FLinearColor& InColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetColorAndOpacity");

	UUserWidget_SetColorAndOpacity_Params params;
	params.InColorAndOpacity = InColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetAnchorsInViewport
// ()
// Parameters:
// struct FAnchors                Anchors                        (Parm)

void UUserWidget::SetAnchorsInViewport(const struct FAnchors& Anchors)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetAnchorsInViewport");

	UUserWidget_SetAnchorsInViewport_Params params;
	params.Anchors = Anchors;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.SetAlignmentInViewport
// ()
// Parameters:
// struct FVector2D               Alignment                      (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::SetAlignmentInViewport(const struct FVector2D& Alignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.SetAlignmentInViewport");

	UUserWidget_SetAlignmentInViewport_Params params;
	params.Alignment = Alignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.ReverseAnimation
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UUserWidget::ReverseAnimation(class UWidgetAnimation* InAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.ReverseAnimation");

	UUserWidget_ReverseAnimation_Params params;
	params.InAnimation = InAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.RemoveFromViewport
// ()

void UUserWidget::RemoveFromViewport()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.RemoveFromViewport");

	UUserWidget_RemoveFromViewport_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.RegisterInputComponent
// ()

void UUserWidget::RegisterInputComponent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.RegisterInputComponent");

	UUserWidget_RegisterInputComponent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.PreConstruct
// ()
// Parameters:
// bool                           IsDesignTime                   (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::PreConstruct(bool IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PreConstruct");

	UUserWidget_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.PlaySound
// ()
// Parameters:
// class USoundBase*              SoundToPlay                    (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::PlaySound(class USoundBase* SoundToPlay)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PlaySound");

	UUserWidget_PlaySound_Params params;
	params.SoundToPlay = SoundToPlay;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.PlayAnimationTo
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// float                          StartAtTime                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          EndAtTime                      (Parm, ZeroConstructor, IsPlainOldData)
// int                            NumLoopsToPlay                 (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<EUMGSequencePlayMode> PlayMode                       (Parm, ZeroConstructor, IsPlainOldData)
// float                          PlaybackSpeed                  (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::PlayAnimationTo(class UWidgetAnimation* InAnimation, float StartAtTime, float EndAtTime, int NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode> PlayMode, float PlaybackSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PlayAnimationTo");

	UUserWidget_PlayAnimationTo_Params params;
	params.InAnimation = InAnimation;
	params.StartAtTime = StartAtTime;
	params.EndAtTime = EndAtTime;
	params.NumLoopsToPlay = NumLoopsToPlay;
	params.PlayMode = PlayMode;
	params.PlaybackSpeed = PlaybackSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.PlayAnimation
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// float                          StartAtTime                    (Parm, ZeroConstructor, IsPlainOldData)
// int                            NumLoopsToPlay                 (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<EUMGSequencePlayMode> PlayMode                       (Parm, ZeroConstructor, IsPlainOldData)
// float                          PlaybackSpeed                  (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::PlayAnimation(class UWidgetAnimation* InAnimation, float StartAtTime, int NumLoopsToPlay, TEnumAsByte<EUMGSequencePlayMode> PlayMode, float PlaybackSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PlayAnimation");

	UUserWidget_PlayAnimation_Params params;
	params.InAnimation = InAnimation;
	params.StartAtTime = StartAtTime;
	params.NumLoopsToPlay = NumLoopsToPlay;
	params.PlayMode = PlayMode;
	params.PlaybackSpeed = PlaybackSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.PauseAnimation
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UUserWidget::PauseAnimation(class UWidgetAnimation* InAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.PauseAnimation");

	UUserWidget_PauseAnimation_Params params;
	params.InAnimation = InAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnTouchStarted
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           InTouchEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnTouchStarted(const struct FGeometry& MyGeometry, const struct FPointerEvent& InTouchEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnTouchStarted");

	UUserWidget_OnTouchStarted_Params params;
	params.MyGeometry = MyGeometry;
	params.InTouchEvent = InTouchEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnTouchMoved
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           InTouchEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnTouchMoved(const struct FGeometry& MyGeometry, const struct FPointerEvent& InTouchEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnTouchMoved");

	UUserWidget_OnTouchMoved_Params params;
	params.MyGeometry = MyGeometry;
	params.InTouchEvent = InTouchEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnTouchGesture
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           GestureEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnTouchGesture(const struct FGeometry& MyGeometry, const struct FPointerEvent& GestureEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnTouchGesture");

	UUserWidget_OnTouchGesture_Params params;
	params.MyGeometry = MyGeometry;
	params.GestureEvent = GestureEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnTouchForceChanged
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           InTouchEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnTouchForceChanged(const struct FGeometry& MyGeometry, const struct FPointerEvent& InTouchEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnTouchForceChanged");

	UUserWidget_OnTouchForceChanged_Params params;
	params.MyGeometry = MyGeometry;
	params.InTouchEvent = InTouchEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnTouchEnded
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           InTouchEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnTouchEnded(const struct FGeometry& MyGeometry, const struct FPointerEvent& InTouchEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnTouchEnded");

	UUserWidget_OnTouchEnded_Params params;
	params.MyGeometry = MyGeometry;
	params.InTouchEvent = InTouchEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnRemovedFromFocusPath
// ()
// Parameters:
// struct FFocusEvent             InFocusEvent                   (Parm)

void UUserWidget::OnRemovedFromFocusPath(const struct FFocusEvent& InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnRemovedFromFocusPath");

	UUserWidget_OnRemovedFromFocusPath_Params params;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnPreviewMouseButtonDown
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnPreviewMouseButtonDown(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnPreviewMouseButtonDown");

	UUserWidget_OnPreviewMouseButtonDown_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnPreviewKeyDown
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FKeyEvent               InKeyEvent                     (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnPreviewKeyDown(const struct FGeometry& MyGeometry, const struct FKeyEvent& InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnPreviewKeyDown");

	UUserWidget_OnPreviewKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnPaint
// ()
// Parameters:
// struct FPaintContext           Context                        (Parm, OutParm, ReferenceParm)

void UUserWidget::OnPaint(struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnPaint");

	UUserWidget_OnPaint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function UMG.UserWidget.OnMouseWheel
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnMouseWheel(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseWheel");

	UUserWidget_OnMouseWheel_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnMouseMove
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnMouseMove(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseMove");

	UUserWidget_OnMouseMove_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnMouseLeave
// ()
// Parameters:
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)

void UUserWidget::OnMouseLeave(const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseLeave");

	UUserWidget_OnMouseLeave_Params params;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnMouseEnter
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)

void UUserWidget::OnMouseEnter(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseEnter");

	UUserWidget_OnMouseEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnMouseCaptureLost
// ()

void UUserWidget::OnMouseCaptureLost()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseCaptureLost");

	UUserWidget_OnMouseCaptureLost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnMouseButtonUp
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnMouseButtonUp(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseButtonUp");

	UUserWidget_OnMouseButtonUp_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnMouseButtonDown
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           MouseEvent                     (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnMouseButtonDown(const struct FGeometry& MyGeometry, const struct FPointerEvent& MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseButtonDown");

	UUserWidget_OnMouseButtonDown_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnMouseButtonDoubleClick
// ()
// Parameters:
// struct FGeometry               InMyGeometry                   (Parm, IsPlainOldData)
// struct FPointerEvent           InMouseEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnMouseButtonDoubleClick(const struct FGeometry& InMyGeometry, const struct FPointerEvent& InMouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMouseButtonDoubleClick");

	UUserWidget_OnMouseButtonDoubleClick_Params params;
	params.InMyGeometry = InMyGeometry;
	params.InMouseEvent = InMouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnMotionDetected
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FMotionEvent            InMotionEvent                  (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnMotionDetected(const struct FGeometry& MyGeometry, const struct FMotionEvent& InMotionEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnMotionDetected");

	UUserWidget_OnMotionDetected_Params params;
	params.MyGeometry = MyGeometry;
	params.InMotionEvent = InMotionEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnKeyUp
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FKeyEvent               InKeyEvent                     (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnKeyUp(const struct FGeometry& MyGeometry, const struct FKeyEvent& InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnKeyUp");

	UUserWidget_OnKeyUp_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnKeyDown
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FKeyEvent               InKeyEvent                     (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnKeyDown(const struct FGeometry& MyGeometry, const struct FKeyEvent& InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnKeyDown");

	UUserWidget_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnKeyChar
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FCharacterEvent         InCharacterEvent               (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnKeyChar(const struct FGeometry& MyGeometry, const struct FCharacterEvent& InCharacterEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnKeyChar");

	UUserWidget_OnKeyChar_Params params;
	params.MyGeometry = MyGeometry;
	params.InCharacterEvent = InCharacterEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnInitialized
// ()

void UUserWidget::OnInitialized()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnInitialized");

	UUserWidget_OnInitialized_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnFocusReceived
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FFocusEvent             InFocusEvent                   (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnFocusReceived(const struct FGeometry& MyGeometry, const struct FFocusEvent& InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnFocusReceived");

	UUserWidget_OnFocusReceived_Params params;
	params.MyGeometry = MyGeometry;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnFocusLost
// ()
// Parameters:
// struct FFocusEvent             InFocusEvent                   (Parm)

void UUserWidget::OnFocusLost(const struct FFocusEvent& InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnFocusLost");

	UUserWidget_OnFocusLost_Params params;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnDrop
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           PointerEvent                   (Parm)
// class UDragDropOperation*      Operation                      (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::OnDrop(const struct FGeometry& MyGeometry, const struct FPointerEvent& PointerEvent, class UDragDropOperation* Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnDrop");

	UUserWidget_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnDragOver
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           PointerEvent                   (Parm)
// class UDragDropOperation*      Operation                      (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::OnDragOver(const struct FGeometry& MyGeometry, const struct FPointerEvent& PointerEvent, class UDragDropOperation* Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnDragOver");

	UUserWidget_OnDragOver_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnDragLeave
// ()
// Parameters:
// struct FPointerEvent           PointerEvent                   (Parm)
// class UDragDropOperation*      Operation                      (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::OnDragLeave(const struct FPointerEvent& PointerEvent, class UDragDropOperation* Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnDragLeave");

	UUserWidget_OnDragLeave_Params params;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnDragEnter
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           PointerEvent                   (Parm)
// class UDragDropOperation*      Operation                      (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::OnDragEnter(const struct FGeometry& MyGeometry, const struct FPointerEvent& PointerEvent, class UDragDropOperation* Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnDragEnter");

	UUserWidget_OnDragEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnDragDetected
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FPointerEvent           PointerEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// class UDragDropOperation*      Operation                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UUserWidget::OnDragDetected(const struct FGeometry& MyGeometry, const struct FPointerEvent& PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnDragDetected");

	UUserWidget_OnDragDetected_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Operation != nullptr)
		*Operation = params.Operation;
}


// Function UMG.UserWidget.OnDragCancelled
// ()
// Parameters:
// struct FPointerEvent           PointerEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// class UDragDropOperation*      Operation                      (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::OnDragCancelled(const struct FPointerEvent& PointerEvent, class UDragDropOperation* Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnDragCancelled");

	UUserWidget_OnDragCancelled_Params params;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnAnimationStarted
// ()
// Parameters:
// class UWidgetAnimation*        Animation                      (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UUserWidget::OnAnimationStarted(class UWidgetAnimation* Animation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnAnimationStarted");

	UUserWidget_OnAnimationStarted_Params params;
	params.Animation = Animation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnAnimationFinished
// ()
// Parameters:
// class UWidgetAnimation*        Animation                      (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UUserWidget::OnAnimationFinished(class UWidgetAnimation* Animation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnAnimationFinished");

	UUserWidget_OnAnimationFinished_Params params;
	params.Animation = Animation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.OnAnalogValueChanged
// ()
// Parameters:
// struct FGeometry               MyGeometry                     (Parm, IsPlainOldData)
// struct FAnalogInputEvent       InAnalogInputEvent             (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UUserWidget::OnAnalogValueChanged(const struct FGeometry& MyGeometry, const struct FAnalogInputEvent& InAnalogInputEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnAnalogValueChanged");

	UUserWidget_OnAnalogValueChanged_Params params;
	params.MyGeometry = MyGeometry;
	params.InAnalogInputEvent = InAnalogInputEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.OnAddedToFocusPath
// ()
// Parameters:
// struct FFocusEvent             InFocusEvent                   (Parm)

void UUserWidget::OnAddedToFocusPath(const struct FFocusEvent& InFocusEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.OnAddedToFocusPath");

	UUserWidget_OnAddedToFocusPath_Params params;
	params.InFocusEvent = InFocusEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.ListenForInputAction
// ()
// Parameters:
// struct FName                   ActionName                     (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<EInputEvent>       EventType                      (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bConsume                       (Parm, ZeroConstructor, IsPlainOldData)
// struct FScriptDelegate         Callback                       (Parm, ZeroConstructor)

void UUserWidget::ListenForInputAction(const struct FName& ActionName, TEnumAsByte<EInputEvent> EventType, bool bConsume, const struct FScriptDelegate& Callback)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.ListenForInputAction");

	UUserWidget_ListenForInputAction_Params params;
	params.ActionName = ActionName;
	params.EventType = EventType;
	params.bConsume = bConsume;
	params.Callback = Callback;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.IsPlayingAnimation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsPlayingAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsPlayingAnimation");

	UUserWidget_IsPlayingAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.IsListeningForInputAction
// ()
// Parameters:
// struct FName                   ActionName                     (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsListeningForInputAction(const struct FName& ActionName)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsListeningForInputAction");

	UUserWidget_IsListeningForInputAction_Params params;
	params.ActionName = ActionName;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.IsInViewport
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsInViewport()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsInViewport");

	UUserWidget_IsInViewport_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.IsInteractable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsInteractable()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsInteractable");

	UUserWidget_IsInteractable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.IsAnyAnimationPlaying
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsAnyAnimationPlaying()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsAnyAnimationPlaying");

	UUserWidget_IsAnyAnimationPlaying_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.IsAnimationPlayingForward
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsAnimationPlayingForward(class UWidgetAnimation* InAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsAnimationPlayingForward");

	UUserWidget_IsAnimationPlayingForward_Params params;
	params.InAnimation = InAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.IsAnimationPlaying
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::IsAnimationPlaying(class UWidgetAnimation* InAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.IsAnimationPlaying");

	UUserWidget_IsAnimationPlaying_Params params;
	params.InAnimation = InAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.GetOwningPlayerPawn
// ()
// Parameters:
// class APawn*                   ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class APawn* UUserWidget::GetOwningPlayerPawn()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetOwningPlayerPawn");

	UUserWidget_GetOwningPlayerPawn_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.GetIsVisible
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::GetIsVisible()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetIsVisible");

	UUserWidget_GetIsVisible_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.GetAnimationCurrentTime
// ()
// Parameters:
// class UWidgetAnimation*        InAnimation                    (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UUserWidget::GetAnimationCurrentTime(class UWidgetAnimation* InAnimation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetAnimationCurrentTime");

	UUserWidget_GetAnimationCurrentTime_Params params;
	params.InAnimation = InAnimation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.GetAnchorsInViewport
// ()
// Parameters:
// struct FAnchors                ReturnValue                    (Parm, OutParm, ReturnParm)

struct FAnchors UUserWidget::GetAnchorsInViewport()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetAnchorsInViewport");

	UUserWidget_GetAnchorsInViewport_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.GetAlignmentInViewport
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UUserWidget::GetAlignmentInViewport()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.GetAlignmentInViewport");

	UUserWidget_GetAlignmentInViewport_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserWidget.Destruct
// ()

void UUserWidget::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.Destruct");

	UUserWidget_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.Construct
// ()

void UUserWidget::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.Construct");

	UUserWidget_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.CancelLatentActions
// ()

void UUserWidget::CancelLatentActions()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.CancelLatentActions");

	UUserWidget_CancelLatentActions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.AddToViewport
// ()
// Parameters:
// int                            ZOrder                         (Parm, ZeroConstructor, IsPlainOldData)

void UUserWidget::AddToViewport(int ZOrder)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.AddToViewport");

	UUserWidget_AddToViewport_Params params;
	params.ZOrder = ZOrder;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserWidget.AddToPlayerScreen
// ()
// Parameters:
// int                            ZOrder                         (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UUserWidget::AddToPlayerScreen(int ZOrder)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserWidget.AddToPlayerScreen");

	UUserWidget_AddToPlayerScreen_Params params;
	params.ZOrder = ZOrder;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.VerticalBox.AddChildToVerticalBox
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UVerticalBoxSlot*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UVerticalBoxSlot* UVerticalBox::AddChildToVerticalBox(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.VerticalBox.AddChildToVerticalBox");

	UVerticalBox_AddChildToVerticalBox_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.DragDropOperation.Drop
// ()
// Parameters:
// struct FPointerEvent           PointerEvent                   (ConstParm, Parm, OutParm, ReferenceParm)

void UDragDropOperation::Drop(const struct FPointerEvent& PointerEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DragDropOperation.Drop");

	UDragDropOperation_Drop_Params params;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.DragDropOperation.Dragged
// ()
// Parameters:
// struct FPointerEvent           PointerEvent                   (ConstParm, Parm, OutParm, ReferenceParm)

void UDragDropOperation::Dragged(const struct FPointerEvent& PointerEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DragDropOperation.Dragged");

	UDragDropOperation_Dragged_Params params;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.DragDropOperation.DragCancelled
// ()
// Parameters:
// struct FPointerEvent           PointerEvent                   (ConstParm, Parm, OutParm, ReferenceParm)

void UDragDropOperation::DragCancelled(const struct FPointerEvent& PointerEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DragDropOperation.DragCancelled");

	UDragDropOperation_DragCancelled_Params params;
	params.PointerEvent = PointerEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetSwitcher.SetActiveWidgetIndex
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetSwitcher::SetActiveWidgetIndex(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcher.SetActiveWidgetIndex");

	UWidgetSwitcher_SetActiveWidgetIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetSwitcher.SetActiveWidget
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidgetSwitcher::SetActiveWidget(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcher.SetActiveWidget");

	UWidgetSwitcher_SetActiveWidget_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetSwitcher.GetWidgetAtIndex
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidgetSwitcher::GetWidgetAtIndex(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcher.GetWidgetAtIndex");

	UWidgetSwitcher_GetWidgetAtIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetSwitcher.GetNumWidgets
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidgetSwitcher::GetNumWidgets()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcher.GetNumWidgets");

	UWidgetSwitcher_GetNumWidgets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetSwitcher.GetActiveWidgetIndex
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UWidgetSwitcher::GetActiveWidgetIndex()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcher.GetActiveWidgetIndex");

	UWidgetSwitcher_GetActiveWidgetIndex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetSwitcher.GetActiveWidget
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidgetSwitcher::GetActiveWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcher.GetActiveWidget");

	UWidgetSwitcher_GetActiveWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.AsyncTaskDownloadImage.DownloadImage
// ()
// Parameters:
// class FString                  URL                            (Parm, ZeroConstructor)
// class UAsyncTaskDownloadImage* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UAsyncTaskDownloadImage* UAsyncTaskDownloadImage::DownloadImage(const class FString& URL)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.AsyncTaskDownloadImage.DownloadImage");

	UAsyncTaskDownloadImage_DownloadImage_Params params;
	params.URL = URL;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.BackgroundBlur.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlur::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetVerticalAlignment");

	UBackgroundBlur_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlur.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlur::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetPadding");

	UBackgroundBlur_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlur.SetLowQualityFallbackBrush
// ()
// Parameters:
// struct FSlateBrush             InBrush                        (ConstParm, Parm, OutParm, ReferenceParm)

void UBackgroundBlur::SetLowQualityFallbackBrush(const struct FSlateBrush& InBrush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetLowQualityFallbackBrush");

	UBackgroundBlur_SetLowQualityFallbackBrush_Params params;
	params.InBrush = InBrush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlur.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlur::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetHorizontalAlignment");

	UBackgroundBlur_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlur.SetBlurStrength
// ()
// Parameters:
// float                          InStrength                     (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlur::SetBlurStrength(float InStrength)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetBlurStrength");

	UBackgroundBlur_SetBlurStrength_Params params;
	params.InStrength = InStrength;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlur.SetBlurRadius
// ()
// Parameters:
// int                            InBlurRadius                   (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlur::SetBlurRadius(int InBlurRadius)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetBlurRadius");

	UBackgroundBlur_SetBlurRadius_Params params;
	params.InBlurRadius = InBlurRadius;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlur.SetApplyAlphaToBlur
// ()
// Parameters:
// bool                           bInApplyAlphaToBlur            (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlur::SetApplyAlphaToBlur(bool bInApplyAlphaToBlur)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlur.SetApplyAlphaToBlur");

	UBackgroundBlur_SetApplyAlphaToBlur_Params params;
	params.bInApplyAlphaToBlur = bInApplyAlphaToBlur;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlurSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlurSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlurSlot.SetVerticalAlignment");

	UBackgroundBlurSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlurSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlurSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlurSlot.SetPadding");

	UBackgroundBlurSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BackgroundBlurSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UBackgroundBlurSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BackgroundBlurSlot.SetHorizontalAlignment");

	UBackgroundBlurSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BoolBinding.GetValue
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBoolBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BoolBinding.GetValue");

	UBoolBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Border.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetVerticalAlignment");

	UBorder_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetPadding");

	UBorder_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetHorizontalAlignment");

	UBorder_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetDesiredSizeScale
// ()
// Parameters:
// struct FVector2D               InScale                        (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetDesiredSizeScale(const struct FVector2D& InScale)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetDesiredSizeScale");

	UBorder_SetDesiredSizeScale_Params params;
	params.InScale = InScale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetContentColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            InContentColorAndOpacity       (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetContentColorAndOpacity(const struct FLinearColor& InContentColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetContentColorAndOpacity");

	UBorder_SetContentColorAndOpacity_Params params;
	params.InContentColorAndOpacity = InContentColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetBrushFromTexture
// ()
// Parameters:
// class UTexture2D*              Texture                        (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetBrushFromTexture(class UTexture2D* Texture)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetBrushFromTexture");

	UBorder_SetBrushFromTexture_Params params;
	params.Texture = Texture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetBrushFromMaterial
// ()
// Parameters:
// class UMaterialInterface*      Material                       (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetBrushFromMaterial(class UMaterialInterface* Material)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetBrushFromMaterial");

	UBorder_SetBrushFromMaterial_Params params;
	params.Material = Material;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetBrushFromAsset
// ()
// Parameters:
// class USlateBrushAsset*        Asset                          (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetBrushFromAsset(class USlateBrushAsset* Asset)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetBrushFromAsset");

	UBorder_SetBrushFromAsset_Params params;
	params.Asset = Asset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetBrushColor
// ()
// Parameters:
// struct FLinearColor            InBrushColor                   (Parm, ZeroConstructor, IsPlainOldData)

void UBorder::SetBrushColor(const struct FLinearColor& InBrushColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetBrushColor");

	UBorder_SetBrushColor_Params params;
	params.InBrushColor = InBrushColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.SetBrush
// ()
// Parameters:
// struct FSlateBrush             InBrush                        (ConstParm, Parm, OutParm, ReferenceParm)

void UBorder::SetBrush(const struct FSlateBrush& InBrush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.SetBrush");

	UBorder_SetBrush_Params params;
	params.InBrush = InBrush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Border.GetDynamicMaterial
// ()
// Parameters:
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* UBorder::GetDynamicMaterial()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Border.GetDynamicMaterial");

	UBorder_GetDynamicMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.BorderSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UBorderSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BorderSlot.SetVerticalAlignment");

	UBorderSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BorderSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UBorderSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BorderSlot.SetPadding");

	UBorderSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BorderSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UBorderSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BorderSlot.SetHorizontalAlignment");

	UBorderSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.BrushBinding.GetValue
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UBrushBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.BrushBinding.GetValue");

	UBrushBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Button.SetTouchMethod
// ()
// Parameters:
// TEnumAsByte<EButtonTouchMethod> InTouchMethod                  (Parm, ZeroConstructor, IsPlainOldData)

void UButton::SetTouchMethod(TEnumAsByte<EButtonTouchMethod> InTouchMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.SetTouchMethod");

	UButton_SetTouchMethod_Params params;
	params.InTouchMethod = InTouchMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Button.SetStyle
// ()
// Parameters:
// struct FButtonStyle            InStyle                        (ConstParm, Parm, OutParm, ReferenceParm)

void UButton::SetStyle(const struct FButtonStyle& InStyle)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.SetStyle");

	UButton_SetStyle_Params params;
	params.InStyle = InStyle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Button.SetPressMethod
// ()
// Parameters:
// TEnumAsByte<EButtonPressMethod> InPressMethod                  (Parm, ZeroConstructor, IsPlainOldData)

void UButton::SetPressMethod(TEnumAsByte<EButtonPressMethod> InPressMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.SetPressMethod");

	UButton_SetPressMethod_Params params;
	params.InPressMethod = InPressMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Button.SetColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            InColorAndOpacity              (Parm, ZeroConstructor, IsPlainOldData)

void UButton::SetColorAndOpacity(const struct FLinearColor& InColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.SetColorAndOpacity");

	UButton_SetColorAndOpacity_Params params;
	params.InColorAndOpacity = InColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Button.SetClickMethod
// ()
// Parameters:
// TEnumAsByte<EButtonClickMethod> InClickMethod                  (Parm, ZeroConstructor, IsPlainOldData)

void UButton::SetClickMethod(TEnumAsByte<EButtonClickMethod> InClickMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.SetClickMethod");

	UButton_SetClickMethod_Params params;
	params.InClickMethod = InClickMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Button.SetBackgroundColor
// ()
// Parameters:
// struct FLinearColor            InBackgroundColor              (Parm, ZeroConstructor, IsPlainOldData)

void UButton::SetBackgroundColor(const struct FLinearColor& InBackgroundColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.SetBackgroundColor");

	UButton_SetBackgroundColor_Params params;
	params.InBackgroundColor = InBackgroundColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Button.IsPressed
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UButton::IsPressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Button.IsPressed");

	UButton_IsPressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ButtonSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UButtonSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ButtonSlot.SetVerticalAlignment");

	UButtonSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ButtonSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UButtonSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ButtonSlot.SetPadding");

	UButtonSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ButtonSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UButtonSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ButtonSlot.SetHorizontalAlignment");

	UButtonSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanel.AddChildToCanvas
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UCanvasPanelSlot*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UCanvasPanelSlot* UCanvasPanel::AddChildToCanvas(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanel.AddChildToCanvas");

	UCanvasPanel_AddChildToCanvas_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.SetZOrder
// ()
// Parameters:
// int                            InZOrder                       (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetZOrder(int InZOrder)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetZOrder");

	UCanvasPanelSlot_SetZOrder_Params params;
	params.InZOrder = InZOrder;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetSize
// ()
// Parameters:
// struct FVector2D               InSize                         (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetSize(const struct FVector2D& InSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetSize");

	UCanvasPanelSlot_SetSize_Params params;
	params.InSize = InSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetPosition
// ()
// Parameters:
// struct FVector2D               InPosition                     (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetPosition(const struct FVector2D& InPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetPosition");

	UCanvasPanelSlot_SetPosition_Params params;
	params.InPosition = InPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetOffsets
// ()
// Parameters:
// struct FMargin                 InOffset                       (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetOffsets(const struct FMargin& InOffset)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetOffsets");

	UCanvasPanelSlot_SetOffsets_Params params;
	params.InOffset = InOffset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetMinimum
// ()
// Parameters:
// struct FVector2D               InMinimumAnchors               (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetMinimum(const struct FVector2D& InMinimumAnchors)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetMinimum");

	UCanvasPanelSlot_SetMinimum_Params params;
	params.InMinimumAnchors = InMinimumAnchors;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetMaximum
// ()
// Parameters:
// struct FVector2D               InMaximumAnchors               (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetMaximum(const struct FVector2D& InMaximumAnchors)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetMaximum");

	UCanvasPanelSlot_SetMaximum_Params params;
	params.InMaximumAnchors = InMaximumAnchors;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetLayout
// ()
// Parameters:
// struct FAnchorData             InLayoutData                   (ConstParm, Parm, OutParm, ReferenceParm)

void UCanvasPanelSlot::SetLayout(const struct FAnchorData& InLayoutData)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetLayout");

	UCanvasPanelSlot_SetLayout_Params params;
	params.InLayoutData = InLayoutData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetAutoSize
// ()
// Parameters:
// bool                           InbAutoSize                    (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetAutoSize(bool InbAutoSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetAutoSize");

	UCanvasPanelSlot_SetAutoSize_Params params;
	params.InbAutoSize = InbAutoSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetAnchors
// ()
// Parameters:
// struct FAnchors                InAnchors                      (Parm)

void UCanvasPanelSlot::SetAnchors(const struct FAnchors& InAnchors)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetAnchors");

	UCanvasPanelSlot_SetAnchors_Params params;
	params.InAnchors = InAnchors;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.SetAlignment
// ()
// Parameters:
// struct FVector2D               InAlignment                    (Parm, ZeroConstructor, IsPlainOldData)

void UCanvasPanelSlot::SetAlignment(const struct FVector2D& InAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.SetAlignment");

	UCanvasPanelSlot_SetAlignment_Params params;
	params.InAlignment = InAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CanvasPanelSlot.GetZOrder
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UCanvasPanelSlot::GetZOrder()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetZOrder");

	UCanvasPanelSlot_GetZOrder_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetSize
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UCanvasPanelSlot::GetSize()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetSize");

	UCanvasPanelSlot_GetSize_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetPosition
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UCanvasPanelSlot::GetPosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetPosition");

	UCanvasPanelSlot_GetPosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetOffsets
// ()
// Parameters:
// struct FMargin                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FMargin UCanvasPanelSlot::GetOffsets()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetOffsets");

	UCanvasPanelSlot_GetOffsets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetLayout
// ()
// Parameters:
// struct FAnchorData             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FAnchorData UCanvasPanelSlot::GetLayout()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetLayout");

	UCanvasPanelSlot_GetLayout_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetAutoSize
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UCanvasPanelSlot::GetAutoSize()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetAutoSize");

	UCanvasPanelSlot_GetAutoSize_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetAnchors
// ()
// Parameters:
// struct FAnchors                ReturnValue                    (Parm, OutParm, ReturnParm)

struct FAnchors UCanvasPanelSlot::GetAnchors()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetAnchors");

	UCanvasPanelSlot_GetAnchors_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CanvasPanelSlot.GetAlignment
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UCanvasPanelSlot::GetAlignment()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CanvasPanelSlot.GetAlignment");

	UCanvasPanelSlot_GetAlignment_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CheckBox.SetIsChecked
// ()
// Parameters:
// bool                           InIsChecked                    (Parm, ZeroConstructor, IsPlainOldData)

void UCheckBox::SetIsChecked(bool InIsChecked)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CheckBox.SetIsChecked");

	UCheckBox_SetIsChecked_Params params;
	params.InIsChecked = InIsChecked;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CheckBox.SetCheckedState
// ()
// Parameters:
// ECheckBoxState                 InCheckedState                 (Parm, ZeroConstructor, IsPlainOldData)

void UCheckBox::SetCheckedState(ECheckBoxState InCheckedState)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CheckBox.SetCheckedState");

	UCheckBox_SetCheckedState_Params params;
	params.InCheckedState = InCheckedState;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CheckBox.IsPressed
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UCheckBox::IsPressed()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CheckBox.IsPressed");

	UCheckBox_IsPressed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CheckBox.IsChecked
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UCheckBox::IsChecked()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CheckBox.IsChecked");

	UCheckBox_IsChecked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CheckBox.GetCheckedState
// ()
// Parameters:
// ECheckBoxState                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ECheckBoxState UCheckBox::GetCheckedState()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CheckBox.GetCheckedState");

	UCheckBox_GetCheckedState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CheckedStateBinding.GetValue
// ()
// Parameters:
// ECheckBoxState                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ECheckBoxState UCheckedStateBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CheckedStateBinding.GetValue");

	UCheckedStateBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.CircularThrobber.SetRadius
// ()
// Parameters:
// float                          InRadius                       (Parm, ZeroConstructor, IsPlainOldData)

void UCircularThrobber::SetRadius(float InRadius)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CircularThrobber.SetRadius");

	UCircularThrobber_SetRadius_Params params;
	params.InRadius = InRadius;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CircularThrobber.SetPeriod
// ()
// Parameters:
// float                          InPeriod                       (Parm, ZeroConstructor, IsPlainOldData)

void UCircularThrobber::SetPeriod(float InPeriod)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CircularThrobber.SetPeriod");

	UCircularThrobber_SetPeriod_Params params;
	params.InPeriod = InPeriod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.CircularThrobber.SetNumberOfPieces
// ()
// Parameters:
// int                            InNumberOfPieces               (Parm, ZeroConstructor, IsPlainOldData)

void UCircularThrobber::SetNumberOfPieces(int InNumberOfPieces)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.CircularThrobber.SetNumberOfPieces");

	UCircularThrobber_SetNumberOfPieces_Params params;
	params.InNumberOfPieces = InNumberOfPieces;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ColorBinding.GetSlateValue
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UColorBinding::GetSlateValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ColorBinding.GetSlateValue");

	UColorBinding_GetSlateValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ColorBinding.GetLinearValue
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor UColorBinding::GetLinearValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ColorBinding.GetLinearValue");

	UColorBinding_GetLinearValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ComboBoxString.SetSelectedOption
// ()
// Parameters:
// class FString                  Option                         (Parm, ZeroConstructor)

void UComboBoxString::SetSelectedOption(const class FString& Option)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.SetSelectedOption");

	UComboBoxString_SetSelectedOption_Params params;
	params.Option = Option;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ComboBoxString.RemoveOption
// ()
// Parameters:
// class FString                  Option                         (Parm, ZeroConstructor)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UComboBoxString::RemoveOption(const class FString& Option)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.RemoveOption");

	UComboBoxString_RemoveOption_Params params;
	params.Option = Option;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ComboBoxString.RefreshOptions
// ()

void UComboBoxString::RefreshOptions()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.RefreshOptions");

	UComboBoxString_RefreshOptions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.ComboBoxString.OnSelectionChangedEvent__DelegateSignature
// ()
// Parameters:
// class FString                  SelectedItem                   (Parm, ZeroConstructor)
// TEnumAsByte<ESelectInfo>       SelectionType                  (Parm, ZeroConstructor, IsPlainOldData)

void UComboBoxString::OnSelectionChangedEvent__DelegateSignature(const class FString& SelectedItem, TEnumAsByte<ESelectInfo> SelectionType)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.ComboBoxString.OnSelectionChangedEvent__DelegateSignature");

	UComboBoxString_OnSelectionChangedEvent__DelegateSignature_Params params;
	params.SelectedItem = SelectedItem;
	params.SelectionType = SelectionType;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.ComboBoxString.OnOpeningEvent__DelegateSignature
// ()

void UComboBoxString::OnOpeningEvent__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.ComboBoxString.OnOpeningEvent__DelegateSignature");

	UComboBoxString_OnOpeningEvent__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ComboBoxString.GetSelectedOption
// ()
// Parameters:
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UComboBoxString::GetSelectedOption()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.GetSelectedOption");

	UComboBoxString_GetSelectedOption_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ComboBoxString.GetOptionCount
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UComboBoxString::GetOptionCount()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.GetOptionCount");

	UComboBoxString_GetOptionCount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ComboBoxString.GetOptionAtIndex
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UComboBoxString::GetOptionAtIndex(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.GetOptionAtIndex");

	UComboBoxString_GetOptionAtIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ComboBoxString.FindOptionIndex
// ()
// Parameters:
// class FString                  Option                         (Parm, ZeroConstructor)
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UComboBoxString::FindOptionIndex(const class FString& Option)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.FindOptionIndex");

	UComboBoxString_FindOptionIndex_Params params;
	params.Option = Option;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ComboBoxString.ClearSelection
// ()

void UComboBoxString::ClearSelection()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.ClearSelection");

	UComboBoxString_ClearSelection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ComboBoxString.ClearOptions
// ()

void UComboBoxString::ClearOptions()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.ClearOptions");

	UComboBoxString_ClearOptions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ComboBoxString.AddOption
// ()
// Parameters:
// class FString                  Option                         (Parm, ZeroConstructor)

void UComboBoxString::AddOption(const class FString& Option)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ComboBoxString.AddOption");

	UComboBoxString_AddOption_Params params;
	params.Option = Option;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.DynamicEntryBox.SetEntrySpacing
// ()
// Parameters:
// struct FVector2D               InEntrySpacing                 (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void UDynamicEntryBox::SetEntrySpacing(const struct FVector2D& InEntrySpacing)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.SetEntrySpacing");

	UDynamicEntryBox_SetEntrySpacing_Params params;
	params.InEntrySpacing = InEntrySpacing;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.DynamicEntryBox.Reset
// ()
// Parameters:
// bool                           bDeleteWidgets                 (Parm, ZeroConstructor, IsPlainOldData)

void UDynamicEntryBox::Reset(bool bDeleteWidgets)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.Reset");

	UDynamicEntryBox_Reset_Params params;
	params.bDeleteWidgets = bDeleteWidgets;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.DynamicEntryBox.RemoveEntry
// ()
// Parameters:
// class UUserWidget*             EntryWidget                    (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UDynamicEntryBox::RemoveEntry(class UUserWidget* EntryWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.RemoveEntry");

	UDynamicEntryBox_RemoveEntry_Params params;
	params.EntryWidget = EntryWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.DynamicEntryBox.GetNumEntries
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UDynamicEntryBox::GetNumEntries()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.GetNumEntries");

	UDynamicEntryBox_GetNumEntries_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.DynamicEntryBox.GetAllEntries
// ()
// Parameters:
// TArray<class UUserWidget*>     ReturnValue                    (ConstParm, ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm)

TArray<class UUserWidget*> UDynamicEntryBox::GetAllEntries()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.GetAllEntries");

	UDynamicEntryBox_GetAllEntries_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.DynamicEntryBox.BP_CreateEntryOfClass
// ()
// Parameters:
// class UClass*                  EntryClass                     (Parm, ZeroConstructor, IsPlainOldData)
// class UUserWidget*             ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UUserWidget* UDynamicEntryBox::BP_CreateEntryOfClass(class UClass* EntryClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.BP_CreateEntryOfClass");

	UDynamicEntryBox_BP_CreateEntryOfClass_Params params;
	params.EntryClass = EntryClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.DynamicEntryBox.BP_CreateEntry
// ()
// Parameters:
// class UUserWidget*             ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UUserWidget* UDynamicEntryBox::BP_CreateEntry()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.DynamicEntryBox.BP_CreateEntry");

	UDynamicEntryBox_BP_CreateEntry_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.EditableText.SetText
// ()
// Parameters:
// struct FText                   InText                         (Parm)

void UEditableText::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableText.SetText");

	UEditableText_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableText.SetIsReadOnly
// ()
// Parameters:
// bool                           InbIsReadyOnly                 (Parm, ZeroConstructor, IsPlainOldData)

void UEditableText::SetIsReadOnly(bool InbIsReadyOnly)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableText.SetIsReadOnly");

	UEditableText_SetIsReadOnly_Params params;
	params.InbIsReadyOnly = InbIsReadyOnly;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableText.SetIsPassword
// ()
// Parameters:
// bool                           InbIsPassword                  (Parm, ZeroConstructor, IsPlainOldData)

void UEditableText::SetIsPassword(bool InbIsPassword)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableText.SetIsPassword");

	UEditableText_SetIsPassword_Params params;
	params.InbIsPassword = InbIsPassword;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableText.SetHintText
// ()
// Parameters:
// struct FText                   InHintText                     (Parm)

void UEditableText::SetHintText(const struct FText& InHintText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableText.SetHintText");

	UEditableText_SetHintText_Params params;
	params.InHintText = InHintText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.EditableText.OnEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (Parm, ZeroConstructor, IsPlainOldData)

void UEditableText::OnEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.EditableText.OnEditableTextCommittedEvent__DelegateSignature");

	UEditableText_OnEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.EditableText.OnEditableTextChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)

void UEditableText::OnEditableTextChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.EditableText.OnEditableTextChangedEvent__DelegateSignature");

	UEditableText_OnEditableTextChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableText.GetText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UEditableText::GetText()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableText.GetText");

	UEditableText_GetText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.EditableTextBox.SetText
// ()
// Parameters:
// struct FText                   InText                         (Parm)

void UEditableTextBox::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.SetText");

	UEditableTextBox_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableTextBox.SetIsReadOnly
// ()
// Parameters:
// bool                           bReadOnly                      (Parm, ZeroConstructor, IsPlainOldData)

void UEditableTextBox::SetIsReadOnly(bool bReadOnly)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.SetIsReadOnly");

	UEditableTextBox_SetIsReadOnly_Params params;
	params.bReadOnly = bReadOnly;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableTextBox.SetIsPassword
// ()
// Parameters:
// bool                           bIsPassword                    (Parm, ZeroConstructor, IsPlainOldData)

void UEditableTextBox::SetIsPassword(bool bIsPassword)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.SetIsPassword");

	UEditableTextBox_SetIsPassword_Params params;
	params.bIsPassword = bIsPassword;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableTextBox.SetHintText
// ()
// Parameters:
// struct FText                   InText                         (Parm)

void UEditableTextBox::SetHintText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.SetHintText");

	UEditableTextBox_SetHintText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableTextBox.SetError
// ()
// Parameters:
// struct FText                   InError                        (Parm)

void UEditableTextBox::SetError(const struct FText& InError)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.SetError");

	UEditableTextBox_SetError_Params params;
	params.InError = InError;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.EditableTextBox.OnEditableTextBoxCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (Parm, ZeroConstructor, IsPlainOldData)

void UEditableTextBox::OnEditableTextBoxCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.EditableTextBox.OnEditableTextBoxCommittedEvent__DelegateSignature");

	UEditableTextBox_OnEditableTextBoxCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.EditableTextBox.OnEditableTextBoxChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)

void UEditableTextBox::OnEditableTextBoxChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.EditableTextBox.OnEditableTextBoxChangedEvent__DelegateSignature");

	UEditableTextBox_OnEditableTextBoxChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.EditableTextBox.HasError
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UEditableTextBox::HasError()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.HasError");

	UEditableTextBox_HasError_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.EditableTextBox.GetText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UEditableTextBox::GetText()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.GetText");

	UEditableTextBox_GetText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.EditableTextBox.ClearError
// ()

void UEditableTextBox::ClearError()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.EditableTextBox.ClearError");

	UEditableTextBox_ClearError_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ExpandableArea.SetIsExpanded_Animated
// ()
// Parameters:
// bool                           IsExpanded                     (Parm, ZeroConstructor, IsPlainOldData)

void UExpandableArea::SetIsExpanded_Animated(bool IsExpanded)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ExpandableArea.SetIsExpanded_Animated");

	UExpandableArea_SetIsExpanded_Animated_Params params;
	params.IsExpanded = IsExpanded;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ExpandableArea.SetIsExpanded
// ()
// Parameters:
// bool                           IsExpanded                     (Parm, ZeroConstructor, IsPlainOldData)

void UExpandableArea::SetIsExpanded(bool IsExpanded)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ExpandableArea.SetIsExpanded");

	UExpandableArea_SetIsExpanded_Params params;
	params.IsExpanded = IsExpanded;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ExpandableArea.GetIsExpanded
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UExpandableArea::GetIsExpanded()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ExpandableArea.GetIsExpanded");

	UExpandableArea_GetIsExpanded_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.FloatBinding.GetValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UFloatBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.FloatBinding.GetValue");

	UFloatBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.GridPanel.SetRowFill
// ()
// Parameters:
// int                            ColumnIndex                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          Coefficient                    (Parm, ZeroConstructor, IsPlainOldData)

void UGridPanel::SetRowFill(int ColumnIndex, float Coefficient)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridPanel.SetRowFill");

	UGridPanel_SetRowFill_Params params;
	params.ColumnIndex = ColumnIndex;
	params.Coefficient = Coefficient;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridPanel.SetColumnFill
// ()
// Parameters:
// int                            ColumnIndex                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          Coefficient                    (Parm, ZeroConstructor, IsPlainOldData)

void UGridPanel::SetColumnFill(int ColumnIndex, float Coefficient)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridPanel.SetColumnFill");

	UGridPanel_SetColumnFill_Params params;
	params.ColumnIndex = ColumnIndex;
	params.Coefficient = Coefficient;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridPanel.AddChildToGrid
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UGridSlot*               ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UGridSlot* UGridPanel::AddChildToGrid(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridPanel.AddChildToGrid");

	UGridPanel_AddChildToGrid_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.GridSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetVerticalAlignment");

	UGridSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetRowSpan
// ()
// Parameters:
// int                            InRowSpan                      (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetRowSpan(int InRowSpan)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetRowSpan");

	UGridSlot_SetRowSpan_Params params;
	params.InRowSpan = InRowSpan;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetRow
// ()
// Parameters:
// int                            InRow                          (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetRow(int InRow)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetRow");

	UGridSlot_SetRow_Params params;
	params.InRow = InRow;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetPadding");

	UGridSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetLayer
// ()
// Parameters:
// int                            InLayer                        (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetLayer(int InLayer)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetLayer");

	UGridSlot_SetLayer_Params params;
	params.InLayer = InLayer;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetHorizontalAlignment");

	UGridSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetColumnSpan
// ()
// Parameters:
// int                            InColumnSpan                   (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetColumnSpan(int InColumnSpan)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetColumnSpan");

	UGridSlot_SetColumnSpan_Params params;
	params.InColumnSpan = InColumnSpan;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.GridSlot.SetColumn
// ()
// Parameters:
// int                            InColumn                       (Parm, ZeroConstructor, IsPlainOldData)

void UGridSlot::SetColumn(int InColumn)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.GridSlot.SetColumn");

	UGridSlot_SetColumn_Params params;
	params.InColumn = InColumn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.HorizontalBox.AddChildToHorizontalBox
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UHorizontalBoxSlot*      ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UHorizontalBoxSlot* UHorizontalBox::AddChildToHorizontalBox(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.HorizontalBox.AddChildToHorizontalBox");

	UHorizontalBox_AddChildToHorizontalBox_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.HorizontalBoxSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UHorizontalBoxSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.HorizontalBoxSlot.SetVerticalAlignment");

	UHorizontalBoxSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.HorizontalBoxSlot.SetSize
// ()
// Parameters:
// struct FSlateChildSize         InSize                         (Parm)

void UHorizontalBoxSlot::SetSize(const struct FSlateChildSize& InSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.HorizontalBoxSlot.SetSize");

	UHorizontalBoxSlot_SetSize_Params params;
	params.InSize = InSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.HorizontalBoxSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UHorizontalBoxSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.HorizontalBoxSlot.SetPadding");

	UHorizontalBoxSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.HorizontalBoxSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UHorizontalBoxSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.HorizontalBoxSlot.SetHorizontalAlignment");

	UHorizontalBoxSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetOpacity
// ()
// Parameters:
// float                          InOpacity                      (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetOpacity(float InOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetOpacity");

	UImage_SetOpacity_Params params;
	params.InOpacity = InOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            InColorAndOpacity              (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetColorAndOpacity(const struct FLinearColor& InColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetColorAndOpacity");

	UImage_SetColorAndOpacity_Params params;
	params.InColorAndOpacity = InColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushTintColor
// ()
// Parameters:
// struct FSlateColor             TintColor                      (Parm)

void UImage::SetBrushTintColor(const struct FSlateColor& TintColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushTintColor");

	UImage_SetBrushTintColor_Params params;
	params.TintColor = TintColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushSize
// ()
// Parameters:
// struct FVector2D               DesiredSize                    (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushSize(const struct FVector2D& DesiredSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushSize");

	UImage_SetBrushSize_Params params;
	params.DesiredSize = DesiredSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushFromTextureDynamic
// ()
// Parameters:
// class UTexture2DDynamic*       Texture                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bMatchSize                     (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushFromTextureDynamic(class UTexture2DDynamic* Texture, bool bMatchSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushFromTextureDynamic");

	UImage_SetBrushFromTextureDynamic_Params params;
	params.Texture = Texture;
	params.bMatchSize = bMatchSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushFromTexture
// ()
// Parameters:
// class UTexture2D*              Texture                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bMatchSize                     (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushFromTexture(class UTexture2D* Texture, bool bMatchSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushFromTexture");

	UImage_SetBrushFromTexture_Params params;
	params.Texture = Texture;
	params.bMatchSize = bMatchSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushFromSoftTexture
// ()
// Parameters:
// TSoftObjectPtr<class UTexture2D> SoftTexture                    (Parm)
// bool                           bMatchSize                     (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushFromSoftTexture(TSoftObjectPtr<class UTexture2D> SoftTexture, bool bMatchSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushFromSoftTexture");

	UImage_SetBrushFromSoftTexture_Params params;
	params.SoftTexture = SoftTexture;
	params.bMatchSize = bMatchSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushFromMaterial
// ()
// Parameters:
// class UMaterialInterface*      Material                       (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushFromMaterial(class UMaterialInterface* Material)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushFromMaterial");

	UImage_SetBrushFromMaterial_Params params;
	params.Material = Material;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushFromAtlasInterface
// ()
// Parameters:
// TScriptInterface<class USlateTextureAtlasInterface> AtlasRegion                    (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bMatchSize                     (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushFromAtlasInterface(const TScriptInterface<class USlateTextureAtlasInterface>& AtlasRegion, bool bMatchSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushFromAtlasInterface");

	UImage_SetBrushFromAtlasInterface_Params params;
	params.AtlasRegion = AtlasRegion;
	params.bMatchSize = bMatchSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrushFromAsset
// ()
// Parameters:
// class USlateBrushAsset*        Asset                          (Parm, ZeroConstructor, IsPlainOldData)

void UImage::SetBrushFromAsset(class USlateBrushAsset* Asset)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrushFromAsset");

	UImage_SetBrushFromAsset_Params params;
	params.Asset = Asset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.SetBrush
// ()
// Parameters:
// struct FSlateBrush             InBrush                        (ConstParm, Parm, OutParm, ReferenceParm)

void UImage::SetBrush(const struct FSlateBrush& InBrush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.SetBrush");

	UImage_SetBrush_Params params;
	params.InBrush = InBrush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Image.GetDynamicMaterial
// ()
// Parameters:
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* UImage::GetDynamicMaterial()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Image.GetDynamicMaterial");

	UImage_GetDynamicMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.InputKeySelector.SetTextBlockVisibility
// ()
// Parameters:
// ESlateVisibility               InVisibility                   (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UInputKeySelector::SetTextBlockVisibility(ESlateVisibility InVisibility)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetTextBlockVisibility");

	UInputKeySelector_SetTextBlockVisibility_Params params;
	params.InVisibility = InVisibility;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.SetSelectedKey
// ()
// Parameters:
// struct FInputChord             InSelectedKey                  (ConstParm, Parm, OutParm, ReferenceParm)

void UInputKeySelector::SetSelectedKey(const struct FInputChord& InSelectedKey)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetSelectedKey");

	UInputKeySelector_SetSelectedKey_Params params;
	params.InSelectedKey = InSelectedKey;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.SetNoKeySpecifiedText
// ()
// Parameters:
// struct FText                   InNoKeySpecifiedText           (Parm)

void UInputKeySelector::SetNoKeySpecifiedText(const struct FText& InNoKeySpecifiedText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetNoKeySpecifiedText");

	UInputKeySelector_SetNoKeySpecifiedText_Params params;
	params.InNoKeySpecifiedText = InNoKeySpecifiedText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.SetKeySelectionText
// ()
// Parameters:
// struct FText                   InKeySelectionText             (Parm)

void UInputKeySelector::SetKeySelectionText(const struct FText& InKeySelectionText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetKeySelectionText");

	UInputKeySelector_SetKeySelectionText_Params params;
	params.InKeySelectionText = InKeySelectionText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.SetEscapeKeys
// ()
// Parameters:
// TArray<struct FKey>            InKeys                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UInputKeySelector::SetEscapeKeys(TArray<struct FKey> InKeys)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetEscapeKeys");

	UInputKeySelector_SetEscapeKeys_Params params;
	params.InKeys = InKeys;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.SetAllowModifierKeys
// ()
// Parameters:
// bool                           bInAllowModifierKeys           (Parm, ZeroConstructor, IsPlainOldData)

void UInputKeySelector::SetAllowModifierKeys(bool bInAllowModifierKeys)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetAllowModifierKeys");

	UInputKeySelector_SetAllowModifierKeys_Params params;
	params.bInAllowModifierKeys = bInAllowModifierKeys;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.SetAllowGamepadKeys
// ()
// Parameters:
// bool                           bInAllowGamepadKeys            (Parm, ZeroConstructor, IsPlainOldData)

void UInputKeySelector::SetAllowGamepadKeys(bool bInAllowGamepadKeys)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.SetAllowGamepadKeys");

	UInputKeySelector_SetAllowGamepadKeys_Params params;
	params.bInAllowGamepadKeys = bInAllowGamepadKeys;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.InputKeySelector.OnKeySelected__DelegateSignature
// ()
// Parameters:
// struct FInputChord             SelectedKey                    (Parm)

void UInputKeySelector::OnKeySelected__DelegateSignature(const struct FInputChord& SelectedKey)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.InputKeySelector.OnKeySelected__DelegateSignature");

	UInputKeySelector_OnKeySelected__DelegateSignature_Params params;
	params.SelectedKey = SelectedKey;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.InputKeySelector.OnIsSelectingKeyChanged__DelegateSignature
// ()

void UInputKeySelector::OnIsSelectingKeyChanged__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.InputKeySelector.OnIsSelectingKeyChanged__DelegateSignature");

	UInputKeySelector_OnIsSelectingKeyChanged__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InputKeySelector.GetIsSelectingKey
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UInputKeySelector::GetIsSelectingKey()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InputKeySelector.GetIsSelectingKey");

	UInputKeySelector_GetIsSelectingKey_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Int32Binding.GetValue
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UInt32Binding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Int32Binding.GetValue");

	UInt32Binding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.InvalidationBox.SetCanCache
// ()
// Parameters:
// bool                           CanCache                       (Parm, ZeroConstructor, IsPlainOldData)

void UInvalidationBox::SetCanCache(bool CanCache)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InvalidationBox.SetCanCache");

	UInvalidationBox_SetCanCache_Params params;
	params.CanCache = CanCache;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InvalidationBox.InvalidateCache
// ()

void UInvalidationBox::InvalidateCache()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InvalidationBox.InvalidateCache");

	UInvalidationBox_InvalidateCache_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.InvalidationBox.GetCanCache
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UInvalidationBox::GetCanCache()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.InvalidationBox.GetCanCache");

	UInvalidationBox_GetCanCache_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.NativeUserListEntry.IsListItemSelected
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNativeUserListEntry::IsListItemSelected()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.NativeUserListEntry.IsListItemSelected");

	UNativeUserListEntry_IsListItemSelected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.NativeUserListEntry.IsListItemExpanded
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UNativeUserListEntry::IsListItemExpanded()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.NativeUserListEntry.IsListItemExpanded");

	UNativeUserListEntry_IsListItemExpanded_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UserListEntry.BP_OnItemSelectionChanged
// ()
// Parameters:
// bool                           bIsSelected                    (Parm, ZeroConstructor, IsPlainOldData)

void UUserListEntry::BP_OnItemSelectionChanged(bool bIsSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserListEntry.BP_OnItemSelectionChanged");

	UUserListEntry_BP_OnItemSelectionChanged_Params params;
	params.bIsSelected = bIsSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserListEntry.BP_OnItemExpansionChanged
// ()
// Parameters:
// bool                           bIsExpanded                    (Parm, ZeroConstructor, IsPlainOldData)

void UUserListEntry::BP_OnItemExpansionChanged(bool bIsExpanded)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserListEntry.BP_OnItemExpansionChanged");

	UUserListEntry_BP_OnItemExpansionChanged_Params params;
	params.bIsExpanded = bIsExpanded;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserListEntry.BP_OnEntryReleased
// ()

void UUserListEntry::BP_OnEntryReleased()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserListEntry.BP_OnEntryReleased");

	UUserListEntry_BP_OnEntryReleased_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserObjectListEntry.OnListItemObjectSet
// ()
// Parameters:
// class UObject*                 ListItemObject                 (Parm, ZeroConstructor, IsPlainOldData)

void UUserObjectListEntry::OnListItemObjectSet(class UObject* ListItemObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserObjectListEntry.OnListItemObjectSet");

	UUserObjectListEntry_OnListItemObjectSet_Params params;
	params.ListItemObject = ListItemObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UserObjectListEntry.GetListItemObject
// ()
// Parameters:
// class UObject*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UObject* UUserObjectListEntry::GetListItemObject()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UserObjectListEntry.GetListItemObject");

	UUserObjectListEntry_GetListItemObject_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListViewBase.ScrollToTop
// ()

void UListViewBase::ScrollToTop()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListViewBase.ScrollToTop");

	UListViewBase_ScrollToTop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListViewBase.ScrollToBottom
// ()

void UListViewBase::ScrollToBottom()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListViewBase.ScrollToBottom");

	UListViewBase_ScrollToBottom_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListViewBase.RegenerateAllEntries
// ()

void UListViewBase::RegenerateAllEntries()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListViewBase.RegenerateAllEntries");

	UListViewBase_RegenerateAllEntries_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListViewBase.GetDisplayedEntryWidgets
// ()
// Parameters:
// TArray<class UUserWidget*>     ReturnValue                    (ConstParm, ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm)

TArray<class UUserWidget*> UListViewBase::GetDisplayedEntryWidgets()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListViewBase.GetDisplayedEntryWidgets");

	UListViewBase_GetDisplayedEntryWidgets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.SetSelectionMode
// ()
// Parameters:
// TEnumAsByte<ESelectionMode>    SelectionMode                  (Parm, ZeroConstructor, IsPlainOldData)

void UListView::SetSelectionMode(TEnumAsByte<ESelectionMode> SelectionMode)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.SetSelectionMode");

	UListView_SetSelectionMode_Params params;
	params.SelectionMode = SelectionMode;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.SetSelectedIndex
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)

void UListView::SetSelectedIndex(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.SetSelectedIndex");

	UListView_SetSelectedIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.ScrollIndexIntoView
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)

void UListView::ScrollIndexIntoView(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.ScrollIndexIntoView");

	UListView_ScrollIndexIntoView_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.NavigateToIndex
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)

void UListView::NavigateToIndex(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.NavigateToIndex");

	UListView_NavigateToIndex_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.IsRefreshPending
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UListView::IsRefreshPending()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.IsRefreshPending");

	UListView_IsRefreshPending_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.GetNumItems
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UListView::GetNumItems()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.GetNumItems");

	UListView_GetNumItems_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.GetListItems
// ()
// Parameters:
// TArray<class UObject*>         ReturnValue                    (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, ReferenceParm)

TArray<class UObject*> UListView::GetListItems()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.GetListItems");

	UListView_GetListItems_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.GetItemAt
// ()
// Parameters:
// int                            Index                          (Parm, ZeroConstructor, IsPlainOldData)
// class UObject*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UObject* UListView::GetItemAt(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.GetItemAt");

	UListView_GetItemAt_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.GetIndexForItem
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UListView::GetIndexForItem(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.GetIndexForItem");

	UListView_GetIndexForItem_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.ClearListItems
// ()

void UListView::ClearListItems()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.ClearListItems");

	UListView_ClearListItems_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_SetSelectedItem
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)

void UListView::BP_SetSelectedItem(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_SetSelectedItem");

	UListView_BP_SetSelectedItem_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_SetListItems
// ()
// Parameters:
// TArray<class UObject*>         InListItems                    (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)

void UListView::BP_SetListItems(TArray<class UObject*> InListItems)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_SetListItems");

	UListView_BP_SetListItems_Params params;
	params.InListItems = InListItems;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_SetItemSelection
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bSelected                      (Parm, ZeroConstructor, IsPlainOldData)

void UListView::BP_SetItemSelection(class UObject* Item, bool bSelected)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_SetItemSelection");

	UListView_BP_SetItemSelection_Params params;
	params.Item = Item;
	params.bSelected = bSelected;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_ScrollItemIntoView
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)

void UListView::BP_ScrollItemIntoView(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_ScrollItemIntoView");

	UListView_BP_ScrollItemIntoView_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_NavigateToItem
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)

void UListView::BP_NavigateToItem(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_NavigateToItem");

	UListView_BP_NavigateToItem_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_IsItemVisible
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UListView::BP_IsItemVisible(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_IsItemVisible");

	UListView_BP_IsItemVisible_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.BP_GetSelectedItems
// ()
// Parameters:
// TArray<class UObject*>         Items                          (Parm, OutParm, ZeroConstructor)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UListView::BP_GetSelectedItems(TArray<class UObject*>* Items)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_GetSelectedItems");

	UListView_BP_GetSelectedItems_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Items != nullptr)
		*Items = params.Items;

	return params.ReturnValue;
}


// Function UMG.ListView.BP_GetSelectedItem
// ()
// Parameters:
// class UObject*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UObject* UListView::BP_GetSelectedItem()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_GetSelectedItem");

	UListView_BP_GetSelectedItem_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.BP_GetNumItemsSelected
// ()
// Parameters:
// int                            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

int UListView::BP_GetNumItemsSelected()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_GetNumItemsSelected");

	UListView_BP_GetNumItemsSelected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ListView.BP_ClearSelection
// ()

void UListView::BP_ClearSelection()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_ClearSelection");

	UListView_BP_ClearSelection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.BP_CancelScrollIntoView
// ()

void UListView::BP_CancelScrollIntoView()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.BP_CancelScrollIntoView");

	UListView_BP_CancelScrollIntoView_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ListView.AddItem
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)

void UListView::AddItem(class UObject* Item)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ListView.AddItem");

	UListView_AddItem_Params params;
	params.Item = Item;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MenuAnchor.ToggleOpen
// ()
// Parameters:
// bool                           bFocusOnOpen                   (Parm, ZeroConstructor, IsPlainOldData)

void UMenuAnchor::ToggleOpen(bool bFocusOnOpen)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.ToggleOpen");

	UMenuAnchor_ToggleOpen_Params params;
	params.bFocusOnOpen = bFocusOnOpen;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MenuAnchor.ShouldOpenDueToClick
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMenuAnchor::ShouldOpenDueToClick()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.ShouldOpenDueToClick");

	UMenuAnchor_ShouldOpenDueToClick_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.MenuAnchor.Open
// ()
// Parameters:
// bool                           bFocusMenu                     (Parm, ZeroConstructor, IsPlainOldData)

void UMenuAnchor::Open(bool bFocusMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.Open");

	UMenuAnchor_Open_Params params;
	params.bFocusMenu = bFocusMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MenuAnchor.IsOpen
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMenuAnchor::IsOpen()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.IsOpen");

	UMenuAnchor_IsOpen_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.MenuAnchor.HasOpenSubMenus
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UMenuAnchor::HasOpenSubMenus()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.HasOpenSubMenus");

	UMenuAnchor_HasOpenSubMenus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.MenuAnchor.GetMenuPosition
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UMenuAnchor::GetMenuPosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.GetMenuPosition");

	UMenuAnchor_GetMenuPosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.MenuAnchor.Close
// ()

void UMenuAnchor::Close()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MenuAnchor.Close");

	UMenuAnchor_Close_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MouseCursorBinding.GetValue
// ()
// Parameters:
// TEnumAsByte<EMouseCursor>      ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

TEnumAsByte<EMouseCursor> UMouseCursorBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MouseCursorBinding.GetValue");

	UMouseCursorBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.MultiLineEditableText.SetText
// ()
// Parameters:
// struct FText                   InText                         (Parm)

void UMultiLineEditableText::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableText.SetText");

	UMultiLineEditableText_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MultiLineEditableText.SetIsReadOnly
// ()
// Parameters:
// bool                           bReadOnly                      (Parm, ZeroConstructor, IsPlainOldData)

void UMultiLineEditableText::SetIsReadOnly(bool bReadOnly)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableText.SetIsReadOnly");

	UMultiLineEditableText_SetIsReadOnly_Params params;
	params.bReadOnly = bReadOnly;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.MultiLineEditableText.OnMultiLineEditableTextCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (Parm, ZeroConstructor, IsPlainOldData)

void UMultiLineEditableText::OnMultiLineEditableTextCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.MultiLineEditableText.OnMultiLineEditableTextCommittedEvent__DelegateSignature");

	UMultiLineEditableText_OnMultiLineEditableTextCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.MultiLineEditableText.OnMultiLineEditableTextChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)

void UMultiLineEditableText::OnMultiLineEditableTextChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.MultiLineEditableText.OnMultiLineEditableTextChangedEvent__DelegateSignature");

	UMultiLineEditableText_OnMultiLineEditableTextChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MultiLineEditableText.GetText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UMultiLineEditableText::GetText()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableText.GetText");

	UMultiLineEditableText_GetText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.MultiLineEditableTextBox.SetText
// ()
// Parameters:
// struct FText                   InText                         (Parm)

void UMultiLineEditableTextBox::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableTextBox.SetText");

	UMultiLineEditableTextBox_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MultiLineEditableTextBox.SetIsReadOnly
// ()
// Parameters:
// bool                           bReadOnly                      (Parm, ZeroConstructor, IsPlainOldData)

void UMultiLineEditableTextBox::SetIsReadOnly(bool bReadOnly)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableTextBox.SetIsReadOnly");

	UMultiLineEditableTextBox_SetIsReadOnly_Params params;
	params.bReadOnly = bReadOnly;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MultiLineEditableTextBox.SetError
// ()
// Parameters:
// struct FText                   InError                        (Parm)

void UMultiLineEditableTextBox::SetError(const struct FText& InError)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableTextBox.SetError");

	UMultiLineEditableTextBox_SetError_Params params;
	params.InError = InError;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.MultiLineEditableTextBox.OnMultiLineEditableTextBoxCommittedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (Parm, ZeroConstructor, IsPlainOldData)

void UMultiLineEditableTextBox::OnMultiLineEditableTextBoxCommittedEvent__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.MultiLineEditableTextBox.OnMultiLineEditableTextBoxCommittedEvent__DelegateSignature");

	UMultiLineEditableTextBox_OnMultiLineEditableTextBoxCommittedEvent__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.MultiLineEditableTextBox.OnMultiLineEditableTextBoxChangedEvent__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)

void UMultiLineEditableTextBox::OnMultiLineEditableTextBoxChangedEvent__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.MultiLineEditableTextBox.OnMultiLineEditableTextBoxChangedEvent__DelegateSignature");

	UMultiLineEditableTextBox_OnMultiLineEditableTextBoxChangedEvent__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.MultiLineEditableTextBox.GetText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UMultiLineEditableTextBox::GetText()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.MultiLineEditableTextBox.GetText");

	UMultiLineEditableTextBox_GetText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Overlay.AddChildToOverlay
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UOverlaySlot*            ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UOverlaySlot* UOverlay::AddChildToOverlay(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Overlay.AddChildToOverlay");

	UOverlay_AddChildToOverlay_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.OverlaySlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UOverlaySlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.OverlaySlot.SetVerticalAlignment");

	UOverlaySlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.OverlaySlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UOverlaySlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.OverlaySlot.SetPadding");

	UOverlaySlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.OverlaySlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UOverlaySlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.OverlaySlot.SetHorizontalAlignment");

	UOverlaySlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ProgressBar.SetPercent
// ()
// Parameters:
// float                          InPercent                      (Parm, ZeroConstructor, IsPlainOldData)

void UProgressBar::SetPercent(float InPercent)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ProgressBar.SetPercent");

	UProgressBar_SetPercent_Params params;
	params.InPercent = InPercent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ProgressBar.SetIsMarquee
// ()
// Parameters:
// bool                           InbIsMarquee                   (Parm, ZeroConstructor, IsPlainOldData)

void UProgressBar::SetIsMarquee(bool InbIsMarquee)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ProgressBar.SetIsMarquee");

	UProgressBar_SetIsMarquee_Params params;
	params.InbIsMarquee = InbIsMarquee;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ProgressBar.SetFillColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            inColor                        (Parm, ZeroConstructor, IsPlainOldData)

void UProgressBar::SetFillColorAndOpacity(const struct FLinearColor& inColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ProgressBar.SetFillColorAndOpacity");

	UProgressBar_SetFillColorAndOpacity_Params params;
	params.inColor = inColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.RetainerBox.SetTextureParameter
// ()
// Parameters:
// struct FName                   TextureParameter               (Parm, ZeroConstructor, IsPlainOldData)

void URetainerBox::SetTextureParameter(const struct FName& TextureParameter)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RetainerBox.SetTextureParameter");

	URetainerBox_SetTextureParameter_Params params;
	params.TextureParameter = TextureParameter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.RetainerBox.SetRenderingPhase
// ()
// Parameters:
// int                            RenderPhase                    (Parm, ZeroConstructor, IsPlainOldData)
// int                            TotalPhases                    (Parm, ZeroConstructor, IsPlainOldData)

void URetainerBox::SetRenderingPhase(int RenderPhase, int TotalPhases)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RetainerBox.SetRenderingPhase");

	URetainerBox_SetRenderingPhase_Params params;
	params.RenderPhase = RenderPhase;
	params.TotalPhases = TotalPhases;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.RetainerBox.SetEffectMaterial
// ()
// Parameters:
// class UMaterialInterface*      EffectMaterial                 (Parm, ZeroConstructor, IsPlainOldData)

void URetainerBox::SetEffectMaterial(class UMaterialInterface* EffectMaterial)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RetainerBox.SetEffectMaterial");

	URetainerBox_SetEffectMaterial_Params params;
	params.EffectMaterial = EffectMaterial;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.RetainerBox.RequestRender
// ()

void URetainerBox::RequestRender()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RetainerBox.RequestRender");

	URetainerBox_RequestRender_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.RetainerBox.GetEffectMaterial
// ()
// Parameters:
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* URetainerBox::GetEffectMaterial()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RetainerBox.GetEffectMaterial");

	URetainerBox_GetEffectMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.RichTextBlock.SetText
// ()
// Parameters:
// struct FText                   InText                         (ConstParm, Parm, OutParm, ReferenceParm)

void URichTextBlock::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RichTextBlock.SetText");

	URichTextBlock_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.RichTextBlock.GetDecoratorByClass
// ()
// Parameters:
// class UClass*                  DecoratorClass                 (Parm, ZeroConstructor, IsPlainOldData)
// class URichTextBlockDecorator* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class URichTextBlockDecorator* URichTextBlock::GetDecoratorByClass(class UClass* DecoratorClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.RichTextBlock.GetDecoratorByClass");

	URichTextBlock_GetDecoratorByClass_Params params;
	params.DecoratorClass = DecoratorClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SafeZone.SetSidesToPad
// ()
// Parameters:
// bool                           InPadLeft                      (Parm, ZeroConstructor, IsPlainOldData)
// bool                           InPadRight                     (Parm, ZeroConstructor, IsPlainOldData)
// bool                           InPadTop                       (Parm, ZeroConstructor, IsPlainOldData)
// bool                           InPadBottom                    (Parm, ZeroConstructor, IsPlainOldData)

void USafeZone::SetSidesToPad(bool InPadLeft, bool InPadRight, bool InPadTop, bool InPadBottom)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SafeZone.SetSidesToPad");

	USafeZone_SetSidesToPad_Params params;
	params.InPadLeft = InPadLeft;
	params.InPadRight = InPadRight;
	params.InPadTop = InPadTop;
	params.InPadBottom = InPadBottom;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBox.SetUserSpecifiedScale
// ()
// Parameters:
// float                          InUserSpecifiedScale           (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBox::SetUserSpecifiedScale(float InUserSpecifiedScale)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBox.SetUserSpecifiedScale");

	UScaleBox_SetUserSpecifiedScale_Params params;
	params.InUserSpecifiedScale = InUserSpecifiedScale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBox.SetStretchDirection
// ()
// Parameters:
// TEnumAsByte<EStretchDirection> InStretchDirection             (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBox::SetStretchDirection(TEnumAsByte<EStretchDirection> InStretchDirection)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBox.SetStretchDirection");

	UScaleBox_SetStretchDirection_Params params;
	params.InStretchDirection = InStretchDirection;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBox.SetStretch
// ()
// Parameters:
// TEnumAsByte<EStretch>          InStretch                      (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBox::SetStretch(TEnumAsByte<EStretch> InStretch)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBox.SetStretch");

	UScaleBox_SetStretch_Params params;
	params.InStretch = InStretch;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBox.SetIgnoreInheritedScale
// ()
// Parameters:
// bool                           bInIgnoreInheritedScale        (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBox::SetIgnoreInheritedScale(bool bInIgnoreInheritedScale)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBox.SetIgnoreInheritedScale");

	UScaleBox_SetIgnoreInheritedScale_Params params;
	params.bInIgnoreInheritedScale = bInIgnoreInheritedScale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBoxSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBoxSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBoxSlot.SetVerticalAlignment");

	UScaleBoxSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBoxSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBoxSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBoxSlot.SetPadding");

	UScaleBoxSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScaleBoxSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UScaleBoxSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScaleBoxSlot.SetHorizontalAlignment");

	UScaleBoxSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBar.SetState
// ()
// Parameters:
// float                          InOffsetFraction               (Parm, ZeroConstructor, IsPlainOldData)
// float                          InThumbSizeFraction            (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBar::SetState(float InOffsetFraction, float InThumbSizeFraction)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBar.SetState");

	UScrollBar_SetState_Params params;
	params.InOffsetFraction = InOffsetFraction;
	params.InThumbSizeFraction = InThumbSizeFraction;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.SetScrollOffset
// ()
// Parameters:
// float                          NewScrollOffset                (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBox::SetScrollOffset(float NewScrollOffset)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.SetScrollOffset");

	UScrollBox_SetScrollOffset_Params params;
	params.NewScrollOffset = NewScrollOffset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.SetScrollBarVisibility
// ()
// Parameters:
// ESlateVisibility               NewScrollBarVisibility         (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBox::SetScrollBarVisibility(ESlateVisibility NewScrollBarVisibility)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.SetScrollBarVisibility");

	UScrollBox_SetScrollBarVisibility_Params params;
	params.NewScrollBarVisibility = NewScrollBarVisibility;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.SetScrollbarThickness
// ()
// Parameters:
// struct FVector2D               NewScrollbarThickness          (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void UScrollBox::SetScrollbarThickness(const struct FVector2D& NewScrollbarThickness)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.SetScrollbarThickness");

	UScrollBox_SetScrollbarThickness_Params params;
	params.NewScrollbarThickness = NewScrollbarThickness;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.SetOrientation
// ()
// Parameters:
// TEnumAsByte<EOrientation>      NewOrientation                 (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBox::SetOrientation(TEnumAsByte<EOrientation> NewOrientation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.SetOrientation");

	UScrollBox_SetOrientation_Params params;
	params.NewOrientation = NewOrientation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.SetAlwaysShowScrollbar
// ()
// Parameters:
// bool                           NewAlwaysShowScrollbar         (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBox::SetAlwaysShowScrollbar(bool NewAlwaysShowScrollbar)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.SetAlwaysShowScrollbar");

	UScrollBox_SetAlwaysShowScrollbar_Params params;
	params.NewAlwaysShowScrollbar = NewAlwaysShowScrollbar;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.SetAllowOverscroll
// ()
// Parameters:
// bool                           NewAllowOverscroll             (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBox::SetAllowOverscroll(bool NewAllowOverscroll)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.SetAllowOverscroll");

	UScrollBox_SetAllowOverscroll_Params params;
	params.NewAllowOverscroll = NewAllowOverscroll;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.ScrollWidgetIntoView
// ()
// Parameters:
// class UWidget*                 WidgetToFind                   (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           AnimateScroll                  (Parm, ZeroConstructor, IsPlainOldData)
// EDescendantScrollDestination   ScrollDestination              (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBox::ScrollWidgetIntoView(class UWidget* WidgetToFind, bool AnimateScroll, EDescendantScrollDestination ScrollDestination)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.ScrollWidgetIntoView");

	UScrollBox_ScrollWidgetIntoView_Params params;
	params.WidgetToFind = WidgetToFind;
	params.AnimateScroll = AnimateScroll;
	params.ScrollDestination = ScrollDestination;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.ScrollToStart
// ()

void UScrollBox::ScrollToStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.ScrollToStart");

	UScrollBox_ScrollToStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.ScrollToEnd
// ()

void UScrollBox::ScrollToEnd()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.ScrollToEnd");

	UScrollBox_ScrollToEnd_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBox.GetViewOffsetFraction
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UScrollBox::GetViewOffsetFraction()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.GetViewOffsetFraction");

	UScrollBox_GetViewOffsetFraction_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ScrollBox.GetScrollOffset
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UScrollBox::GetScrollOffset()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBox.GetScrollOffset");

	UScrollBox_GetScrollOffset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.ScrollBoxSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBoxSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBoxSlot.SetVerticalAlignment");

	UScrollBoxSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBoxSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBoxSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBoxSlot.SetPadding");

	UScrollBoxSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.ScrollBoxSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UScrollBoxSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.ScrollBoxSlot.SetHorizontalAlignment");

	UScrollBoxSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetWidthOverride
// ()
// Parameters:
// float                          InWidthOverride                (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetWidthOverride(float InWidthOverride)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetWidthOverride");

	USizeBox_SetWidthOverride_Params params;
	params.InWidthOverride = InWidthOverride;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetMinDesiredWidth
// ()
// Parameters:
// float                          InMinDesiredWidth              (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetMinDesiredWidth(float InMinDesiredWidth)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetMinDesiredWidth");

	USizeBox_SetMinDesiredWidth_Params params;
	params.InMinDesiredWidth = InMinDesiredWidth;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetMinDesiredHeight
// ()
// Parameters:
// float                          InMinDesiredHeight             (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetMinDesiredHeight(float InMinDesiredHeight)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetMinDesiredHeight");

	USizeBox_SetMinDesiredHeight_Params params;
	params.InMinDesiredHeight = InMinDesiredHeight;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetMaxDesiredWidth
// ()
// Parameters:
// float                          InMaxDesiredWidth              (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetMaxDesiredWidth(float InMaxDesiredWidth)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetMaxDesiredWidth");

	USizeBox_SetMaxDesiredWidth_Params params;
	params.InMaxDesiredWidth = InMaxDesiredWidth;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetMaxDesiredHeight
// ()
// Parameters:
// float                          InMaxDesiredHeight             (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetMaxDesiredHeight(float InMaxDesiredHeight)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetMaxDesiredHeight");

	USizeBox_SetMaxDesiredHeight_Params params;
	params.InMaxDesiredHeight = InMaxDesiredHeight;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetMaxAspectRatio
// ()
// Parameters:
// float                          InMaxAspectRatio               (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetMaxAspectRatio(float InMaxAspectRatio)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetMaxAspectRatio");

	USizeBox_SetMaxAspectRatio_Params params;
	params.InMaxAspectRatio = InMaxAspectRatio;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.SetHeightOverride
// ()
// Parameters:
// float                          InHeightOverride               (Parm, ZeroConstructor, IsPlainOldData)

void USizeBox::SetHeightOverride(float InHeightOverride)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.SetHeightOverride");

	USizeBox_SetHeightOverride_Params params;
	params.InHeightOverride = InHeightOverride;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearWidthOverride
// ()

void USizeBox::ClearWidthOverride()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearWidthOverride");

	USizeBox_ClearWidthOverride_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearMinDesiredWidth
// ()

void USizeBox::ClearMinDesiredWidth()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearMinDesiredWidth");

	USizeBox_ClearMinDesiredWidth_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearMinDesiredHeight
// ()

void USizeBox::ClearMinDesiredHeight()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearMinDesiredHeight");

	USizeBox_ClearMinDesiredHeight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearMaxDesiredWidth
// ()

void USizeBox::ClearMaxDesiredWidth()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearMaxDesiredWidth");

	USizeBox_ClearMaxDesiredWidth_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearMaxDesiredHeight
// ()

void USizeBox::ClearMaxDesiredHeight()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearMaxDesiredHeight");

	USizeBox_ClearMaxDesiredHeight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearMaxAspectRatio
// ()

void USizeBox::ClearMaxAspectRatio()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearMaxAspectRatio");

	USizeBox_ClearMaxAspectRatio_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBox.ClearHeightOverride
// ()

void USizeBox::ClearHeightOverride()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBox.ClearHeightOverride");

	USizeBox_ClearHeightOverride_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBoxSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void USizeBoxSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBoxSlot.SetVerticalAlignment");

	USizeBoxSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBoxSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void USizeBoxSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBoxSlot.SetPadding");

	USizeBoxSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SizeBoxSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void USizeBoxSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SizeBoxSlot.SetHorizontalAlignment");

	USizeBoxSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SlateBlueprintLibrary.ScreenToWidgetLocal
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               ScreenPosition                 (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               LocalCoordinate                (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void USlateBlueprintLibrary::ScreenToWidgetLocal(class UObject* WorldContextObject, const struct FGeometry& Geometry, const struct FVector2D& ScreenPosition, struct FVector2D* LocalCoordinate)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.ScreenToWidgetLocal");

	USlateBlueprintLibrary_ScreenToWidgetLocal_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Geometry = Geometry;
	params.ScreenPosition = ScreenPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (LocalCoordinate != nullptr)
		*LocalCoordinate = params.LocalCoordinate;
}


// Function UMG.SlateBlueprintLibrary.ScreenToWidgetAbsolute
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ScreenPosition                 (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               AbsoluteCoordinate             (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void USlateBlueprintLibrary::ScreenToWidgetAbsolute(class UObject* WorldContextObject, const struct FVector2D& ScreenPosition, struct FVector2D* AbsoluteCoordinate)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.ScreenToWidgetAbsolute");

	USlateBlueprintLibrary_ScreenToWidgetAbsolute_Params params;
	params.WorldContextObject = WorldContextObject;
	params.ScreenPosition = ScreenPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (AbsoluteCoordinate != nullptr)
		*AbsoluteCoordinate = params.AbsoluteCoordinate;
}


// Function UMG.SlateBlueprintLibrary.ScreenToViewport
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ScreenPosition                 (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ViewportPosition               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void USlateBlueprintLibrary::ScreenToViewport(class UObject* WorldContextObject, const struct FVector2D& ScreenPosition, struct FVector2D* ViewportPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.ScreenToViewport");

	USlateBlueprintLibrary_ScreenToViewport_Params params;
	params.WorldContextObject = WorldContextObject;
	params.ScreenPosition = ScreenPosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ViewportPosition != nullptr)
		*ViewportPosition = params.ViewportPosition;
}


// Function UMG.SlateBlueprintLibrary.LocalToViewport
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               LocalCoordinate                (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               PixelPosition                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ViewportPosition               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void USlateBlueprintLibrary::LocalToViewport(class UObject* WorldContextObject, const struct FGeometry& Geometry, const struct FVector2D& LocalCoordinate, struct FVector2D* PixelPosition, struct FVector2D* ViewportPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.LocalToViewport");

	USlateBlueprintLibrary_LocalToViewport_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Geometry = Geometry;
	params.LocalCoordinate = LocalCoordinate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (PixelPosition != nullptr)
		*PixelPosition = params.PixelPosition;
	if (ViewportPosition != nullptr)
		*ViewportPosition = params.ViewportPosition;
}


// Function UMG.SlateBlueprintLibrary.LocalToAbsolute
// ()
// Parameters:
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               LocalCoordinate                (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D USlateBlueprintLibrary::LocalToAbsolute(const struct FGeometry& Geometry, const struct FVector2D& LocalCoordinate)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.LocalToAbsolute");

	USlateBlueprintLibrary_LocalToAbsolute_Params params;
	params.Geometry = Geometry;
	params.LocalCoordinate = LocalCoordinate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SlateBlueprintLibrary.IsUnderLocation
// ()
// Parameters:
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               AbsoluteCoordinate             (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool USlateBlueprintLibrary::IsUnderLocation(const struct FGeometry& Geometry, const struct FVector2D& AbsoluteCoordinate)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.IsUnderLocation");

	USlateBlueprintLibrary_IsUnderLocation_Params params;
	params.Geometry = Geometry;
	params.AbsoluteCoordinate = AbsoluteCoordinate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SlateBlueprintLibrary.GetLocalSize
// ()
// Parameters:
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D USlateBlueprintLibrary::GetLocalSize(const struct FGeometry& Geometry)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.GetLocalSize");

	USlateBlueprintLibrary_GetLocalSize_Params params;
	params.Geometry = Geometry;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SlateBlueprintLibrary.GetAbsoluteSize
// ()
// Parameters:
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D USlateBlueprintLibrary::GetAbsoluteSize(const struct FGeometry& Geometry)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.GetAbsoluteSize");

	USlateBlueprintLibrary_GetAbsoluteSize_Params params;
	params.Geometry = Geometry;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SlateBlueprintLibrary.EqualEqual_SlateBrush
// ()
// Parameters:
// struct FSlateBrush             A                              (ConstParm, Parm, OutParm, ReferenceParm)
// struct FSlateBrush             B                              (ConstParm, Parm, OutParm, ReferenceParm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool USlateBlueprintLibrary::EqualEqual_SlateBrush(const struct FSlateBrush& A, const struct FSlateBrush& B)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.EqualEqual_SlateBrush");

	USlateBlueprintLibrary_EqualEqual_SlateBrush_Params params;
	params.A = A;
	params.B = B;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SlateBlueprintLibrary.AbsoluteToViewport
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               AbsoluteDesktopCoordinate      (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               PixelPosition                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ViewportPosition               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void USlateBlueprintLibrary::AbsoluteToViewport(class UObject* WorldContextObject, const struct FVector2D& AbsoluteDesktopCoordinate, struct FVector2D* PixelPosition, struct FVector2D* ViewportPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.AbsoluteToViewport");

	USlateBlueprintLibrary_AbsoluteToViewport_Params params;
	params.WorldContextObject = WorldContextObject;
	params.AbsoluteDesktopCoordinate = AbsoluteDesktopCoordinate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (PixelPosition != nullptr)
		*PixelPosition = params.PixelPosition;
	if (ViewportPosition != nullptr)
		*ViewportPosition = params.ViewportPosition;
}


// Function UMG.SlateBlueprintLibrary.AbsoluteToLocal
// ()
// Parameters:
// struct FGeometry               Geometry                       (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector2D               AbsoluteCoordinate             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D USlateBlueprintLibrary::AbsoluteToLocal(const struct FGeometry& Geometry, const struct FVector2D& AbsoluteCoordinate)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SlateBlueprintLibrary.AbsoluteToLocal");

	USlateBlueprintLibrary_AbsoluteToLocal_Params params;
	params.Geometry = Geometry;
	params.AbsoluteCoordinate = AbsoluteCoordinate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Slider.SetValue
// ()
// Parameters:
// float                          InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USlider::SetValue(float InValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.SetValue");

	USlider_SetValue_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Slider.SetStepSize
// ()
// Parameters:
// float                          InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USlider::SetStepSize(float InValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.SetStepSize");

	USlider_SetStepSize_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Slider.SetSliderHandleColor
// ()
// Parameters:
// struct FLinearColor            InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USlider::SetSliderHandleColor(const struct FLinearColor& InValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.SetSliderHandleColor");

	USlider_SetSliderHandleColor_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Slider.SetSliderBarColor
// ()
// Parameters:
// struct FLinearColor            InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USlider::SetSliderBarColor(const struct FLinearColor& InValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.SetSliderBarColor");

	USlider_SetSliderBarColor_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Slider.SetLocked
// ()
// Parameters:
// bool                           InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USlider::SetLocked(bool InValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.SetLocked");

	USlider_SetLocked_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Slider.SetIndentHandle
// ()
// Parameters:
// bool                           InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USlider::SetIndentHandle(bool InValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.SetIndentHandle");

	USlider_SetIndentHandle_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Slider.GetValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float USlider::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Slider.GetValue");

	USlider_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Spacer.SetSize
// ()
// Parameters:
// struct FVector2D               InSize                         (Parm, ZeroConstructor, IsPlainOldData)

void USpacer::SetSize(const struct FVector2D& InSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Spacer.SetSize");

	USpacer_SetSize_Params params;
	params.InSize = InSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.SetValue
// ()
// Parameters:
// float                          NewValue                       (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::SetValue(float NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.SetValue");

	USpinBox_SetValue_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.SetMinValue
// ()
// Parameters:
// float                          NewValue                       (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::SetMinValue(float NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.SetMinValue");

	USpinBox_SetMinValue_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.SetMinSliderValue
// ()
// Parameters:
// float                          NewValue                       (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::SetMinSliderValue(float NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.SetMinSliderValue");

	USpinBox_SetMinSliderValue_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.SetMaxValue
// ()
// Parameters:
// float                          NewValue                       (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::SetMaxValue(float NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.SetMaxValue");

	USpinBox_SetMaxValue_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.SetMaxSliderValue
// ()
// Parameters:
// float                          NewValue                       (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::SetMaxSliderValue(float NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.SetMaxSliderValue");

	USpinBox_SetMaxSliderValue_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.SetForegroundColor
// ()
// Parameters:
// struct FSlateColor             InForegroundColor              (Parm)

void USpinBox::SetForegroundColor(const struct FSlateColor& InForegroundColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.SetForegroundColor");

	USpinBox_SetForegroundColor_Params params;
	params.InForegroundColor = InForegroundColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.SpinBox.OnSpinBoxValueCommittedEvent__DelegateSignature
// ()
// Parameters:
// float                          InValue                        (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ETextCommit>       CommitMethod                   (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::OnSpinBoxValueCommittedEvent__DelegateSignature(float InValue, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.SpinBox.OnSpinBoxValueCommittedEvent__DelegateSignature");

	USpinBox_OnSpinBoxValueCommittedEvent__DelegateSignature_Params params;
	params.InValue = InValue;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.SpinBox.OnSpinBoxValueChangedEvent__DelegateSignature
// ()
// Parameters:
// float                          InValue                        (Parm, ZeroConstructor, IsPlainOldData)

void USpinBox::OnSpinBoxValueChangedEvent__DelegateSignature(float InValue)
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.SpinBox.OnSpinBoxValueChangedEvent__DelegateSignature");

	USpinBox_OnSpinBoxValueChangedEvent__DelegateSignature_Params params;
	params.InValue = InValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// DelegateFunction UMG.SpinBox.OnSpinBoxBeginSliderMovement__DelegateSignature
// ()

void USpinBox::OnSpinBoxBeginSliderMovement__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.SpinBox.OnSpinBoxBeginSliderMovement__DelegateSignature");

	USpinBox_OnSpinBoxBeginSliderMovement__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.GetValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float USpinBox::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.GetValue");

	USpinBox_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SpinBox.GetMinValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float USpinBox::GetMinValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.GetMinValue");

	USpinBox_GetMinValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SpinBox.GetMinSliderValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float USpinBox::GetMinSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.GetMinSliderValue");

	USpinBox_GetMinSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SpinBox.GetMaxValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float USpinBox::GetMaxValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.GetMaxValue");

	USpinBox_GetMaxValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SpinBox.GetMaxSliderValue
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float USpinBox::GetMaxSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.GetMaxSliderValue");

	USpinBox_GetMaxSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.SpinBox.ClearMinValue
// ()

void USpinBox::ClearMinValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.ClearMinValue");

	USpinBox_ClearMinValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.ClearMinSliderValue
// ()

void USpinBox::ClearMinSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.ClearMinSliderValue");

	USpinBox_ClearMinSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.ClearMaxValue
// ()

void USpinBox::ClearMaxValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.ClearMaxValue");

	USpinBox_ClearMaxValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.SpinBox.ClearMaxSliderValue
// ()

void USpinBox::ClearMaxSliderValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.SpinBox.ClearMaxSliderValue");

	USpinBox_ClearMaxSliderValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBinding.GetTextValue
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UTextBinding::GetTextValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBinding.GetTextValue");

	UTextBinding_GetTextValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.TextBinding.GetStringValue
// ()
// Parameters:
// class FString                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm)

class FString UTextBinding::GetStringValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBinding.GetStringValue");

	UTextBinding_GetStringValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.TextBlock.SetText
// ()
// Parameters:
// struct FText                   InText                         (Parm)

void UTextBlock::SetText(const struct FText& InText)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetText");

	UTextBlock_SetText_Params params;
	params.InText = InText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetShadowOffset
// ()
// Parameters:
// struct FVector2D               InShadowOffset                 (Parm, ZeroConstructor, IsPlainOldData)

void UTextBlock::SetShadowOffset(const struct FVector2D& InShadowOffset)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetShadowOffset");

	UTextBlock_SetShadowOffset_Params params;
	params.InShadowOffset = InShadowOffset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetShadowColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            InShadowColorAndOpacity        (Parm, ZeroConstructor, IsPlainOldData)

void UTextBlock::SetShadowColorAndOpacity(const struct FLinearColor& InShadowColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetShadowColorAndOpacity");

	UTextBlock_SetShadowColorAndOpacity_Params params;
	params.InShadowColorAndOpacity = InShadowColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetOpacity
// ()
// Parameters:
// float                          InOpacity                      (Parm, ZeroConstructor, IsPlainOldData)

void UTextBlock::SetOpacity(float InOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetOpacity");

	UTextBlock_SetOpacity_Params params;
	params.InOpacity = InOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetMinDesiredWidth
// ()
// Parameters:
// float                          InMinDesiredWidth              (Parm, ZeroConstructor, IsPlainOldData)

void UTextBlock::SetMinDesiredWidth(float InMinDesiredWidth)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetMinDesiredWidth");

	UTextBlock_SetMinDesiredWidth_Params params;
	params.InMinDesiredWidth = InMinDesiredWidth;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetJustification
// ()
// Parameters:
// TEnumAsByte<ETextJustify>      InJustification                (Parm, ZeroConstructor, IsPlainOldData)

void UTextBlock::SetJustification(TEnumAsByte<ETextJustify> InJustification)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetJustification");

	UTextBlock_SetJustification_Params params;
	params.InJustification = InJustification;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetFont
// ()
// Parameters:
// struct FSlateFontInfo          InFontInfo                     (Parm)

void UTextBlock::SetFont(const struct FSlateFontInfo& InFontInfo)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetFont");

	UTextBlock_SetFont_Params params;
	params.InFontInfo = InFontInfo;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetColorAndOpacity
// ()
// Parameters:
// struct FSlateColor             InColorAndOpacity              (Parm)

void UTextBlock::SetColorAndOpacity(const struct FSlateColor& InColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetColorAndOpacity");

	UTextBlock_SetColorAndOpacity_Params params;
	params.InColorAndOpacity = InColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.SetAutoWrapText
// ()
// Parameters:
// bool                           InAutoTextWrap                 (Parm, ZeroConstructor, IsPlainOldData)

void UTextBlock::SetAutoWrapText(bool InAutoTextWrap)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.SetAutoWrapText");

	UTextBlock_SetAutoWrapText_Params params;
	params.InAutoTextWrap = InAutoTextWrap;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TextBlock.GetText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UTextBlock::GetText()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.GetText");

	UTextBlock_GetText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.TextBlock.GetDynamicOutlineMaterial
// ()
// Parameters:
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* UTextBlock::GetDynamicOutlineMaterial()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.GetDynamicOutlineMaterial");

	UTextBlock_GetDynamicOutlineMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.TextBlock.GetDynamicFontMaterial
// ()
// Parameters:
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* UTextBlock::GetDynamicFontMaterial()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TextBlock.GetDynamicFontMaterial");

	UTextBlock_GetDynamicFontMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Throbber.SetNumberOfPieces
// ()
// Parameters:
// int                            InNumberOfPieces               (Parm, ZeroConstructor, IsPlainOldData)

void UThrobber::SetNumberOfPieces(int InNumberOfPieces)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Throbber.SetNumberOfPieces");

	UThrobber_SetNumberOfPieces_Params params;
	params.InNumberOfPieces = InNumberOfPieces;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Throbber.SetAnimateVertically
// ()
// Parameters:
// bool                           bInAnimateVertically           (Parm, ZeroConstructor, IsPlainOldData)

void UThrobber::SetAnimateVertically(bool bInAnimateVertically)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Throbber.SetAnimateVertically");

	UThrobber_SetAnimateVertically_Params params;
	params.bInAnimateVertically = bInAnimateVertically;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Throbber.SetAnimateOpacity
// ()
// Parameters:
// bool                           bInAnimateOpacity              (Parm, ZeroConstructor, IsPlainOldData)

void UThrobber::SetAnimateOpacity(bool bInAnimateOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Throbber.SetAnimateOpacity");

	UThrobber_SetAnimateOpacity_Params params;
	params.bInAnimateOpacity = bInAnimateOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Throbber.SetAnimateHorizontally
// ()
// Parameters:
// bool                           bInAnimateHorizontally         (Parm, ZeroConstructor, IsPlainOldData)

void UThrobber::SetAnimateHorizontally(bool bInAnimateHorizontally)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Throbber.SetAnimateHorizontally");

	UThrobber_SetAnimateHorizontally_Params params;
	params.bInAnimateHorizontally = bInAnimateHorizontally;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TileView.SetEntryWidth
// ()
// Parameters:
// float                          NewWidth                       (Parm, ZeroConstructor, IsPlainOldData)

void UTileView::SetEntryWidth(float NewWidth)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TileView.SetEntryWidth");

	UTileView_SetEntryWidth_Params params;
	params.NewWidth = NewWidth;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TileView.SetEntryHeight
// ()
// Parameters:
// float                          NewHeight                      (Parm, ZeroConstructor, IsPlainOldData)

void UTileView::SetEntryHeight(float NewHeight)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TileView.SetEntryHeight");

	UTileView_SetEntryHeight_Params params;
	params.NewHeight = NewHeight;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TreeView.SetItemExpansion
// ()
// Parameters:
// class UObject*                 Item                           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bExpandItem                    (Parm, ZeroConstructor, IsPlainOldData)

void UTreeView::SetItemExpansion(class UObject* Item, bool bExpandItem)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TreeView.SetItemExpansion");

	UTreeView_SetItemExpansion_Params params;
	params.Item = Item;
	params.bExpandItem = bExpandItem;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TreeView.ExpandAll
// ()

void UTreeView::ExpandAll()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TreeView.ExpandAll");

	UTreeView_ExpandAll_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.TreeView.CollapseAll
// ()

void UTreeView::CollapseAll()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.TreeView.CollapseAll");

	UTreeView_CollapseAll_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridPanel.SetSlotPadding
// ()
// Parameters:
// struct FMargin                 InSlotPadding                  (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridPanel::SetSlotPadding(const struct FMargin& InSlotPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridPanel.SetSlotPadding");

	UUniformGridPanel_SetSlotPadding_Params params;
	params.InSlotPadding = InSlotPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridPanel.SetMinDesiredSlotWidth
// ()
// Parameters:
// float                          InMinDesiredSlotWidth          (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridPanel::SetMinDesiredSlotWidth(float InMinDesiredSlotWidth)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridPanel.SetMinDesiredSlotWidth");

	UUniformGridPanel_SetMinDesiredSlotWidth_Params params;
	params.InMinDesiredSlotWidth = InMinDesiredSlotWidth;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridPanel.SetMinDesiredSlotHeight
// ()
// Parameters:
// float                          InMinDesiredSlotHeight         (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridPanel::SetMinDesiredSlotHeight(float InMinDesiredSlotHeight)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridPanel.SetMinDesiredSlotHeight");

	UUniformGridPanel_SetMinDesiredSlotHeight_Params params;
	params.InMinDesiredSlotHeight = InMinDesiredSlotHeight;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridPanel.AddChildToUniformGrid
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UUniformGridSlot*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UUniformGridSlot* UUniformGridPanel::AddChildToUniformGrid(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridPanel.AddChildToUniformGrid");

	UUniformGridPanel_AddChildToUniformGrid_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.UniformGridSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridSlot.SetVerticalAlignment");

	UUniformGridSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridSlot.SetRow
// ()
// Parameters:
// int                            InRow                          (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridSlot::SetRow(int InRow)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridSlot.SetRow");

	UUniformGridSlot_SetRow_Params params;
	params.InRow = InRow;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridSlot.SetHorizontalAlignment");

	UUniformGridSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.UniformGridSlot.SetColumn
// ()
// Parameters:
// int                            InColumn                       (Parm, ZeroConstructor, IsPlainOldData)

void UUniformGridSlot::SetColumn(int InColumn)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.UniformGridSlot.SetColumn");

	UUniformGridSlot_SetColumn_Params params;
	params.InColumn = InColumn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.VerticalBoxSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UVerticalBoxSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.VerticalBoxSlot.SetVerticalAlignment");

	UVerticalBoxSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.VerticalBoxSlot.SetSize
// ()
// Parameters:
// struct FSlateChildSize         InSize                         (Parm)

void UVerticalBoxSlot::SetSize(const struct FSlateChildSize& InSize)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.VerticalBoxSlot.SetSize");

	UVerticalBoxSlot_SetSize_Params params;
	params.InSize = InSize;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.VerticalBoxSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UVerticalBoxSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.VerticalBoxSlot.SetPadding");

	UVerticalBoxSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.VerticalBoxSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UVerticalBoxSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.VerticalBoxSlot.SetHorizontalAlignment");

	UVerticalBoxSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Viewport.Spawn
// ()
// Parameters:
// class UClass*                  ActorClass                     (Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class AActor* UViewport::Spawn(class UClass* ActorClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Viewport.Spawn");

	UViewport_Spawn_Params params;
	params.ActorClass = ActorClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Viewport.SetViewRotation
// ()
// Parameters:
// struct FRotator                Rotation                       (Parm, ZeroConstructor, IsPlainOldData)

void UViewport::SetViewRotation(const struct FRotator& Rotation)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Viewport.SetViewRotation");

	UViewport_SetViewRotation_Params params;
	params.Rotation = Rotation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Viewport.SetViewLocation
// ()
// Parameters:
// struct FVector                 Location                       (Parm, ZeroConstructor, IsPlainOldData)

void UViewport::SetViewLocation(const struct FVector& Location)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Viewport.SetViewLocation");

	UViewport_SetViewLocation_Params params;
	params.Location = Location;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.Viewport.GetViewRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator UViewport::GetViewRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Viewport.GetViewRotation");

	UViewport_GetViewRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Viewport.GetViewportWorld
// ()
// Parameters:
// class UWorld*                  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UWorld* UViewport::GetViewportWorld()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Viewport.GetViewportWorld");

	UViewport_GetViewportWorld_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.Viewport.GetViewLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector UViewport::GetViewLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.Viewport.GetViewLocation");

	UViewport_GetViewLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.VisibilityBinding.GetValue
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UVisibilityBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.VisibilityBinding.GetValue");

	UVisibilityBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetAnimation.GetStartTime
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidgetAnimation::GetStartTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetAnimation.GetStartTime");

	UWidgetAnimation_GetStartTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetAnimation.GetEndTime
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidgetAnimation::GetEndTime()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetAnimation.GetEndTime");

	UWidgetAnimation_GetEndTime_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBinding.GetValue
// ()
// Parameters:
// class UWidget*                 ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidget* UWidgetBinding::GetValue()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBinding.GetValue");

	UWidgetBinding_GetValue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.UnlockMouse
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::UnlockMouse(struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.UnlockMouse");

	UWidgetBlueprintLibrary_UnlockMouse_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.Unhandled
// ()
// Parameters:
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::Unhandled()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.Unhandled");

	UWidgetBlueprintLibrary_Unhandled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.SetWindowTitleBarState
// ()
// Parameters:
// class UWidget*                 TitleBarContent                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// EWindowTitleBarMode            Mode                           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bTitleBarDragEnabled           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bWindowButtonsVisible          (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bTitleBarVisible               (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetWindowTitleBarState(class UWidget* TitleBarContent, EWindowTitleBarMode Mode, bool bTitleBarDragEnabled, bool bWindowButtonsVisible, bool bTitleBarVisible)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetWindowTitleBarState");

	UWidgetBlueprintLibrary_SetWindowTitleBarState_Params params;
	params.TitleBarContent = TitleBarContent;
	params.Mode = Mode;
	params.bTitleBarDragEnabled = bTitleBarDragEnabled;
	params.bWindowButtonsVisible = bWindowButtonsVisible;
	params.bTitleBarVisible = bTitleBarVisible;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetWindowTitleBarOnCloseClickedDelegate
// ()
// Parameters:
// struct FScriptDelegate         Delegate                       (Parm, ZeroConstructor)

void UWidgetBlueprintLibrary::SetWindowTitleBarOnCloseClickedDelegate(const struct FScriptDelegate& Delegate)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetWindowTitleBarOnCloseClickedDelegate");

	UWidgetBlueprintLibrary_SetWindowTitleBarOnCloseClickedDelegate_Params params;
	params.Delegate = Delegate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetWindowTitleBarCloseButtonActive
// ()
// Parameters:
// bool                           bActive                        (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetWindowTitleBarCloseButtonActive(bool bActive)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetWindowTitleBarCloseButtonActive");

	UWidgetBlueprintLibrary_SetWindowTitleBarCloseButtonActive_Params params;
	params.bActive = bActive;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetUserFocus
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// class UWidget*                 FocusWidget                    (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           bInAllUsers                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::SetUserFocus(class UWidget* FocusWidget, bool bInAllUsers, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetUserFocus");

	UWidgetBlueprintLibrary_SetUserFocus_Params params;
	params.FocusWidget = FocusWidget;
	params.bInAllUsers = bInAllUsers;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.SetMousePosition
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// struct FVector2D               NewMousePosition               (Parm, ZeroConstructor, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::SetMousePosition(const struct FVector2D& NewMousePosition, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetMousePosition");

	UWidgetBlueprintLibrary_SetMousePosition_Params params;
	params.NewMousePosition = NewMousePosition;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.SetInputMode_UIOnlyEx
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 InWidgetToFocus                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// EMouseLockMode                 InMouseLockMode                (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(class APlayerController* PlayerController, class UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetInputMode_UIOnlyEx");

	UWidgetBlueprintLibrary_SetInputMode_UIOnlyEx_Params params;
	params.PlayerController = PlayerController;
	params.InWidgetToFocus = InWidgetToFocus;
	params.InMouseLockMode = InMouseLockMode;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetInputMode_UIOnly
// ()
// Parameters:
// class APlayerController*       Target                         (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 InWidgetToFocus                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           bLockMouseToViewport           (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetInputMode_UIOnly(class APlayerController* Target, class UWidget* InWidgetToFocus, bool bLockMouseToViewport)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetInputMode_UIOnly");

	UWidgetBlueprintLibrary_SetInputMode_UIOnly_Params params;
	params.Target = Target;
	params.InWidgetToFocus = InWidgetToFocus;
	params.bLockMouseToViewport = bLockMouseToViewport;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetInputMode_GameOnly
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetInputMode_GameOnly(class APlayerController* PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetInputMode_GameOnly");

	UWidgetBlueprintLibrary_SetInputMode_GameOnly_Params params;
	params.PlayerController = PlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetInputMode_GameAndUIEx
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 InWidgetToFocus                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// EMouseLockMode                 InMouseLockMode                (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bHideCursorDuringCapture       (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(class APlayerController* PlayerController, class UWidget* InWidgetToFocus, EMouseLockMode InMouseLockMode, bool bHideCursorDuringCapture)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetInputMode_GameAndUIEx");

	UWidgetBlueprintLibrary_SetInputMode_GameAndUIEx_Params params;
	params.PlayerController = PlayerController;
	params.InWidgetToFocus = InWidgetToFocus;
	params.InMouseLockMode = InMouseLockMode;
	params.bHideCursorDuringCapture = bHideCursorDuringCapture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetInputMode_GameAndUI
// ()
// Parameters:
// class APlayerController*       Target                         (Parm, ZeroConstructor, IsPlainOldData)
// class UWidget*                 InWidgetToFocus                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           bLockMouseToViewport           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bHideCursorDuringCapture       (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetInputMode_GameAndUI(class APlayerController* Target, class UWidget* InWidgetToFocus, bool bLockMouseToViewport, bool bHideCursorDuringCapture)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetInputMode_GameAndUI");

	UWidgetBlueprintLibrary_SetInputMode_GameAndUI_Params params;
	params.Target = Target;
	params.InWidgetToFocus = InWidgetToFocus;
	params.bLockMouseToViewport = bLockMouseToViewport;
	params.bHideCursorDuringCapture = bHideCursorDuringCapture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetHardwareCursor
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<EMouseCursor>      CursorShape                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   CursorName                     (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               HotSpot                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetBlueprintLibrary::SetHardwareCursor(class UObject* WorldContextObject, TEnumAsByte<EMouseCursor> CursorShape, const struct FName& CursorName, const struct FVector2D& HotSpot)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetHardwareCursor");

	UWidgetBlueprintLibrary_SetHardwareCursor_Params params;
	params.WorldContextObject = WorldContextObject;
	params.CursorShape = CursorShape;
	params.CursorName = CursorName;
	params.HotSpot = HotSpot;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.SetFocusToGameViewport
// ()

void UWidgetBlueprintLibrary::SetFocusToGameViewport()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetFocusToGameViewport");

	UWidgetBlueprintLibrary_SetFocusToGameViewport_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.SetBrushResourceToTexture
// ()
// Parameters:
// struct FSlateBrush             Brush                          (Parm, OutParm, ReferenceParm)
// class UTexture2D*              Texture                        (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetBrushResourceToTexture(class UTexture2D* Texture, struct FSlateBrush* Brush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetBrushResourceToTexture");

	UWidgetBlueprintLibrary_SetBrushResourceToTexture_Params params;
	params.Texture = Texture;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Brush != nullptr)
		*Brush = params.Brush;
}


// Function UMG.WidgetBlueprintLibrary.SetBrushResourceToMaterial
// ()
// Parameters:
// struct FSlateBrush             Brush                          (Parm, OutParm, ReferenceParm)
// class UMaterialInterface*      Material                       (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::SetBrushResourceToMaterial(class UMaterialInterface* Material, struct FSlateBrush* Brush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.SetBrushResourceToMaterial");

	UWidgetBlueprintLibrary_SetBrushResourceToMaterial_Params params;
	params.Material = Material;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Brush != nullptr)
		*Brush = params.Brush;
}


// Function UMG.WidgetBlueprintLibrary.RestorePreviousWindowTitleBarState
// ()

void UWidgetBlueprintLibrary::RestorePreviousWindowTitleBarState()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.RestorePreviousWindowTitleBarState");

	UWidgetBlueprintLibrary_RestorePreviousWindowTitleBarState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.ReleaseMouseCapture
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::ReleaseMouseCapture(struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.ReleaseMouseCapture");

	UWidgetBlueprintLibrary_ReleaseMouseCapture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.ReleaseJoystickCapture
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// bool                           bInAllJoysticks                (Parm, ZeroConstructor, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::ReleaseJoystickCapture(bool bInAllJoysticks, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.ReleaseJoystickCapture");

	UWidgetBlueprintLibrary_ReleaseJoystickCapture_Params params;
	params.bInAllJoysticks = bInAllJoysticks;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// DelegateFunction UMG.WidgetBlueprintLibrary.OnGameWindowCloseButtonClickedDelegate__DelegateSignature
// ()

void UWidgetBlueprintLibrary::OnGameWindowCloseButtonClickedDelegate__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("DelegateFunction UMG.WidgetBlueprintLibrary.OnGameWindowCloseButtonClickedDelegate__DelegateSignature");

	UWidgetBlueprintLibrary_OnGameWindowCloseButtonClickedDelegate__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.NoResourceBrush
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidgetBlueprintLibrary::NoResourceBrush()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.NoResourceBrush");

	UWidgetBlueprintLibrary_NoResourceBrush_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.MakeBrushFromTexture
// ()
// Parameters:
// class UTexture2D*              Texture                        (Parm, ZeroConstructor, IsPlainOldData)
// int                            Width                          (Parm, ZeroConstructor, IsPlainOldData)
// int                            Height                         (Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidgetBlueprintLibrary::MakeBrushFromTexture(class UTexture2D* Texture, int Width, int Height)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.MakeBrushFromTexture");

	UWidgetBlueprintLibrary_MakeBrushFromTexture_Params params;
	params.Texture = Texture;
	params.Width = Width;
	params.Height = Height;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.MakeBrushFromMaterial
// ()
// Parameters:
// class UMaterialInterface*      Material                       (Parm, ZeroConstructor, IsPlainOldData)
// int                            Width                          (Parm, ZeroConstructor, IsPlainOldData)
// int                            Height                         (Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidgetBlueprintLibrary::MakeBrushFromMaterial(class UMaterialInterface* Material, int Width, int Height)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.MakeBrushFromMaterial");

	UWidgetBlueprintLibrary_MakeBrushFromMaterial_Params params;
	params.Material = Material;
	params.Width = Width;
	params.Height = Height;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.MakeBrushFromAsset
// ()
// Parameters:
// class USlateBrushAsset*        BrushAsset                     (Parm, ZeroConstructor, IsPlainOldData)
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidgetBlueprintLibrary::MakeBrushFromAsset(class USlateBrushAsset* BrushAsset)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.MakeBrushFromAsset");

	UWidgetBlueprintLibrary_MakeBrushFromAsset_Params params;
	params.BrushAsset = BrushAsset;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.LockMouse
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// class UWidget*                 CapturingWidget                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::LockMouse(class UWidget* CapturingWidget, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.LockMouse");

	UWidgetBlueprintLibrary_LockMouse_Params params;
	params.CapturingWidget = CapturingWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.IsDragDropping
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetBlueprintLibrary::IsDragDropping()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.IsDragDropping");

	UWidgetBlueprintLibrary_IsDragDropping_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.Handled
// ()
// Parameters:
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::Handled()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.Handled");

	UWidgetBlueprintLibrary_Handled_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetSafeZonePadding
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector4                SafePadding                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               SafePaddingScale               (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FVector4                SpillOverPadding               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::GetSafeZonePadding(class UObject* WorldContextObject, struct FVector4* SafePadding, struct FVector2D* SafePaddingScale, struct FVector4* SpillOverPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetSafeZonePadding");

	UWidgetBlueprintLibrary_GetSafeZonePadding_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (SafePadding != nullptr)
		*SafePadding = params.SafePadding;
	if (SafePaddingScale != nullptr)
		*SafePaddingScale = params.SafePaddingScale;
	if (SpillOverPadding != nullptr)
		*SpillOverPadding = params.SpillOverPadding;
}


// Function UMG.WidgetBlueprintLibrary.GetKeyEventFromAnalogInputEvent
// ()
// Parameters:
// struct FAnalogInputEvent       Event                          (ConstParm, Parm, OutParm, ReferenceParm)
// struct FKeyEvent               ReturnValue                    (Parm, OutParm, ReturnParm)

struct FKeyEvent UWidgetBlueprintLibrary::GetKeyEventFromAnalogInputEvent(const struct FAnalogInputEvent& Event)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetKeyEventFromAnalogInputEvent");

	UWidgetBlueprintLibrary_GetKeyEventFromAnalogInputEvent_Params params;
	params.Event = Event;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetInputEventFromPointerEvent
// ()
// Parameters:
// struct FPointerEvent           Event                          (ConstParm, Parm, OutParm, ReferenceParm)
// struct FInputEvent             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FInputEvent UWidgetBlueprintLibrary::GetInputEventFromPointerEvent(const struct FPointerEvent& Event)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetInputEventFromPointerEvent");

	UWidgetBlueprintLibrary_GetInputEventFromPointerEvent_Params params;
	params.Event = Event;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetInputEventFromNavigationEvent
// ()
// Parameters:
// struct FNavigationEvent        Event                          (ConstParm, Parm, OutParm, ReferenceParm)
// struct FInputEvent             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FInputEvent UWidgetBlueprintLibrary::GetInputEventFromNavigationEvent(const struct FNavigationEvent& Event)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetInputEventFromNavigationEvent");

	UWidgetBlueprintLibrary_GetInputEventFromNavigationEvent_Params params;
	params.Event = Event;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetInputEventFromKeyEvent
// ()
// Parameters:
// struct FKeyEvent               Event                          (ConstParm, Parm, OutParm, ReferenceParm)
// struct FInputEvent             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FInputEvent UWidgetBlueprintLibrary::GetInputEventFromKeyEvent(const struct FKeyEvent& Event)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetInputEventFromKeyEvent");

	UWidgetBlueprintLibrary_GetInputEventFromKeyEvent_Params params;
	params.Event = Event;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetInputEventFromCharacterEvent
// ()
// Parameters:
// struct FCharacterEvent         Event                          (ConstParm, Parm, OutParm, ReferenceParm)
// struct FInputEvent             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FInputEvent UWidgetBlueprintLibrary::GetInputEventFromCharacterEvent(const struct FCharacterEvent& Event)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetInputEventFromCharacterEvent");

	UWidgetBlueprintLibrary_GetInputEventFromCharacterEvent_Params params;
	params.Event = Event;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetDynamicMaterial
// ()
// Parameters:
// struct FSlateBrush             Brush                          (Parm, OutParm, ReferenceParm)
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* UWidgetBlueprintLibrary::GetDynamicMaterial(struct FSlateBrush* Brush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetDynamicMaterial");

	UWidgetBlueprintLibrary_GetDynamicMaterial_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Brush != nullptr)
		*Brush = params.Brush;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetDragDroppingContent
// ()
// Parameters:
// class UDragDropOperation*      ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UDragDropOperation* UWidgetBlueprintLibrary::GetDragDroppingContent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetDragDroppingContent");

	UWidgetBlueprintLibrary_GetDragDroppingContent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetBrushResourceAsTexture2D
// ()
// Parameters:
// struct FSlateBrush             Brush                          (ConstParm, Parm, OutParm, ReferenceParm)
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(const struct FSlateBrush& Brush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetBrushResourceAsTexture2D");

	UWidgetBlueprintLibrary_GetBrushResourceAsTexture2D_Params params;
	params.Brush = Brush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetBrushResourceAsMaterial
// ()
// Parameters:
// struct FSlateBrush             Brush                          (ConstParm, Parm, OutParm, ReferenceParm)
// class UMaterialInterface*      ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInterface* UWidgetBlueprintLibrary::GetBrushResourceAsMaterial(const struct FSlateBrush& Brush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetBrushResourceAsMaterial");

	UWidgetBlueprintLibrary_GetBrushResourceAsMaterial_Params params;
	params.Brush = Brush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetBrushResource
// ()
// Parameters:
// struct FSlateBrush             Brush                          (ConstParm, Parm, OutParm, ReferenceParm)
// class UObject*                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UObject* UWidgetBlueprintLibrary::GetBrushResource(const struct FSlateBrush& Brush)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetBrushResource");

	UWidgetBlueprintLibrary_GetBrushResource_Params params;
	params.Brush = Brush;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.GetAllWidgetsWithInterface
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  Interface                      (Parm, ZeroConstructor, IsPlainOldData)
// TArray<class UUserWidget*>     FoundWidgets                   (Parm, OutParm, ZeroConstructor)
// bool                           TopLevelOnly                   (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(class UObject* WorldContextObject, class UClass* Interface, bool TopLevelOnly, TArray<class UUserWidget*>* FoundWidgets)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetAllWidgetsWithInterface");

	UWidgetBlueprintLibrary_GetAllWidgetsWithInterface_Params params;
	params.WorldContextObject = WorldContextObject;
	params.Interface = Interface;
	params.TopLevelOnly = TopLevelOnly;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (FoundWidgets != nullptr)
		*FoundWidgets = params.FoundWidgets;
}


// Function UMG.WidgetBlueprintLibrary.GetAllWidgetsOfClass
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// TArray<class UUserWidget*>     FoundWidgets                   (Parm, OutParm, ZeroConstructor)
// class UClass*                  WidgetClass                    (Parm, ZeroConstructor, IsPlainOldData)
// bool                           TopLevelOnly                   (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::GetAllWidgetsOfClass(class UObject* WorldContextObject, class UClass* WidgetClass, bool TopLevelOnly, TArray<class UUserWidget*>* FoundWidgets)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.GetAllWidgetsOfClass");

	UWidgetBlueprintLibrary_GetAllWidgetsOfClass_Params params;
	params.WorldContextObject = WorldContextObject;
	params.WidgetClass = WidgetClass;
	params.TopLevelOnly = TopLevelOnly;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (FoundWidgets != nullptr)
		*FoundWidgets = params.FoundWidgets;
}


// Function UMG.WidgetBlueprintLibrary.EndDragDrop
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::EndDragDrop(struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.EndDragDrop");

	UWidgetBlueprintLibrary_EndDragDrop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.DrawTextFormatted
// ()
// Parameters:
// struct FPaintContext           Context                        (Parm, OutParm, ReferenceParm)
// struct FText                   Text                           (ConstParm, Parm, OutParm, ReferenceParm)
// struct FVector2D               Position                       (Parm, ZeroConstructor, IsPlainOldData)
// class UFont*                   Font                           (Parm, ZeroConstructor, IsPlainOldData)
// int                            FontSize                       (Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   FontTypeFace                   (Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            Tint                           (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::DrawTextFormatted(const struct FText& Text, const struct FVector2D& Position, class UFont* Font, int FontSize, const struct FName& FontTypeFace, const struct FLinearColor& Tint, struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DrawTextFormatted");

	UWidgetBlueprintLibrary_DrawTextFormatted_Params params;
	params.Text = Text;
	params.Position = Position;
	params.Font = Font;
	params.FontSize = FontSize;
	params.FontTypeFace = FontTypeFace;
	params.Tint = Tint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function UMG.WidgetBlueprintLibrary.DrawText
// ()
// Parameters:
// struct FPaintContext           Context                        (Parm, OutParm, ReferenceParm)
// class FString                  inString                       (Parm, ZeroConstructor)
// struct FVector2D               Position                       (Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            Tint                           (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::DrawText(const class FString& inString, const struct FVector2D& Position, const struct FLinearColor& Tint, struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DrawText");

	UWidgetBlueprintLibrary_DrawText_Params params;
	params.inString = inString;
	params.Position = Position;
	params.Tint = Tint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function UMG.WidgetBlueprintLibrary.DrawLines
// ()
// Parameters:
// struct FPaintContext           Context                        (Parm, OutParm, ReferenceParm)
// TArray<struct FVector2D>       Points                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
// struct FLinearColor            Tint                           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bAntiAlias                     (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::DrawLines(TArray<struct FVector2D> Points, const struct FLinearColor& Tint, bool bAntiAlias, struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DrawLines");

	UWidgetBlueprintLibrary_DrawLines_Params params;
	params.Points = Points;
	params.Tint = Tint;
	params.bAntiAlias = bAntiAlias;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function UMG.WidgetBlueprintLibrary.DrawLine
// ()
// Parameters:
// struct FPaintContext           Context                        (Parm, OutParm, ReferenceParm)
// struct FVector2D               PositionA                      (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               PositionB                      (Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            Tint                           (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bAntiAlias                     (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::DrawLine(const struct FVector2D& PositionA, const struct FVector2D& PositionB, const struct FLinearColor& Tint, bool bAntiAlias, struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DrawLine");

	UWidgetBlueprintLibrary_DrawLine_Params params;
	params.PositionA = PositionA;
	params.PositionB = PositionB;
	params.Tint = Tint;
	params.bAntiAlias = bAntiAlias;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function UMG.WidgetBlueprintLibrary.DrawBox
// ()
// Parameters:
// struct FPaintContext           Context                        (Parm, OutParm, ReferenceParm)
// struct FVector2D               Position                       (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               Size                           (Parm, ZeroConstructor, IsPlainOldData)
// class USlateBrushAsset*        Brush                          (Parm, ZeroConstructor, IsPlainOldData)
// struct FLinearColor            Tint                           (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetBlueprintLibrary::DrawBox(const struct FVector2D& Position, const struct FVector2D& Size, class USlateBrushAsset* Brush, const struct FLinearColor& Tint, struct FPaintContext* Context)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DrawBox");

	UWidgetBlueprintLibrary_DrawBox_Params params;
	params.Position = Position;
	params.Size = Size;
	params.Brush = Brush;
	params.Tint = Tint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Context != nullptr)
		*Context = params.Context;
}


// Function UMG.WidgetBlueprintLibrary.DismissAllMenus
// ()

void UWidgetBlueprintLibrary::DismissAllMenus()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DismissAllMenus");

	UWidgetBlueprintLibrary_DismissAllMenus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetBlueprintLibrary.DetectDragIfPressed
// ()
// Parameters:
// struct FPointerEvent           PointerEvent                   (ConstParm, Parm, OutParm, ReferenceParm)
// class UWidget*                 WidgetDetectingDrag            (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FKey                    DragKey                        (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::DetectDragIfPressed(const struct FPointerEvent& PointerEvent, class UWidget* WidgetDetectingDrag, const struct FKey& DragKey)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DetectDragIfPressed");

	UWidgetBlueprintLibrary_DetectDragIfPressed_Params params;
	params.PointerEvent = PointerEvent;
	params.WidgetDetectingDrag = WidgetDetectingDrag;
	params.DragKey = DragKey;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.DetectDrag
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// class UWidget*                 WidgetDetectingDrag            (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FKey                    DragKey                        (Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::DetectDrag(class UWidget* WidgetDetectingDrag, const struct FKey& DragKey, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.DetectDrag");

	UWidgetBlueprintLibrary_DetectDrag_Params params;
	params.WidgetDetectingDrag = WidgetDetectingDrag;
	params.DragKey = DragKey;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.CreateDragDropOperation
// ()
// Parameters:
// class UClass*                  OperationClass                 (Parm, ZeroConstructor, IsPlainOldData)
// class UDragDropOperation*      ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UDragDropOperation* UWidgetBlueprintLibrary::CreateDragDropOperation(class UClass* OperationClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.CreateDragDropOperation");

	UWidgetBlueprintLibrary_CreateDragDropOperation_Params params;
	params.OperationClass = OperationClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.Create
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  WidgetType                     (Parm, ZeroConstructor, IsPlainOldData)
// class APlayerController*       OwningPlayer                   (Parm, ZeroConstructor, IsPlainOldData)
// class UUserWidget*             ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UUserWidget* UWidgetBlueprintLibrary::Create(class UObject* WorldContextObject, class UClass* WidgetType, class APlayerController* OwningPlayer)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.Create");

	UWidgetBlueprintLibrary_Create_Params params;
	params.WorldContextObject = WorldContextObject;
	params.WidgetType = WidgetType;
	params.OwningPlayer = OwningPlayer;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.ClearUserFocus
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// bool                           bInAllUsers                    (Parm, ZeroConstructor, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::ClearUserFocus(bool bInAllUsers, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.ClearUserFocus");

	UWidgetBlueprintLibrary_ClearUserFocus_Params params;
	params.bInAllUsers = bInAllUsers;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.CaptureMouse
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// class UWidget*                 CapturingWidget                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::CaptureMouse(class UWidget* CapturingWidget, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.CaptureMouse");

	UWidgetBlueprintLibrary_CaptureMouse_Params params;
	params.CapturingWidget = CapturingWidget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.CaptureJoystick
// ()
// Parameters:
// struct FEventReply             Reply                          (Parm, OutParm, ReferenceParm)
// class UWidget*                 CapturingWidget                (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool                           bInAllJoysticks                (Parm, ZeroConstructor, IsPlainOldData)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidgetBlueprintLibrary::CaptureJoystick(class UWidget* CapturingWidget, bool bInAllJoysticks, struct FEventReply* Reply)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.CaptureJoystick");

	UWidgetBlueprintLibrary_CaptureJoystick_Params params;
	params.CapturingWidget = CapturingWidget;
	params.bInAllJoysticks = bInAllJoysticks;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Reply != nullptr)
		*Reply = params.Reply;

	return params.ReturnValue;
}


// Function UMG.WidgetBlueprintLibrary.CancelDragDrop
// ()

void UWidgetBlueprintLibrary::CancelDragDrop()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetBlueprintLibrary.CancelDragDrop");

	UWidgetBlueprintLibrary_CancelDragDrop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.SetWidget
// ()
// Parameters:
// class UUserWidget*             Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidgetComponent::SetWidget(class UUserWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.SetWidget");

	UWidgetComponent_SetWidget_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.SetTintColorAndOpacity
// ()
// Parameters:
// struct FLinearColor            NewTintColorAndOpacity         (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UWidgetComponent::SetTintColorAndOpacity(const struct FLinearColor& NewTintColorAndOpacity)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.SetTintColorAndOpacity");

	UWidgetComponent_SetTintColorAndOpacity_Params params;
	params.NewTintColorAndOpacity = NewTintColorAndOpacity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.SetOwnerPlayer
// ()
// Parameters:
// class ULocalPlayer*            LocalPlayer                    (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetComponent::SetOwnerPlayer(class ULocalPlayer* LocalPlayer)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.SetOwnerPlayer");

	UWidgetComponent_SetOwnerPlayer_Params params;
	params.LocalPlayer = LocalPlayer;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.SetManuallyRedraw
// ()
// Parameters:
// bool                           bUseManualRedraw               (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetComponent::SetManuallyRedraw(bool bUseManualRedraw)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.SetManuallyRedraw");

	UWidgetComponent_SetManuallyRedraw_Params params;
	params.bUseManualRedraw = bUseManualRedraw;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.SetDrawSize
// ()
// Parameters:
// struct FVector2D               Size                           (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetComponent::SetDrawSize(const struct FVector2D& Size)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.SetDrawSize");

	UWidgetComponent_SetDrawSize_Params params;
	params.Size = Size;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.SetBackgroundColor
// ()
// Parameters:
// struct FLinearColor            NewBackgroundColor             (ConstParm, Parm, ZeroConstructor, IsPlainOldData)

void UWidgetComponent::SetBackgroundColor(const struct FLinearColor& NewBackgroundColor)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.SetBackgroundColor");

	UWidgetComponent_SetBackgroundColor_Params params;
	params.NewBackgroundColor = NewBackgroundColor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.RequestRedraw
// ()

void UWidgetComponent::RequestRedraw()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.RequestRedraw");

	UWidgetComponent_RequestRedraw_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetComponent.GetUserWidgetObject
// ()
// Parameters:
// class UUserWidget*             ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UUserWidget* UWidgetComponent::GetUserWidgetObject()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.GetUserWidgetObject");

	UWidgetComponent_GetUserWidgetObject_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetComponent.GetRenderTarget
// ()
// Parameters:
// class UTextureRenderTarget2D*  ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTextureRenderTarget2D* UWidgetComponent::GetRenderTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.GetRenderTarget");

	UWidgetComponent_GetRenderTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetComponent.GetOwnerPlayer
// ()
// Parameters:
// class ULocalPlayer*            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class ULocalPlayer* UWidgetComponent::GetOwnerPlayer()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.GetOwnerPlayer");

	UWidgetComponent_GetOwnerPlayer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetComponent.GetMaterialInstance
// ()
// Parameters:
// class UMaterialInstanceDynamic* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UMaterialInstanceDynamic* UWidgetComponent::GetMaterialInstance()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.GetMaterialInstance");

	UWidgetComponent_GetMaterialInstance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetComponent.GetDrawSize
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UWidgetComponent::GetDrawSize()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetComponent.GetDrawSize");

	UWidgetComponent_GetDrawSize_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.SetCustomHitResult
// ()
// Parameters:
// struct FHitResult              HitResult                      (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)

void UWidgetInteractionComponent::SetCustomHitResult(const struct FHitResult& HitResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.SetCustomHitResult");

	UWidgetInteractionComponent_SetCustomHitResult_Params params;
	params.HitResult = HitResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetInteractionComponent.SendKeyChar
// ()
// Parameters:
// class FString                  Characters                     (Parm, ZeroConstructor)
// bool                           bRepeat                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::SendKeyChar(const class FString& Characters, bool bRepeat)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.SendKeyChar");

	UWidgetInteractionComponent_SendKeyChar_Params params;
	params.Characters = Characters;
	params.bRepeat = bRepeat;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.ScrollWheel
// ()
// Parameters:
// float                          ScrollDelta                    (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetInteractionComponent::ScrollWheel(float ScrollDelta)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.ScrollWheel");

	UWidgetInteractionComponent_ScrollWheel_Params params;
	params.ScrollDelta = ScrollDelta;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetInteractionComponent.ReleasePointerKey
// ()
// Parameters:
// struct FKey                    Key                            (Parm)

void UWidgetInteractionComponent::ReleasePointerKey(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.ReleasePointerKey");

	UWidgetInteractionComponent_ReleasePointerKey_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetInteractionComponent.ReleaseKey
// ()
// Parameters:
// struct FKey                    Key                            (Parm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::ReleaseKey(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.ReleaseKey");

	UWidgetInteractionComponent_ReleaseKey_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.PressPointerKey
// ()
// Parameters:
// struct FKey                    Key                            (Parm)

void UWidgetInteractionComponent::PressPointerKey(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.PressPointerKey");

	UWidgetInteractionComponent_PressPointerKey_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetInteractionComponent.PressKey
// ()
// Parameters:
// struct FKey                    Key                            (Parm)
// bool                           bRepeat                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::PressKey(const struct FKey& Key, bool bRepeat)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.PressKey");

	UWidgetInteractionComponent_PressKey_Params params;
	params.Key = Key;
	params.bRepeat = bRepeat;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.PressAndReleaseKey
// ()
// Parameters:
// struct FKey                    Key                            (Parm)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::PressAndReleaseKey(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.PressAndReleaseKey");

	UWidgetInteractionComponent_PressAndReleaseKey_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.IsOverInteractableWidget
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::IsOverInteractableWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.IsOverInteractableWidget");

	UWidgetInteractionComponent_IsOverInteractableWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.IsOverHitTestVisibleWidget
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::IsOverHitTestVisibleWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.IsOverHitTestVisibleWidget");

	UWidgetInteractionComponent_IsOverHitTestVisibleWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.IsOverFocusableWidget
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetInteractionComponent::IsOverFocusableWidget()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.IsOverFocusableWidget");

	UWidgetInteractionComponent_IsOverFocusableWidget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.GetLastHitResult
// ()
// Parameters:
// struct FHitResult              ReturnValue                    (ConstParm, Parm, OutParm, ReturnParm, ReferenceParm, IsPlainOldData)

struct FHitResult UWidgetInteractionComponent::GetLastHitResult()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.GetLastHitResult");

	UWidgetInteractionComponent_GetLastHitResult_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.GetHoveredWidgetComponent
// ()
// Parameters:
// class UWidgetComponent*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWidgetComponent* UWidgetInteractionComponent::GetHoveredWidgetComponent()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.GetHoveredWidgetComponent");

	UWidgetInteractionComponent_GetHoveredWidgetComponent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetInteractionComponent.Get2DHitLocation
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UWidgetInteractionComponent::Get2DHitLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetInteractionComponent.Get2DHitLocation");

	UWidgetInteractionComponent_Get2DHitLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsVerticalBoxSlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UVerticalBoxSlot*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UVerticalBoxSlot* UWidgetLayoutLibrary::SlotAsVerticalBoxSlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsVerticalBoxSlot");

	UWidgetLayoutLibrary_SlotAsVerticalBoxSlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsUniformGridSlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UUniformGridSlot*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UUniformGridSlot* UWidgetLayoutLibrary::SlotAsUniformGridSlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsUniformGridSlot");

	UWidgetLayoutLibrary_SlotAsUniformGridSlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsOverlaySlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UOverlaySlot*            ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UOverlaySlot* UWidgetLayoutLibrary::SlotAsOverlaySlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsOverlaySlot");

	UWidgetLayoutLibrary_SlotAsOverlaySlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsHorizontalBoxSlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UHorizontalBoxSlot*      ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UHorizontalBoxSlot* UWidgetLayoutLibrary::SlotAsHorizontalBoxSlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsHorizontalBoxSlot");

	UWidgetLayoutLibrary_SlotAsHorizontalBoxSlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsGridSlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UGridSlot*               ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UGridSlot* UWidgetLayoutLibrary::SlotAsGridSlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsGridSlot");

	UWidgetLayoutLibrary_SlotAsGridSlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsCanvasSlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UCanvasPanelSlot*        ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UCanvasPanelSlot* UWidgetLayoutLibrary::SlotAsCanvasSlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsCanvasSlot");

	UWidgetLayoutLibrary_SlotAsCanvasSlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.SlotAsBorderSlot
// ()
// Parameters:
// class UWidget*                 Widget                         (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UBorderSlot*             ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UBorderSlot* UWidgetLayoutLibrary::SlotAsBorderSlot(class UWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.SlotAsBorderSlot");

	UWidgetLayoutLibrary_SlotAsBorderSlot_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.RemoveAllWidgets
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetLayoutLibrary::RemoveAllWidgets(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.RemoveAllWidgets");

	UWidgetLayoutLibrary_RemoveAllWidgets_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetLayoutLibrary.ProjectWorldLocationToWidgetPosition
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 WorldLocation                  (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ScreenPosition                 (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(class APlayerController* PlayerController, const struct FVector& WorldLocation, struct FVector2D* ScreenPosition)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.ProjectWorldLocationToWidgetPosition");

	UWidgetLayoutLibrary_ProjectWorldLocationToWidgetPosition_Params params;
	params.PlayerController = PlayerController;
	params.WorldLocation = WorldLocation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ScreenPosition != nullptr)
		*ScreenPosition = params.ScreenPosition;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetViewportWidgetGeometry
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FGeometry               ReturnValue                    (Parm, OutParm, ReturnParm, IsPlainOldData)

struct FGeometry UWidgetLayoutLibrary::GetViewportWidgetGeometry(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetViewportWidgetGeometry");

	UWidgetLayoutLibrary_GetViewportWidgetGeometry_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetViewportSize
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UWidgetLayoutLibrary::GetViewportSize(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetViewportSize");

	UWidgetLayoutLibrary_GetViewportSize_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetViewportScale
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidgetLayoutLibrary::GetViewportScale(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetViewportScale");

	UWidgetLayoutLibrary_GetViewportScale_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetPlayerScreenWidgetGeometry
// ()
// Parameters:
// class APlayerController*       PlayerController               (Parm, ZeroConstructor, IsPlainOldData)
// struct FGeometry               ReturnValue                    (Parm, OutParm, ReturnParm, IsPlainOldData)

struct FGeometry UWidgetLayoutLibrary::GetPlayerScreenWidgetGeometry(class APlayerController* PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetPlayerScreenWidgetGeometry");

	UWidgetLayoutLibrary_GetPlayerScreenWidgetGeometry_Params params;
	params.PlayerController = PlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetMousePositionScaledByDPI
// ()
// Parameters:
// class APlayerController*       Player                         (Parm, ZeroConstructor, IsPlainOldData)
// float                          LocationX                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// float                          LocationY                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UWidgetLayoutLibrary::GetMousePositionScaledByDPI(class APlayerController* Player, float* LocationX, float* LocationY)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetMousePositionScaledByDPI");

	UWidgetLayoutLibrary_GetMousePositionScaledByDPI_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (LocationX != nullptr)
		*LocationX = params.LocationX;
	if (LocationY != nullptr)
		*LocationY = params.LocationY;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetMousePositionOnViewport
// ()
// Parameters:
// class UObject*                 WorldContextObject             (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UWidgetLayoutLibrary::GetMousePositionOnViewport(class UObject* WorldContextObject)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetMousePositionOnViewport");

	UWidgetLayoutLibrary_GetMousePositionOnViewport_Params params;
	params.WorldContextObject = WorldContextObject;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetLayoutLibrary.GetMousePositionOnPlatform
// ()
// Parameters:
// struct FVector2D               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector2D UWidgetLayoutLibrary::GetMousePositionOnPlatform()
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetLayoutLibrary.GetMousePositionOnPlatform");

	UWidgetLayoutLibrary_GetMousePositionOnPlatform_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WidgetSwitcherSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetSwitcherSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcherSlot.SetVerticalAlignment");

	UWidgetSwitcherSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetSwitcherSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetSwitcherSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcherSlot.SetPadding");

	UWidgetSwitcherSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WidgetSwitcherSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UWidgetSwitcherSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WidgetSwitcherSlot.SetHorizontalAlignment");

	UWidgetSwitcherSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WindowTitleBarArea.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UWindowTitleBarArea::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WindowTitleBarArea.SetVerticalAlignment");

	UWindowTitleBarArea_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WindowTitleBarArea.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UWindowTitleBarArea::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WindowTitleBarArea.SetPadding");

	UWindowTitleBarArea_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WindowTitleBarArea.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UWindowTitleBarArea::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WindowTitleBarArea.SetHorizontalAlignment");

	UWindowTitleBarArea_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WindowTitleBarAreaSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UWindowTitleBarAreaSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WindowTitleBarAreaSlot.SetVerticalAlignment");

	UWindowTitleBarAreaSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WindowTitleBarAreaSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UWindowTitleBarAreaSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WindowTitleBarAreaSlot.SetPadding");

	UWindowTitleBarAreaSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WindowTitleBarAreaSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UWindowTitleBarAreaSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WindowTitleBarAreaSlot.SetHorizontalAlignment");

	UWindowTitleBarAreaSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WrapBox.SetInnerSlotPadding
// ()
// Parameters:
// struct FVector2D               InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UWrapBox::SetInnerSlotPadding(const struct FVector2D& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBox.SetInnerSlotPadding");

	UWrapBox_SetInnerSlotPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WrapBox.AddChildWrapBox
// ()
// Parameters:
// class UWidget*                 Content                        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UWrapBoxSlot*            ReturnValue                    (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UWrapBoxSlot* UWrapBox::AddChildWrapBox(class UWidget* Content)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBox.AddChildWrapBox");

	UWrapBox_AddChildWrapBox_Params params;
	params.Content = Content;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function UMG.WrapBoxSlot.SetVerticalAlignment
// ()
// Parameters:
// TEnumAsByte<EVerticalAlignment> InVerticalAlignment            (Parm, ZeroConstructor, IsPlainOldData)

void UWrapBoxSlot::SetVerticalAlignment(TEnumAsByte<EVerticalAlignment> InVerticalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBoxSlot.SetVerticalAlignment");

	UWrapBoxSlot_SetVerticalAlignment_Params params;
	params.InVerticalAlignment = InVerticalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WrapBoxSlot.SetPadding
// ()
// Parameters:
// struct FMargin                 InPadding                      (Parm, ZeroConstructor, IsPlainOldData)

void UWrapBoxSlot::SetPadding(const struct FMargin& InPadding)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBoxSlot.SetPadding");

	UWrapBoxSlot_SetPadding_Params params;
	params.InPadding = InPadding;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WrapBoxSlot.SetHorizontalAlignment
// ()
// Parameters:
// TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment          (Parm, ZeroConstructor, IsPlainOldData)

void UWrapBoxSlot::SetHorizontalAlignment(TEnumAsByte<EHorizontalAlignment> InHorizontalAlignment)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBoxSlot.SetHorizontalAlignment");

	UWrapBoxSlot_SetHorizontalAlignment_Params params;
	params.InHorizontalAlignment = InHorizontalAlignment;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WrapBoxSlot.SetFillSpanWhenLessThan
// ()
// Parameters:
// float                          InFillSpanWhenLessThan         (Parm, ZeroConstructor, IsPlainOldData)

void UWrapBoxSlot::SetFillSpanWhenLessThan(float InFillSpanWhenLessThan)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBoxSlot.SetFillSpanWhenLessThan");

	UWrapBoxSlot_SetFillSpanWhenLessThan_Params params;
	params.InFillSpanWhenLessThan = InFillSpanWhenLessThan;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function UMG.WrapBoxSlot.SetFillEmptySpace
// ()
// Parameters:
// bool                           InbFillEmptySpace              (Parm, ZeroConstructor, IsPlainOldData)

void UWrapBoxSlot::SetFillEmptySpace(bool InbFillEmptySpace)
{
	static auto fn = UObject::FindObject<UFunction>("Function UMG.WrapBoxSlot.SetFillEmptySpace");

	UWrapBoxSlot_SetFillEmptySpace_Params params;
	params.InbFillEmptySpace = InbFillEmptySpace;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
