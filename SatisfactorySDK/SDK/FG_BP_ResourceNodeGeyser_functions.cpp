// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ResourceNodeGeyser_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.UserConstructionScript
// ()

void ABP_ResourceNodeGeyser_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.UserConstructionScript");

	ABP_ResourceNodeGeyser_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.OnIsOccupiedChanged
// ()
// Parameters:
// bool*                          newIsOccupied                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ResourceNodeGeyser_C::OnIsOccupiedChanged(bool* newIsOccupied)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.OnIsOccupiedChanged");

	ABP_ResourceNodeGeyser_C_OnIsOccupiedChanged_Params params;
	params.newIsOccupied = newIsOccupied;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.GainedSignificance
// ()

void ABP_ResourceNodeGeyser_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.GainedSignificance");

	ABP_ResourceNodeGeyser_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.LostSignificance
// ()

void ABP_ResourceNodeGeyser_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.LostSignificance");

	ABP_ResourceNodeGeyser_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.EruptLoop
// ()

void ABP_ResourceNodeGeyser_C::EruptLoop()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.EruptLoop");

	ABP_ResourceNodeGeyser_C_EruptLoop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.ExecuteUbergraph_BP_ResourceNodeGeyser
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_ResourceNodeGeyser_C::ExecuteUbergraph_BP_ResourceNodeGeyser(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ResourceNodeGeyser.BP_ResourceNodeGeyser_C.ExecuteUbergraph_BP_ResourceNodeGeyser");

	ABP_ResourceNodeGeyser_C_ExecuteUbergraph_BP_ResourceNodeGeyser_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
