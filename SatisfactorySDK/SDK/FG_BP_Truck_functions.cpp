// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Truck_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Truck.BP_Truck_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABP_Truck_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.GetActorRepresentationTexture");

	ABP_Truck_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Truck.BP_Truck_C.OnRep_mFlashlightOn
// ()

void ABP_Truck_C::OnRep_mFlashlightOn()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.OnRep_mFlashlightOn");

	ABP_Truck_C_OnRep_mFlashlightOn_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Truck.BP_Truck_C.GetAttackLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABP_Truck_C::GetAttackLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.GetAttackLocation");

	ABP_Truck_C_GetAttackLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Truck.BP_Truck_C.GetEnemyTargetDesirability
// ()
// Parameters:
// class AFGEnemyController**     forController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_Truck_C::GetEnemyTargetDesirability(class AFGEnemyController** forController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.GetEnemyTargetDesirability");

	ABP_Truck_C_GetEnemyTargetDesirability_Params params;
	params.forController = forController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Truck.BP_Truck_C.ShouldAutoregisterAsTargetable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Truck_C::ShouldAutoregisterAsTargetable()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.ShouldAutoregisterAsTargetable");

	ABP_Truck_C_ShouldAutoregisterAsTargetable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Truck.BP_Truck_C.UserConstructionScript
// ()

void ABP_Truck_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.UserConstructionScript");

	ABP_Truck_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Truck.BP_Truck_C.InpActEvt_Flashlight_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_Truck_C::InpActEvt_Flashlight_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.InpActEvt_Flashlight_K2Node_InputActionEvent_1");

	ABP_Truck_C_InpActEvt_Flashlight_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Truck.BP_Truck_C.OpenTrunk
// ()

void ABP_Truck_C::OpenTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.OpenTrunk");

	ABP_Truck_C_OpenTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Truck.BP_Truck_C.CloseTrunk
// ()

void ABP_Truck_C::CloseTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.CloseTrunk");

	ABP_Truck_C_CloseTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Truck.BP_Truck_C.Server_SetFlashlightOn
// ()
// Parameters:
// bool                           FlashlightOn                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Truck_C::Server_SetFlashlightOn(bool FlashlightOn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.Server_SetFlashlightOn");

	ABP_Truck_C_Server_SetFlashlightOn_Params params;
	params.FlashlightOn = FlashlightOn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Truck.BP_Truck_C.ExecuteUbergraph_BP_Truck
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Truck_C::ExecuteUbergraph_BP_Truck(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Truck.BP_Truck_C.ExecuteUbergraph_BP_Truck");

	ABP_Truck_C_ExecuteUbergraph_BP_Truck_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
