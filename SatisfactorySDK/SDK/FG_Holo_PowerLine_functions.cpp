// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Holo_PowerLine_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Holo_PowerLine.Holo_PowerLine_C.UserConstructionScript
// ()

void AHolo_PowerLine_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_PowerLine.Holo_PowerLine_C.UserConstructionScript");

	AHolo_PowerLine_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Holo_PowerLine.Holo_PowerLine_C.OnAutomaticPoleDisableToggle
// ()
// Parameters:
// bool*                          Disabled                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AHolo_PowerLine_C::OnAutomaticPoleDisableToggle(bool* Disabled)
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_PowerLine.Holo_PowerLine_C.OnAutomaticPoleDisableToggle");

	AHolo_PowerLine_C_OnAutomaticPoleDisableToggle_Params params;
	params.Disabled = Disabled;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Holo_PowerLine.Holo_PowerLine_C.ExecuteUbergraph_Holo_PowerLine
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AHolo_PowerLine_C::ExecuteUbergraph_Holo_PowerLine(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_PowerLine.Holo_PowerLine_C.ExecuteUbergraph_Holo_PowerLine");

	AHolo_PowerLine_C_ExecuteUbergraph_Holo_PowerLine_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
