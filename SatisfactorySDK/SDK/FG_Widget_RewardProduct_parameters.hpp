#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardProduct_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RewardProduct.Widget_RewardProduct_C.IsValidRewardItem
struct UWidget_RewardProduct_C_IsValidRewardItem_Params
{
	bool                                               IsValid;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RewardProduct.Widget_RewardProduct_C.GetName
struct UWidget_RewardProduct_C_GetName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RewardProduct.Widget_RewardProduct_C.GetIcon
struct UWidget_RewardProduct_C_GetIcon_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_RewardProduct.Widget_RewardProduct_C.OnRewardClicked
struct UWidget_RewardProduct_C_OnRewardClicked_Params
{
};

// Function Widget_RewardProduct.Widget_RewardProduct_C.Construct
struct UWidget_RewardProduct_C_Construct_Params
{
};

// Function Widget_RewardProduct.Widget_RewardProduct_C.ExecuteUbergraph_Widget_RewardProduct
struct UWidget_RewardProduct_C_ExecuteUbergraph_Widget_RewardProduct_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
