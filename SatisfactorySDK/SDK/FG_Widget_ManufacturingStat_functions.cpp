// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManufacturingStat_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.SetBrush
// ()

void UWidget_ManufacturingStat_C::SetBrush()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.SetBrush");

	UWidget_ManufacturingStat_C_SetBrush_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.SetIconColor
// ()

void UWidget_ManufacturingStat_C::SetIconColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.SetIconColor");

	UWidget_ManufacturingStat_C_SetIconColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.GetStatText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_ManufacturingStat_C::GetStatText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.GetStatText");

	UWidget_ManufacturingStat_C_GetStatText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManufacturingStat_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.PreConstruct");

	UWidget_ManufacturingStat_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.OnDragEnter
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManufacturingStat_C::OnDragEnter(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.OnDragEnter");

	UWidget_ManufacturingStat_C_OnDragEnter_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.OnDragLeave
// ()
// Parameters:
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManufacturingStat_C::OnDragLeave(struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.OnDragLeave");

	UWidget_ManufacturingStat_C_OnDragLeave_Params params;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.Construct
// ()

void UWidget_ManufacturingStat_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.Construct");

	UWidget_ManufacturingStat_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.UpdateStat
// ()

void UWidget_ManufacturingStat_C::UpdateStat()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.UpdateStat");

	UWidget_ManufacturingStat_C_UpdateStat_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.Destruct
// ()

void UWidget_ManufacturingStat_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.Destruct");

	UWidget_ManufacturingStat_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.ExecuteUbergraph_Widget_ManufacturingStat
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ManufacturingStat_C::ExecuteUbergraph_Widget_ManufacturingStat(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.ExecuteUbergraph_Widget_ManufacturingStat");

	UWidget_ManufacturingStat_C_ExecuteUbergraph_Widget_ManufacturingStat_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
