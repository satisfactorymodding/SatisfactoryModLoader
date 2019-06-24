// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PoleConnections_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_PoleConnections.Widget_PoleConnections_C.SetStyle
// ()
// Parameters:
// bool                           UseBackground                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PoleConnections_C::SetStyle(bool UseBackground)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.SetStyle");

	UWidget_PoleConnections_C_SetStyle_Params params;
	params.UseBackground = UseBackground;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.GetColorAndOpacity_1
// ()
// Parameters:
// struct FSlateColor             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateColor UWidget_PoleConnections_C::GetColorAndOpacity_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.GetColorAndOpacity_1");

	UWidget_PoleConnections_C_GetColorAndOpacity_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.GetText_1
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_PoleConnections_C::GetText_1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.GetText_1");

	UWidget_PoleConnections_C_GetText_1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.Construct
// ()

void UWidget_PoleConnections_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.Construct");

	UWidget_PoleConnections_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.UpdateConnections
// ()

void UWidget_PoleConnections_C::UpdateConnections()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.UpdateConnections");

	UWidget_PoleConnections_C_UpdateConnections_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.Destruct
// ()

void UWidget_PoleConnections_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.Destruct");

	UWidget_PoleConnections_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.PreConstruct
// ()
// Parameters:
// bool*                          IsDesignTime                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PoleConnections_C::PreConstruct(bool* IsDesignTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.PreConstruct");

	UWidget_PoleConnections_C_PreConstruct_Params params;
	params.IsDesignTime = IsDesignTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_PoleConnections.Widget_PoleConnections_C.ExecuteUbergraph_Widget_PoleConnections
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_PoleConnections_C::ExecuteUbergraph_Widget_PoleConnections(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_PoleConnections.Widget_PoleConnections_C.ExecuteUbergraph_Widget_PoleConnections");

	UWidget_PoleConnections_C_ExecuteUbergraph_Widget_PoleConnections_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
