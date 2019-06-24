// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_KeyBindFocus_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnKeyUp
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_KeyBindFocus_C::OnKeyUp(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnKeyUp");

	UWidget_KeyBindFocus_C_OnKeyUp_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.HandleInput
// ()
// Parameters:
// struct FInputEvent             InputEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FKey                    keyPressed                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             Handled                        (Parm, OutParm)

void UWidget_KeyBindFocus_C::HandleInput(const struct FInputEvent& InputEvent, const struct FKey& keyPressed, struct FEventReply* Handled)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.HandleInput");

	UWidget_KeyBindFocus_C_HandleInput_Params params;
	params.InputEvent = InputEvent;
	params.keyPressed = keyPressed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Handled != nullptr)
		*Handled = params.Handled;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnMouseWheel
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_KeyBindFocus_C::OnMouseWheel(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnMouseWheel");

	UWidget_KeyBindFocus_C_OnMouseWheel_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.GetKeyRebindText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_KeyBindFocus_C::GetKeyRebindText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.GetKeyRebindText");

	UWidget_KeyBindFocus_C_GetKeyRebindText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_KeyBindFocus_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnKeyDown");

	UWidget_KeyBindFocus_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnMouseButtonDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_KeyBindFocus_C::OnMouseButtonDown(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.OnMouseButtonDown");

	UWidget_KeyBindFocus_C_OnMouseButtonDown_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.Construct
// ()

void UWidget_KeyBindFocus_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.Construct");

	UWidget_KeyBindFocus_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.ExecuteUbergraph_Widget_KeyBindFocus
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_KeyBindFocus_C::ExecuteUbergraph_Widget_KeyBindFocus(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_KeyBindFocus.Widget_KeyBindFocus_C.ExecuteUbergraph_Widget_KeyBindFocus");

	UWidget_KeyBindFocus_C_ExecuteUbergraph_Widget_KeyBindFocus_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
