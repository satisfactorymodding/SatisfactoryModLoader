// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ButtonSpotLight_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.UpdateMousePosition
// ()

void UWidget_ButtonSpotLight_C::UpdateMousePosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.UpdateMousePosition");

	UWidget_ButtonSpotLight_C_UpdateMousePosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseMove
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UWidget_ButtonSpotLight_C::OnMouseMove(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseMove");

	UWidget_ButtonSpotLight_C_OnMouseMove_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ButtonSpotLight_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.PreConstruct");

	UWidget_ButtonSpotLight_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.Construct
// ()

void UWidget_ButtonSpotLight_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.Construct");

	UWidget_ButtonSpotLight_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseLeave
// ()
// Parameters:
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ButtonSpotLight_C::OnMouseLeave(struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseLeave");

	UWidget_ButtonSpotLight_C_OnMouseLeave_Params params;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseEnter
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          MouseEvent                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void UWidget_ButtonSpotLight_C::OnMouseEnter(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseEnter");

	UWidget_ButtonSpotLight_C_OnMouseEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.MouseEvent = MouseEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.ExecuteUbergraph_Widget_ButtonSpotLight
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ButtonSpotLight_C::ExecuteUbergraph_Widget_ButtonSpotLight(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.ExecuteUbergraph_Widget_ButtonSpotLight");

	UWidget_ButtonSpotLight_C_ExecuteUbergraph_Widget_ButtonSpotLight_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
