// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_PassengerSeat_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_PassengerSeat.BP_PassengerSeat_C.UserConstructionScript
// ()

void ABP_PassengerSeat_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.UserConstructionScript");

	ABP_PassengerSeat_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PassengerSeat.BP_PassengerSeat_C.InpActEvt_Use_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_PassengerSeat_C::InpActEvt_Use_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.InpActEvt_Use_K2Node_InputActionEvent_1");

	ABP_PassengerSeat_C_InpActEvt_Use_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PassengerSeat.BP_PassengerSeat_C.UpdateCamera
// ()

void ABP_PassengerSeat_C::UpdateCamera()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.UpdateCamera");

	ABP_PassengerSeat_C_UpdateCamera_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PassengerSeat.BP_PassengerSeat_C.ReceivePossessed
// ()
// Parameters:
// class AController**            NewController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PassengerSeat_C::ReceivePossessed(class AController** NewController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.ReceivePossessed");

	ABP_PassengerSeat_C_ReceivePossessed_Params params;
	params.NewController = NewController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PassengerSeat.BP_PassengerSeat_C.ReceiveUnpossessed
// ()
// Parameters:
// class AController**            OldController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PassengerSeat_C::ReceiveUnpossessed(class AController** OldController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.ReceiveUnpossessed");

	ABP_PassengerSeat_C_ReceiveUnpossessed_Params params;
	params.OldController = OldController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PassengerSeat.BP_PassengerSeat_C.Server_Leave
// ()

void ABP_PassengerSeat_C::Server_Leave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.Server_Leave");

	ABP_PassengerSeat_C_Server_Leave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_PassengerSeat.BP_PassengerSeat_C.ExecuteUbergraph_BP_PassengerSeat
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_PassengerSeat_C::ExecuteUbergraph_BP_PassengerSeat(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_PassengerSeat.BP_PassengerSeat_C.ExecuteUbergraph_BP_PassengerSeat");

	ABP_PassengerSeat_C_ExecuteUbergraph_BP_PassengerSeat_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
