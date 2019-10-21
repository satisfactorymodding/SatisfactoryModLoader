#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TrainDockingStation_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_TrainDockingStation.Build_TrainDockingStation_C.IsMoving
struct ABuild_TrainDockingStation_C_IsMoving_Params
{
	class AActor*                                      Actor;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsMoving;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Build_TrainDockingStation.Build_TrainDockingStation_C.UserConstructionScript
struct ABuild_TrainDockingStation_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
