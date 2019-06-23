// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorAttachmentSplitterSmart_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorAttachmentSplitterSmart.Build_ConveyorAttachmentSplitterSmart_C.UserConstructionScript
// ()

void ABuild_ConveyorAttachmentSplitterSmart_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitterSmart.Build_ConveyorAttachmentSplitterSmart_C.UserConstructionScript");

	ABuild_ConveyorAttachmentSplitterSmart_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentSplitterSmart.Build_ConveyorAttachmentSplitterSmart_C.PlayConstructSound
// ()

void ABuild_ConveyorAttachmentSplitterSmart_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitterSmart.Build_ConveyorAttachmentSplitterSmart_C.PlayConstructSound");

	ABuild_ConveyorAttachmentSplitterSmart_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorAttachmentSplitterSmart.Build_ConveyorAttachmentSplitterSmart_C.ExecuteUbergraph_Build_ConveyorAttachmentSplitterSmart
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorAttachmentSplitterSmart_C::ExecuteUbergraph_Build_ConveyorAttachmentSplitterSmart(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorAttachmentSplitterSmart.Build_ConveyorAttachmentSplitterSmart_C.ExecuteUbergraph_Build_ConveyorAttachmentSplitterSmart");

	ABuild_ConveyorAttachmentSplitterSmart_C_ExecuteUbergraph_Build_ConveyorAttachmentSplitterSmart_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
