#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PauseWidget_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_PauseWidget.BP_PauseWidget_C.UpdateMenuItemVisibility
struct UBP_PauseWidget_C_UpdateMenuItemVisibility_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.Get_bRespawn_Visibility_1
struct UBP_PauseWidget_C_Get_bRespawn_Visibility_1_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_PauseWidget.BP_PauseWidget_C.Get_bSkipIntro_bIsEnabled_1
struct UBP_PauseWidget_C_Get_bSkipIntro_bIsEnabled_1_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_PauseWidget.BP_PauseWidget_C.UpdateHostNATText
struct UBP_PauseWidget_C_UpdateHostNATText_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.GetPlayDurationText
struct UBP_PauseWidget_C_GetPlayDurationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_PauseWidget.BP_PauseWidget_C.GetSessionNameText
struct UBP_PauseWidget_C_GetSessionNameText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_PauseWidget.BP_PauseWidget_C.DoResume
struct UBP_PauseWidget_C_DoResume_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.OnEscape
struct UBP_PauseWidget_C_OnEscape_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bResume_K2Node_ComponentBoundEvent_152_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bResume_K2Node_ComponentBoundEvent_152_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bLoadGame_K2Node_ComponentBoundEvent_166_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bLoadGame_K2Node_ComponentBoundEvent_166_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bRespawn_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bRespawn_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bSaveGame_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bSaveGame_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.Construct
struct UBP_PauseWidget_C_Construct_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bFeedback_K2Node_ComponentBoundEvent_53_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bFeedback_K2Node_ComponentBoundEvent_53_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.Event ExitToMainMenu
struct UBP_PauseWidget_C_Event_ExitToMainMenu_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PauseWidget.BP_PauseWidget_C.Event ExitToDesktop
struct UBP_PauseWidget_C_Event_ExitToDesktop_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bExitMainMenu_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bExitMainMenu_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bExitDesktop_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bExitDesktop_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__mOptions_K2Node_ComponentBoundEvent_4_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__mOptions_K2Node_ComponentBoundEvent_4_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.BndEvt__bSkipIntro_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature
struct UBP_PauseWidget_C_BndEvt__bSkipIntro_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.Destruct
struct UBP_PauseWidget_C_Destruct_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.ExecuteUbergraph_BP_PauseWidget
struct UBP_PauseWidget_C_ExecuteUbergraph_BP_PauseWidget_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_PauseWidget.BP_PauseWidget_C.OnBackClicked__DelegateSignature
struct UBP_PauseWidget_C_OnBackClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.OnManagePlayersClicked__DelegateSignature
struct UBP_PauseWidget_C_OnManagePlayersClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.OnOptionsClicked__DelegateSignature
struct UBP_PauseWidget_C_OnOptionsClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.OnLoadClicked__DelegateSignature
struct UBP_PauseWidget_C_OnLoadClicked__DelegateSignature_Params
{
};

// Function BP_PauseWidget.BP_PauseWidget_C.OnSaveClicked__DelegateSignature
struct UBP_PauseWidget_C_OnSaveClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
