#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_CheatResourceSpawner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.InternalGetOutput
struct ABuild_CheatResourceSpawner_C_InternalGetOutput_Params
{
	class UClass*                                      Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UClass*                                      Output;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.Factory_GrabOutput
struct ABuild_CheatResourceSpawner_C_Factory_GrabOutput_Params
{
	class UFGFactoryConnectionComponent**              Connection;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FInventoryItem                              out_item;                                                 // (Parm, OutParm)
	float                                              out_OffsetBeyond;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class UClass**                                     Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.Factory_PeekOutput
struct ABuild_CheatResourceSpawner_C_Factory_PeekOutput_Params
{
	class UFGFactoryConnectionComponent**              Connection;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FInventoryItem>                      out_items;                                                // (Parm, OutParm, ZeroConstructor)
	class UClass**                                     Type;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_CheatResourceSpawner.Build_CheatResourceSpawner_C.UserConstructionScript
struct ABuild_CheatResourceSpawner_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
