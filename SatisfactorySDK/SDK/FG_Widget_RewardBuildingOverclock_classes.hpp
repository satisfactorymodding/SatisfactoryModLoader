#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardBuildingOverclock_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C
// 0x0090 (0x03C0 - 0x0330)
class UWidget_RewardBuildingOverclock_C : public UWidget_SchematicRewardItem_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0330(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FSlateBrush                                 mOverclockBrush;                                          // 0x0338(0x0088) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_RewardBuildingOverclock.Widget_RewardBuildingOverclock_C");
		return ptr;
	}


	void IsValidRewardItem(bool* IsValid);
	void UpdateVisibility();
	struct FText GetName();
	struct FSlateBrush GetIcon();
	void PreConstruct(bool* IsDesignTime);
	void Tick(struct FGeometry* MyGeometry, float* InDeltaTime);
	void OnRewardClicked();
	void ExecuteUbergraph_Widget_RewardBuildingOverclock(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
