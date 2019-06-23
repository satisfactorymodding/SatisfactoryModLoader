// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_BuildingPreview_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_BuildingPreview.BP_BuildingPreview_C.UserConstructionScript
// ()

void ABP_BuildingPreview_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingPreview.BP_BuildingPreview_C.UserConstructionScript");

	ABP_BuildingPreview_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildingPreview.BP_BuildingPreview_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_BuildingPreview_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingPreview.BP_BuildingPreview_C.ReceiveTick");

	ABP_BuildingPreview_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_BuildingPreview.BP_BuildingPreview_C.ExecuteUbergraph_BP_BuildingPreview
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_BuildingPreview_C::ExecuteUbergraph_BP_BuildingPreview(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_BuildingPreview.BP_BuildingPreview_C.ExecuteUbergraph_BP_BuildingPreview");

	ABP_BuildingPreview_C_ExecuteUbergraph_BP_BuildingPreview_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
