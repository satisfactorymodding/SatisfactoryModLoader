#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_OptionsCheckbox_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_OptionsCheckbox.Widget_OptionsCheckbox_C
// 0x0370 (0x05A0 - 0x0230)
class UWidget_OptionsCheckbox_C : public UWidget_OptionValueController_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0230(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UImage*                                      mBG;                                                      // 0x0238(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UButton*                                     mButton;                                                  // 0x0240(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UImage*                                      mCheck;                                                   // 0x0248(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UBorder*                                     mTintBorder;                                              // 0x0250(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	struct FSlateBrush                                 mUnchecked;                                               // 0x0258(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 mUncheckedPressed;                                        // 0x02E0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 mUncheckedHover;                                          // 0x0368(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 mChecked;                                                 // 0x03F0(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 mCheckedHover;                                            // 0x0478(0x0088) (Edit, BlueprintVisible)
	struct FSlateBrush                                 mCheckedPressed;                                          // 0x0500(0x0088) (Edit, BlueprintVisible)
	bool                                               mIsChecked;                                               // 0x0588(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0589(0x0007) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnCheckChanged;                                           // 0x0590(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_OptionsCheckbox.Widget_OptionsCheckbox_C");
		return ptr;
	}


	void SetChecked(bool mIsChecked, bool TriggerCheckedEvent, bool* IsChecked);
	void BndEvt__mButton_K2Node_ComponentBoundEvent_5_OnButtonPressedEvent__DelegateSignature();
	void BndEvt__mButton_K2Node_ComponentBoundEvent_6_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__mButton_K2Node_ComponentBoundEvent_7_OnButtonHoverEvent__DelegateSignature();
	void BndEvt__mButton_K2Node_ComponentBoundEvent_8_OnButtonClickedEvent__DelegateSignature();
	void PreConstruct(bool* IsDesignTime);
	void OnRowHovered();
	void OnRowUnhovered();
	void ExecuteUbergraph_Widget_OptionsCheckbox(int EntryPoint);
	void OnCheckChanged__DelegateSignature(bool IsChecked);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
