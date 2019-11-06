#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_TrainStation_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.GetPowerConsumption
struct UWidget_ActorDetails_TrainStation_C_GetPowerConsumption_Params
{
	class AFGBuildableFactory*                         TrainStation;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.CheckIfPowerConnected
struct UWidget_ActorDetails_TrainStation_C_CheckIfPowerConnected_Params
{
	class AFGBuildableRailroadStation*                 mTrainStation;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.Construct
struct UWidget_ActorDetails_TrainStation_C_Construct_Params
{
};

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.Destruct
struct UWidget_ActorDetails_TrainStation_C_Destruct_Params
{
};

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.UpdateTrainStationStats
struct UWidget_ActorDetails_TrainStation_C_UpdateTrainStationStats_Params
{
};

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.ExecuteUbergraph_Widget_ActorDetails_TrainStation
struct UWidget_ActorDetails_TrainStation_C_ExecuteUbergraph_Widget_ActorDetails_TrainStation_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
