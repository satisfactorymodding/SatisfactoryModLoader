#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_AggroEntry_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_AggroEntry.Widget_AggroEntry_C.GetSortedAggroEntries
struct UWidget_AggroEntry_C_GetSortedAggroEntries_Params
{
	TArray<struct FAggroEntry>                         allEntries;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm)
	TArray<struct FAggroEntry>                         sortedEntries;                                            // (Parm, OutParm, ZeroConstructor)
};

// Function Widget_AggroEntry.Widget_AggroEntry_C.UpdateAggroList
struct UWidget_AggroEntry_C_UpdateAggroList_Params
{
};

// Function Widget_AggroEntry.Widget_AggroEntry_C.Construct
struct UWidget_AggroEntry_C_Construct_Params
{
};

// Function Widget_AggroEntry.Widget_AggroEntry_C.Tick
struct UWidget_AggroEntry_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_AggroEntry.Widget_AggroEntry_C.ExecuteUbergraph_Widget_AggroEntry
struct UWidget_AggroEntry_C_ExecuteUbergraph_Widget_AggroEntry_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
