#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SplitterProgrammable_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_SplitterProgrammable.Widget_SplitterProgrammable_C
// 0x0061 (0x02D9 - 0x0278)
class UWidget_SplitterProgrammable_C : public UWidget_UseableBase_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0278(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UWidget_Splitter_OutputList_C*               mCenterOutputList;                                        // 0x0280(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UVerticalBox*                                mContainer;                                               // 0x0288(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Splitter_OutputList_C*               mLeftOutputList;                                          // 0x0290(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Splitter_OutputList_C*               mRightOutputList;                                         // 0x0298(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_ProgrammableSplitter_List_C*         Widget_ProgrammableSplitter_List;                         // 0x02A0(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Window_ContentBackground_DarkMode_C* Widget_Window_ContentBackground_DarkMode;                 // 0x02A8(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Window_DarkMode_C*                   Widget_Window_DarkMode;                                   // 0x02B0(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class AFGBuildableSplitterSmart*                   mSplitterSmart;                                           // 0x02B8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	struct FSplitterSortRule                           mDefaultRule;                                             // 0x02C0(0x0010) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UWidget_SplitterProgrammableRule_C*          mActiveRule;                                              // 0x02D0(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	bool                                               mIsSmartSplitter;                                         // 0x02D8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_SplitterProgrammable.Widget_SplitterProgrammable_C");
		return ptr;
	}


	void DeslectAllRules();
	void SetAddButtonVisibility();
	void CheckIfSmartSplitter();
	int GetLastRuleIndex();
	void UpdateRuleIndexes();
	void GenerateRules();
	void GetOutputFromIndex(int Index, class UVerticalBox** List);
	void AddRuleToOutput(const struct FSplitterSortRule& SplitterSortRule, int RuleIndex);
	void SetWindowTitle();
	void SetSortRuleWidgetBindings(class UWidget_SplitterProgrammableRule_C** Widget);
	int GetNumSortRules();
	void InitWindow();
	void OnRuleRemoved(class UWidget_SplitterProgrammableRule_C* SplitterRule);
	void OnRuleUpdated(int RuleIndex, const struct FSplitterSortRule& RuleData);
	void OnRuleAdded(const struct FSplitterSortRule& RuleData);
	void PreConstruct(bool* IsDesignTime);
	void ShowDescriptors(class UWidget_SplitterProgrammableRule_C* SplitterRule);
	void HideDescriptors();
	void UpdateRuleFromDescriptorList(class UClass* SelectedDescriptor);
	void Construct();
	void UpdateListFromServer();
	void Destruct();
	void BndEvt__mLeftOutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature();
	void BndEvt__mCenterOutputList_K2Node_ComponentBoundEvent_1_OnAddClicked__DelegateSignature();
	void BndEvt__mRightOutputList_K2Node_ComponentBoundEvent_2_OnAddClicked__DelegateSignature();
	void ExecuteUbergraph_Widget_SplitterProgrammable(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
