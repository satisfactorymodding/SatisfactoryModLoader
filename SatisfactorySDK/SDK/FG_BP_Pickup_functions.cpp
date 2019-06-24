// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Pickup_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Pickup.BP_Pickup_C.UserConstructionScript
// ()

void ABP_Pickup_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.UserConstructionScript");

	ABP_Pickup_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.StartIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Pickup_C::StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.StartIsLookedAt");

	ABP_Pickup_C_StartIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.StopIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Pickup_C::StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.StopIsLookedAt");

	ABP_Pickup_C_StopIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.ReceiveBeginPlay
// ()

void ABP_Pickup_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.ReceiveBeginPlay");

	ABP_Pickup_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.GainedSignificance
// ()

void ABP_Pickup_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.GainedSignificance");

	ABP_Pickup_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.LostSignificance
// ()

void ABP_Pickup_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.LostSignificance");

	ABP_Pickup_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.PlayPickupEffect
// ()

void ABP_Pickup_C::PlayPickupEffect()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.PlayPickupEffect");

	ABP_Pickup_C_PlayPickupEffect_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Pickup_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.ReceiveEndPlay");

	ABP_Pickup_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Pickup.BP_Pickup_C.ExecuteUbergraph_BP_Pickup
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Pickup_C::ExecuteUbergraph_BP_Pickup(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Pickup.BP_Pickup_C.ExecuteUbergraph_BP_Pickup");

	ABP_Pickup_C_ExecuteUbergraph_BP_Pickup_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
