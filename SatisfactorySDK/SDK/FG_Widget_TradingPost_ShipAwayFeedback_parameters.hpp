#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_ShipAwayFeedback_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetProgressbarVisibility
struct UWidget_TradingPost_ShipAwayFeedback_C_GetProgressbarVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetProgressbarPercent
struct UWidget_TradingPost_ShipAwayFeedback_C_GetProgressbarPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetSchematicTitle
struct UWidget_TradingPost_ShipAwayFeedback_C_GetSchematicTitle_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetScematicIcon
struct UWidget_TradingPost_ShipAwayFeedback_C_GetScematicIcon_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPost_ShipAwayFeedback.Widget_TradingPost_ShipAwayFeedback_C.GetShipTimerText
struct UWidget_TradingPost_ShipAwayFeedback_C_GetShipTimerText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
