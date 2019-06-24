#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_LoadSession_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_LoadSession.Widget_LoadSession_C.PopulateSavesFromSession
struct UWidget_LoadSession_C_PopulateSavesFromSession_Params
{
	struct FSessionSaveStruct                          session;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_LoadSession.Widget_LoadSession_C.ShowLoadButtons
struct UWidget_LoadSession_C_ShowLoadButtons_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.IsDeleteSessionButtonEnabled
struct UWidget_LoadSession_C_IsDeleteSessionButtonEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.IsValidCurrentSession
struct UWidget_LoadSession_C_IsValidCurrentSession_Params
{
	bool                                               IsValid;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.UpdateCurrentSession
struct UWidget_LoadSession_C_UpdateCurrentSession_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.ShouldShowSaveGames
struct UWidget_LoadSession_C_ShouldShowSaveGames_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.IsValidCurrentSave
struct UWidget_LoadSession_C_IsValidCurrentSave_Params
{
	bool                                               IsValid;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.OnSaveClicked
struct UWidget_LoadSession_C_OnSaveClicked_Params
{
	struct FSaveHeader                                 SaveHeader;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_LoadSession.Widget_LoadSession_C.PopulateSessionList
struct UWidget_LoadSession_C_PopulateSessionList_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.BndEvt__mDeleteSaveGameButton_K2Node_ComponentBoundEvent_115_OnClicked__DelegateSignature
struct UWidget_LoadSession_C_BndEvt__mDeleteSaveGameButton_K2Node_ComponentBoundEvent_115_OnClicked__DelegateSignature_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.BndEvt__button2save_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_LoadSession_C_BndEvt__button2save_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.ConfirmDeleteSessionPopUp
struct UWidget_LoadSession_C_ConfirmDeleteSessionPopUp_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.EventDeleteSession
struct UWidget_LoadSession_C_EventDeleteSession_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.EventDeleteSave
struct UWidget_LoadSession_C_EventDeleteSave_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.ConfirmDeleteSavePopUp
struct UWidget_LoadSession_C_ConfirmDeleteSavePopUp_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.OnEscape
struct UWidget_LoadSession_C_OnEscape_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.SpawnAnim
struct UWidget_LoadSession_C_SpawnAnim_Params
{
	bool*                                              PlayBackgroundAnim;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.LoadCurrentSave
struct UWidget_LoadSession_C_LoadCurrentSave_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_LoadSession_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.HideLoadAndDeleteButtons
struct UWidget_LoadSession_C_HideLoadAndDeleteButtons_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.BndEvt__DeleteSave_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature
struct UWidget_LoadSession_C_BndEvt__DeleteSave_K2Node_ComponentBoundEvent_2_OnClicked__DelegateSignature_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.HideDeleteSessionButton
struct UWidget_LoadSession_C_HideDeleteSessionButton_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.BndEvt__DeleteSessionButton_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UWidget_LoadSession_C_BndEvt__DeleteSessionButton_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function Widget_LoadSession.Widget_LoadSession_C.OnMenuEnter
struct UWidget_LoadSession_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.ExecuteUbergraph_Widget_LoadSession
struct UWidget_LoadSession_C_ExecuteUbergraph_Widget_LoadSession_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.OnLoadClicked__DelegateSignature
struct UWidget_LoadSession_C_OnLoadClicked__DelegateSignature_Params
{
	struct FSaveHeader                                 SaveGame;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               IsPrivateGame;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_LoadSession.Widget_LoadSession_C.OnBackClicked__DelegateSignature
struct UWidget_LoadSession_C_OnBackClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
