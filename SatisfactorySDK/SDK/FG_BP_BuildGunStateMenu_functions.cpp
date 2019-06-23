// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildGunStateMenu_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.EndState
// ()

void UBP_BuildGunStateMenu_C::EndState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.EndState");

	UBP_BuildGunStateMenu_C_EndState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.SecondaryFire
// ()

void UBP_BuildGunStateMenu_C::SecondaryFire()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.SecondaryFire");

	UBP_BuildGunStateMenu_C_SecondaryFire_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.BeginState
// ()

void UBP_BuildGunStateMenu_C::BeginState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.BeginState");

	UBP_BuildGunStateMenu_C_BeginState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.ExecuteUbergraph_BP_BuildGunStateMenu
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_BuildGunStateMenu_C::ExecuteUbergraph_BP_BuildGunStateMenu(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildGunStateMenu.BP_BuildGunStateMenu_C.ExecuteUbergraph_BP_BuildGunStateMenu");

	UBP_BuildGunStateMenu_C_ExecuteUbergraph_BP_BuildGunStateMenu_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
