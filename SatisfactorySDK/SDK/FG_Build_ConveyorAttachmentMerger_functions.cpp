// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorAttachmentMerger_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorAttachmentMerger.Build_ConveyorAttachmentMerger_C.UserConstructionScript
// ()

void ABuild_ConveyorAttachmentMerger_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentMerger.Build_ConveyorAttachmentMerger_C.UserConstructionScript");

	ABuild_ConveyorAttachmentMerger_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentMerger.Build_ConveyorAttachmentMerger_C.PlayConstructSound
// ()

void ABuild_ConveyorAttachmentMerger_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentMerger.Build_ConveyorAttachmentMerger_C.PlayConstructSound");

	ABuild_ConveyorAttachmentMerger_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentMerger.Build_ConveyorAttachmentMerger_C.ExecuteUbergraph_Build_ConveyorAttachmentMerger
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorAttachmentMerger_C::ExecuteUbergraph_Build_ConveyorAttachmentMerger(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentMerger.Build_ConveyorAttachmentMerger_C.ExecuteUbergraph_Build_ConveyorAttachmentMerger");

	ABuild_ConveyorAttachmentMerger_C_ExecuteUbergraph_Build_ConveyorAttachmentMerger_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
