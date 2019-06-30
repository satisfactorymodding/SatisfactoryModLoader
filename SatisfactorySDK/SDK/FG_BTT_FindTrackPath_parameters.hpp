#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FindTrackPath_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_FindTrackPath.BTT_FindTrackPath_C.FindPath
struct UBTT_FindTrackPath_C_FindPath_Params
{
	class AFGTrain*                                    Train;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AFGTrainStationIdentifier*                   Station;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Success;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FRailroadPathFindingResult                  Result;                                                   // (Parm, OutParm)
	class AFGLocomotive*                               Locomotive;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FindTrackPath.BTT_FindTrackPath_C.ReportError
struct UBTT_FindTrackPath_C_ReportError_Params
{
	struct FText                                       MESSAGE;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BTT_FindTrackPath.BTT_FindTrackPath_C.ReceiveExecuteAI
struct UBTT_FindTrackPath_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FindTrackPath.BTT_FindTrackPath_C.ExecuteUbergraph_BTT_FindTrackPath
struct UBTT_FindTrackPath_C_ExecuteUbergraph_BTT_FindTrackPath_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
