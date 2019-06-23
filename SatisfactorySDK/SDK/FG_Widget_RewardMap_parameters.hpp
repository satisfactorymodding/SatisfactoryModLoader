#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RewardMap_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RewardMap.Widget_RewardMap_C.IsValidRewardItem
struct UWidget_RewardMap_C_IsValidRewardItem_Params
{
	bool                                               IsValid;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RewardMap.Widget_RewardMap_C.UpdateVisibility
struct UWidget_RewardMap_C_UpdateVisibility_Params
{
};

// Function Widget_RewardMap.Widget_RewardMap_C.PreConstruct
struct UWidget_RewardMap_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RewardMap.Widget_RewardMap_C.Construct
struct UWidget_RewardMap_C_Construct_Params
{
};

// Function Widget_RewardMap.Widget_RewardMap_C.OnRewardClicked
struct UWidget_RewardMap_C_OnRewardClicked_Params
{
};

// Function Widget_RewardMap.Widget_RewardMap_C.ExecuteUbergraph_Widget_RewardMap
struct UWidget_RewardMap_C_ExecuteUbergraph_Widget_RewardMap_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
