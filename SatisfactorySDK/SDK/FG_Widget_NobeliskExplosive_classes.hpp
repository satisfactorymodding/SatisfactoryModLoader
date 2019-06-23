#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_NobeliskExplosive_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_NobeliskExplosive.Widget_NobeliskExplosive_C
// 0x0008 (0x0210 - 0x0208)
class UWidget_NobeliskExplosive_C : public UUserWidget
{
public:
	class UProgressBar*                                mNobeliskThrowbar;                                        // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_NobeliskExplosive.Widget_NobeliskExplosive_C");
		return ptr;
	}


	ESlateVisibility Get_mNobeliskThrowbar_Visibility_1();
	struct FLinearColor Get_mNobeliskThrowbar_FillColorAndOpacity_1();
	float GetThrowPercent();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
