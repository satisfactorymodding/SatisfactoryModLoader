// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TruckStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_TruckStation.Build_TruckStation_C.GetActorCompassViewDistance
// ()
// Parameters:
// ECompassViewDistance           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ECompassViewDistance ABuild_TruckStation_C::GetActorCompassViewDistance()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorCompassViewDistance");

	ABuild_TruckStation_C_GetActorCompassViewDistance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.SetActorCompassViewDistance
// ()
// Parameters:
// ECompassViewDistance           compassViewDistance            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// ECompassViewDistance           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ECompassViewDistance ABuild_TruckStation_C::SetActorCompassViewDistance(ECompassViewDistance compassViewDistance)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.SetActorCompassViewDistance");

	ABuild_TruckStation_C_SetActorCompassViewDistance_Params params;
	params.compassViewDistance = compassViewDistance;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.AddAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_TruckStation_C::AddAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.AddAsRepresentation");

	ABuild_TruckStation_C_AddAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorFogOfWarRevealRadius
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABuild_TruckStation_C::GetActorFogOfWarRevealRadius()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorFogOfWarRevealRadius");

	ABuild_TruckStation_C_GetActorFogOfWarRevealRadius_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorFogOfWarRevealType
// ()
// Parameters:
// EFogOfWarRevealType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EFogOfWarRevealType ABuild_TruckStation_C::GetActorFogOfWarRevealType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorFogOfWarRevealType");

	ABuild_TruckStation_C_GetActorFogOfWarRevealType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor ABuild_TruckStation_C::GetActorRepresentationColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationColor");

	ABuild_TruckStation_C_GetActorRepresentationColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABuild_TruckStation_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationText");

	ABuild_TruckStation_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABuild_TruckStation_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationTexture");

	ABuild_TruckStation_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationType
// ()
// Parameters:
// ERepresentationType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ERepresentationType ABuild_TruckStation_C::GetActorRepresentationType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorRepresentationType");

	ABuild_TruckStation_C_GetActorRepresentationType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorShouldShowInCompass
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_TruckStation_C::GetActorShouldShowInCompass()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorShouldShowInCompass");

	ABuild_TruckStation_C_GetActorShouldShowInCompass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetActorShouldShowOnMap
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_TruckStation_C::GetActorShouldShowOnMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetActorShouldShowOnMap");

	ABuild_TruckStation_C_GetActorShouldShowOnMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetRealActorLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABuild_TruckStation_C::GetRealActorLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetRealActorLocation");

	ABuild_TruckStation_C_GetRealActorLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.GetRealActorRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator ABuild_TruckStation_C::GetRealActorRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.GetRealActorRotation");

	ABuild_TruckStation_C_GetRealActorRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.IsActorStatic
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_TruckStation_C::IsActorStatic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.IsActorStatic");

	ABuild_TruckStation_C_IsActorStatic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.RemoveAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_TruckStation_C::RemoveAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.RemoveAsRepresentation");

	ABuild_TruckStation_C_RemoveAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.SetActorRepresentationText
// ()
// Parameters:
// struct FText                   newText                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABuild_TruckStation_C::SetActorRepresentationText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.SetActorRepresentationText");

	ABuild_TruckStation_C_SetActorRepresentationText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.UpdateRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_TruckStation_C::UpdateRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.UpdateRepresentation");

	ABuild_TruckStation_C_UpdateRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_TruckStation.Build_TruckStation_C.UserConstructionScript
// ()

void ABuild_TruckStation_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.UserConstructionScript");

	ABuild_TruckStation_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_TruckStation.Build_TruckStation_C.BndEvt__Box_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABuild_TruckStation_C::BndEvt__Box_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.BndEvt__Box_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	ABuild_TruckStation_C_BndEvt__Box_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
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


// Function Build_TruckStation.Build_TruckStation_C.BndEvt__Box_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_TruckStation_C::BndEvt__Box_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.BndEvt__Box_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature");

	ABuild_TruckStation_C_BndEvt__Box_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_TruckStation.Build_TruckStation_C.ReceiveBeginPlay
// ()

void ABuild_TruckStation_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.ReceiveBeginPlay");

	ABuild_TruckStation_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_TruckStation.Build_TruckStation_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_TruckStation_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.ReceiveEndPlay");

	ABuild_TruckStation_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_TruckStation.Build_TruckStation_C.ExecuteUbergraph_Build_TruckStation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_TruckStation_C::ExecuteUbergraph_Build_TruckStation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TruckStation.Build_TruckStation_C.ExecuteUbergraph_Build_TruckStation");

	ABuild_TruckStation_C_ExecuteUbergraph_Build_TruckStation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
