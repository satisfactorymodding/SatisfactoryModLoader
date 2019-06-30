// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SelfDrivingLocomotiveController_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.UserConstructionScript
// ()

void ABP_SelfDrivingLocomotiveController_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.UserConstructionScript");

	ABP_SelfDrivingLocomotiveController_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.ReceiveBeginPlay
// ()

void ABP_SelfDrivingLocomotiveController_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.ReceiveBeginPlay");

	ABP_SelfDrivingLocomotiveController_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.OnPossess
// ()
// Parameters:
// class APawn**                  PossessedPawn                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SelfDrivingLocomotiveController_C::OnPossess(class APawn** PossessedPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.OnPossess");

	ABP_SelfDrivingLocomotiveController_C_OnPossess_Params params;
	params.PossessedPawn = PossessedPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.OnUnpossess
// ()
// Parameters:
// class APawn**                  UnpossessedPawn                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SelfDrivingLocomotiveController_C::OnUnpossess(class APawn** UnpossessedPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.OnUnpossess");

	ABP_SelfDrivingLocomotiveController_C_OnUnpossess_Params params;
	params.UnpossessedPawn = UnpossessedPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.ExecuteUbergraph_BP_SelfDrivingLocomotiveController
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SelfDrivingLocomotiveController_C::ExecuteUbergraph_BP_SelfDrivingLocomotiveController(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SelfDrivingLocomotiveController.BP_SelfDrivingLocomotiveController_C.ExecuteUbergraph_BP_SelfDrivingLocomotiveController");

	ABP_SelfDrivingLocomotiveController_C_ExecuteUbergraph_BP_SelfDrivingLocomotiveController_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
