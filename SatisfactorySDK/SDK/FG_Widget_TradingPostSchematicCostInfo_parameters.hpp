#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPostSchematicCostInfo_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TradingPostSchematicCostInfo.Widget_TradingPostSchematicCostInfo_C.UpdateSchematicCosts
struct UWidget_TradingPostSchematicCostInfo_C_UpdateSchematicCosts_Params
{
	class AFGSchematicManager*                         mSchematicManager;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      mSchematic;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_TradingPost_RecipePreview_C*         mSchematicPreview;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
