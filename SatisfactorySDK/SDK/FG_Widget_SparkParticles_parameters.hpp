#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SparkParticles_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SparkParticles.Widget_SparkParticles_C.CreateSparks
struct UWidget_SparkParticles_C_CreateSparks_Params
{
	int                                                NumberOfSparks;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SparkParticles.Widget_SparkParticles_C.OnSparkBounce
struct UWidget_SparkParticles_C_OnSparkBounce_Params
{
	struct FVector2D                                   Position;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   Scale;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SparkParticles.Widget_SparkParticles_C.ExecuteUbergraph_Widget_SparkParticles
struct UWidget_SparkParticles_C_ExecuteUbergraph_Widget_SparkParticles_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
