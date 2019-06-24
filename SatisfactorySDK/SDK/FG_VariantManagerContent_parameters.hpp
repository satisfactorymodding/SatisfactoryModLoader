#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_VariantManagerContent_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function VariantManagerContent.LevelVariantSets.GetVariantSet
struct ULevelVariantSets_GetVariantSet_Params
{
	int                                                VariantSetIndex;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class UVariantSet*                                 ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.LevelVariantSets.GetNumVariantSets
struct ULevelVariantSets_GetNumVariantSets_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.LevelVariantSetsActor.SwitchOnVariantByName
struct ALevelVariantSetsActor_SwitchOnVariantByName_Params
{
	class FString                                      VariantSetName;                                           // (Parm, ZeroConstructor)
	class FString                                      VariantName;                                              // (Parm, ZeroConstructor)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.LevelVariantSetsActor.SwitchOnVariantByIndex
struct ALevelVariantSetsActor_SwitchOnVariantByIndex_Params
{
	int                                                VariantSetIndex;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                VariantIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.LevelVariantSetsActor.SetLevelVariantSets
struct ALevelVariantSetsActor_SetLevelVariantSets_Params
{
	class ULevelVariantSets*                           InVariantSets;                                            // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function VariantManagerContent.LevelVariantSetsActor.GetLevelVariantSets
struct ALevelVariantSetsActor_GetLevelVariantSets_Params
{
	bool                                               bLoad;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class ULevelVariantSets*                           ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function VariantManagerContent.Variant.SwitchOn
struct UVariant_SwitchOn_Params
{
};

// Function VariantManagerContent.Variant.SetDisplayText
struct UVariant_SetDisplayText_Params
{
	struct FText                                       NewDisplayText;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function VariantManagerContent.Variant.GetNumActors
struct UVariant_GetNumActors_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.Variant.GetDisplayText
struct UVariant_GetDisplayText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function VariantManagerContent.Variant.GetActor
struct UVariant_GetActor_Params
{
	int                                                ActorIndex;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.VariantSet.SetDisplayText
struct UVariantSet_SetDisplayText_Params
{
	struct FText                                       NewDisplayText;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function VariantManagerContent.VariantSet.GetVariant
struct UVariantSet_GetVariant_Params
{
	int                                                VariantIndex;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UVariant*                                    ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function VariantManagerContent.VariantSet.GetNumVariants
struct UVariantSet_GetNumVariants_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function VariantManagerContent.VariantSet.GetDisplayText
struct UVariantSet_GetDisplayText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
