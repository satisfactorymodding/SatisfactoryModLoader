#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupToggleSelect_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_PopupToggleSelect.Widget_PopupToggleSelect_C
// 0x0048 (0x0260 - 0x0218)
class UWidget_PopupToggleSelect_C : public UFGPopupWidgetContent
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0218(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UHorizontalBox*                              mSlot;                                                    // 0x0220(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UTextBlock*                                  mTitleText;                                               // 0x0228(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	struct FText                                       mBody;                                                    // 0x0230(0x0028) (Edit, BlueprintVisible)
	int                                                mSelectedChild;                                           // 0x0248(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x024C(0x0004) MISSED OFFSET
	TArray<class UUserWidget*>                         mSelectionWidgets;                                        // 0x0250(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_PopupToggleSelect.Widget_PopupToggleSelect_C");
		return ptr;
	}


	void SetOptionalTextElements(struct FText* Title, struct FText* Desc);
	bool GetShouldOkayBeEnabled();
	void SetInstigatorAndInitialize(class UObject** Instigator);
	void OnChildSelected(int ChildIndex);
	void NotifyPopupConfirmed();
	void NotifyPopupCanceled();
	void ExecuteUbergraph_Widget_PopupToggleSelect(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
