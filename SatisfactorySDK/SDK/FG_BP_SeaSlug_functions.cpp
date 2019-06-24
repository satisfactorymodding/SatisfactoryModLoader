// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SeaSlug_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SeaSlug.BP_SeaSlug_C.UpdateMesh
// ()
// Parameters:
// float                          Position                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class USkeletalMeshComponent*  Mesh                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_SeaSlug_C::UpdateMesh(float Position, class USkeletalMeshComponent* Mesh)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.UpdateMesh");

	ABP_SeaSlug_C_UpdateMesh_Params params;
	params.Position = Position;
	params.Mesh = Mesh;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.UserConstructionScript
// ()

void ABP_SeaSlug_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.UserConstructionScript");

	ABP_SeaSlug_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_1__FinishedFunc
// ()

void ABP_SeaSlug_C::Timeline_1__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.Timeline_1__FinishedFunc");

	ABP_SeaSlug_C_Timeline_1__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_1__UpdateFunc
// ()

void ABP_SeaSlug_C::Timeline_1__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.Timeline_1__UpdateFunc");

	ABP_SeaSlug_C_Timeline_1__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_0__FinishedFunc
// ()

void ABP_SeaSlug_C::Timeline_0__FinishedFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.Timeline_0__FinishedFunc");

	ABP_SeaSlug_C_Timeline_0__FinishedFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.Timeline_0__UpdateFunc
// ()

void ABP_SeaSlug_C::Timeline_0__UpdateFunc()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.Timeline_0__UpdateFunc");

	ABP_SeaSlug_C_Timeline_0__UpdateFunc_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.ReceiveBeginPlay
// ()

void ABP_SeaSlug_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.ReceiveBeginPlay");

	ABP_SeaSlug_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABP_SeaSlug_C::BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	ABP_SeaSlug_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;
	params.bFromSweep = bFromSweep;
	params.SweepResult = SweepResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SeaSlug_C::BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature");

	ABP_SeaSlug_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.Reset
// ()

void ABP_SeaSlug_C::Reset()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.Reset");

	ABP_SeaSlug_C_Reset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SeaSlug.BP_SeaSlug_C.ExecuteUbergraph_BP_SeaSlug
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SeaSlug_C::ExecuteUbergraph_BP_SeaSlug(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SeaSlug.BP_SeaSlug_C.ExecuteUbergraph_BP_SeaSlug");

	ABP_SeaSlug_C_ExecuteUbergraph_BP_SeaSlug_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
