#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPost_PayOffGrid_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C
// 0x0030 (0x0238 - 0x0208)
class UWidget_TradingPost_PayOffGrid_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UUniformGridPanel*                           mPayOffGrid;                                              // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UClass*                                      mSchematic;                                               // 0x0218(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UWidget_TradingPost_C*                       mTradingPostWidget;                                       // 0x0220(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	TArray<class UWidget_TradingPostPayOffSlot_C*>     mPayOffSlots;                                             // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_TradingPost_PayOffGrid.Widget_TradingPost_PayOffGrid_C");
		return ptr;
	}


	void DropInventorySlotStack(class UWidget_InventorySlot_C* InventorySlot, bool* Result);
	void SetUpPayOffSlots(class UClass* mSchematic);
	void Construct();
	void ExecuteUbergraph_Widget_TradingPost_PayOffGrid(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
