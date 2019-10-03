#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_GenericParticle_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_GenericParticle.Widget_GenericParticle_C.Construct
struct UWidget_GenericParticle_C_Construct_Params
{
};

// Function Widget_GenericParticle.Widget_GenericParticle_C.Tick
struct UWidget_GenericParticle_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_GenericParticle.Widget_GenericParticle_C.ExecuteUbergraph_Widget_GenericParticle
struct UWidget_GenericParticle_C_ExecuteUbergraph_Widget_GenericParticle_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
