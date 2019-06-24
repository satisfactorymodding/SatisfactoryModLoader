// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FootPrint_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_FootPrint.BP_FootPrint_C.UserConstructionScript
// ()

void ABP_FootPrint_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.UserConstructionScript");

	ABP_FootPrint_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.ReceiveBeginPlay
// ()

void ABP_FootPrint_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.ReceiveBeginPlay");

	ABP_FootPrint_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.FootOnGrass
// ()

void ABP_FootPrint_C::FootOnGrass()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.FootOnGrass");

	ABP_FootPrint_C_FootOnGrass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.DestroyFootPrint
// ()

void ABP_FootPrint_C::DestroyFootPrint()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.DestroyFootPrint");

	ABP_FootPrint_C_DestroyFootPrint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.FootOnSand
// ()

void ABP_FootPrint_C::FootOnSand()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.FootOnSand");

	ABP_FootPrint_C_FootOnSand_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.AdjustToGround
// ()

void ABP_FootPrint_C::AdjustToGround()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.AdjustToGround");

	ABP_FootPrint_C_AdjustToGround_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_FootPrint_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.ReceiveTick");

	ABP_FootPrint_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.ReceiveActorBeginOverlap
// ()
// Parameters:
// class AActor**                 OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_FootPrint_C::ReceiveActorBeginOverlap(class AActor** OtherActor)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.ReceiveActorBeginOverlap");

	ABP_FootPrint_C_ReceiveActorBeginOverlap_Params params;
	params.OtherActor = OtherActor;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.BeginFade
// ()

void ABP_FootPrint_C::BeginFade()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.BeginFade");

	ABP_FootPrint_C_BeginFade_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.FootOnGravel
// ()

void ABP_FootPrint_C::FootOnGravel()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.FootOnGravel");

	ABP_FootPrint_C_FootOnGravel_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_FootPrint.BP_FootPrint_C.ExecuteUbergraph_BP_FootPrint
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_FootPrint_C::ExecuteUbergraph_BP_FootPrint(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_FootPrint.BP_FootPrint_C.ExecuteUbergraph_BP_FootPrint");

	ABP_FootPrint_C_ExecuteUbergraph_BP_FootPrint_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
