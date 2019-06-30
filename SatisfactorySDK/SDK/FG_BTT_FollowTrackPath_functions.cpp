// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_FollowTrackPath_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.CalcBrakeCurve
// ()
// Parameters:
// float                          Distance                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          New_Speed                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Deceleration                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           Is_Stopping                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Target_Speed                   (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBTT_FollowTrackPath_C::CalcBrakeCurve(float Distance, float New_Speed, float Deceleration, bool Is_Stopping, float* Target_Speed)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.CalcBrakeCurve");

	UBTT_FollowTrackPath_C_CalcBrakeCurve_Params params;
	params.Distance = Distance;
	params.New_Speed = New_Speed;
	params.Deceleration = Deceleration;
	params.Is_Stopping = Is_Stopping;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Target_Speed != nullptr)
		*Target_Speed = params.Target_Speed;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.CalcBrakeDistance
// ()
// Parameters:
// float                          Speed                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          New_Speed                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Deceleration                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          Distance                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBTT_FollowTrackPath_C::CalcBrakeDistance(float Speed, float New_Speed, float Deceleration, float* Distance)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.CalcBrakeDistance");

	UBTT_FollowTrackPath_C_CalcBrakeDistance_Params params;
	params.Speed = Speed;
	params.New_Speed = New_Speed;
	params.Deceleration = Deceleration;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Distance != nullptr)
		*Distance = params.Distance;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FollowTrackPath_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveExecuteAI");

	UBTT_FollowTrackPath_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveTickAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FollowTrackPath_C::ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveTickAI");

	UBTT_FollowTrackPath_C_ReceiveTickAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveAbortAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FollowTrackPath_C::ReceiveAbortAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ReceiveAbortAI");

	UBTT_FollowTrackPath_C_ReceiveAbortAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.FinishStopping
// ()

void UBTT_FollowTrackPath_C::FinishStopping()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.FinishStopping");

	UBTT_FollowTrackPath_C_FinishStopping_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.StopAllMovement
// ()

void UBTT_FollowTrackPath_C::StopAllMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.StopAllMovement");

	UBTT_FollowTrackPath_C_StopAllMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.InvalidatePath
// ()

void UBTT_FollowTrackPath_C::InvalidatePath()
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.InvalidatePath");

	UBTT_FollowTrackPath_C_InvalidatePath_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ExecuteUbergraph_BTT_FollowTrackPath
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_FollowTrackPath_C::ExecuteUbergraph_BTT_FollowTrackPath(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_FollowTrackPath.BTT_FollowTrackPath_C.ExecuteUbergraph_BTT_FollowTrackPath");

	UBTT_FollowTrackPath_C_ExecuteUbergraph_BTT_FollowTrackPath_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
