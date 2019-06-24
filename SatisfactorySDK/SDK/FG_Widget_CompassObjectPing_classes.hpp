#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CompassObjectPing_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_CompassObjectPing.Widget_CompassObjectPing_C
// 0x0010 (0x0288 - 0x0278)
class UWidget_CompassObjectPing_C : public UFGCompassObjectWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0278(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UWidget_MapCompass_Icon_C*                   Widget_MapCompass_Icon;                                   // 0x0280(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_CompassObjectPing.Widget_CompassObjectPing_C");
		return ptr;
	}


	void Construct();
	void ExecuteUbergraph_Widget_CompassObjectPing(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
