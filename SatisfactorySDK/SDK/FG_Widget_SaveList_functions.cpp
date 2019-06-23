// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SaveList_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_SaveList.Widget_SaveList_C.GetSaveErrorMessage
// ()
// Parameters:
// ESaveExists                    saveFileExists                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   errorMessage                   (Parm, OutParm)

void UWidget_SaveList_C::GetSaveErrorMessage(ESaveExists saveFileExists, struct FText* errorMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.GetSaveErrorMessage");

	UWidget_SaveList_C_GetSaveErrorMessage_Params params;
	params.saveFileExists = saveFileExists;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (errorMessage != nullptr)
		*errorMessage = params.errorMessage;
}


// Function Widget_SaveList.Widget_SaveList_C.ConvertIntToTwoDidgitText
// ()
// Parameters:
// int                            Int                            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_SaveList_C::ConvertIntToTwoDidgitText(int Int)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.ConvertIntToTwoDidgitText");

	UWidget_SaveList_C_ConvertIntToTwoDidgitText_Params params;
	params.Int = Int;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveList.Widget_SaveList_C.ClearSaves
// ()

void UWidget_SaveList_C::ClearSaves()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.ClearSaves");

	UWidget_SaveList_C_ClearSaves_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.PopulateSessions
// ()

void UWidget_SaveList_C::PopulateSessions()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.PopulateSessions");

	UWidget_SaveList_C_PopulateSessions_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.DeleteSaveGame
// ()
// Parameters:
// bool                           confirm                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SaveList_C::DeleteSaveGame(bool confirm)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.DeleteSaveGame");

	UWidget_SaveList_C_DeleteSaveGame_Params params;
	params.confirm = confirm;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.GetDeleteButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SaveList_C::GetDeleteButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.GetDeleteButtonVisibility");

	UWidget_SaveList_C_GetDeleteButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveList.Widget_SaveList_C.SaveGame
// ()
// Parameters:
// bool                           Confrim                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SaveList_C::SaveGame(bool Confrim)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.SaveGame");

	UWidget_SaveList_C_SaveGame_Params params;
	params.Confrim = Confrim;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.GetSaveButtonVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_SaveList_C::GetSaveButtonVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.GetSaveButtonVisibility");

	UWidget_SaveList_C_GetSaveButtonVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_SaveList.Widget_SaveList_C.GetDesiredSaveGameName
// ()
// Parameters:
// class FString                  saveName                       (Parm, OutParm, ZeroConstructor)

void UWidget_SaveList_C::GetDesiredSaveGameName(class FString* saveName)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.GetDesiredSaveGameName");

	UWidget_SaveList_C_GetDesiredSaveGameName_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (saveName != nullptr)
		*saveName = params.saveName;
}


// Function Widget_SaveList.Widget_SaveList_C.AddNewSaveSlot
// ()

void UWidget_SaveList_C::AddNewSaveSlot()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.AddNewSaveSlot");

	UWidget_SaveList_C_AddNewSaveSlot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.RefreshSaveList
// ()

void UWidget_SaveList_C::RefreshSaveList()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.RefreshSaveList");

	UWidget_SaveList_C_RefreshSaveList_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.InternalSetupSaveGame
// ()
// Parameters:
// class UWidget_SaveListRow_C*   saveRow                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveList_C::InternalSetupSaveGame(class UWidget_SaveListRow_C* saveRow)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.InternalSetupSaveGame");

	UWidget_SaveList_C_InternalSetupSaveGame_Params params;
	params.saveRow = saveRow;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.InternalAddSaveGame
// ()
// Parameters:
// struct FSaveHeader             Header                         (BlueprintVisible, BlueprintReadOnly, Parm)
// bool                           isNewGame                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_SaveListRow_C*   saveRow                        (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveList_C::InternalAddSaveGame(const struct FSaveHeader& Header, bool isNewGame, class UWidget_SaveListRow_C** saveRow)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.InternalAddSaveGame");

	UWidget_SaveList_C_InternalAddSaveGame_Params params;
	params.Header = Header;
	params.isNewGame = isNewGame;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (saveRow != nullptr)
		*saveRow = params.saveRow;
}


// Function Widget_SaveList.Widget_SaveList_C.AddNewSaveGame
// ()
// Parameters:
// class UWidget_SaveListRow_C*   newRow                         (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveList_C::AddNewSaveGame(class UWidget_SaveListRow_C** newRow)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.AddNewSaveGame");

	UWidget_SaveList_C_AddNewSaveGame_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (newRow != nullptr)
		*newRow = params.newRow;
}


// Function Widget_SaveList.Widget_SaveList_C.OnSaveClickedEvent
// ()
// Parameters:
// class UWidget_SaveListRow_C*   clickedSave                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveList_C::OnSaveClickedEvent(class UWidget_SaveListRow_C* clickedSave)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.OnSaveClickedEvent");

	UWidget_SaveList_C_OnSaveClickedEvent_Params params;
	params.clickedSave = clickedSave;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.AddSaveGame
// ()
// Parameters:
// struct FSaveHeader             SaveHeader                     (BlueprintVisible, BlueprintReadOnly, Parm)
// class UWidget_SaveListRow_C*   rowWidget                      (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveList_C::AddSaveGame(const struct FSaveHeader& SaveHeader, class UWidget_SaveListRow_C** rowWidget)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.AddSaveGame");

	UWidget_SaveList_C_AddSaveGame_Params params;
	params.SaveHeader = SaveHeader;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (rowWidget != nullptr)
		*rowWidget = params.rowWidget;
}


// Function Widget_SaveList.Widget_SaveList_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature
// ()

void UWidget_SaveList_C::BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature");

	UWidget_SaveList_C_BndEvt__mDeleteButton_K2Node_ComponentBoundEvent_6_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.OnEscape
// ()

void UWidget_SaveList_C::OnEscape()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.OnEscape");

	UWidget_SaveList_C_OnEscape_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.ConfirmDeleteSessionPopUp
// ()

void UWidget_SaveList_C::ConfirmDeleteSessionPopUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.ConfirmDeleteSessionPopUp");

	UWidget_SaveList_C_ConfirmDeleteSessionPopUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.ConfirmOverwriteSavePopup
// ()

void UWidget_SaveList_C::ConfirmOverwriteSavePopup()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.ConfirmOverwriteSavePopup");

	UWidget_SaveList_C_ConfirmOverwriteSavePopup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.OnWorldSave
// ()
// Parameters:
// bool                           wasSuccessful                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FText                   errorMessage                   (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SaveList_C::OnWorldSave(bool wasSuccessful, const struct FText& errorMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.OnWorldSave");

	UWidget_SaveList_C_OnWorldSave_Params params;
	params.wasSuccessful = wasSuccessful;
	params.errorMessage = errorMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.Destruct
// ()

void UWidget_SaveList_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.Destruct");

	UWidget_SaveList_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_7_OnTextCommited__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)
// TEnumAsByte<ETextCommit>       CommitMethod                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SaveList_C::BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_7_OnTextCommited__DelegateSignature(const struct FText& Text, TEnumAsByte<ETextCommit> CommitMethod)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_7_OnTextCommited__DelegateSignature");

	UWidget_SaveList_C_BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_7_OnTextCommited__DelegateSignature_Params params;
	params.Text = Text;
	params.CommitMethod = CommitMethod;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_9_OnTextChanged__DelegateSignature
// ()
// Parameters:
// struct FText                   Text                           (BlueprintVisible, BlueprintReadOnly, Parm)

void UWidget_SaveList_C::BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_9_OnTextChanged__DelegateSignature(const struct FText& Text)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_9_OnTextChanged__DelegateSignature");

	UWidget_SaveList_C_BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_9_OnTextChanged__DelegateSignature_Params params;
	params.Text = Text;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_11_OnClicked__DelegateSignature
// ()

void UWidget_SaveList_C::BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_11_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_11_OnClicked__DelegateSignature");

	UWidget_SaveList_C_BndEvt__Widget_FrontEnd_Button_K2Node_ComponentBoundEvent_11_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.BndEvt__mDeleteSaveButton_K2Node_ComponentBoundEvent_12_OnClicked__DelegateSignature
// ()

void UWidget_SaveList_C::BndEvt__mDeleteSaveButton_K2Node_ComponentBoundEvent_12_OnClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.BndEvt__mDeleteSaveButton_K2Node_ComponentBoundEvent_12_OnClicked__DelegateSignature");

	UWidget_SaveList_C_BndEvt__mDeleteSaveButton_K2Node_ComponentBoundEvent_12_OnClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_13_OnFocused__DelegateSignature
// ()

void UWidget_SaveList_C::BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_13_OnFocused__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_13_OnFocused__DelegateSignature");

	UWidget_SaveList_C_BndEvt__Widget_SaveInputBox_K2Node_ComponentBoundEvent_13_OnFocused__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.OnMenuEnter
// ()
// Parameters:
// class UWidget**                prevMenu                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_SaveList_C::OnMenuEnter(class UWidget** prevMenu)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.OnMenuEnter");

	UWidget_SaveList_C_OnMenuEnter_Params params;
	params.prevMenu = prevMenu;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.ExecuteUbergraph_Widget_SaveList
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_SaveList_C::ExecuteUbergraph_Widget_SaveList(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.ExecuteUbergraph_Widget_SaveList");

	UWidget_SaveList_C_ExecuteUbergraph_Widget_SaveList_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.OnBackClicked__DelegateSignature
// ()

void UWidget_SaveList_C::OnBackClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.OnBackClicked__DelegateSignature");

	UWidget_SaveList_C_OnBackClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_SaveList.Widget_SaveList_C.OnSaveClicked__DelegateSignature
// ()

void UWidget_SaveList_C::OnSaveClicked__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_SaveList.Widget_SaveList_C.OnSaveClicked__DelegateSignature");

	UWidget_SaveList_C_OnSaveClicked__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
