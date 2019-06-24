#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_OptionValueController_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_OptionValueController.Widget_OptionValueController_C
// 0x0028 (0x0230 - 0x0208)
class UWidget_OptionValueController_C : public UUserWidget
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0208(0x0008) (ZeroConstructor, Transient, DuplicateTransient)
	struct FLinearColor                                mHoveredColor;                                            // 0x0210(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	struct FLinearColor                                mUnhoveredColor;                                          // 0x0220(0x0010) (Edit, BlueprintVisible, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_OptionValueController.Widget_OptionValueController_C");
		return ptr;
	}


	void OnRowHovered();
	void OnRowUnhovered();
	void Construct();
	void ExecuteUbergraph_Widget_OptionValueController(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
