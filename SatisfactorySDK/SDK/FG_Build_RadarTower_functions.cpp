// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_RadarTower_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_RadarTower.Build_RadarTower_C.SetActorRepresentationText
// ()
// Parameters:
// struct FText                   newText                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABuild_RadarTower_C::SetActorRepresentationText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.SetActorRepresentationText");

	ABuild_RadarTower_C_SetActorRepresentationText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.UpdateRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RadarTower_C::UpdateRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.UpdateRepresentation");

	ABuild_RadarTower_C_UpdateRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor ABuild_RadarTower_C::GetActorRepresentationColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationColor");

	ABuild_RadarTower_C_GetActorRepresentationColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABuild_RadarTower_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationText");

	ABuild_RadarTower_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABuild_RadarTower_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationTexture");

	ABuild_RadarTower_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationType
// ()
// Parameters:
// ERepresentationType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ERepresentationType ABuild_RadarTower_C::GetActorRepresentationType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorRepresentationType");

	ABuild_RadarTower_C_GetActorRepresentationType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorShouldShowInCompass
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RadarTower_C::GetActorShouldShowInCompass()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorShouldShowInCompass");

	ABuild_RadarTower_C_GetActorShouldShowInCompass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.AddAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RadarTower_C::AddAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.AddAsRepresentation");

	ABuild_RadarTower_C_AddAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorFogOfWarRevealRadius
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABuild_RadarTower_C::GetActorFogOfWarRevealRadius()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorFogOfWarRevealRadius");

	ABuild_RadarTower_C_GetActorFogOfWarRevealRadius_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorFogOfWarRevealType
// ()
// Parameters:
// EFogOfWarRevealType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EFogOfWarRevealType ABuild_RadarTower_C::GetActorFogOfWarRevealType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorFogOfWarRevealType");

	ABuild_RadarTower_C_GetActorFogOfWarRevealType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetActorShouldShowOnMap
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RadarTower_C::GetActorShouldShowOnMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetActorShouldShowOnMap");

	ABuild_RadarTower_C_GetActorShouldShowOnMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetRealActorLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABuild_RadarTower_C::GetRealActorLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetRealActorLocation");

	ABuild_RadarTower_C_GetRealActorLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.GetRealActorRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator ABuild_RadarTower_C::GetRealActorRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.GetRealActorRotation");

	ABuild_RadarTower_C_GetRealActorRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.IsActorStatic
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RadarTower_C::IsActorStatic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.IsActorStatic");

	ABuild_RadarTower_C_IsActorStatic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.RemoveAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RadarTower_C::RemoveAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.RemoveAsRepresentation");

	ABuild_RadarTower_C_RemoveAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RadarTower.Build_RadarTower_C.UserConstructionScript
// ()

void ABuild_RadarTower_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.UserConstructionScript");

	ABuild_RadarTower_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RadarTower.Build_RadarTower_C.ReceiveBeginPlay
// ()

void ABuild_RadarTower_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.ReceiveBeginPlay");

	ABuild_RadarTower_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RadarTower.Build_RadarTower_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_RadarTower_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.ReceiveEndPlay");

	ABuild_RadarTower_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RadarTower.Build_RadarTower_C.OnRadiusExpansionTriggered
// ()

void ABuild_RadarTower_C::OnRadiusExpansionTriggered()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.OnRadiusExpansionTriggered");

	ABuild_RadarTower_C_OnRadiusExpansionTriggered_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RadarTower.Build_RadarTower_C.Factory_ReceiveStartProducing
// ()

void ABuild_RadarTower_C::Factory_ReceiveStartProducing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.Factory_ReceiveStartProducing");

	ABuild_RadarTower_C_Factory_ReceiveStartProducing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RadarTower.Build_RadarTower_C.ExecuteUbergraph_Build_RadarTower
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_RadarTower_C::ExecuteUbergraph_Build_RadarTower(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RadarTower.Build_RadarTower_C.ExecuteUbergraph_Build_RadarTower");

	ABuild_RadarTower_C_ExecuteUbergraph_Build_RadarTower_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
