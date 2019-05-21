// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_RailroadVehicleSoundComponent_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.UpdateRTPCs
// ()

void UBP_RailroadVehicleSoundComponent_C::UpdateRTPCs()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.UpdateRTPCs");

	UBP_RailroadVehicleSoundComponent_C_UpdateRTPCs_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.ReceiveBeginPlay
// ()

void UBP_RailroadVehicleSoundComponent_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.ReceiveBeginPlay");

	UBP_RailroadVehicleSoundComponent_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.OnStartedMoving
// ()

void UBP_RailroadVehicleSoundComponent_C::OnStartedMoving()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.OnStartedMoving");

	UBP_RailroadVehicleSoundComponent_C_OnStartedMoving_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.OnStoppedMoving
// ()

void UBP_RailroadVehicleSoundComponent_C::OnStoppedMoving()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.OnStoppedMoving");

	UBP_RailroadVehicleSoundComponent_C_OnStoppedMoving_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.ExecuteUbergraph_BP_RailroadVehicleSoundComponent
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_RailroadVehicleSoundComponent_C::ExecuteUbergraph_BP_RailroadVehicleSoundComponent(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_RailroadVehicleSoundComponent.BP_RailroadVehicleSoundComponent_C.ExecuteUbergraph_BP_RailroadVehicleSoundComponent");

	UBP_RailroadVehicleSoundComponent_C_ExecuteUbergraph_BP_RailroadVehicleSoundComponent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
