#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NetworkErrorPopup_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.CreatePopup
struct UWidget_NetworkErrorPopup_C_CreatePopup_Params
{
	struct FFGGameNetworkErrorMsg                      FGGameNetworkErrorMsg;                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.Construct
struct UWidget_NetworkErrorPopup_C_Construct_Params
{
};

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.mOnNetworkErrorRecieved_Event_1
struct UWidget_NetworkErrorPopup_C_mOnNetworkErrorRecieved_Event_1_Params
{
	TEnumAsByte<ENetworkFailure>                       errorType;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      errorMsg;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.CheckErrors
struct UWidget_NetworkErrorPopup_C_CheckErrors_Params
{
};

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.OnPopupClosed
struct UWidget_NetworkErrorPopup_C_OnPopupClosed_Params
{
	bool                                               NewParam;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_NetworkErrorPopup.Widget_NetworkErrorPopup_C.ExecuteUbergraph_Widget_NetworkErrorPopup
struct UWidget_NetworkErrorPopup_C_ExecuteUbergraph_Widget_NetworkErrorPopup_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
