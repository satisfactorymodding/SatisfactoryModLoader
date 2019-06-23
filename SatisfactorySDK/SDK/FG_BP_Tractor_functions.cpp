// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Tractor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Tractor.BP_Tractor_C.OnRep_mFlashlightOn
// ()

void ABP_Tractor_C::OnRep_mFlashlightOn()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.OnRep_mFlashlightOn");

	ABP_Tractor_C_OnRep_mFlashlightOn_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.ToggleFlashlight
// ()

void ABP_Tractor_C::ToggleFlashlight()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ToggleFlashlight");

	ABP_Tractor_C_ToggleFlashlight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.GetEnemyTargetDesirability
// ()
// Parameters:
// class AFGEnemyController**     forController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_Tractor_C::GetEnemyTargetDesirability(class AFGEnemyController** forController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.GetEnemyTargetDesirability");

	ABP_Tractor_C_GetEnemyTargetDesirability_Params params;
	params.forController = forController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Tractor.BP_Tractor_C.GetAttackLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABP_Tractor_C::GetAttackLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.GetAttackLocation");

	ABP_Tractor_C_GetAttackLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Tractor.BP_Tractor_C.ShouldAutoregisterAsTargetable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Tractor_C::ShouldAutoregisterAsTargetable()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ShouldAutoregisterAsTargetable");

	ABP_Tractor_C_ShouldAutoregisterAsTargetable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Tractor.BP_Tractor_C.UserConstructionScript
// ()

void ABP_Tractor_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.UserConstructionScript");

	ABP_Tractor_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.InpActEvt_Flashlight_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_Tractor_C::InpActEvt_Flashlight_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.InpActEvt_Flashlight_K2Node_InputActionEvent_1");

	ABP_Tractor_C_InpActEvt_Flashlight_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.ToggleFreeCamera
// ()

void ABP_Tractor_C::ToggleFreeCamera()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ToggleFreeCamera");

	ABP_Tractor_C_ToggleFreeCamera_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.ReceiveBeginPlay
// ()

void ABP_Tractor_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ReceiveBeginPlay");

	ABP_Tractor_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.CloseTrunk
// ()

void ABP_Tractor_C::CloseTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.CloseTrunk");

	ABP_Tractor_C_CloseTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.ReceiveOnVehicleStartup
// ()

void ABP_Tractor_C::ReceiveOnVehicleStartup()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ReceiveOnVehicleStartup");

	ABP_Tractor_C_ReceiveOnVehicleStartup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.ReceiveOnVehicleShutDown
// ()

void ABP_Tractor_C::ReceiveOnVehicleShutDown()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ReceiveOnVehicleShutDown");

	ABP_Tractor_C_ReceiveOnVehicleShutDown_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.OpenTrunk
// ()

void ABP_Tractor_C::OpenTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.OpenTrunk");

	ABP_Tractor_C_OpenTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.Server_SetFlashlightOn
// ()
// Parameters:
// bool                           FlashlightOn                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Tractor_C::Server_SetFlashlightOn(bool FlashlightOn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.Server_SetFlashlightOn");

	ABP_Tractor_C_Server_SetFlashlightOn_Params params;
	params.FlashlightOn = FlashlightOn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Tractor.BP_Tractor_C.ExecuteUbergraph_BP_Tractor
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Tractor_C::ExecuteUbergraph_BP_Tractor(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Tractor.BP_Tractor_C.ExecuteUbergraph_BP_Tractor");

	ABP_Tractor_C_ExecuteUbergraph_BP_Tractor_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
