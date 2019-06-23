// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_StingerGas_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_StingerGas.BP_StingerGas_C.UserConstructionScript
// ()

void ABP_StingerGas_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.UserConstructionScript");

	ABP_StingerGas_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StingerGas.BP_StingerGas_C.Timeline_1__FinishedFunc
// ()

void ABP_StingerGas_C::Timeline_1__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.Timeline_1__FinishedFunc");

	ABP_StingerGas_C_Timeline_1__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StingerGas.BP_StingerGas_C.Timeline_1__UpdateFunc
// ()

void ABP_StingerGas_C::Timeline_1__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.Timeline_1__UpdateFunc");

	ABP_StingerGas_C_Timeline_1__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StingerGas.BP_StingerGas_C.Timeline_0__FinishedFunc
// ()

void ABP_StingerGas_C::Timeline_0__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.Timeline_0__FinishedFunc");

	ABP_StingerGas_C_Timeline_0__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StingerGas.BP_StingerGas_C.Timeline_0__UpdateFunc
// ()

void ABP_StingerGas_C::Timeline_0__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.Timeline_0__UpdateFunc");

	ABP_StingerGas_C_Timeline_0__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StingerGas.BP_StingerGas_C.ReceiveBeginPlay
// ()

void ABP_StingerGas_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.ReceiveBeginPlay");

	ABP_StingerGas_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StingerGas.BP_StingerGas_C.ExecuteUbergraph_BP_StingerGas
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_StingerGas_C::ExecuteUbergraph_BP_StingerGas(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StingerGas.BP_StingerGas_C.ExecuteUbergraph_BP_StingerGas");

	ABP_StingerGas_C_ExecuteUbergraph_BP_StingerGas_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
