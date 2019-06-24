#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CaveFloor_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_CaveFloor.BP_CaveFloor_C.GetEntrenceAndExitIndex
struct ABP_CaveFloor_C_GetEntrenceAndExitIndex_Params
{
	int                                                entrence;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	int                                                Exit;                                                     // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CaveFloor.BP_CaveFloor_C.GetStaticMeshForIndex
struct ABP_CaveFloor_C_GetStaticMeshForIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UStaticMesh*                                 NewParam;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_CaveFloor.BP_CaveFloor_C.BuildCaveElement
struct ABP_CaveFloor_C_BuildCaveElement_Params
{
};

// Function BP_CaveFloor.BP_CaveFloor_C.UserConstructionScript
struct ABP_CaveFloor_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
