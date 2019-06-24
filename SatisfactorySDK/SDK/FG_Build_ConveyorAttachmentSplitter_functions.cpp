// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorAttachmentSplitter_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorAttachmentSplitter.Build_ConveyorAttachmentSplitter_C.UserConstructionScript
// ()

void ABuild_ConveyorAttachmentSplitter_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitter.Build_ConveyorAttachmentSplitter_C.UserConstructionScript");

	ABuild_ConveyorAttachmentSplitter_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentSplitter.Build_ConveyorAttachmentSplitter_C.PlayConstructSound
// ()

void ABuild_ConveyorAttachmentSplitter_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitter.Build_ConveyorAttachmentSplitter_C.PlayConstructSound");

	ABuild_ConveyorAttachmentSplitter_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentSplitter.Build_ConveyorAttachmentSplitter_C.ExecuteUbergraph_Build_ConveyorAttachmentSplitter
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorAttachmentSplitter_C::ExecuteUbergraph_Build_ConveyorAttachmentSplitter(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitter.Build_ConveyorAttachmentSplitter_C.ExecuteUbergraph_Build_ConveyorAttachmentSplitter");

	ABuild_ConveyorAttachmentSplitter_C_ExecuteUbergraph_Build_ConveyorAttachmentSplitter_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
