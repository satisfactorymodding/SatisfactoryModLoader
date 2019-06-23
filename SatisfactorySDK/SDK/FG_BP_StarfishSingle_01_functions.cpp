// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_StarfishSingle_01_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.IsTooClose
// ()
// Parameters:
// bool                           IsTooClose                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_StarfishSingle_01_C::IsTooClose(bool* IsTooClose)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.IsTooClose");

	ABP_StarfishSingle_01_C_IsTooClose_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsTooClose != nullptr)
		*IsTooClose = params.IsTooClose;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.Burrow
// ()

void ABP_StarfishSingle_01_C::Burrow()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.Burrow");

	ABP_StarfishSingle_01_C_Burrow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.CanMove
// ()
// Parameters:
// bool                           CanMove                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_StarfishSingle_01_C::CanMove(bool* CanMove)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.CanMove");

	ABP_StarfishSingle_01_C_CanMove_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (CanMove != nullptr)
		*CanMove = params.CanMove;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.MoveStarFish
// ()

void ABP_StarfishSingle_01_C::MoveStarFish()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.MoveStarFish");

	ABP_StarfishSingle_01_C_MoveStarFish_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.UpdateMesh
// ()
// Parameters:
// float                          Position                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UStaticMeshComponent*    Mesh                           (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)

void ABP_StarfishSingle_01_C::UpdateMesh(float Position, class UStaticMeshComponent* Mesh)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.UpdateMesh");

	ABP_StarfishSingle_01_C_UpdateMesh_Params params;
	params.Position = Position;
	params.Mesh = Mesh;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.UserConstructionScript
// ()

void ABP_StarfishSingle_01_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.UserConstructionScript");

	ABP_StarfishSingle_01_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ReceiveBeginPlay
// ()

void ABP_StarfishSingle_01_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ReceiveBeginPlay");

	ABP_StarfishSingle_01_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABP_StarfishSingle_01_C::BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	ABP_StarfishSingle_01_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
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


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_StarfishSingle_01_C::BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature");

	ABP_StarfishSingle_01_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.StartBurrow
// ()

void ABP_StarfishSingle_01_C::StartBurrow()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.StartBurrow");

	ABP_StarfishSingle_01_C_StartBurrow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_StarfishSingle_01_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ReceiveTick");

	ABP_StarfishSingle_01_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.StopBurrow
// ()

void ABP_StarfishSingle_01_C::StopBurrow()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.StopBurrow");

	ABP_StarfishSingle_01_C_StopBurrow_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere2_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_StarfishSingle_01_C::BndEvt__Sphere2_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.BndEvt__Sphere2_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature");

	ABP_StarfishSingle_01_C_BndEvt__Sphere2_K2Node_ComponentBoundEvent_0_ComponentEndOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ExecuteUbergraph_BP_StarfishSingle_01
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_StarfishSingle_01_C::ExecuteUbergraph_BP_StarfishSingle_01(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_StarfishSingle_01.BP_StarfishSingle_01_C.ExecuteUbergraph_BP_StarfishSingle_01");

	ABP_StarfishSingle_01_C_ExecuteUbergraph_BP_StarfishSingle_01_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
