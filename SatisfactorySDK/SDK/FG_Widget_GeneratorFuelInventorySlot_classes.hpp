#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GeneratorFuelInventorySlot_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C
// 0x0010 (0x0218 - 0x0208)
class UWidget_GeneratorFuelInventorySlot_C : public UUserWidget
{
public:
	class UWidget_InventorySlot_C*                     Widget_InventorySlot;                                     // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class AFGBuildableGeneratorFuel*                   mGenerator;                                               // 0x0210(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_GeneratorFuelInventorySlot.Widget_GeneratorFuelInventorySlot_C");
		return ptr;
	}


	void Init(class AFGBuildableGeneratorFuel* Generator);
	float GetFuelPercent();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
