// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_ManualManufacturingComponent_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.AwardRewards
// ()

void UBP_ManualManufacturingComponent_C::AwardRewards()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.AwardRewards");

	UBP_ManualManufacturingComponent_C_AwardRewards_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.CraftComplete
// ()

void UBP_ManualManufacturingComponent_C::CraftComplete()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.CraftComplete");

	UBP_ManualManufacturingComponent_C_CraftComplete_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.ExecuteUbergraph_BP_ManualManufacturingComponent
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_ManualManufacturingComponent_C::ExecuteUbergraph_BP_ManualManufacturingComponent(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.ExecuteUbergraph_BP_ManualManufacturingComponent");

	UBP_ManualManufacturingComponent_C_ExecuteUbergraph_BP_ManualManufacturingComponent_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.OnCraftCompleted__DelegateSignature
// ()

void UBP_ManualManufacturingComponent_C::OnCraftCompleted__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_ManualManufacturingComponent.BP_ManualManufacturingComponent_C.OnCraftCompleted__DelegateSignature");

	UBP_ManualManufacturingComponent_C_OnCraftCompleted__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
