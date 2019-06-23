#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventorySlot_DropArea_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C
// 0x0038 (0x0240 - 0x0208)
class UWidget_InventorySlot_DropArea_C : public UUserWidget
{
public:
	class UNamedSlot*                                  mContent;                                                 // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	TEnumAsByte<EInventory_DropArea_States>            mDropAreaState;                                           // 0x0210(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0211(0x0007) MISSED OFFSET
	TArray<class UWidget_InventorySlot_C*>             mInventorySlots;                                          // 0x0218(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	class UWidget_TradingPost_PayOffGrid_C*            mHudPayOffGrid;                                           // 0x0228(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget_SpaceElevator_C*                     mSpaceElevator;                                           // 0x0230(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	class UWidget_MAMResearchSlot_C*                   mMAMResearchSlot;                                         // 0x0238(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_InventorySlot_DropArea.Widget_InventorySlot_DropArea_C");
		return ptr;
	}


	void OnDropInventorySlot(class UWidget_InventorySlot_C* InventorySlot, bool* Result);
	void FindCorrectSlot(class UWidget_InventorySlot_C* payload, class UWidget_InventorySlot_C** InventorySlot, bool* Success);
	bool OnDrop(struct FGeometry* MyGeometry, struct FPointerEvent* PointerEvent, class UDragDropOperation** Operation);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
