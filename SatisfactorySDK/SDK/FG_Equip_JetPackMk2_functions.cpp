// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_JetPackMk2_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_JetPackMk2.Equip_JetPackMk2_C.UserConstructionScript
// ()

void AEquip_JetPackMk2_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JetPackMk2.Equip_JetPackMk2_C.UserConstructionScript");

	AEquip_JetPackMk2_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_JetPackMk2.Equip_JetPackMk2_C.ConsumeFuel
// ()
// Parameters:
// float*                         Delta                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_JetPackMk2_C::ConsumeFuel(float* Delta)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JetPackMk2.Equip_JetPackMk2_C.ConsumeFuel");

	AEquip_JetPackMk2_C_ConsumeFuel_Params params;
	params.Delta = Delta;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_JetPackMk2.Equip_JetPackMk2_C.ExecuteUbergraph_Equip_JetPackMk2
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_JetPackMk2_C::ExecuteUbergraph_Equip_JetPackMk2(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_JetPackMk2.Equip_JetPackMk2_C.ExecuteUbergraph_Equip_JetPackMk2");

	AEquip_JetPackMk2_C_ExecuteUbergraph_Equip_JetPackMk2_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
