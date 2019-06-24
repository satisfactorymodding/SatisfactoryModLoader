#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupContentResolutionTimer_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C
// 0x0034 (0x024C - 0x0218)
class UWidget_PopupContentResolutionTimer_C : public UFGPopupWidgetContent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0218(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UTextBlock*                                  mText;                                                    // 0x0220(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	struct FText                                       mBody;                                                    // 0x0228(0x0028) (Edit, BlueprintVisible)
	struct FTimerHandle                                TimerHandle;                                              // 0x0240(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	float                                              TimerDuration;                                            // 0x0248(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_PopupContentResolutionTimer.Widget_PopupContentResolutionTimer_C");
		return ptr;
	}


	bool GetShouldOkayBeEnabled();
	struct FText Get_TimerText();
	void Construct();
	void TriggerCancel();
	void SetOptionalTextElements(struct FText* Title, struct FText* Desc);
	void Destruct();
	void ExecuteUbergraph_Widget_PopupContentResolutionTimer(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
