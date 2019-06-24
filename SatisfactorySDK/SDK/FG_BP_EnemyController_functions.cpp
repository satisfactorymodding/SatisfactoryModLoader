// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_EnemyController_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_EnemyController.BP_EnemyController_C.UserConstructionScript
// ()

void ABP_EnemyController_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_EnemyController.BP_EnemyController_C.UserConstructionScript");

	ABP_EnemyController_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_EnemyController.BP_EnemyController_C.OnPossess
// ()
// Parameters:
// class APawn**                  PossessedPawn                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_EnemyController_C::OnPossess(class APawn** PossessedPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_EnemyController.BP_EnemyController_C.OnPossess");

	ABP_EnemyController_C_OnPossess_Params params;
	params.PossessedPawn = PossessedPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_EnemyController.BP_EnemyController_C.OnAggroTargetLost
// ()
// Parameters:
// class AActor**                 lostActor                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_EnemyController_C::OnAggroTargetLost(class AActor** lostActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_EnemyController.BP_EnemyController_C.OnAggroTargetLost");

	ABP_EnemyController_C_OnAggroTargetLost_Params params;
	params.lostActor = lostActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_EnemyController.BP_EnemyController_C.ExecuteUbergraph_BP_EnemyController
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_EnemyController_C::ExecuteUbergraph_BP_EnemyController(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_EnemyController.BP_EnemyController_C.ExecuteUbergraph_BP_EnemyController");

	ABP_EnemyController_C_ExecuteUbergraph_BP_EnemyController_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
