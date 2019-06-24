#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardBuildingProductivity_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_RewardBuildingProductivity.Widget_RewardBuildingProductivity_C
// 0x0090 (0x03C0 - 0x0330)
class UWidget_RewardBuildingProductivity_C : public UWidget_SchematicRewardItem_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0330(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FSlateBrush                                 mProductivityBrush;                                       // 0x0338(0x0088) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_RewardBuildingProductivity.Widget_RewardBuildingProductivity_C");
		return ptr;
	}


	void IsValidRewardItem(bool* IsValid);
	void UpdateVisibility();
	void PreConstruct(bool* IsDesignTime);
	void Construct();
	void OnRewardClicked();
	void ExecuteUbergraph_Widget_RewardBuildingProductivity(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
