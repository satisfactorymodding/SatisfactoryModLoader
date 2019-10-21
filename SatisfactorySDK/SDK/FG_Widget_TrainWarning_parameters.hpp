#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TrainWarning_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TrainWarning.Widget_TrainWarning_C.ShouldForceWarning
struct UWidget_TrainWarning_C_ShouldForceWarning_Params
{
	bool                                               ForceWarning;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       WarningText;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.UpdateWarning
struct UWidget_TrainWarning_C_UpdateWarning_Params
{
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.HideWarning
struct UWidget_TrainWarning_C_HideWarning_Params
{
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.ShowWarning
struct UWidget_TrainWarning_C_ShowWarning_Params
{
	struct FText                                       WarningText;                                              // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.Init
struct UWidget_TrainWarning_C_Init_Params
{
	class AFGTrain*                                    Train;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.CheckErrors
struct UWidget_TrainWarning_C_CheckErrors_Params
{
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.Destruct
struct UWidget_TrainWarning_C_Destruct_Params
{
};

// Function Widget_TrainWarning.Widget_TrainWarning_C.ExecuteUbergraph_Widget_TrainWarning
struct UWidget_TrainWarning_C_ExecuteUbergraph_Widget_TrainWarning_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
