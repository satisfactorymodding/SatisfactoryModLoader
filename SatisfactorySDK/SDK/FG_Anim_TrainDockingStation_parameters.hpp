#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_TrainDockingStation_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.CalculateAnimGraphValues
struct UAnim_TrainDockingStation_C_CalculateAnimGraphValues_Params
{
};

// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.BlueprintUpdateAnimation
struct UAnim_TrainDockingStation_C_BlueprintUpdateAnimation_Params
{
	float*                                             DeltaTimeX;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.AnimNotify_StartOffset
struct UAnim_TrainDockingStation_C_AnimNotify_StartOffset_Params
{
};

// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.AnimNotify_EndOffset
struct UAnim_TrainDockingStation_C_AnimNotify_EndOffset_Params
{
};

// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.ExecuteUbergraph_Anim_TrainDockingStation
struct UAnim_TrainDockingStation_C_ExecuteUbergraph_Anim_TrainDockingStation_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
