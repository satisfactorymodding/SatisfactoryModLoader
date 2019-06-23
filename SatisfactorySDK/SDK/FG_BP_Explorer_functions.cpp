// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Explorer_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Explorer.BP_Explorer_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_Explorer_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.GetActorRepresentationText");

	ABP_Explorer_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Explorer.BP_Explorer_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABP_Explorer_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.GetActorRepresentationTexture");

	ABP_Explorer_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Explorer.BP_Explorer_C.CheckSuspension
// ()
// Parameters:
// float                          InDeltaTime                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Explorer_C::CheckSuspension(float InDeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.CheckSuspension");

	ABP_Explorer_C_CheckSuspension_Params params;
	params.InDeltaTime = InDeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.OnRep_mFlashlightOn
// ()

void ABP_Explorer_C::OnRep_mFlashlightOn()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.OnRep_mFlashlightOn");

	ABP_Explorer_C_OnRep_mFlashlightOn_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.GetAttackLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABP_Explorer_C::GetAttackLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.GetAttackLocation");

	ABP_Explorer_C_GetAttackLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Explorer.BP_Explorer_C.GetEnemyTargetDesirability
// ()
// Parameters:
// class AFGEnemyController**     forController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_Explorer_C::GetEnemyTargetDesirability(class AFGEnemyController** forController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.GetEnemyTargetDesirability");

	ABP_Explorer_C_GetEnemyTargetDesirability_Params params;
	params.forController = forController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Explorer.BP_Explorer_C.ShouldAutoregisterAsTargetable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Explorer_C::ShouldAutoregisterAsTargetable()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.ShouldAutoregisterAsTargetable");

	ABP_Explorer_C_ShouldAutoregisterAsTargetable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Explorer.BP_Explorer_C.UserConstructionScript
// ()

void ABP_Explorer_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.UserConstructionScript");

	ABP_Explorer_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.InpActEvt_Flashlight_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_Explorer_C::InpActEvt_Flashlight_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.InpActEvt_Flashlight_K2Node_InputActionEvent_1");

	ABP_Explorer_C_InpActEvt_Flashlight_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.InpActEvt_Y_K2Node_InputKeyEvent_3
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_Explorer_C::InpActEvt_Y_K2Node_InputKeyEvent_3(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.InpActEvt_Y_K2Node_InputKeyEvent_3");

	ABP_Explorer_C_InpActEvt_Y_K2Node_InputKeyEvent_3_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.InpActEvt_NumPadZero_K2Node_InputKeyEvent_2
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_Explorer_C::InpActEvt_NumPadZero_K2Node_InputKeyEvent_2(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.InpActEvt_NumPadZero_K2Node_InputKeyEvent_2");

	ABP_Explorer_C_InpActEvt_NumPadZero_K2Node_InputKeyEvent_2_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.InpActEvt_NumPadOne_K2Node_InputKeyEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_Explorer_C::InpActEvt_NumPadOne_K2Node_InputKeyEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.InpActEvt_NumPadOne_K2Node_InputKeyEvent_1");

	ABP_Explorer_C_InpActEvt_NumPadOne_K2Node_InputKeyEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Explorer_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.ReceiveTick");

	ABP_Explorer_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.CloseTrunk
// ()

void ABP_Explorer_C::CloseTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.CloseTrunk");

	ABP_Explorer_C_CloseTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.OpenTrunk
// ()

void ABP_Explorer_C::OpenTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.OpenTrunk");

	ABP_Explorer_C_OpenTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1
// ()
// Parameters:
// float                          AxisValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Explorer_C::InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1(float AxisValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1");

	ABP_Explorer_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_1_Params params;
	params.AxisValue = AxisValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.Server_SetFlashlightOn
// ()
// Parameters:
// bool                           FlashlightOn                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Explorer_C::Server_SetFlashlightOn(bool FlashlightOn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.Server_SetFlashlightOn");

	ABP_Explorer_C_Server_SetFlashlightOn_Params params;
	params.FlashlightOn = FlashlightOn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Explorer.BP_Explorer_C.ExecuteUbergraph_BP_Explorer
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Explorer_C::ExecuteUbergraph_BP_Explorer(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Explorer.BP_Explorer_C.ExecuteUbergraph_BP_Explorer");

	ABP_Explorer_C_ExecuteUbergraph_BP_Explorer_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
