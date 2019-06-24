// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_PowerPoleMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.UserConstructionScript
// ()

void ABuild_PowerPoleMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.UserConstructionScript");

	ABuild_PowerPoleMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.OnHasPowerChanged_2
// ()
// Parameters:
// bool                           newHasPower                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_PowerPoleMk1_C::OnHasPowerChanged_2(bool newHasPower)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.OnHasPowerChanged_2");

	ABuild_PowerPoleMk1_C_OnHasPowerChanged_2_Params params;
	params.newHasPower = newHasPower;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.PlayConstructSound
// ()

void ABuild_PowerPoleMk1_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.PlayConstructSound");

	ABuild_PowerPoleMk1_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.ReceiveBeginPlay
// ()

void ABuild_PowerPoleMk1_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.ReceiveBeginPlay");

	ABuild_PowerPoleMk1_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.ExecuteUbergraph_Build_PowerPoleMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_PowerPoleMk1_C::ExecuteUbergraph_Build_PowerPoleMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_PowerPoleMk1.Build_PowerPoleMk1_C.ExecuteUbergraph_Build_PowerPoleMk1");

	ABuild_PowerPoleMk1_C_ExecuteUbergraph_Build_PowerPoleMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
