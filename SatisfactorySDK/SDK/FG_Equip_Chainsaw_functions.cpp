// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_Chainsaw_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Equip_Chainsaw.Equip_Chainsaw_C.CanStartSawing
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AEquip_Chainsaw_C::CanStartSawing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.CanStartSawing");

	AEquip_Chainsaw_C_CanStartSawing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.UpdateAttachmentState
// ()
// Parameters:
// TEnumAsByte<EChainsawUseState> ChainsawState                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ForceUpdate                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Chainsaw_C::UpdateAttachmentState(TEnumAsByte<EChainsawUseState> ChainsawState, bool ForceUpdate)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.UpdateAttachmentState");

	AEquip_Chainsaw_C_UpdateAttachmentState_Params params;
	params.ChainsawState = ChainsawState;
	params.ForceUpdate = ForceUpdate;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.InterpSawProgress
// ()
// Parameters:
// float                          DeltaTime                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Chainsaw_C::InterpSawProgress(float DeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.InterpSawProgress");

	AEquip_Chainsaw_C_InterpSawProgress_Params params;
	params.DeltaTime = DeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.UserConstructionScript
// ()

void AEquip_Chainsaw_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.UserConstructionScript");

	AEquip_Chainsaw_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Chainsaw_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.ReceiveTick");

	AEquip_Chainsaw_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.WasEquipped
// ()

void AEquip_Chainsaw_C::WasEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.WasEquipped");

	AEquip_Chainsaw_C_WasEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.WasUnEquipped
// ()

void AEquip_Chainsaw_C::WasUnEquipped()
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.WasUnEquipped");

	AEquip_Chainsaw_C_WasUnEquipped_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Equip_Chainsaw.Equip_Chainsaw_C.ExecuteUbergraph_Equip_Chainsaw
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AEquip_Chainsaw_C::ExecuteUbergraph_Equip_Chainsaw(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Equip_Chainsaw.Equip_Chainsaw_C.ExecuteUbergraph_Equip_Chainsaw");

	AEquip_Chainsaw_C_ExecuteUbergraph_Equip_Chainsaw_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
