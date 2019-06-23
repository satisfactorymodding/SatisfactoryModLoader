// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Beacon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_Beacon.Equip_Beacon_C.SpawnBeacon
// ()

void AEquip_Beacon_C::SpawnBeacon()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Beacon.Equip_Beacon_C.SpawnBeacon");

	AEquip_Beacon_C_SpawnBeacon_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Beacon.Equip_Beacon_C.UserConstructionScript
// ()

void AEquip_Beacon_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Beacon.Equip_Beacon_C.UserConstructionScript");

	AEquip_Beacon_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Beacon.Equip_Beacon_C.WasEquipped
// ()

void AEquip_Beacon_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Beacon.Equip_Beacon_C.WasEquipped");

	AEquip_Beacon_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Beacon.Equip_Beacon_C.WasUnEquipped
// ()

void AEquip_Beacon_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Beacon.Equip_Beacon_C.WasUnEquipped");

	AEquip_Beacon_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Beacon.Equip_Beacon_C.ExecuteUbergraph_Equip_Beacon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Beacon_C::ExecuteUbergraph_Equip_Beacon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Beacon.Equip_Beacon_C.ExecuteUbergraph_Equip_Beacon");

	AEquip_Beacon_C_ExecuteUbergraph_Equip_Beacon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
