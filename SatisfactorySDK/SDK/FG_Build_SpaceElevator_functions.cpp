// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_SpaceElevator_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_SpaceElevator.Build_SpaceElevator_C.SetActorRepresentationText
// ()
// Parameters:
// struct FText                   newText                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABuild_SpaceElevator_C::SetActorRepresentationText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.SetActorRepresentationText");

	ABuild_SpaceElevator_C_SetActorRepresentationText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.UpdateRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_SpaceElevator_C::UpdateRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.UpdateRepresentation");

	ABuild_SpaceElevator_C_UpdateRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor ABuild_SpaceElevator_C::GetActorRepresentationColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationColor");

	ABuild_SpaceElevator_C_GetActorRepresentationColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABuild_SpaceElevator_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationText");

	ABuild_SpaceElevator_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABuild_SpaceElevator_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationTexture");

	ABuild_SpaceElevator_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationType
// ()
// Parameters:
// ERepresentationType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ERepresentationType ABuild_SpaceElevator_C::GetActorRepresentationType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationType");

	ABuild_SpaceElevator_C_GetActorRepresentationType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorShouldShowInCompass
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_SpaceElevator_C::GetActorShouldShowInCompass()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorShouldShowInCompass");

	ABuild_SpaceElevator_C_GetActorShouldShowInCompass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.AddAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_SpaceElevator_C::AddAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.AddAsRepresentation");

	ABuild_SpaceElevator_C_AddAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorFogOfWarRevealRadius
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABuild_SpaceElevator_C::GetActorFogOfWarRevealRadius()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorFogOfWarRevealRadius");

	ABuild_SpaceElevator_C_GetActorFogOfWarRevealRadius_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorFogOfWarRevealType
// ()
// Parameters:
// EFogOfWarRevealType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EFogOfWarRevealType ABuild_SpaceElevator_C::GetActorFogOfWarRevealType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorFogOfWarRevealType");

	ABuild_SpaceElevator_C_GetActorFogOfWarRevealType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorShouldShowOnMap
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_SpaceElevator_C::GetActorShouldShowOnMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorShouldShowOnMap");

	ABuild_SpaceElevator_C_GetActorShouldShowOnMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetRealActorLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABuild_SpaceElevator_C::GetRealActorLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetRealActorLocation");

	ABuild_SpaceElevator_C_GetRealActorLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.GetRealActorRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator ABuild_SpaceElevator_C::GetRealActorRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.GetRealActorRotation");

	ABuild_SpaceElevator_C_GetRealActorRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.IsActorStatic
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_SpaceElevator_C::IsActorStatic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.IsActorStatic");

	ABuild_SpaceElevator_C_IsActorStatic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.RemoveAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_SpaceElevator_C::RemoveAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.RemoveAsRepresentation");

	ABuild_SpaceElevator_C_RemoveAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.UserConstructionScript
// ()

void ABuild_SpaceElevator_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.UserConstructionScript");

	ABuild_SpaceElevator_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_01
// ()

void ABuild_SpaceElevator_C::CamShake_01()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_01");

	ABuild_SpaceElevator_C_CamShake_01_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_02
// ()

void ABuild_SpaceElevator_C::CamShake_02()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_02");

	ABuild_SpaceElevator_C_CamShake_02_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_03
// ()

void ABuild_SpaceElevator_C::CamShake_03()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_03");

	ABuild_SpaceElevator_C_CamShake_03_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_04
// ()

void ABuild_SpaceElevator_C::CamShake_04()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_04");

	ABuild_SpaceElevator_C_CamShake_04_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.UpperlineVisible
// ()

void ABuild_SpaceElevator_C::UpperlineVisible()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.UpperlineVisible");

	ABuild_SpaceElevator_C_UpperlineVisible_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.Event_StartSound
// ()

void ABuild_SpaceElevator_C::Event_StartSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.Event_StartSound");

	ABuild_SpaceElevator_C_Event_StartSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveBeginPlay
// ()

void ABuild_SpaceElevator_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveBeginPlay");

	ABuild_SpaceElevator_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.OnPhaseChanged
// ()
// Parameters:
// TEnumAsByte<EGamePhase>        gamePhase                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_SpaceElevator_C::OnPhaseChanged(TEnumAsByte<EGamePhase> gamePhase)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.OnPhaseChanged");

	ABuild_SpaceElevator_C_OnPhaseChanged_Params params;
	params.gamePhase = gamePhase;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.PlayUpgradeSequence
// ()

void ABuild_SpaceElevator_C::PlayUpgradeSequence()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.PlayUpgradeSequence");

	ABuild_SpaceElevator_C_PlayUpgradeSequence_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.Event_SE_SendOff
// ()

void ABuild_SpaceElevator_C::Event_SE_SendOff()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.Event_SE_SendOff");

	ABuild_SpaceElevator_C_Event_SE_SendOff_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveDestroyed
// ()

void ABuild_SpaceElevator_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveDestroyed");

	ABuild_SpaceElevator_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_SpaceElevator_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveEndPlay");

	ABuild_SpaceElevator_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_SpaceElevator.Build_SpaceElevator_C.ExecuteUbergraph_Build_SpaceElevator
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_SpaceElevator_C::ExecuteUbergraph_Build_SpaceElevator(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_SpaceElevator.Build_SpaceElevator_C.ExecuteUbergraph_Build_SpaceElevator");

	ABuild_SpaceElevator_C_ExecuteUbergraph_Build_SpaceElevator_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
