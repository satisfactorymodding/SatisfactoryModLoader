// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Holo_ConveyorAttachment_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.UserConstructionScript
// ()

void AHolo_ConveyorAttachment_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.UserConstructionScript");

	AHolo_ConveyorAttachment_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.ReceiveConfigureComponents
// ()
// Parameters:
// class AFGBuildable**           inBuildable                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AHolo_ConveyorAttachment_C::ReceiveConfigureComponents(class AFGBuildable** inBuildable)
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.ReceiveConfigureComponents");

	AHolo_ConveyorAttachment_C_ReceiveConfigureComponents_Params params;
	params.inBuildable = inBuildable;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.ExecuteUbergraph_Holo_ConveyorAttachment
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AHolo_ConveyorAttachment_C::ExecuteUbergraph_Holo_ConveyorAttachment(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Holo_ConveyorAttachment.Holo_ConveyorAttachment_C.ExecuteUbergraph_Holo_ConveyorAttachment");

	AHolo_ConveyorAttachment_C_ExecuteUbergraph_Holo_ConveyorAttachment_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
