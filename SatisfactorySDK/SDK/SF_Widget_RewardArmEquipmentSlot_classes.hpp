#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_RewardArmEquipmentSlot_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C
// 0x0090 (0x03C0 - 0x0330)
class UWidget_RewardArmEquipmentSlot_C : public UWidget_SchematicRewardItem_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0330(0x0008) (Transient, DuplicateTransient)
	struct FSlateBrush                                 mInventorySlotBrush;                                      // 0x0338(0x0088) (Edit, BlueprintVisible, DisableEditOnInstance)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_RewardArmEquipmentSlot.Widget_RewardArmEquipmentSlot_C");
		return ptr;
	}


	void IsValidRewardItem(bool* IsValid);
	void UpdateVisibility();
	void PreConstruct(bool* IsDesignTime);
	void Construct();
	void ExecuteUbergraph_Widget_RewardArmEquipmentSlot(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
