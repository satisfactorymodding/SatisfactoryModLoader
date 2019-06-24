#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LetterSpacedLetter_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.SetTextAndFont
struct UWidget_LetterSpacedLetter_C_SetTextAndFont_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FSlateFontInfo                              Font;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.PreConstruct
struct UWidget_LetterSpacedLetter_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LetterSpacedLetter.Widget_LetterSpacedLetter_C.ExecuteUbergraph_Widget_LetterSpacedLetter
struct UWidget_LetterSpacedLetter_C_ExecuteUbergraph_Widget_LetterSpacedLetter_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
