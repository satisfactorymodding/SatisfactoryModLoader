#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TitleLabel_DarkMode_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TitleLabel_DarkMode.Widget_TitleLabel_DarkMode_C.SetFicsItDriverText
struct UWidget_TitleLabel_DarkMode_C_SetFicsItDriverText_Params
{
};

// Function Widget_TitleLabel_DarkMode.Widget_TitleLabel_DarkMode_C.SetTitle
struct UWidget_TitleLabel_DarkMode_C_SetTitle_Params
{
	struct FText                                       Title;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_TitleLabel_DarkMode.Widget_TitleLabel_DarkMode_C.PreConstruct
struct UWidget_TitleLabel_DarkMode_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TitleLabel_DarkMode.Widget_TitleLabel_DarkMode_C.ExecuteUbergraph_Widget_TitleLabel_DarkMode
struct UWidget_TitleLabel_DarkMode_C_ExecuteUbergraph_Widget_TitleLabel_DarkMode_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
