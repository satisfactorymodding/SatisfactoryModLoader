// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPostSchematicCostInfo_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_TradingPostSchematicCostInfo.Widget_TradingPostSchematicCostInfo_C.UpdateSchematicCosts
// ()
// Parameters:
// class AFGSchematicManager*     mSchematicManager              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UClass*                  mSchematic                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UWidget_TradingPost_RecipePreview_C* mSchematicPreview              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void UWidget_TradingPostSchematicCostInfo_C::UpdateSchematicCosts(class AFGSchematicManager* mSchematicManager, class UClass* mSchematic, class UWidget_TradingPost_RecipePreview_C* mSchematicPreview)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_TradingPostSchematicCostInfo.Widget_TradingPostSchematicCostInfo_C.UpdateSchematicCosts");

	UWidget_TradingPostSchematicCostInfo_C_UpdateSchematicCosts_Params params;
	params.mSchematicManager = mSchematicManager;
	params.mSchematic = mSchematic;
	params.mSchematicPreview = mSchematicPreview;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
