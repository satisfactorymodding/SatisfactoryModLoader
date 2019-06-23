#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LetterSpacedText_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.PreConstruct
struct UWidget_LetterSpacedText_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.SetTitle
struct UWidget_LetterSpacedText_C_SetTitle_Params
{
	class FString                                      Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.OnAnimateText
struct UWidget_LetterSpacedText_C_OnAnimateText_Params
{
};

// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.Construct
struct UWidget_LetterSpacedText_C_Construct_Params
{
};

// Function Widget_LetterSpacedText.Widget_LetterSpacedText_C.ExecuteUbergraph_Widget_LetterSpacedText
struct UWidget_LetterSpacedText_C_ExecuteUbergraph_Widget_LetterSpacedText_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
