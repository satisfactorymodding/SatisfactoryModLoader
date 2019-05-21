#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Widget_RewardProduct_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// WidgetBlueprintGeneratedClass Widget_RewardProduct.Widget_RewardProduct_C
// 0x0020 (0x0350 - 0x0330)
class UWidget_RewardProduct_C : public UWidget_SchematicRewardItem_C
{
public:
	struct FPointerToUberGraphFrame                    UberGraphFrame;                                           // 0x0330(0x0008) (Transient, DuplicateTransient)
	struct FItemAmount                                 mProduct;                                                 // 0x0338(0x0010) (Edit, BlueprintVisible)
	class UTexture*                                    mForcedCategoryIcon;                                      // 0x0348(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("WidgetBlueprintGeneratedClass Widget_RewardProduct.Widget_RewardProduct_C");
		return ptr;
	}


	void IsValidRewardItem(bool* IsValid);
	struct FText GetName();
	struct FSlateBrush GetIcon();
	void OnRewardClicked();
	void Construct();
	void ExecuteUbergraph_Widget_RewardProduct(int EntryPoint);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
