#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_CompassObjectCardinalDirection_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C
// 0x0010 (0x0280 - 0x0270)
class UWidget_CompassObjectCardinalDirection_C : public UFGCompassObjectWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0270(0x0008) (Transient, DuplicateTransient)
	class UImage*                                      Image_1;                                                  // 0x0278(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_CompassObjectCardinalDirection.Widget_CompassObjectCardinalDirection_C");
		return ptr;
	}


	ESlateVisibility GetVisibility_1();
	void OnCompassObjectAddedToPanel(class UCanvasPanelSlot** parentSlot);
	void ExecuteUbergraph_Widget_CompassObjectCardinalDirection(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
