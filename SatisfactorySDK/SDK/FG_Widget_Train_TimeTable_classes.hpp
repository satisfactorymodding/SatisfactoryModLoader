#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Train_TimeTable_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_Train_TimeTable.Widget_Train_TimeTable_C
// 0x0078 (0x0280 - 0x0208)
class UWidget_Train_TimeTable_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UOverlay*                                    mApplyChangesPrompt;                                      // 0x0210(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Splitter_OutputList_C*               Widget_Splitter_OutputList;                               // 0x0218(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Window_ContentBackground_DarkMode_C* Widget_Window_ContentBackground_DarkMode;                 // 0x0220(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	TArray<class AFGTrainStationIdentifier*>           mTrainStations;                                           // 0x0228(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance)
	class AFGTrain*                                    mTrain;                                                   // 0x0238(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnTemplate, DisableEditOnInstance, IsPlainOldData)
	class AFGRailroadTimeTable*                        mTimeTable;                                               // 0x0240(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	class UWidget_Train_TimeTable_AvilableStations_C*  mAvailableStationsWidget;                                 // 0x0248(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UWidget_Train_TimeTable_Rule_C*              SelectedRule;                                             // 0x0250(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	int                                                mAvailableStationsSelectedIndex;                          // 0x0258(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x025C(0x0004) MISSED OFFSET
	TArray<struct FTimeTableStop>                      mNewStops;                                                // 0x0260(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	class UWidget_Train_TimeTable_Rule_C*              mCurrentStopRule;                                         // 0x0270(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	struct FTimerHandle                                mCheckCurrentStopTimer;                                   // 0x0278(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_Train_TimeTable.Widget_Train_TimeTable_C");
		return ptr;
	}


	void SetCurrentStop(class UWidget_Train_TimeTable_Rule_C* RuleWidget);
	void ShowApplyChangesPrompt();
	void CloseAvailableStationsWidget();
	void MoveRule(class UWidget_Train_TimeTable_Rule_C* RuleWidget, bool MoveDown);
	void SetSelectedRule(class UWidget_Train_TimeTable_Rule_C* SelectedRule);
	void AddRule(class AFGTrainStationIdentifier* mStation);
	void UpdateStopsOnServer();
	void GenerateNewStopArray();
	void PopulateAvailableStations();
	void PopulateTimeTable();
	void UpdateTrainStations();
	void Init(class AFGTrain* Train);
	void BndEvt__Widget_Splitter_OutputList_K2Node_ComponentBoundEvent_0_OnAddClicked__DelegateSignature();
	void OnRuleClicked(class UWidget_Train_TimeTable_Rule_C* RuleWidget);
	void UpdateStation();
	void UpdateAvailableStationsSelectedIndex(int Index, class UWidget_ListButton_C* ListButton);
	void OnRuleDeleted(class UWidget_Train_TimeTable_Rule_C* RuleWidget);
	void Destruct();
	void OnRuleMoveUp(class UWidget_Train_TimeTable_Rule_C* RuleWidget);
	void OnRuleMoveDown(class UWidget_Train_TimeTable_Rule_C* RuleWidget);
	void CheckCurrentStop();
	void ExecuteUbergraph_Widget_Train_TimeTable(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
