// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_BP_Manta_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Manta.BP_Manta_C.UpdateMesh
// ()
// Parameters:
// float                          Position                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class USkeletalMeshComponent*  Mesh                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_Manta_C::UpdateMesh(float Position, class USkeletalMeshComponent* Mesh)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.UpdateMesh");

	ABP_Manta_C_UpdateMesh_Params params;
	params.Position = Position;
	params.Mesh = Mesh;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.UserConstructionScript
// ()

void ABP_Manta_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.UserConstructionScript");

	ABP_Manta_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.Timeline_1__FinishedFunc
// ()

void ABP_Manta_C::Timeline_1__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.Timeline_1__FinishedFunc");

	ABP_Manta_C_Timeline_1__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.Timeline_1__UpdateFunc
// ()

void ABP_Manta_C::Timeline_1__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.Timeline_1__UpdateFunc");

	ABP_Manta_C_Timeline_1__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.Timeline_0__FinishedFunc
// ()

void ABP_Manta_C::Timeline_0__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.Timeline_0__FinishedFunc");

	ABP_Manta_C_Timeline_0__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.Timeline_0__UpdateFunc
// ()

void ABP_Manta_C::Timeline_0__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.Timeline_0__UpdateFunc");

	ABP_Manta_C_Timeline_0__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.Reset
// ()

void ABP_Manta_C::Reset()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.Reset");

	ABP_Manta_C_Reset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Manta_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.ReceiveTick");

	ABP_Manta_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.ReceiveBeginPlay
// ()

void ABP_Manta_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.ReceiveBeginPlay");

	ABP_Manta_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.Recheck
// ()

void ABP_Manta_C::Recheck()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.Recheck");

	ABP_Manta_C_Recheck_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Manta.BP_Manta_C.ExecuteUbergraph_BP_Manta
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Manta_C::ExecuteUbergraph_BP_Manta(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Manta.BP_Manta_C.ExecuteUbergraph_BP_Manta");

	ABP_Manta_C_ExecuteUbergraph_BP_Manta_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
