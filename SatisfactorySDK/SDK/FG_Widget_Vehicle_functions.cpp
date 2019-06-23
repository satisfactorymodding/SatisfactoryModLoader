// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Vehicle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_Vehicle.Widget_Vehicle_C.OnItemAddedOrRemoved
// ()
// Parameters:
// class UClass*                  ItemClass                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            NumAddedRemoved                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Vehicle_C::OnItemAddedOrRemoved(class UClass* ItemClass, int NumAddedRemoved)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.OnItemAddedOrRemoved");

	UWidget_Vehicle_C_OnItemAddedOrRemoved_Params params;
	params.ItemClass = ItemClass;
	params.NumAddedRemoved = NumAddedRemoved;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.UpdateTransferStatus
// ()

void UWidget_Vehicle_C::UpdateTransferStatus()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.UpdateTransferStatus");

	UWidget_Vehicle_C_UpdateTransferStatus_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.GetSelfDrivingText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Vehicle_C::GetSelfDrivingText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.GetSelfDrivingText");

	UWidget_Vehicle_C_GetSelfDrivingText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Vehicle.Widget_Vehicle_C.GetVehicleHealthPercent
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UWidget_Vehicle_C::GetVehicleHealthPercent()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.GetVehicleHealthPercent");

	UWidget_Vehicle_C_GetVehicleHealthPercent_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentSpeedVisibility
// ()
// Parameters:
// ESlateVisibility               ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ESlateVisibility UWidget_Vehicle_C::GetCurrentSpeedVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentSpeedVisibility");

	UWidget_Vehicle_C_GetCurrentSpeedVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentGearText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Vehicle_C::GetCurrentGearText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentGearText");

	UWidget_Vehicle_C_GetCurrentGearText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentSpeedinKMHText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Vehicle_C::GetCurrentSpeedinKMHText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.GetCurrentSpeedinKMHText");

	UWidget_Vehicle_C_GetCurrentSpeedinKMHText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Vehicle.Widget_Vehicle_C.GetRPMText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText UWidget_Vehicle_C::GetRPMText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.GetRPMText");

	UWidget_Vehicle_C_GetRPMText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Widget_Vehicle.Widget_Vehicle_C.Init
// ()
// Parameters:
// class ABP_WheeledVehicle_C*    Vehicle                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Vehicle_C::Init(class ABP_WheeledVehicle_C* Vehicle)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.Init");

	UWidget_Vehicle_C_Init_Params params;
	params.Vehicle = Vehicle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.StopRecording
// ()

void UWidget_Vehicle_C::StopRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.StopRecording");

	UWidget_Vehicle_C_StopRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.StartRecording
// ()

void UWidget_Vehicle_C::StartRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.StartRecording");

	UWidget_Vehicle_C_StartRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.Construct
// ()

void UWidget_Vehicle_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.Construct");

	UWidget_Vehicle_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.Tick
// ()
// Parameters:
// struct FGeometry*              MyGeometry                     (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
// float*                         InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Vehicle_C::Tick(struct FGeometry* MyGeometry, float* InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.Tick");

	UWidget_Vehicle_C_Tick_Params params;
	params.MyGeometry = MyGeometry;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.AutoPilotCheck
// ()

void UWidget_Vehicle_C::AutoPilotCheck()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.AutoPilotCheck");

	UWidget_Vehicle_C_AutoPilotCheck_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_Vehicle.Widget_Vehicle_C.ExecuteUbergraph_Widget_Vehicle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_Vehicle_C::ExecuteUbergraph_Widget_Vehicle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_Vehicle.Widget_Vehicle_C.ExecuteUbergraph_Widget_Vehicle");

	UWidget_Vehicle_C_ExecuteUbergraph_Widget_Vehicle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
