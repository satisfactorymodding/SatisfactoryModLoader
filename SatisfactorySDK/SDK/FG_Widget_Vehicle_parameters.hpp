#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Vehicle_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Vehicle.Widget_Vehicle_C.OnItemAddedOrRemoved
struct UWidget_Vehicle_C_OnItemAddedOrRemoved_Params
{
	class UClass*                                      ItemClass;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                NumAddedRemoved;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Vehicle.Widget_Vehicle_C.UpdateTransferStatus
struct UWidget_Vehicle_C_UpdateTransferStatus_Params
{
};

// Function Widget_Vehicle.Widget_Vehicle_C.GetSelfDrivingText
struct UWidget_Vehicle_C_GetSelfDrivingText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Vehicle.Widget_Vehicle_C.GetVehicleHealthPercent
struct UWidget_Vehicle_C_GetVehicleHealthPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentSpeedVisibility
struct UWidget_Vehicle_C_GetCurrentSpeedVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentGearText
struct UWidget_Vehicle_C_GetCurrentGearText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentSpeedinKMHText
struct UWidget_Vehicle_C_GetCurrentSpeedinKMHText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Vehicle.Widget_Vehicle_C.GetRPMText
struct UWidget_Vehicle_C_GetRPMText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Vehicle.Widget_Vehicle_C.Init
struct UWidget_Vehicle_C_Init_Params
{
	class ABP_WheeledVehicle_C*                        Vehicle;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Vehicle.Widget_Vehicle_C.StopRecording
struct UWidget_Vehicle_C_StopRecording_Params
{
};

// Function Widget_Vehicle.Widget_Vehicle_C.StartRecording
struct UWidget_Vehicle_C_StartRecording_Params
{
};

// Function Widget_Vehicle.Widget_Vehicle_C.Construct
struct UWidget_Vehicle_C_Construct_Params
{
};

// Function Widget_Vehicle.Widget_Vehicle_C.Tick
struct UWidget_Vehicle_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Vehicle.Widget_Vehicle_C.AutoPilotCheck
struct UWidget_Vehicle_C_AutoPilotCheck_Params
{
};

// Function Widget_Vehicle.Widget_Vehicle_C.ExecuteUbergraph_Widget_Vehicle
struct UWidget_Vehicle_C_ExecuteUbergraph_Widget_Vehicle_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
