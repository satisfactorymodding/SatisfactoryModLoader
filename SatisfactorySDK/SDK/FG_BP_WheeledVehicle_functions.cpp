// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_WheeledVehicle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.SetActorRepresentationText
// ()
// Parameters:
// struct FText                   newText                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_WheeledVehicle_C::SetActorRepresentationText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.SetActorRepresentationText");

	ABP_WheeledVehicle_C_SetActorRepresentationText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_WheeledVehicle_C::UpdateRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateRepresentation");

	ABP_WheeledVehicle_C_UpdateRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor ABP_WheeledVehicle_C::GetActorRepresentationColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationColor");

	ABP_WheeledVehicle_C_GetActorRepresentationColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_WheeledVehicle_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationText");

	ABP_WheeledVehicle_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABP_WheeledVehicle_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationTexture");

	ABP_WheeledVehicle_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationType
// ()
// Parameters:
// ERepresentationType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ERepresentationType ABP_WheeledVehicle_C::GetActorRepresentationType()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationType");

	ABP_WheeledVehicle_C_GetActorRepresentationType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorShouldShowInCompass
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_WheeledVehicle_C::GetActorShouldShowInCompass()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorShouldShowInCompass");

	ABP_WheeledVehicle_C_GetActorShouldShowInCompass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorFogOfWarRevealRadius
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_WheeledVehicle_C::GetActorFogOfWarRevealRadius()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorFogOfWarRevealRadius");

	ABP_WheeledVehicle_C_GetActorFogOfWarRevealRadius_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorFogOfWarRevealType
// ()
// Parameters:
// EFogOfWarRevealType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EFogOfWarRevealType ABP_WheeledVehicle_C::GetActorFogOfWarRevealType()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorFogOfWarRevealType");

	ABP_WheeledVehicle_C_GetActorFogOfWarRevealType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.RemoveAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_WheeledVehicle_C::RemoveAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.RemoveAsRepresentation");

	ABP_WheeledVehicle_C_RemoveAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.AddAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_WheeledVehicle_C::AddAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.AddAsRepresentation");

	ABP_WheeledVehicle_C_AddAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorShouldShowOnMap
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_WheeledVehicle_C::GetActorShouldShowOnMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorShouldShowOnMap");

	ABP_WheeledVehicle_C_GetActorShouldShowOnMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetRealActorLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABP_WheeledVehicle_C::GetRealActorLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetRealActorLocation");

	ABP_WheeledVehicle_C_GetRealActorLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetRealActorRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator ABP_WheeledVehicle_C::GetRealActorRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetRealActorRotation");

	ABP_WheeledVehicle_C_GetRealActorRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.IsActorStatic
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_WheeledVehicle_C::IsActorStatic()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.IsActorStatic");

	ABP_WheeledVehicle_C_IsActorStatic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetDriftForceOffset
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABP_WheeledVehicle_C::GetDriftForceOffset()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetDriftForceOffset");

	ABP_WheeledVehicle_C_GetDriftForceOffset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ShouldStopVehicle
// ()
// Parameters:
// bool                           ShouldStop                     (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ShouldStopVehicle(bool* ShouldStop)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ShouldStopVehicle");

	ABP_WheeledVehicle_C_ShouldStopVehicle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (ShouldStop != nullptr)
		*ShouldStop = params.ShouldStop;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TurnOverVehicle
// ()

void ABP_WheeledVehicle_C::TurnOverVehicle()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TurnOverVehicle");

	ABP_WheeledVehicle_C_TurnOverVehicle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.AdjustThrottle
// ()
// Parameters:
// float                          Throttle                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          adjustedThrottle               (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::AdjustThrottle(float Throttle, float* adjustedThrottle)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.AdjustThrottle");

	ABP_WheeledVehicle_C_AdjustThrottle_Params params;
	params.Throttle = Throttle;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (adjustedThrottle != nullptr)
		*adjustedThrottle = params.adjustedThrottle;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TogglePathVisibility
// ()

void ABP_WheeledVehicle_C::TogglePathVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TogglePathVisibility");

	ABP_WheeledVehicle_C_TogglePathVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ToggleAutoPilot
// ()

void ABP_WheeledVehicle_C::ToggleAutoPilot()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ToggleAutoPilot");

	ABP_WheeledVehicle_C_ToggleAutoPilot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TogglePauseRecording
// ()

void ABP_WheeledVehicle_C::TogglePauseRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TogglePauseRecording");

	ABP_WheeledVehicle_C_TogglePauseRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickSimulationMovement
// ()

void ABP_WheeledVehicle_C::TickSimulationMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickSimulationMovement");

	ABP_WheeledVehicle_C_TickSimulationMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CalculateReverseSteering
// ()

void ABP_WheeledVehicle_C::CalculateReverseSteering()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.CalculateReverseSteering");

	ABP_WheeledVehicle_C_CalculateReverseSteering_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopVehicle
// ()

void ABP_WheeledVehicle_C::StopVehicle()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopVehicle");

	ABP_WheeledVehicle_C_StopVehicle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CanMove
// ()
// Parameters:
// bool                           CanMove                        (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::CanMove(bool* CanMove)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.CanMove");

	ABP_WheeledVehicle_C_CanMove_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (CanMove != nullptr)
		*CanMove = params.CanMove;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateEngineLoadSound
// ()
// Parameters:
// float                          dt                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::UpdateEngineLoadSound(float dt)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateEngineLoadSound");

	ABP_WheeledVehicle_C_UpdateEngineLoadSound_Params params;
	params.dt = dt;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateAccelerationSound
// ()

void ABP_WheeledVehicle_C::UpdateAccelerationSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateAccelerationSound");

	ABP_WheeledVehicle_C_UpdateAccelerationSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateThrottleState
// ()

void ABP_WheeledVehicle_C::UpdateThrottleState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateThrottleState");

	ABP_WheeledVehicle_C_UpdateThrottleState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.DidGearDown
// ()

void ABP_WheeledVehicle_C::DidGearDown()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.DidGearDown");

	ABP_WheeledVehicle_C_DidGearDown_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.DidGearUp
// ()

void ABP_WheeledVehicle_C::DidGearUp()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.DidGearUp");

	ABP_WheeledVehicle_C_DidGearUp_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CheckCurrentGear
// ()

void ABP_WheeledVehicle_C::CheckCurrentGear()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.CheckCurrentGear");

	ABP_WheeledVehicle_C_CheckCurrentGear_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopSoundLoops
// ()

void ABP_WheeledVehicle_C::StopSoundLoops()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopSoundLoops");

	ABP_WheeledVehicle_C_StopSoundLoops_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartSoundLoops
// ()

void ABP_WheeledVehicle_C::StartSoundLoops()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartSoundLoops");

	ABP_WheeledVehicle_C_StartSoundLoops_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ToggleFreeCamera
// ()

void ABP_WheeledVehicle_C::ToggleFreeCamera()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ToggleFreeCamera");

	ABP_WheeledVehicle_C_ToggleFreeCamera_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetLookAtDecription
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_WheeledVehicle_C::GetLookAtDecription(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetLookAtDecription");

	ABP_WheeledVehicle_C_GetLookAtDecription_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CloseVehicleUI
// ()
// Parameters:
// class AFGCharacterPlayer*      inCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::CloseVehicleUI(class AFGCharacterPlayer* inCharacter)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.CloseVehicleUI");

	ABP_WheeledVehicle_C_CloseVehicleUI_Params params;
	params.inCharacter = inCharacter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OpenVehicleUI
// ()
// Parameters:
// class AFGCharacterPlayer*      inCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::OpenVehicleUI(class AFGCharacterPlayer* inCharacter)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OpenVehicleUI");

	ABP_WheeledVehicle_C_OpenVehicleUI_Params params;
	params.inCharacter = inCharacter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.PonderOpeningTrunk
// ()
// Parameters:
// class AFGCharacterPlayer*      inCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::PonderOpeningTrunk(class AFGCharacterPlayer* inCharacter)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.PonderOpeningTrunk");

	ABP_WheeledVehicle_C_PonderOpeningTrunk_Params params;
	params.inCharacter = inCharacter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateUseState
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                atLocation                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class UPrimitiveComponent**    componentHit                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FUseState               out_useState                   (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_WheeledVehicle_C::UpdateUseState(class AFGCharacterPlayer** byCharacter, struct FVector* atLocation, class UPrimitiveComponent** componentHit, struct FUseState* out_useState)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateUseState");

	ABP_WheeledVehicle_C_UpdateUseState_Params params;
	params.byCharacter = byCharacter;
	params.atLocation = atLocation;
	params.componentHit = componentHit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_useState != nullptr)
		*out_useState = params.out_useState;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnRep_mIsFollowingPath
// ()

void ABP_WheeledVehicle_C::OnRep_mIsFollowingPath()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnRep_mIsFollowingPath");

	ABP_WheeledVehicle_C_OnRep_mIsFollowingPath_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateSpeedLimit
// ()
// Parameters:
// class ABP_VehicleTargetPoint_C* TargetPoint                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::UpdateSpeedLimit(class ABP_VehicleTargetPoint_C* TargetPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateSpeedLimit");

	ABP_WheeledVehicle_C_UpdateSpeedLimit_Params params;
	params.TargetPoint = TargetPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.DoReverseToFreedom
// ()

void ABP_WheeledVehicle_C::DoReverseToFreedom()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.DoReverseToFreedom");

	ABP_WheeledVehicle_C_DoReverseToFreedom_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReverseToFreedom
// ()

void ABP_WheeledVehicle_C::ReverseToFreedom()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReverseToFreedom");

	ABP_WheeledVehicle_C_ReverseToFreedom_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CacheSpeedInKMH
// ()

void ABP_WheeledVehicle_C::CacheSpeedInKMH()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.CacheSpeedInKMH");

	ABP_WheeledVehicle_C_CacheSpeedInKMH_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnRep_mIsRecording
// ()

void ABP_WheeledVehicle_C::OnRep_mIsRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnRep_mIsRecording");

	ABP_WheeledVehicle_C_OnRep_mIsRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.MoveToLocation
// ()

void ABP_WheeledVehicle_C::MoveToLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.MoveToLocation");

	ABP_WheeledVehicle_C_MoveToLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickRecording
// ()
// Parameters:
// float                          dt                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::TickRecording(float dt)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickRecording");

	ABP_WheeledVehicle_C_TickRecording_Params params;
	params.dt = dt;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateVehicleMovement
// ()

void ABP_WheeledVehicle_C::UpdateVehicleMovement()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateVehicleMovement");

	ABP_WheeledVehicle_C_UpdateVehicleMovement_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartRecording
// ()

void ABP_WheeledVehicle_C::StartRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartRecording");

	ABP_WheeledVehicle_C_StartRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopRecording
// ()

void ABP_WheeledVehicle_C::StopRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopRecording");

	ABP_WheeledVehicle_C_StopRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GatherData
// ()

void ABP_WheeledVehicle_C::GatherData()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GatherData");

	ABP_WheeledVehicle_C_GatherData_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.RemoveOldTargets
// ()

void ABP_WheeledVehicle_C::RemoveOldTargets()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.RemoveOldTargets");

	ABP_WheeledVehicle_C_RemoveOldTargets_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.PlaceTargetPoint
// ()

void ABP_WheeledVehicle_C::PlaceTargetPoint()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.PlaceTargetPoint");

	ABP_WheeledVehicle_C_PlaceTargetPoint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TargetReached
// ()

void ABP_WheeledVehicle_C::TargetReached()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TargetReached");

	ABP_WheeledVehicle_C_TargetReached_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.SetNewPath
// ()
// Parameters:
// class ABP_VehicleTargetPoint_C* newTarget                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::SetNewPath(class ABP_VehicleTargetPoint_C** newTarget)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.SetNewPath");

	ABP_WheeledVehicle_C_SetNewPath_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (newTarget != nullptr)
		*newTarget = params.newTarget;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetTargetDistance
// ()
// Parameters:
// float                          Distance                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::GetTargetDistance(float* Distance)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetTargetDistance");

	ABP_WheeledVehicle_C_GetTargetDistance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (Distance != nullptr)
		*Distance = params.Distance;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateThrottle
// ()

void ABP_WheeledVehicle_C::UpdateThrottle()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateThrottle");

	ABP_WheeledVehicle_C_UpdateThrottle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateSteering
// ()

void ABP_WheeledVehicle_C::UpdateSteering()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateSteering");

	ABP_WheeledVehicle_C_UpdateSteering_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UserConstructionScript
// ()

void ABP_WheeledVehicle_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UserConstructionScript");

	ABP_WheeledVehicle_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Reload_K2Node_InputActionEvent_7
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_Reload_K2Node_InputActionEvent_7(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Reload_K2Node_InputActionEvent_7");

	ABP_WheeledVehicle_C_InpActEvt_Reload_K2Node_InputActionEvent_7_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Use_K2Node_InputActionEvent_6
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_Use_K2Node_InputActionEvent_6(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Use_K2Node_InputActionEvent_6");

	ABP_WheeledVehicle_C_InpActEvt_Use_K2Node_InputActionEvent_6_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_5
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_Jump_Drift_K2Node_InputActionEvent_5(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_5");

	ABP_WheeledVehicle_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_5_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_4
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_Jump_Drift_K2Node_InputActionEvent_4(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_4");

	ABP_WheeledVehicle_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_4_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_3
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_3(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_3");

	ABP_WheeledVehicle_C_InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_3_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_2
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_2(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_2");

	ABP_WheeledVehicle_C_InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_2_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void ABP_WheeledVehicle_C::InpActEvt_PrimaryFire_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_1");

	ABP_WheeledVehicle_C_InpActEvt_PrimaryFire_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerToggleRecording
// ()

void ABP_WheeledVehicle_C::ServerToggleRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerToggleRecording");

	ABP_WheeledVehicle_C_ServerToggleRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveUnpossessed
// ()
// Parameters:
// class AController**            OldController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ReceiveUnpossessed(class AController** OldController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveUnpossessed");

	ABP_WheeledVehicle_C_ReceiveUnpossessed_Params params;
	params.OldController = OldController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveHit
// ()
// Parameters:
// class UPrimitiveComponent**    MyComp                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor**                 Other                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent**    OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// bool*                          bSelfMoved                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                HitLocation                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                HitNormal                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                NormalImpulse                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult*             Hit                            (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABP_WheeledVehicle_C::ReceiveHit(class UPrimitiveComponent** MyComp, class AActor** Other, class UPrimitiveComponent** OtherComp, bool* bSelfMoved, struct FVector* HitLocation, struct FVector* HitNormal, struct FVector* NormalImpulse, struct FHitResult* Hit)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveHit");

	ABP_WheeledVehicle_C_ReceiveHit_Params params;
	params.MyComp = MyComp;
	params.Other = Other;
	params.OtherComp = OtherComp;
	params.bSelfMoved = bSelfMoved;
	params.HitLocation = HitLocation;
	params.HitNormal = HitNormal;
	params.NormalImpulse = NormalImpulse;
	params.Hit = Hit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveDestroyed
// ()

void ABP_WheeledVehicle_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveDestroyed");

	ABP_WheeledVehicle_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ResetImpactSound
// ()

void ABP_WheeledVehicle_C::ResetImpactSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ResetImpactSound");

	ABP_WheeledVehicle_C_ResetImpactSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnUse
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_WheeledVehicle_C::OnUse(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnUse");

	ABP_WheeledVehicle_C_OnUse_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerSetTrunkUser
// ()
// Parameters:
// class AFGCharacterPlayer*      inCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ServerSetTrunkUser(class AFGCharacterPlayer* inCharacter)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerSetTrunkUser");

	ABP_WheeledVehicle_C_ServerSetTrunkUser_Params params;
	params.inCharacter = inCharacter;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OpenTrunk
// ()

void ABP_WheeledVehicle_C::OpenTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OpenTrunk");

	ABP_WheeledVehicle_C_OpenTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_OpenTrunk
// ()

void ABP_WheeledVehicle_C::Multicast_OpenTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_OpenTrunk");

	ABP_WheeledVehicle_C_Multicast_OpenTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CloseTrunk
// ()

void ABP_WheeledVehicle_C::CloseTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.CloseTrunk");

	ABP_WheeledVehicle_C_CloseTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_CloseTrunk
// ()

void ABP_WheeledVehicle_C::Multicast_CloseTrunk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_CloseTrunk");

	ABP_WheeledVehicle_C_Multicast_CloseTrunk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceivePossessed
// ()
// Parameters:
// class AController**            NewController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ReceivePossessed(class AController** NewController)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceivePossessed");

	ABP_WheeledVehicle_C_ReceivePossessed_Params params;
	params.NewController = NewController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ClientClearAIMovment
// ()

void ABP_WheeledVehicle_C::ClientClearAIMovment()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ClientClearAIMovment");

	ABP_WheeledVehicle_C_ClientClearAIMovment_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartAccelerating
// ()

void ABP_WheeledVehicle_C::StartAccelerating()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartAccelerating");

	ABP_WheeledVehicle_C_StartAccelerating_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopAccelerating
// ()

void ABP_WheeledVehicle_C::StopAccelerating()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopAccelerating");

	ABP_WheeledVehicle_C_StopAccelerating_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickVehicleSound
// ()
// Parameters:
// float                          dt                             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::TickVehicleSound(float dt)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickVehicleSound");

	ABP_WheeledVehicle_C_TickVehicleSound_Params params;
	params.dt = dt;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveTick");

	ABP_WheeledVehicle_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateCamera
// ()

void ABP_WheeledVehicle_C::UpdateCamera()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateCamera");

	ABP_WheeledVehicle_C_UpdateCamera_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveBeginPlay
// ()

void ABP_WheeledVehicle_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveBeginPlay");

	ABP_WheeledVehicle_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.WasDocked
// ()
// Parameters:
// class AFGBuildableDockingStation** atStation                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::WasDocked(class AFGBuildableDockingStation** atStation)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.WasDocked");

	ABP_WheeledVehicle_C_WasDocked_Params params;
	params.atStation = atStation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerSetMenuOpen
// ()
// Parameters:
// bool                           menuOpen                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ServerSetMenuOpen(bool menuOpen)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerSetMenuOpen");

	ABP_WheeledVehicle_C_ServerSetMenuOpen_Params params;
	params.menuOpen = menuOpen;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerClearPathRecording
// ()

void ABP_WheeledVehicle_C::ServerClearPathRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerClearPathRecording");

	ABP_WheeledVehicle_C_ServerClearPathRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.WasUndocked
// ()

void ABP_WheeledVehicle_C::WasUndocked()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.WasUndocked");

	ABP_WheeledVehicle_C_WasUndocked_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerTogglePauseRecording
// ()

void ABP_WheeledVehicle_C::ServerTogglePauseRecording()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerTogglePauseRecording");

	ABP_WheeledVehicle_C_ServerTogglePauseRecording_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerToggleAutoPilot
// ()

void ABP_WheeledVehicle_C::ServerToggleAutoPilot()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerToggleAutoPilot");

	ABP_WheeledVehicle_C_ServerToggleAutoPilot_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerTogglePathVisibility
// ()

void ABP_WheeledVehicle_C::ServerTogglePathVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerTogglePathVisibility");

	ABP_WheeledVehicle_C_ServerTogglePathVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Server_Leave
// ()

void ABP_WheeledVehicle_C::Server_Leave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.Server_Leave");

	ABP_WheeledVehicle_C_Server_Leave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnVehicleStartup
// ()

void ABP_WheeledVehicle_C::ReceiveOnVehicleStartup()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnVehicleStartup");

	ABP_WheeledVehicle_C_ReceiveOnVehicleStartup_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnVehicleShutDown
// ()

void ABP_WheeledVehicle_C::ReceiveOnVehicleShutDown()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnVehicleShutDown");

	ABP_WheeledVehicle_C_ReceiveOnVehicleShutDown_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnDriverEnter
// ()

void ABP_WheeledVehicle_C::ReceiveOnDriverEnter()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnDriverEnter");

	ABP_WheeledVehicle_C_ReceiveOnDriverEnter_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnDriverLeave
// ()

void ABP_WheeledVehicle_C::ReceiveOnDriverLeave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnDriverLeave");

	ABP_WheeledVehicle_C_ReceiveOnDriverLeave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.PlayFoliageDestroyedEffect
// ()
// Parameters:
// class UParticleSystem**        destroyEffect                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UAkAudioEvent**          destroyAudioEvent              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector*                Location                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::PlayFoliageDestroyedEffect(class UParticleSystem** destroyEffect, class UAkAudioEvent** destroyAudioEvent, struct FVector* Location)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.PlayFoliageDestroyedEffect");

	ABP_WheeledVehicle_C_PlayFoliageDestroyedEffect_Params params;
	params.destroyEffect = destroyEffect;
	params.destroyAudioEvent = destroyAudioEvent;
	params.Location = Location;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2
// ()
// Parameters:
// float                          AxisValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2(float AxisValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2");

	ABP_WheeledVehicle_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2_Params params;
	params.AxisValue = AxisValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_3
// ()
// Parameters:
// float                          AxisValue                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::InpAxisEvt_MoveRight_K2Node_InputAxisEvent_3(float AxisValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_3");

	ABP_WheeledVehicle_C_InpAxisEvt_MoveRight_K2Node_InputAxisEvent_3_Params params;
	params.AxisValue = AxisValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Server_Honk
// ()

void ABP_WheeledVehicle_C::Server_Honk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.Server_Honk");

	ABP_WheeledVehicle_C_Server_Honk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_Honk
// ()

void ABP_WheeledVehicle_C::Multicast_Honk()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_Honk");

	ABP_WheeledVehicle_C_Multicast_Honk_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ExecuteUbergraph_BP_WheeledVehicle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_WheeledVehicle_C::ExecuteUbergraph_BP_WheeledVehicle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.ExecuteUbergraph_BP_WheeledVehicle");

	ABP_WheeledVehicle_C_ExecuteUbergraph_BP_WheeledVehicle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnStartRecording__DelegateSignature
// ()

void ABP_WheeledVehicle_C::OnStartRecording__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnStartRecording__DelegateSignature");

	ABP_WheeledVehicle_C_OnStartRecording__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnStopRecording__DelegateSignature
// ()

void ABP_WheeledVehicle_C::OnStopRecording__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnStopRecording__DelegateSignature");

	ABP_WheeledVehicle_C_OnStopRecording__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WheeledVehicle.BP_WheeledVehicle_C.LocationReached__DelegateSignature
// ()

void ABP_WheeledVehicle_C::LocationReached__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WheeledVehicle.BP_WheeledVehicle_C.LocationReached__DelegateSignature");

	ABP_WheeledVehicle_C_LocationReached__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
