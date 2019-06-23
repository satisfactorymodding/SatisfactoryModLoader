#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SchematicPopUp_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.ClearRelevantRewards
struct UWidget_SchematicPopUp_C_ClearRelevantRewards_Params
{
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.CreateRewardIcon
struct UWidget_SchematicPopUp_C_CreateRewardIcon_Params
{
	class UTexture*                                    Icon;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Icon_Text;                                                // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.GenerateSchematicRewardIcons
struct UWidget_SchematicPopUp_C_GenerateSchematicRewardIcons_Params
{
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.SetRelevantRewards
struct UWidget_SchematicPopUp_C_SetRelevantRewards_Params
{
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.Set Stinger Content
struct UWidget_SchematicPopUp_C_Set_Stinger_Content_Params
{
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.GetSchematicUnlockedText
struct UWidget_SchematicPopUp_C_GetSchematicUnlockedText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.Construct
struct UWidget_SchematicPopUp_C_Construct_Params
{
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.OnSchematicPurchased
struct UWidget_SchematicPopUp_C_OnSchematicPurchased_Params
{
	class UClass*                                      Schematic;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SchematicPopUp.Widget_SchematicPopUp_C.ExecuteUbergraph_Widget_SchematicPopUp
struct UWidget_SchematicPopUp_C_ExecuteUbergraph_Widget_SchematicPopUp_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
