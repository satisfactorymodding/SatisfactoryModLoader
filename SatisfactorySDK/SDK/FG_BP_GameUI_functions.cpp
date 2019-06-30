// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GameUI_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_GameUI.BP_GameUI_C.OnPreviewKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UBP_GameUI_C::OnPreviewKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnPreviewKeyDown");

	UBP_GameUI_C_OnPreviewKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.SetVersionLabelPosition
// ()

void UBP_GameUI_C::SetVersionLabelPosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.SetVersionLabelPosition");

	UBP_GameUI_C_SetVersionLabelPosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetExperimentalVisibility
// ()

void UBP_GameUI_C::GetExperimentalVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetExperimentalVisibility");

	UBP_GameUI_C_GetExperimentalVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetChildUIVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::GetChildUIVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetChildUIVisibility");

	UBP_GameUI_C_GetChildUIVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.PrePopWidget
// ()
// Parameters:
// class UFGInteractWidget*       WidgetBeingRemoved             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::PrePopWidget(class UFGInteractWidget* WidgetBeingRemoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.PrePopWidget");

	UBP_GameUI_C_PrePopWidget_Params params;
	params.WidgetBeingRemoved = WidgetBeingRemoved;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ShowTutorialHint
// ()

void UBP_GameUI_C::ShowTutorialHint()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ShowTutorialHint");

	UBP_GameUI_C_ShowTutorialHint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetFGHUD
// ()
// Parameters:
// class AFGHUD*                  HUD                            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::GetFGHUD(class AFGHUD** HUD)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetFGHUD");

	UBP_GameUI_C_GetFGHUD_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (HUD != nullptr)
		*HUD = params.HUD;
}


// Function BP_GameUI.BP_GameUI_C.SetPrototypeCameraVisibility
// ()
// Parameters:
// bool                           New_Visibility                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::SetPrototypeCameraVisibility(bool New_Visibility)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.SetPrototypeCameraVisibility");

	UBP_GameUI_C_SetPrototypeCameraVisibility_Params params;
	params.New_Visibility = New_Visibility;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.SetPrototypeVisibility
// ()
// Parameters:
// bool                           NewVisibility                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::SetPrototypeVisibility(bool NewVisibility)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.SetPrototypeVisibility");

	UBP_GameUI_C_SetPrototypeVisibility_Params params;
	params.NewVisibility = NewVisibility;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.OnInventorySlotStackMove
// ()
// Parameters:
// class UWidget_InventorySlot_C* InventorySlot                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// TEnumAsByte<EInteractionDirection> InteractionDirection           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::OnInventorySlotStackMove(class UWidget_InventorySlot_C* InventorySlot, TEnumAsByte<EInteractionDirection> InteractionDirection)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnInventorySlotStackMove");

	UBP_GameUI_C_OnInventorySlotStackMove_Params params;
	params.InventorySlot = InventorySlot;
	params.InteractionDirection = InteractionDirection;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.CreateAddOnPlayerInventory
// ()
// Parameters:
// class UPanelWidget*            Container                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::CreateAddOnPlayerInventory(class UPanelWidget* Container)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.CreateAddOnPlayerInventory");

	UBP_GameUI_C_CreateAddOnPlayerInventory_Params params;
	params.Container = Container;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.IsChatWindowVisible
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::IsChatWindowVisible()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.IsChatWindowVisible");

	UBP_GameUI_C_IsChatWindowVisible_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.PlayAudioMessage
// ()
// Parameters:
// class UClass*                  MessageClass                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::PlayAudioMessage(class UClass* MessageClass)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.PlayAudioMessage");

	UBP_GameUI_C_PlayAudioMessage_Params params;
	params.MessageClass = MessageClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetUIVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::GetUIVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetUIVisibility");

	UBP_GameUI_C_GetUIVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.GetEquipmentHUDParent
// ()
// Parameters:
// EEquipmentSlot                 slotType                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UOverlay*                overlayParent                  (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::GetEquipmentHUDParent(EEquipmentSlot slotType, class UOverlay** overlayParent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetEquipmentHUDParent");

	UBP_GameUI_C_GetEquipmentHUDParent_Params params;
	params.slotType = slotType;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (overlayParent != nullptr)
		*overlayParent = params.overlayParent;
}


// Function BP_GameUI.BP_GameUI_C.OnKeyDown
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FKeyEvent*              InKeyEvent                     (BlueprintVisible, BlueprintReadOnly, Parm)
// struct FEventReply             ReturnValue                    (Parm, OutParm, ReturnParm)

struct FEventReply UBP_GameUI_C::OnKeyDown(struct FGeometry* MyGeometry, struct FKeyEvent* InKeyEvent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnKeyDown");

	UBP_GameUI_C_OnKeyDown_Params params;
	params.MyGeometry = MyGeometry;
	params.InKeyEvent = InKeyEvent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.HUDPanelVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::HUDPanelVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.HUDPanelVisibility");

	UBP_GameUI_C_HUDPanelVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.GetMessageNotifierVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::GetMessageNotifierVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetMessageNotifierVisibility");

	UBP_GameUI_C_GetMessageNotifierVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.UpdateHUDVisibility
// ()

void UBP_GameUI_C::UpdateHUDVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.UpdateHUDVisibility");

	UBP_GameUI_C_UpdateHUDVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetSchematicPopupVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::GetSchematicPopupVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetSchematicPopupVisibility");

	UBP_GameUI_C_GetSchematicPopupVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.AddMessageNotification
// ()
// Parameters:
// class UClass*                  newMessage                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::AddMessageNotification(class UClass* newMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.AddMessageNotification");

	UBP_GameUI_C_AddMessageNotification_Params params;
	params.newMessage = newMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetItemDropLocation
// ()
// Parameters:
// struct FVector                 dropLocation                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::GetItemDropLocation(struct FVector* dropLocation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetItemDropLocation");

	UBP_GameUI_C_GetItemDropLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (dropLocation != nullptr)
		*dropLocation = params.dropLocation;
}


// Function BP_GameUI.BP_GameUI_C.OnDrop
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// struct FPointerEvent*          PointerEvent                   (BlueprintVisible, BlueprintReadOnly, Parm)
// class UDragDropOperation**     Operation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBP_GameUI_C::OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnDrop");

	UBP_GameUI_C_OnDrop_Params params;
	params.MyGeometry = MyGeometry;
	params.PointerEvent = PointerEvent;
	params.Operation = Operation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.RefreshInputMode
// ()

void UBP_GameUI_C::RefreshInputMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.RefreshInputMode");

	UBP_GameUI_C_RefreshInputMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.CreatePopupWidget
// ()
// Parameters:
// struct FPopupData*             PopupData                      (BlueprintVisible, BlueprintReadOnly, Parm)
// class UFGPopupWidget*          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)

class UFGPopupWidget* UBP_GameUI_C::CreatePopupWidget(struct FPopupData* PopupData)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.CreatePopupWidget");

	UBP_GameUI_C_CreatePopupWidget_Params params;
	params.PopupData = PopupData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.GetReloadRespawnText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UBP_GameUI_C::GetReloadRespawnText()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetReloadRespawnText");

	UBP_GameUI_C_GetReloadRespawnText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.GetReloadRespawnTextVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::GetReloadRespawnTextVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetReloadRespawnTextVisibility");

	UBP_GameUI_C_GetReloadRespawnTextVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.PopAllWidgets_Internal
// ()

void UBP_GameUI_C::PopAllWidgets_Internal()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.PopAllWidgets_Internal");

	UBP_GameUI_C_PopAllWidgets_Internal_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.FindWidgetByClass
// ()
// Parameters:
// class UClass*                  WidgetClass                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UFGInteractWidget*       Widget                         (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::FindWidgetByClass(class UClass* WidgetClass, class UFGInteractWidget** Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.FindWidgetByClass");

	UBP_GameUI_C_FindWidgetByClass_Params params;
	params.WidgetClass = WidgetClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Widget != nullptr)
		*Widget = params.Widget;
}


// Function BP_GameUI.BP_GameUI_C.DoesWidgetExist
// ()
// Parameters:
// class UClass*                  WidgetClass                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           doesExist                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::DoesWidgetExist(class UClass* WidgetClass, bool* doesExist)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.DoesWidgetExist");

	UBP_GameUI_C_DoesWidgetExist_Params params;
	params.WidgetClass = WidgetClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (doesExist != nullptr)
		*doesExist = params.doesExist;
}


// Function BP_GameUI.BP_GameUI_C.FindWidgetToPop
// ()
// Parameters:
// class UFGInteractWidget*       WidgetToPop                    (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::FindWidgetToPop(class UFGInteractWidget** WidgetToPop)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.FindWidgetToPop");

	UBP_GameUI_C_FindWidgetToPop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (WidgetToPop != nullptr)
		*WidgetToPop = params.WidgetToPop;
}


// Function BP_GameUI.BP_GameUI_C.PopWidget
// ()
// Parameters:
// class UFGInteractWidget*       widgetToRemove                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::PopWidget(class UFGInteractWidget* widgetToRemove)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.PopWidget");

	UBP_GameUI_C_PopWidget_Params params;
	params.widgetToRemove = widgetToRemove;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.GetPlayerInteractionVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UBP_GameUI_C::GetPlayerInteractionVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.GetPlayerInteractionVisibility");

	UBP_GameUI_C_GetPlayerInteractionVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_GameUI.BP_GameUI_C.PopAllWidgets
// ()

void UBP_GameUI_C::PopAllWidgets()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.PopAllWidgets");

	UBP_GameUI_C_PopAllWidgets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ClosePopup
// ()

void UBP_GameUI_C::ClosePopup()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ClosePopup");

	UBP_GameUI_C_ClosePopup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.Destruct
// ()

void UBP_GameUI_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.Destruct");

	UBP_GameUI_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.Play Landed Effect
// ()
// Parameters:
// float                          Velocity                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::Play_Landed_Effect(float Velocity)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.Play Landed Effect");

	UBP_GameUI_C_Play_Landed_Effect_Params params;
	params.Velocity = Velocity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.PushWidget
// ()
// Parameters:
// class UFGInteractWidget*       Widget                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::PushWidget(class UFGInteractWidget* Widget)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.PushWidget");

	UBP_GameUI_C_PushWidget_Params params;
	params.Widget = Widget;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ReceivedMessage
// ()
// Parameters:
// class UClass**                 inMessage                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::ReceivedMessage(class UClass** inMessage)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ReceivedMessage");

	UBP_GameUI_C_ReceivedMessage_Params params;
	params.inMessage = inMessage;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.RemoveAudioMessage
// ()

void UBP_GameUI_C::RemoveAudioMessage()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.RemoveAudioMessage");

	UBP_GameUI_C_RemoveAudioMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.AddIntroTutorialInfo
// ()
// Parameters:
// struct FTutorialHintData*      TutorialHintData               (BlueprintVisible, BlueprintReadOnly, Parm)

void UBP_GameUI_C::AddIntroTutorialInfo(struct FTutorialHintData* TutorialHintData)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.AddIntroTutorialInfo");

	UBP_GameUI_C_AddIntroTutorialInfo_Params params;
	params.TutorialHintData = TutorialHintData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.UpdateTutorialInfo
// ()
// Parameters:
// struct FTutorialHintData       hintData                       (BlueprintVisible, BlueprintReadOnly, Parm)

void UBP_GameUI_C::UpdateTutorialInfo(const struct FTutorialHintData& hintData)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.UpdateTutorialInfo");

	UBP_GameUI_C_UpdateTutorialInfo_Params params;
	params.hintData = hintData;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.HandleFocusLost
// ()

void UBP_GameUI_C::HandleFocusLost()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.HandleFocusLost");

	UBP_GameUI_C_HandleFocusLost_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.AddPawnHUD
// ()
// Parameters:
// class UUserWidget**            newContent                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::AddPawnHUD(class UUserWidget** newContent)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.AddPawnHUD");

	UBP_GameUI_C_AddPawnHUD_Params params;
	params.newContent = newContent;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.RemovePawnHUD
// ()

void UBP_GameUI_C::RemovePawnHUD()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.RemovePawnHUD");

	UBP_GameUI_C_RemovePawnHUD_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.AddInteractWidget
// ()
// Parameters:
// class UFGInteractWidget**      widgetToAdd                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UBP_GameUI_C::AddInteractWidget(class UFGInteractWidget** widgetToAdd)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.AddInteractWidget");

	UBP_GameUI_C_AddInteractWidget_Params params;
	params.widgetToAdd = widgetToAdd;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.OnPlayerBeginTypeMessage
// ()

void UBP_GameUI_C::OnPlayerBeginTypeMessage()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnPlayerBeginTypeMessage");

	UBP_GameUI_C_OnPlayerBeginTypeMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.Construct
// ()

void UBP_GameUI_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.Construct");

	UBP_GameUI_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.OnChatMessageReceived
// ()

void UBP_GameUI_C::OnChatMessageReceived()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnChatMessageReceived");

	UBP_GameUI_C_OnChatMessageReceived_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ClearHintOnTutorialStepCompleted
// ()

void UBP_GameUI_C::ClearHintOnTutorialStepCompleted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ClearHintOnTutorialStepCompleted");

	UBP_GameUI_C_ClearHintOnTutorialStepCompleted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ResetInput
// ()

void UBP_GameUI_C::ResetInput()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ResetInput");

	UBP_GameUI_C_ResetInput_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ShowRespawnMessage
// ()

void UBP_GameUI_C::ShowRespawnMessage()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ShowRespawnMessage");

	UBP_GameUI_C_ShowRespawnMessage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.OnReceiveRadiationStart
// ()

void UBP_GameUI_C::OnReceiveRadiationStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnReceiveRadiationStart");

	UBP_GameUI_C_OnReceiveRadiationStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.OnReceiveRadiationStop
// ()

void UBP_GameUI_C::OnReceiveRadiationStop()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnReceiveRadiationStop");

	UBP_GameUI_C_OnReceiveRadiationStop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.OnRadiationIntensityUpdated
// ()
// Parameters:
// float*                         radiationIntensity             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         radiationImmunity              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::OnRadiationIntensityUpdated(float* radiationIntensity, float* radiationImmunity)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.OnRadiationIntensityUpdated");

	UBP_GameUI_C_OnRadiationIntensityUpdated_Params params;
	params.radiationIntensity = radiationIntensity;
	params.radiationImmunity = radiationImmunity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ForceStopRadiationUI
// ()

void UBP_GameUI_C::ForceStopRadiationUI()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ForceStopRadiationUI");

	UBP_GameUI_C_ForceStopRadiationUI_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameUI.BP_GameUI_C.ExecuteUbergraph_BP_GameUI
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_GameUI_C::ExecuteUbergraph_BP_GameUI(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameUI.BP_GameUI_C.ExecuteUbergraph_BP_GameUI");

	UBP_GameUI_C_ExecuteUbergraph_BP_GameUI_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
