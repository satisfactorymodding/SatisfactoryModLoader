// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_CreatureSeat_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_CreatureSeat.BP_CreatureSeat_C.UserConstructionScript
// ()

void ABP_CreatureSeat_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.UserConstructionScript");

	ABP_CreatureSeat_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.InpActEvt_Use_K2Node_InputActionEvent_2
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_CreatureSeat_C::InpActEvt_Use_K2Node_InputActionEvent_2(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.InpActEvt_Use_K2Node_InputActionEvent_2");

	ABP_CreatureSeat_C_InpActEvt_Use_K2Node_InputActionEvent_2_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_CreatureSeat_C::InpActEvt_Jump_Drift_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_1");

	ABP_CreatureSeat_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1
// ()
// Parameters:
// float                          AxisValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CreatureSeat_C::InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1(float AxisValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1");

	ABP_CreatureSeat_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1_Params params;
	params.AxisValue = AxisValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.UpdateCamera
// ()

void ABP_CreatureSeat_C::UpdateCamera()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.UpdateCamera");

	ABP_CreatureSeat_C_UpdateCamera_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CreatureSeat_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.ReceiveTick");

	ABP_CreatureSeat_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.ReceivePossessed
// ()
// Parameters:
// class AController**            NewController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CreatureSeat_C::ReceivePossessed(class AController** NewController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.ReceivePossessed");

	ABP_CreatureSeat_C_ReceivePossessed_Params params;
	params.NewController = NewController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.ClientSetupHUD
// ()
// Parameters:
// class AFGPlayerController*     Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CreatureSeat_C::ClientSetupHUD(class AFGPlayerController* Controller)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.ClientSetupHUD");

	ABP_CreatureSeat_C_ClientSetupHUD_Params params;
	params.Controller = Controller;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.Server_Leave
// ()

void ABP_CreatureSeat_C::Server_Leave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.Server_Leave");

	ABP_CreatureSeat_C_Server_Leave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.Server_DoAction
// ()

void ABP_CreatureSeat_C::Server_DoAction()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.Server_DoAction");

	ABP_CreatureSeat_C_Server_DoAction_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.Multicast_PlayClap
// ()

void ABP_CreatureSeat_C::Multicast_PlayClap()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.Multicast_PlayClap");

	ABP_CreatureSeat_C_Multicast_PlayClap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.Server_PlayClap
// ()

void ABP_CreatureSeat_C::Server_PlayClap()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.Server_PlayClap");

	ABP_CreatureSeat_C_Server_PlayClap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.PlayClap
// ()

void ABP_CreatureSeat_C::PlayClap()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.PlayClap");

	ABP_CreatureSeat_C_PlayClap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_CreatureSeat.BP_CreatureSeat_C.ExecuteUbergraph_BP_CreatureSeat
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_CreatureSeat_C::ExecuteUbergraph_BP_CreatureSeat(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_CreatureSeat.BP_CreatureSeat_C.ExecuteUbergraph_BP_CreatureSeat");

	ABP_CreatureSeat_C_ExecuteUbergraph_BP_CreatureSeat_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
