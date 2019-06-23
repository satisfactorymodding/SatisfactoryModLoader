#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TabsContainer_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_TabsContainer.Widget_TabsContainer_C
// 0x0090 (0x0298 - 0x0208)
class UWidget_TabsContainer_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UCanvasPanel*                                mContainer;                                               // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_SlidingTabs_Button_C*                Widget_SlidingTabs_Button;                                // 0x0218(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_SlidingTabs_C*                       mSlidingTabsWidget;                                       // 0x0220(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FImageAndText>                       mButtons;                                                 // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	struct FVector2D                                   mButtonSize;                                              // 0x0238(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FScriptMulticastDelegate                    OnButtonHovered;                                          // 0x0240(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnButtonUnhovered;                                        // 0x0250(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnButtonClicked;                                          // 0x0260(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	bool                                               mOverrideButtonFunctions;                                 // 0x0270(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0271(0x0007) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnNoTabsGenerated;                                        // 0x0278(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnTabsGenerated;                                          // 0x0288(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, BlueprintAssignable)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_TabsContainer.Widget_TabsContainer_C");
		return ptr;
	}


	void SetActiveButton(class UWidget_SlidingTabs_Button_C* ActiveButton);
	void IfButtonClicked(class UWidget_SlidingTabs_Button_C* Instigator);
	void IfButtonUnhovered(class UWidget_SlidingTabs_Button_C* Insitagor);
	void IfButtonHovered(class UWidget_SlidingTabs_Button_C* Instigator);
	void GenerateButtons();
	void PreConstruct(bool* IsDesignTime);
	void Init();
	void Destruct();
	void ExecuteUbergraph_Widget_TabsContainer(int EntryPoint);
	void OnTabsGenerated__DelegateSignature();
	void OnNoTabsGenerated__DelegateSignature();
	void OnButtonClicked__DelegateSignature(int ButtonIndex);
	void OnButtonUnhovered__DelegateSignature(bool IsActiveButton);
	void OnButtonHovered__DelegateSignature(bool IsActiveButton);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
