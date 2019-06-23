// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorAttachmentSplitterProgrammable_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorAttachmentSplitterProgrammable.Build_ConveyorAttachmentSplitterProgrammable_C.UserConstructionScript
// ()

void ABuild_ConveyorAttachmentSplitterProgrammable_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitterProgrammable.Build_ConveyorAttachmentSplitterProgrammable_C.UserConstructionScript");

	ABuild_ConveyorAttachmentSplitterProgrammable_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentSplitterProgrammable.Build_ConveyorAttachmentSplitterProgrammable_C.PlayConstructSound
// ()

void ABuild_ConveyorAttachmentSplitterProgrammable_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitterProgrammable.Build_ConveyorAttachmentSplitterProgrammable_C.PlayConstructSound");

	ABuild_ConveyorAttachmentSplitterProgrammable_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentSplitterProgrammable.Build_ConveyorAttachmentSplitterProgrammable_C.ExecuteUbergraph_Build_ConveyorAttachmentSplitterProgrammable
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorAttachmentSplitterProgrammable_C::ExecuteUbergraph_Build_ConveyorAttachmentSplitterProgrammable(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitterProgrammable.Build_ConveyorAttachmentSplitterProgrammable_C.ExecuteUbergraph_Build_ConveyorAttachmentSplitterProgrammable");

	ABuild_ConveyorAttachmentSplitterProgrammable_C_ExecuteUbergraph_Build_ConveyorAttachmentSplitterProgrammable_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
