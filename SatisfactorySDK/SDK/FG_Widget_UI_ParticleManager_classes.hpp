#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_UI_ParticleManager_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_UI_ParticleManager.Widget_UI_ParticleManager_C
// 0x0024 (0x022C - 0x0208)
class UWidget_UI_ParticleManager_C : public UUserWidget
{
public:
	class UCanvasPanel*                                mParticleContainer;                                       // 0x0208(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	TArray<struct FCursorParticleStruct>               mParticleWidgets;                                         // 0x0210(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	class UWidget*                                     mLastClickedParticleWidget;                               // 0x0220(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	int                                                mParticleWidgetClickCount;                                // 0x0228(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_UI_ParticleManager.Widget_UI_ParticleManager_C");
		return ptr;
	}


	void CreateParticle();
	struct FEventReply OnMouseButtonDown(struct FGeometry* MyGeometry, struct FPointerEvent* MouseEvent);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
