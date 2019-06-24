// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateDismantle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.TickState
// ()
// Parameters:
// float*                         DeltaTime                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildGunStateDismantle_C::TickState(float* DeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.TickState");

	UBP_BuildGunStateDismantle_C_TickState_Params params;
	params.DeltaTime = DeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.SecondaryFire
// ()

void UBP_BuildGunStateDismantle_C::SecondaryFire()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.SecondaryFire");

	UBP_BuildGunStateDismantle_C_SecondaryFire_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.BeginState
// ()

void UBP_BuildGunStateDismantle_C::BeginState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.BeginState");

	UBP_BuildGunStateDismantle_C_BeginState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.EndState
// ()

void UBP_BuildGunStateDismantle_C::EndState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.EndState");

	UBP_BuildGunStateDismantle_C_EndState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.OnStartDismantle
// ()

void UBP_BuildGunStateDismantle_C::OnStartDismantle()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.OnStartDismantle");

	UBP_BuildGunStateDismantle_C_OnStartDismantle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.OnStopDismantle
// ()

void UBP_BuildGunStateDismantle_C::OnStopDismantle()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.OnStopDismantle");

	UBP_BuildGunStateDismantle_C_OnStopDismantle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.ExecuteUbergraph_BP_BuildGunStateDismantle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildGunStateDismantle_C::ExecuteUbergraph_BP_BuildGunStateDismantle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateDismantle.BP_BuildGunStateDismantle_C.ExecuteUbergraph_BP_BuildGunStateDismantle");

	UBP_BuildGunStateDismantle_C_ExecuteUbergraph_BP_BuildGunStateDismantle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
