// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Parachute_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_Parachute.Equip_Parachute_C.UserConstructionScript
// ()

void AEquip_Parachute_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Parachute.Equip_Parachute_C.UserConstructionScript");

	AEquip_Parachute_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Parachute.Equip_Parachute_C.OnDeployed
// ()

void AEquip_Parachute_C::OnDeployed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Parachute.Equip_Parachute_C.OnDeployed");

	AEquip_Parachute_C_OnDeployed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Parachute.Equip_Parachute_C.OnDeployStop
// ()

void AEquip_Parachute_C::OnDeployStop()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Parachute.Equip_Parachute_C.OnDeployStop");

	AEquip_Parachute_C_OnDeployStop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Parachute.Equip_Parachute_C.ExecuteUbergraph_Equip_Parachute
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Parachute_C::ExecuteUbergraph_Equip_Parachute(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Parachute.Equip_Parachute_C.ExecuteUbergraph_Equip_Parachute");

	AEquip_Parachute_C_ExecuteUbergraph_Equip_Parachute_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
