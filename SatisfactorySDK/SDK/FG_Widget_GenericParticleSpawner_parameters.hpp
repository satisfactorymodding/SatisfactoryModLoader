#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GenericParticleSpawner_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_GenericParticleSpawner.Widget_GenericParticleSpawner_C.CreateParticles
struct UWidget_GenericParticleSpawner_C_CreateParticles_Params
{
	int                                                NumberOfParticles;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_GenericParticleSpawner.Widget_GenericParticleSpawner_C.ExecuteUbergraph_Widget_GenericParticleSpawner
struct UWidget_GenericParticleSpawner_C_ExecuteUbergraph_Widget_GenericParticleSpawner_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
