// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TrainDockingStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_TrainDockingStation.Build_TrainDockingStation_C.IsMoving
// ()
// Parameters:
// class AActor*                  Actor                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsMoving                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABuild_TrainDockingStation_C::IsMoving(class AActor* Actor, bool* IsMoving)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TrainDockingStation.Build_TrainDockingStation_C.IsMoving");

	ABuild_TrainDockingStation_C_IsMoving_Params params;
	params.Actor = Actor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsMoving != nullptr)
		*IsMoving = params.IsMoving;
}


// Function Build_TrainDockingStation.Build_TrainDockingStation_C.UserConstructionScript
// ()

void ABuild_TrainDockingStation_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TrainDockingStation.Build_TrainDockingStation_C.UserConstructionScript");

	ABuild_TrainDockingStation_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
