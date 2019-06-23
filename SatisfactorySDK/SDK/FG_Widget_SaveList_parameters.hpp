#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SaveList_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SaveList.Widget_SaveList_C.GetSaveErrorMessage
struct UWidget_SaveList_C_GetSaveErrorMessage_Params
{
	ESaveExists                                        saveFileExists;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       errorMessage;                                             // (Parm, OutParm)
};

// Function Widget_SaveList.Widget_SaveList_C.ConvertIntToTwoDidgitText
struct UWidget_SaveList_C_ConvertIntToTwoDidgitText_Params
{
	int                                                Int;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SaveList.Widget_SaveList_C.ClearSaves
struct UWidget_SaveList_C_ClearSaves_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.PopulateSessions
struct UWidget_SaveList_C_PopulateSessions_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.DeleteSaveGame
struct UWidget_SaveList_C_DeleteSaveGame_Params
{
	bool                                               confirm;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.GetDeleteButtonVisibility
struct UWidget_SaveList_C_GetDeleteButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.SaveGame
struct UWidget_SaveList_C_SaveGame_Params
{
	bool                                               Confrim;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.GetSaveButtonVisibility
struct UWidget_SaveList_C_GetSaveButtonVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.GetDesiredSaveGameName
struct UWidget_SaveList_C_GetDesiredSaveGameName_Params
{
	class FString                                      saveName;                                                 // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_SaveList.Widget_SaveList_C.AddNewSaveSlot
struct UWidget_SaveList_C_AddNewSaveSlot_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.RefreshSaveList
struct UWidget_SaveList_C_RefreshSaveList_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.InternalSetupSaveGame
struct UWidget_SaveList_C_InternalSetupSaveGame_Params
{
	class UWidget_SaveListRow_C*                       saveRow;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.InternalAddSaveGame
struct UWidget_SaveList_C_InternalAddSaveGame_Params
{
	struct FSaveHeader                                 Header;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm)
	bool                                               isNewGame;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_SaveListRow_C*                       saveRow;                                                  // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.AddNewSaveGame
struct UWidget_SaveList_C_AddNewSaveGame_Params
{
	class UWidget_SaveListRow_C*                       newRow;                                                   // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.OnSaveClickedEvent
struct UWidget_SaveList_C_OnSaveClickedEvent_Params
{
	class UWidget_SaveListRow_C*                       clickedSave;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.AddSaveGame
struct UWidget_SaveList_C_AddSaveGame_Params
{
	struct FSaveHeader                                 SaveHeader;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UWidget_SaveListRow_C*                       rowWidget;                                                // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature
struct UWidget_SaveList_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.OnEscape
struct UWidget_SaveList_C_OnEscape_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.ConfirmDeleteSessionPopUp
struct UWidget_SaveList_C_ConfirmDeleteSessionPopUp_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.ConfirmOverwriteSavePopup
struct UWidget_SaveList_C_ConfirmOverwriteSavePopup_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.OnWorldSave
struct UWidget_SaveList_C_OnWorldSave_Params
{
	bool                                               wasSuccessful;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       errorMessage;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SaveList.Widget_SaveList_C.Destruct
struct UWidget_SaveList_C_Destruct_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_7_OnTextCommited__DelegateSignature
struct UWidget_SaveList_C_BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_7_OnTextCommited__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_9_OnTextChanged__DelegateSignature
struct UWidget_SaveList_C_BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_9_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_11_OnClicked__DelegateSignature
struct UWidget_SaveList_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_11_OnClicked__DelegateSignature_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.BndEvt__mDeleteSaveButton_K2Node_ComponentBoundEvent_12_OnClicked__DelegateSignature
struct UWidget_SaveList_C_BndEvt__mDeleteSaveButton_K2Node_ComponentBoundEvent_12_OnClicked__DelegateSignature_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_13_OnFocused__DelegateSignature
struct UWidget_SaveList_C_BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_13_OnFocused__DelegateSignature_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.OnMenuEnter
struct UWidget_SaveList_C_OnMenuEnter_Params
{
	class UWidget**                                    prevMenu;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.ExecuteUbergraph_Widget_SaveList
struct UWidget_SaveList_C_ExecuteUbergraph_Widget_SaveList_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SaveList.Widget_SaveList_C.OnBackClicked__DelegateSignature
struct UWidget_SaveList_C_OnBackClicked__DelegateSignature_Params
{
};

// Function Widget_SaveList.Widget_SaveList_C.OnSaveClicked__DelegateSignature
struct UWidget_SaveList_C_OnSaveClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
