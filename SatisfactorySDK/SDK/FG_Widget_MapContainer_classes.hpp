#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MapContainer_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_MapContainer.Widget_MapContainer_C
// 0x00A8 (0x0300 - 0x0258)
class UWidget_MapContainer_C : public UFGInteractWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0258(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	class UTextBlock*                                  mMenuButtonText;                                          // 0x0260(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UButton*                                     mShowHideButton;                                          // 0x0268(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class USlider*                                     mZoomSlider;                                              // 0x0270(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UTextBlock*                                  mZoomText;                                                // 0x0278(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_ButtonShine_C*                       Widget_ButtonShine;                                       // 0x0280(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Map_C*                               Widget_Map;                                               // 0x0288(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Map_Filters_Container_C*             Widget_Map_Filters_Container;                             // 0x0290(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Window_ContentBackground_DarkMode_C* Widget_Window_ContentBackground_DarkMode;                 // 0x0298(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	class UWidget_Window_DarkMode_C*                   Widget_Window_DarkMode;                                   // 0x02A0(0x0008) (BlueprintVisible, ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData, RepSkip, RepNotify, Interp, NonTransactional, EditorOnly, NoDestructor, AutoWeak, ContainsInstancedReference, AssetRegistrySearchable, SimpleDisplay, AdvancedDisplay, Protected, BlueprintCallable, BlueprintAuthorityOnly, TextExportTransient, NonPIEDuplicateTransient, ExposeOnSpawn, PersistentInstance, UObjectWrapper, HasGetValueTypeHash, NativeAccessSpecifierPublic, NativeAccessSpecifierProtected, NativeAccessSpecifierPrivate)
	bool                                               IsMapOpen;                                                // 0x02A8(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x02A9(0x0007) MISSED OFFSET
	TArray<struct FMapFilterStruct>                    mFilterCategories;                                        // 0x02B0(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)
	struct FTimerHandle                                mAnimationTimer;                                          // 0x02C0(0x0008) (Edit, BlueprintVisible, DisableEditOnInstance)
	class UWidget_MapObject_C*                         mHoveredMapObject;                                        // 0x02C8(0x0008) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, InstancedReference, IsPlainOldData)
	int                                                mBeaconInt;                                               // 0x02D0(0x0004) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x02D4(0x0004) MISSED OFFSET
	struct FMapFilterStruct                            mBeaconSearchResult;                                      // 0x02D8(0x0028) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_MapContainer.Widget_MapContainer_C");
		return ptr;
	}


	void UpdateBeaconViewDistances();
	void SetupBeaconBindings(class UWidget_BeaconViewdistanceSlider_C* WidgetBeaconViewdistanceSlider);
	void ClearSearch();
	void PopulateSearchResults(const struct FText& Text);
	void GetBeacons(struct FMapFilterStruct* BeaconCategory);
	void AddChildToBeacons(class UFGActorRepresentation* actorRepresentation);
	void RemoveActorRepresentationFromFilterCategories(class UFGActorRepresentation* actorRepresentation);
	struct FText UglyFixForActorName(ERepresentationType actorRepresentation);
	void UpdateMapObjectVisibility(ERepresentationType Type);
	bool GetCompassRepresentation(ERepresentationType Type);
	bool GetMapRepresentation(ERepresentationType Type);
	void SetCompassRepresentation(ERepresentationType Type, bool visible);
	void SetMapRepresentation(ERepresentationType Type, bool visible);
	int GetIndexInParent(class UWidget* Widget);
	void AddUniqueToFilterCategories(class UFGActorRepresentation* actorRepresentation, class UWidget_MapObject_C* WidgetMapObject, bool* CreatedNewCategory);
	void AddChildToFilters(ERepresentationType actorRepresentation);
	void NormalizedValueToZoomValue(float NormalizedValue, struct FVector2D* ZoomValue);
	void UpdateZoomSlider();
	void SetOpenMap(bool OpenMap);
	void Construct();
	void CloseMap();
	void OnEscapePressed();
	void Destruct();
	void BndEvt__mZoomSlider_K2Node_ComponentBoundEvent_0_OnFloatValueChangedEvent__DelegateSignature(float Value);
	void SetInputMode();
	void BndEvt__Widget_Map_K2Node_ComponentBoundEvent_1_OnObjectAddedToMapDispatch__DelegateSignature(class UFGActorRepresentation* actorRepresentation, class UWidget_MapObject_C* WidgetMapObject);
	void BndEvt__Widget_Map_K2Node_ComponentBoundEvent_2_OnObjectUpdatedOnMapDispatch__DelegateSignature(class UFGActorRepresentation* actorRepresentation);
	void BndEvt__Widget_Map_K2Node_ComponentBoundEvent_3_OnObjectRemovedFromMapDispatch__DelegateSignature(class UFGActorRepresentation* ActorRespresentation);
	void OnFilterHovered(class UWidget_FilterButton_C* Instigator);
	void OnFilterUnhovered(class UWidget_FilterButton_C* Instigator);
	void onFilterShowOnMapChanged(class UWidget_FilterButton_C* Instigator, bool ShowOnMap);
	void onFilterShowOnCompassChanged(class UWidget_FilterButton_C* Instigator, bool ShowOnCompass);
	void BndEvt__Button_0_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature();
	void OnBeaconViewDistanceChanged(class UWidget_BeaconViewdistanceSlider_C* Instigator, ECompassViewDistance NewViewDistance);
	void OnBeaconHovered(class UWidget_BeaconViewdistanceSlider_C* Instigaotr);
	void OnBeaconUnhovered(class UWidget_BeaconViewdistanceSlider_C* Instigator);
	void OnBeaconVeiwDistanceHovered(class UWidget_BeaconViewdistanceSlider_C* Instigator, ECompassViewDistance viewDistance);
	void OnBeaconViewDistanceUnhovered(class UWidget_BeaconViewdistanceSlider_C* Instigator);
	void BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_5_OnBeaconSearchChanged__DelegateSignature(const struct FText& Text);
	void BndEvt__Widget_Map_Filters_Container_K2Node_ComponentBoundEvent_6_OnClearSearchResults__DelegateSignature();
	void ExecuteUbergraph_Widget_MapContainer(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
