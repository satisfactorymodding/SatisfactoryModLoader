#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FollowTrackPath_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.CalcBrakeCurve
struct UBTT_FollowTrackPath_C_CalcBrakeCurve_Params
{
	float                                              Distance;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              New_Speed;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Deceleration;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Is_Stopping;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Target_Speed;                                             // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.CalcBrakeDistance
struct UBTT_FollowTrackPath_C_CalcBrakeDistance_Params
{
	float                                              Speed;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              New_Speed;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Deceleration;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Distance;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveExecuteAI
struct UBTT_FollowTrackPath_C_ReceiveExecuteAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveTickAI
struct UBTT_FollowTrackPath_C_ReceiveTickAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveAbortAI
struct UBTT_FollowTrackPath_C_ReceiveAbortAI_Params
{
	class AAIController**                              OwnerController;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class APawn**                                      ControlledPawn;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.FinishStopping
struct UBTT_FollowTrackPath_C_FinishStopping_Params
{
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.StopAllMovement
struct UBTT_FollowTrackPath_C_StopAllMovement_Params
{
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.InvalidatePath
struct UBTT_FollowTrackPath_C_InvalidatePath_Params
{
};

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ExecuteUbergraph_BTT_FollowTrackPath
struct UBTT_FollowTrackPath_C_ExecuteUbergraph_BTT_FollowTrackPath_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
