#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayMenu_Alpha_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.SetStartButtonEnable
struct UWidget_PlayMenu_Alpha_C_SetStartButtonEnable_Params
{
	bool                                               Enabled;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.CheckSessionNameForError
struct UWidget_PlayMenu_Alpha_C_CheckSessionNameForError_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.SetPlayButtonError
struct UWidget_PlayMenu_Alpha_C_SetPlayButtonError_Params
{
	bool                                               Error;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       errorMessage;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.Init
struct UWidget_PlayMenu_Alpha_C_Init_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnEscape
struct UWidget_PlayMenu_Alpha_C_OnEscape_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.Construct
struct UWidget_PlayMenu_Alpha_C_Construct_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_2_onSelectionChanged__DelegateSignature
struct UWidget_PlayMenu_Alpha_C_BndEvt__Widget_Options_DropdownBox_K2Node_ComponentBoundEvent_2_onSelectionChanged__DelegateSignature_Params
{
	class FString                                      SelectedOption;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnStartLocClicked
struct UWidget_PlayMenu_Alpha_C_OnStartLocClicked_Params
{
	TEnumAsByte<EStartingLocations>                    mStartingLocs;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.PreConstruct
struct UWidget_PlayMenu_Alpha_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature
struct UWidget_PlayMenu_Alpha_C_BndEvt__mStartGame_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature
struct UWidget_PlayMenu_Alpha_C_BndEvt__mStartGame_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__EditableTextBox_0_K2Node_ComponentBoundEvent_6_OnEditableTextBoxChangedEvent__DelegateSignature
struct UWidget_PlayMenu_Alpha_C_BndEvt__EditableTextBox_0_K2Node_ComponentBoundEvent_6_OnEditableTextBoxChangedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.BndEvt__mStartGame_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature
struct UWidget_PlayMenu_Alpha_C_BndEvt__mStartGame_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.OnMenuEnter
struct UWidget_PlayMenu_Alpha_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_PlayMenu_Alpha.Widget_PlayMenu_Alpha_C.ExecuteUbergraph_Widget_PlayMenu_Alpha
struct UWidget_PlayMenu_Alpha_C_ExecuteUbergraph_Widget_PlayMenu_Alpha_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
