// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_JumpingStilts_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_JumpingStilts.Equip_JumpingStilts_C.UserConstructionScript
// ()

void AEquip_JumpingStilts_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JumpingStilts.Equip_JumpingStilts_C.UserConstructionScript");

	AEquip_JumpingStilts_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_JumpingStilts.Equip_JumpingStilts_C.WasEquipped
// ()

void AEquip_JumpingStilts_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JumpingStilts.Equip_JumpingStilts_C.WasEquipped");

	AEquip_JumpingStilts_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_JumpingStilts.Equip_JumpingStilts_C.WasUnEquipped
// ()

void AEquip_JumpingStilts_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JumpingStilts.Equip_JumpingStilts_C.WasUnEquipped");

	AEquip_JumpingStilts_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_JumpingStilts.Equip_JumpingStilts_C.ReceiveBeginPlay
// ()

void AEquip_JumpingStilts_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JumpingStilts.Equip_JumpingStilts_C.ReceiveBeginPlay");

	AEquip_JumpingStilts_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_JumpingStilts.Equip_JumpingStilts_C.ExecuteUbergraph_Equip_JumpingStilts
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_JumpingStilts_C::ExecuteUbergraph_Equip_JumpingStilts(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JumpingStilts.Equip_JumpingStilts_C.ExecuteUbergraph_Equip_JumpingStilts");

	AEquip_JumpingStilts_C_ExecuteUbergraph_Equip_JumpingStilts_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
