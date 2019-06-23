// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SequenceHelper_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SequenceHelper.Widget_SequenceHelper_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_SequenceHelper_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SequenceHelper.Widget_SequenceHelper_C.OnKeyDown");

	UWidget_SequenceHelper_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SequenceHelper.Widget_SequenceHelper_C.Construct
// ()

void UWidget_SequenceHelper_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SequenceHelper.Widget_SequenceHelper_C.Construct");

	UWidget_SequenceHelper_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SequenceHelper.Widget_SequenceHelper_C.Destruct
// ()

void UWidget_SequenceHelper_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SequenceHelper.Widget_SequenceHelper_C.Destruct");

	UWidget_SequenceHelper_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SequenceHelper.Widget_SequenceHelper_C.OnClickedWithRef_Event_1
// ()
// Parameters:
// class UWidget_Button_C*        ClickedButton                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SequenceHelper_C::OnClickedWithRef_Event_1(class UWidget_Button_C* ClickedButton)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SequenceHelper.Widget_SequenceHelper_C.OnClickedWithRef_Event_1");

	UWidget_SequenceHelper_C_OnClickedWithRef_Event_1_Params params;
	params.ClickedButton = ClickedButton;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SequenceHelper.Widget_SequenceHelper_C.CustomEvent_1
// ()

void UWidget_SequenceHelper_C::CustomEvent_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SequenceHelper.Widget_SequenceHelper_C.CustomEvent_1");

	UWidget_SequenceHelper_C_CustomEvent_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SequenceHelper.Widget_SequenceHelper_C.ExecuteUbergraph_Widget_SequenceHelper
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SequenceHelper_C::ExecuteUbergraph_Widget_SequenceHelper(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SequenceHelper.Widget_SequenceHelper_C.ExecuteUbergraph_Widget_SequenceHelper");

	UWidget_SequenceHelper_C_ExecuteUbergraph_Widget_SequenceHelper_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
