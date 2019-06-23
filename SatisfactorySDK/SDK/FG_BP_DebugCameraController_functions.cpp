// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DebugCameraController_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_DebugCameraController.BP_DebugCameraController_C.UserConstructionScript
// ()

void ABP_DebugCameraController_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DebugCameraController.BP_DebugCameraController_C.UserConstructionScript");

	ABP_DebugCameraController_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DebugCameraController.BP_DebugCameraController_C.InpActEvt_Shift_P_K2Node_InputKeyEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_DebugCameraController_C::InpActEvt_Shift_P_K2Node_InputKeyEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DebugCameraController.BP_DebugCameraController_C.InpActEvt_Shift_P_K2Node_InputKeyEvent_1");

	ABP_DebugCameraController_C_InpActEvt_Shift_P_K2Node_InputKeyEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DebugCameraController.BP_DebugCameraController_C.ReceiveOnActivate
// ()
// Parameters:
// class APlayerController**      OriginalPC                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_DebugCameraController_C::ReceiveOnActivate(class APlayerController** OriginalPC)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DebugCameraController.BP_DebugCameraController_C.ReceiveOnActivate");

	ABP_DebugCameraController_C_ReceiveOnActivate_Params params;
	params.OriginalPC = OriginalPC;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DebugCameraController.BP_DebugCameraController_C.ReceiveOnDeactivate
// ()
// Parameters:
// class APlayerController**      RestoredPC                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_DebugCameraController_C::ReceiveOnDeactivate(class APlayerController** RestoredPC)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DebugCameraController.BP_DebugCameraController_C.ReceiveOnDeactivate");

	ABP_DebugCameraController_C_ReceiveOnDeactivate_Params params;
	params.RestoredPC = RestoredPC;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_DebugCameraController.BP_DebugCameraController_C.ExecuteUbergraph_BP_DebugCameraController
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_DebugCameraController_C::ExecuteUbergraph_BP_DebugCameraController(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_DebugCameraController.BP_DebugCameraController_C.ExecuteUbergraph_BP_DebugCameraController");

	ABP_DebugCameraController_C_ExecuteUbergraph_BP_DebugCameraController_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
