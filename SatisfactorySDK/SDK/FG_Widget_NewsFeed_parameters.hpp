#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NewsFeed_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_NewsFeed.Widget_NewsFeed_C.GetNewsHeaderText
struct UWidget_NewsFeed_C_GetNewsHeaderText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.GetHeaderAndBody
struct UWidget_NewsFeed_C_GetHeaderAndBody_Params
{
	struct FText                                       InText;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FText                                       Header;                                                   // (Parm, OutParm)
	struct FText                                       Body;                                                     // (Parm, OutParm)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.GetNewsBodyText
struct UWidget_NewsFeed_C_GetNewsBodyText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.OnFail_74A37E23495D65D8B1428F9D6302EA77
struct UWidget_NewsFeed_C_OnFail_74A37E23495D65D8B1428F9D6302EA77_Params
{
	class UTexture2DDynamic*                           Texture;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.OnSuccess_74A37E23495D65D8B1428F9D6302EA77
struct UWidget_NewsFeed_C_OnSuccess_74A37E23495D65D8B1428F9D6302EA77_Params
{
	class UTexture2DDynamic*                           Texture;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.Construct
struct UWidget_NewsFeed_C_Construct_Params
{
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.FindNewsFeedActor
struct UWidget_NewsFeed_C_FindNewsFeedActor_Params
{
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.OnNewsTextReceived
struct UWidget_NewsFeed_C_OnNewsTextReceived_Params
{
	struct FText                                       NewsText;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.PreConstruct
struct UWidget_NewsFeed_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_NewsFeed_C_BndEvt__Button_0_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_NewsFeed_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature
struct UWidget_NewsFeed_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.ParseText
struct UWidget_NewsFeed_C_ParseText_Params
{
	struct FText                                       NewsText;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UWidget_NewsFeed_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function Widget_NewsFeed.Widget_NewsFeed_C.ExecuteUbergraph_Widget_NewsFeed
struct UWidget_NewsFeed_C_ExecuteUbergraph_Widget_NewsFeed_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
