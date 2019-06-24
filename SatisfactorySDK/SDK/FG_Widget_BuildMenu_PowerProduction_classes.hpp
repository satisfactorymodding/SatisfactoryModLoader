#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BuildMenu_PowerProduction_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C
// 0x0018 (0x0220 - 0x0208)
class UWidget_BuildMenu_PowerProduction_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UTextBlock*                                  mStatText;                                                // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UClass*                                      mBuildingDesc;                                            // 0x0218(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_BuildMenu_PowerProduction.Widget_BuildMenu_PowerProduction_C");
		return ptr;
	}


	void GetStatText();
	void PreConstruct(bool* IsDesignTime);
	void ExecuteUbergraph_Widget_BuildMenu_PowerProduction(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
