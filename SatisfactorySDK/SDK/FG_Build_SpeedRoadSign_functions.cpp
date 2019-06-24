// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_SpeedRoadSign_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.OnRep_mSpeedRestriction
// ()

void ABuild_SpeedRoadSign_C::OnRep_mSpeedRestriction()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.OnRep_mSpeedRestriction");

	ABuild_SpeedRoadSign_C_OnRep_mSpeedRestriction_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.UserConstructionScript
// ()

void ABuild_SpeedRoadSign_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.UserConstructionScript");

	ABuild_SpeedRoadSign_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.ReceiveBeginPlay
// ()

void ABuild_SpeedRoadSign_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.ReceiveBeginPlay");

	ABuild_SpeedRoadSign_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_111_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABuild_SpeedRoadSign_C::BndEvt__Sphere_K2Node_ComponentBoundEvent_111_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_111_ComponentBeginOverlapSignature__DelegateSignature");

	ABuild_SpeedRoadSign_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_111_ComponentBeginOverlapSignature__DelegateSignature_Params params;
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


// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.UpdateSpeedLimit
// ()
// Parameters:
// int                            newSpeed                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_SpeedRoadSign_C::UpdateSpeedLimit(int newSpeed)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.UpdateSpeedLimit");

	ABuild_SpeedRoadSign_C_UpdateSpeedLimit_Params params;
	params.newSpeed = newSpeed;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.ExecuteUbergraph_Build_SpeedRoadSign
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_SpeedRoadSign_C::ExecuteUbergraph_Build_SpeedRoadSign(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpeedRoadSign.Build_SpeedRoadSign_C.ExecuteUbergraph_Build_SpeedRoadSign");

	ABuild_SpeedRoadSign_C_ExecuteUbergraph_Build_SpeedRoadSign_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
