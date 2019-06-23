#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPostSchematicCostInfo_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_TradingPostSchematicCostInfo.Widget_TradingPostSchematicCostInfo_C
// 0x0030 (0x0238 - 0x0208)
class UWidget_TradingPostSchematicCostInfo_C : public UUserWidget
{
public:
	class UWrapBox*                                    mCostGrid;                                                // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class ABuild_TradingPost_C*                        mTradingPost;                                             // 0x0210(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class UClass*                                      mSchematic;                                               // 0x0218(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class AFGSchematicManager*                         mSchematicManager;                                        // 0x0220(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	TArray<class UWidget_CostSlotWrapper_C*>           AllCostSlots;                                             // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_TradingPostSchematicCostInfo.Widget_TradingPostSchematicCostInfo_C");
		return ptr;
	}


	void UpdateSchematicCosts(class AFGSchematicManager* mSchematicManager, class UClass* mSchematic, class UWidget_TradingPost_RecipePreview_C* mSchematicPreview);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
