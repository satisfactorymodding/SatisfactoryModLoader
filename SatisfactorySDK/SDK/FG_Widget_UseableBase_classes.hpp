#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_UseableBase_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_UseableBase.Widget_UseableBase_C
// 0x0020 (0x0278 - 0x0258)
class UWidget_UseableBase_C : public UFGInteractWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0258(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	bool                                               mShouldOpenInventory;                                     // 0x0260(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0261(0x0007) MISSED OFFSET
	struct FScriptMulticastDelegate                    InventorySlotStackMoveEvent;                              // 0x0268(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_UseableBase.Widget_UseableBase_C");
		return ptr;
	}


	void DropInventoryStackOnInventoryWidget(class UWidget_InventorySlot_C* InventorySlot, class UWidget_Inventory_C* WidgetInventory, bool* Result);
	void InitInventoryWidgetCallbacks(class UWidget_Inventory_C* InventoryComponent);
	void OnInventorySlotStackMove(class UWidget_InventorySlot_C* InventorySlot);
	void DropInventorySlotStack(class UWidget_InventorySlot_C* InventorySlot, bool* WasStackMoved);
	void SetInventoryVisibility(bool Visible);
	void GetDefaultRCO(class UBP_RemoteCallObject_C** RCO);
	void PreConstruct(bool* IsDesignTime);
	void Construct();
	void Destruct();
	void SetupDefaultFocus();
	void ExecuteUbergraph_Widget_UseableBase(int EntryPoint);
	void InventorySlotStackMoveEvent__DelegateSignature(class UWidget_InventorySlot_C* InventorySlot, TEnumAsByte<EInteractionDirection> InteractionDirection);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
