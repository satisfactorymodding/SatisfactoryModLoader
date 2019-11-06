// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ActorDetails_TrainStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.GetPowerConsumption
// ()
// Parameters:
// class AFGBuildableFactory*     TrainStation                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_TrainStation_C::GetPowerConsumption(class AFGBuildableFactory* TrainStation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.GetPowerConsumption");

	UWidget_ActorDetails_TrainStation_C_GetPowerConsumption_Params params;
	params.TrainStation = TrainStation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.CheckIfPowerConnected
// ()
// Parameters:
// class AFGBuildableRailroadStation* mTrainStation                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_TrainStation_C::CheckIfPowerConnected(class AFGBuildableRailroadStation** mTrainStation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.CheckIfPowerConnected");

	UWidget_ActorDetails_TrainStation_C_CheckIfPowerConnected_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (mTrainStation != nullptr)
		*mTrainStation = params.mTrainStation;
}


// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.Construct
// ()

void UWidget_ActorDetails_TrainStation_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.Construct");

	UWidget_ActorDetails_TrainStation_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.Destruct
// ()

void UWidget_ActorDetails_TrainStation_C::Destruct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.Destruct");

	UWidget_ActorDetails_TrainStation_C_Destruct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.UpdateTrainStationStats
// ()

void UWidget_ActorDetails_TrainStation_C::UpdateTrainStationStats()
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.UpdateTrainStationStats");

	UWidget_ActorDetails_TrainStation_C_UpdateTrainStationStats_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.ExecuteUbergraph_Widget_ActorDetails_TrainStation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWidget_ActorDetails_TrainStation_C::ExecuteUbergraph_Widget_ActorDetails_TrainStation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Widget_ActorDetails_TrainStation.Widget_ActorDetails_TrainStation_C.ExecuteUbergraph_Widget_ActorDetails_TrainStation");

	UWidget_ActorDetails_TrainStation_C_ExecuteUbergraph_Widget_ActorDetails_TrainStation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
