// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GasPillar_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_GasPillar.BP_GasPillar_C.UserConstructionScript
// ()

void ABP_GasPillar_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GasPillar.BP_GasPillar_C.UserConstructionScript");

	ABP_GasPillar_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GasPillar.BP_GasPillar_C.ReceiveBeginPlay
// ()

void ABP_GasPillar_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GasPillar.BP_GasPillar_C.ReceiveBeginPlay");

	ABP_GasPillar_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GasPillar.BP_GasPillar_C.GainedSignificance
// ()

void ABP_GasPillar_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GasPillar.BP_GasPillar_C.GainedSignificance");

	ABP_GasPillar_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GasPillar.BP_GasPillar_C.LostSignificance
// ()

void ABP_GasPillar_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GasPillar.BP_GasPillar_C.LostSignificance");

	ABP_GasPillar_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GasPillar.BP_GasPillar_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_GasPillar_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GasPillar.BP_GasPillar_C.ReceiveEndPlay");

	ABP_GasPillar_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GasPillar.BP_GasPillar_C.ExecuteUbergraph_BP_GasPillar
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_GasPillar_C::ExecuteUbergraph_BP_GasPillar(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GasPillar.BP_GasPillar_C.ExecuteUbergraph_BP_GasPillar");

	ABP_GasPillar_C_ExecuteUbergraph_BP_GasPillar_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
