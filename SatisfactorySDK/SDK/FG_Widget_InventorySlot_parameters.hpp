#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventorySlot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_InventorySlot.Widget_InventorySlot_C.CheckForNuclearWaste
struct UWidget_InventorySlot_C_CheckForNuclearWaste_Params
{
	class UClass*                                      Object;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.QuickMoveInventory
struct UWidget_InventorySlot_C_QuickMoveInventory_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.SetSlotSize
struct UWidget_InventorySlot_C_SetSlotSize_Params
{
	bool                                               SmallSlot;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               BigSlot;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.DropOntoInventorySlot
struct UWidget_InventorySlot_C_DropOntoInventorySlot_Params
{
	class UWidget_InventorySlot_C*                     OtherInventorySlot;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Result;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseButtonUp
struct UWidget_InventorySlot_C_OnMouseButtonUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.ResetHoverEffect
struct UWidget_InventorySlot_C_ResetHoverEffect_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetOrangeColor
struct UWidget_InventorySlot_C_GetOrangeColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotBorderColor
struct UWidget_InventorySlot_C_GetSlotBorderColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackSizeBGColor
struct UWidget_InventorySlot_C_GetStackSizeBGColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnKeyUp
struct UWidget_InventorySlot_C_OnKeyUp_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnKeyDown
struct UWidget_InventorySlot_C_OnKeyDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FKeyEvent*                                  InKeyEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotStateColor
struct UWidget_InventorySlot_C_GetSlotStateColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetBorderVisibility
struct UWidget_InventorySlot_C_GetBorderVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.CheckSlotHasItems
struct UWidget_InventorySlot_C_CheckSlotHasItems_Params
{
	bool                                               slotHasItems;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetSlotColor
struct UWidget_InventorySlot_C_GetSlotColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetNumItems
struct UWidget_InventorySlot_C_GetNumItems_Params
{
	int                                                Num;                                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemClass
struct UWidget_InventorySlot_C_GetItemClass_Params
{
	class UClass*                                      ItemClass;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStack
struct UWidget_InventorySlot_C_GetStack_Params
{
	struct FInventoryStack                             stack;                                                    // (Parm, OutParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseDoubleClick
struct UWidget_InventorySlot_C_OnMouseDoubleClick_Params
{
	struct FGeometry                                   MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent                               MouseEvent;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetTooltipWidget
struct UWidget_InventorySlot_C_GetTooltipWidget_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetNumLabelVisibility
struct UWidget_InventorySlot_C_GetNumLabelVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetFilterImageVisibility
struct UWidget_InventorySlot_C_GetFilterImageVisibility_Params
{
	bool                                               Visible;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.CreateSplitSlider
struct UWidget_InventorySlot_C_CreateSplitSlider_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackNumber
struct UWidget_InventorySlot_C_GetStackNumber_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnFocusReceived
struct UWidget_InventorySlot_C_OnFocusReceived_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetGamepadButtonIsEnabled
struct UWidget_InventorySlot_C_GetGamepadButtonIsEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetFilterImage
struct UWidget_InventorySlot_C_GetFilterImage_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.PlaySomeSound
struct UWidget_InventorySlot_C_PlaySomeSound_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemImageBrush
struct UWidget_InventorySlot_C_GetItemImageBrush_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDrop
struct UWidget_InventorySlot_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseButtonDown
struct UWidget_InventorySlot_C_OnMouseButtonDown_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragDetected
struct UWidget_InventorySlot_C_OnDragDetected_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	class UDragDropOperation*                          Operation;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetStackSizeText
struct UWidget_InventorySlot_C_GetStackSizeText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.GetItemVisibility
struct UWidget_InventorySlot_C_GetItemVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.CacheSlotData
struct UWidget_InventorySlot_C_CacheSlotData_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseLeave
struct UWidget_InventorySlot_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragLeave
struct UWidget_InventorySlot_C_OnDragLeave_Params
{
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnDragEnter
struct UWidget_InventorySlot_C_OnDragEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnFocusLost
struct UWidget_InventorySlot_C_OnFocusLost_Params
{
	struct FFocusEvent*                                InFocusEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.Tick
struct UWidget_InventorySlot_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.SubscribeToParentWindow
struct UWidget_InventorySlot_C_SubscribeToParentWindow_Params
{
	class UWidget_Window_C*                            ParentWindow;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.PreConstruct
struct UWidget_InventorySlot_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.UpdateStyle
struct UWidget_InventorySlot_C_UpdateStyle_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.Destruct
struct UWidget_InventorySlot_C_Destruct_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.Construct
struct UWidget_InventorySlot_C_Construct_Params
{
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.Event CreateNuclearWastePopup
struct UWidget_InventorySlot_C_Event_CreateNuclearWastePopup_Params
{
	bool                                               isNuclearWaste;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.CloseNuclearWastePopup
struct UWidget_InventorySlot_C_CloseNuclearWastePopup_Params
{
	bool                                               ConfirmClicked;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMouseEnter
struct UWidget_InventorySlot_C_OnMouseEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.ExecuteUbergraph_Widget_InventorySlot
struct UWidget_InventorySlot_C_ExecuteUbergraph_Widget_InventorySlot_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnMoveStack__DelegateSignature
struct UWidget_InventorySlot_C_OnMoveStack__DelegateSignature_Params
{
	class UWidget_InventorySlot_C*                     Sender;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_InventorySlot.Widget_InventorySlot_C.OnSlotHovered__DelegateSignature
struct UWidget_InventorySlot_C_OnSlotHovered__DelegateSignature_Params
{
	class UWidget_InventorySlot_C*                     SelfInventorySlot;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
