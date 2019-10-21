// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_ShipAwayFeedback_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetProgressbarVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_TradingPost_ShipAwayFeedback_C::GetProgressbarVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetProgressbarVisibility");

	UWidget_TradingPost_ShipAwayFeedback_C_GetProgressbarVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetProgressbarPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_TradingPost_ShipAwayFeedback_C::GetProgressbarPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetProgressbarPercent");

	UWidget_TradingPost_ShipAwayFeedback_C_GetProgressbarPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetSchematicTitle
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_TradingPost_ShipAwayFeedback_C::GetSchematicTitle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetSchematicTitle");

	UWidget_TradingPost_ShipAwayFeedback_C_GetSchematicTitle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetScematicIcon
// ()
// Parameters:
// struct FSlateBrush             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FSlateBrush UWidget_TradingPost_ShipAwayFeedback_C::GetScematicIcon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetScematicIcon");

	UWidget_TradingPost_ShipAwayFeedback_C_GetScematicIcon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetShipTimerText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_TradingPost_ShipAwayFeedback_C::GetShipTimerText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetShipTimerText");

	UWidget_TradingPost_ShipAwayFeedback_C_GetShipTimerText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
