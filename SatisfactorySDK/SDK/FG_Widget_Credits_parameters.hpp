#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Credits_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Credits.Widget_Credits_C.OnEscape
struct UWidget_Credits_C_OnEscape_Params
{
};

// Function Widget_Credits.Widget_Credits_C.Construct
struct UWidget_Credits_C_Construct_Params
{
};

// Function Widget_Credits.Widget_Credits_C.OnMenuEnter
struct UWidget_Credits_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Credits.Widget_Credits_C.ExecuteUbergraph_Widget_Credits
struct UWidget_Credits_C_ExecuteUbergraph_Widget_Credits_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Credits.Widget_Credits_C.OnBackClicked__DelegateSignature
struct UWidget_Credits_C_OnBackClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
