#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SchematicList_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SchematicList.Widget_SchematicList_C.GetTradingPostWidget
struct UWidget_SchematicList_C_GetTradingPostWidget_Params
{
};

// Function Widget_SchematicList.Widget_SchematicList_C.PopulateSchematicForTier
struct UWidget_SchematicList_C_PopulateSchematicForTier_Params
{
	int                                                inTier;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	TArray<class UClass*>                              schematicsInRing;                                         // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_SchematicList.Widget_SchematicList_C.CreateSchematicButtons
struct UWidget_SchematicList_C_CreateSchematicButtons_Params
{
};

// Function Widget_SchematicList.Widget_SchematicList_C.Construct
struct UWidget_SchematicList_C_Construct_Params
{
};

// Function Widget_SchematicList.Widget_SchematicList_C.Destruct
struct UWidget_SchematicList_C_Destruct_Params
{
};

// Function Widget_SchematicList.Widget_SchematicList_C.ExecuteUbergraph_Widget_SchematicList
struct UWidget_SchematicList_C_ExecuteUbergraph_Widget_SchematicList_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
