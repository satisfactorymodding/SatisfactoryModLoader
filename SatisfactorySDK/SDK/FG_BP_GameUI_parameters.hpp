#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GameUI_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_GameUI.BP_GameUI_C.OnPreviewKeyDown
struct UBP_GameUI_C_OnPreviewKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_GameUI.BP_GameUI_C.SetVersionLabelPosition
struct UBP_GameUI_C_SetVersionLabelPosition_Params
{
};

// Function BP_GameUI.BP_GameUI_C.GetExperimentalVisibility
struct UBP_GameUI_C_GetExperimentalVisibility_Params
{
};

// Function BP_GameUI.BP_GameUI_C.GetChildUIVisibility
struct UBP_GameUI_C_GetChildUIVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.PrePopWidget
struct UBP_GameUI_C_PrePopWidget_Params
{
	class UFGInteractWidget*                           WidgetBeingRemoved;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.ShowTutorialHint
struct UBP_GameUI_C_ShowTutorialHint_Params
{
};

// Function BP_GameUI.BP_GameUI_C.GetFGHUD
struct UBP_GameUI_C_GetFGHUD_Params
{
	class AFGHUD*                                      HUD;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.SetPrototypeCameraVisibility
struct UBP_GameUI_C_SetPrototypeCameraVisibility_Params
{
	bool                                               New_Visibility;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.SetPrototypeVisibility
struct UBP_GameUI_C_SetPrototypeVisibility_Params
{
	bool                                               NewVisibility;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.OnInventorySlotStackMove
struct UBP_GameUI_C_OnInventorySlotStackMove_Params
{
	class UWidget_InventorySlot_C*                     InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	TEnumAsByte<EInteractionDirection>                 InteractionDirection;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.CreateAddOnPlayerInventory
struct UBP_GameUI_C_CreateAddOnPlayerInventory_Params
{
	class UPanelWidget*                                Container;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.IsChatWindowVisible
struct UBP_GameUI_C_IsChatWindowVisible_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.PlayAudioMessage
struct UBP_GameUI_C_PlayAudioMessage_Params
{
	class UClass*                                      MessageClass;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.GetUIVisibility
struct UBP_GameUI_C_GetUIVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.GetEquipmentHUDParent
struct UBP_GameUI_C_GetEquipmentHUDParent_Params
{
	EEquipmentSlot                                     slotType;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UOverlay*                                    overlayParent;                                            // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.OnKeyDown
struct UBP_GameUI_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_GameUI.BP_GameUI_C.HUDPanelVisibility
struct UBP_GameUI_C_HUDPanelVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.GetMessageNotifierVisibility
struct UBP_GameUI_C_GetMessageNotifierVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.UpdateHUDVisibility
struct UBP_GameUI_C_UpdateHUDVisibility_Params
{
};

// Function BP_GameUI.BP_GameUI_C.GetSchematicPopupVisibility
struct UBP_GameUI_C_GetSchematicPopupVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.AddMessageNotification
struct UBP_GameUI_C_AddMessageNotification_Params
{
	class UClass*                                      newMessage;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.GetItemDropLocation
struct UBP_GameUI_C_GetItemDropLocation_Params
{
	struct FVector                                     dropLocation;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.OnDrop
struct UBP_GameUI_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.RefreshInputMode
struct UBP_GameUI_C_RefreshInputMode_Params
{
};

// Function BP_GameUI.BP_GameUI_C.CreatePopupWidget
struct UBP_GameUI_C_CreatePopupWidget_Params
{
	struct FPopupData*                                 PopupData;                                                // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UFGPopupWidget*                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.GetReloadRespawnText
struct UBP_GameUI_C_GetReloadRespawnText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_GameUI.BP_GameUI_C.GetReloadRespawnTextVisibility
struct UBP_GameUI_C_GetReloadRespawnTextVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.PopAllWidgets_Internal
struct UBP_GameUI_C_PopAllWidgets_Internal_Params
{
};

// Function BP_GameUI.BP_GameUI_C.FindWidgetByClass
struct UBP_GameUI_C_FindWidgetByClass_Params
{
	class UClass*                                      WidgetClass;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UFGInteractWidget*                           Widget;                                                   // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.DoesWidgetExist
struct UBP_GameUI_C_DoesWidgetExist_Params
{
	class UClass*                                      WidgetClass;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               doesExist;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.FindWidgetToPop
struct UBP_GameUI_C_FindWidgetToPop_Params
{
	class UFGInteractWidget*                           WidgetToPop;                                              // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.PopWidget
struct UBP_GameUI_C_PopWidget_Params
{
	class UFGInteractWidget*                           widgetToRemove;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.GetPlayerInteractionVisibility
struct UBP_GameUI_C_GetPlayerInteractionVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.PopAllWidgets
struct UBP_GameUI_C_PopAllWidgets_Params
{
};

// Function BP_GameUI.BP_GameUI_C.ClosePopup
struct UBP_GameUI_C_ClosePopup_Params
{
};

// Function BP_GameUI.BP_GameUI_C.Destruct
struct UBP_GameUI_C_Destruct_Params
{
};

// Function BP_GameUI.BP_GameUI_C.Play Landed Effect
struct UBP_GameUI_C_Play_Landed_Effect_Params
{
	float                                              Velocity;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.PushWidget
struct UBP_GameUI_C_PushWidget_Params
{
	class UFGInteractWidget*                           Widget;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.ReceivedMessage
struct UBP_GameUI_C_ReceivedMessage_Params
{
	class UClass**                                     inMessage;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.RemoveAudioMessage
struct UBP_GameUI_C_RemoveAudioMessage_Params
{
};

// Function BP_GameUI.BP_GameUI_C.AddIntroTutorialInfo
struct UBP_GameUI_C_AddIntroTutorialInfo_Params
{
	struct FTutorialHintData*                          TutorialHintData;                                         // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_GameUI.BP_GameUI_C.UpdateTutorialInfo
struct UBP_GameUI_C_UpdateTutorialInfo_Params
{
	struct FTutorialHintData                           hintData;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_GameUI.BP_GameUI_C.HandleFocusLost
struct UBP_GameUI_C_HandleFocusLost_Params
{
};

// Function BP_GameUI.BP_GameUI_C.AddPawnHUD
struct UBP_GameUI_C_AddPawnHUD_Params
{
	class UUserWidget**                                newContent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.RemovePawnHUD
struct UBP_GameUI_C_RemovePawnHUD_Params
{
};

// Function BP_GameUI.BP_GameUI_C.AddInteractWidget
struct UBP_GameUI_C_AddInteractWidget_Params
{
	class UFGInteractWidget**                          widgetToAdd;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.OnPlayerBeginTypeMessage
struct UBP_GameUI_C_OnPlayerBeginTypeMessage_Params
{
};

// Function BP_GameUI.BP_GameUI_C.Construct
struct UBP_GameUI_C_Construct_Params
{
};

// Function BP_GameUI.BP_GameUI_C.OnChatMessageReceived
struct UBP_GameUI_C_OnChatMessageReceived_Params
{
};

// Function BP_GameUI.BP_GameUI_C.ClearHintOnTutorialStepCompleted
struct UBP_GameUI_C_ClearHintOnTutorialStepCompleted_Params
{
};

// Function BP_GameUI.BP_GameUI_C.ResetInput
struct UBP_GameUI_C_ResetInput_Params
{
};

// Function BP_GameUI.BP_GameUI_C.ShowRespawnMessage
struct UBP_GameUI_C_ShowRespawnMessage_Params
{
};

// Function BP_GameUI.BP_GameUI_C.OnReceiveRadiationStart
struct UBP_GameUI_C_OnReceiveRadiationStart_Params
{
};

// Function BP_GameUI.BP_GameUI_C.OnReceiveRadiationStop
struct UBP_GameUI_C_OnReceiveRadiationStop_Params
{
};

// Function BP_GameUI.BP_GameUI_C.OnRadiationIntensityUpdated
struct UBP_GameUI_C_OnRadiationIntensityUpdated_Params
{
	float*                                             radiationIntensity;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             radiationImmunity;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_GameUI.BP_GameUI_C.ForceStopRadiationUI
struct UBP_GameUI_C_ForceStopRadiationUI_Params
{
};

// Function BP_GameUI.BP_GameUI_C.ExecuteUbergraph_BP_GameUI
struct UBP_GameUI_C_ExecuteUbergraph_BP_GameUI_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
