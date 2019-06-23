// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Player_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_Player.Char_Player_C.SetActorRepresentationText
// ()
// Parameters:
// struct FText                   newText                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText AChar_Player_C::SetActorRepresentationText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.SetActorRepresentationText");

	AChar_Player_C_SetActorRepresentationText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.UpdateRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_Player_C::UpdateRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.UpdateRepresentation");

	AChar_Player_C_UpdateRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorRepresentationColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor AChar_Player_C::GetActorRepresentationColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorRepresentationColor");

	AChar_Player_C_GetActorRepresentationColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText AChar_Player_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorRepresentationText");

	AChar_Player_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* AChar_Player_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorRepresentationTexture");

	AChar_Player_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorRepresentationType
// ()
// Parameters:
// ERepresentationType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ERepresentationType AChar_Player_C::GetActorRepresentationType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorRepresentationType");

	AChar_Player_C_GetActorRepresentationType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorShouldShowInCompass
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_Player_C::GetActorShouldShowInCompass()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorShouldShowInCompass");

	AChar_Player_C_GetActorShouldShowInCompass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorFogOfWarRevealRadius
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float AChar_Player_C::GetActorFogOfWarRevealRadius()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorFogOfWarRevealRadius");

	AChar_Player_C_GetActorFogOfWarRevealRadius_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorFogOfWarRevealType
// ()
// Parameters:
// EFogOfWarRevealType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EFogOfWarRevealType AChar_Player_C::GetActorFogOfWarRevealType()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorFogOfWarRevealType");

	AChar_Player_C_GetActorFogOfWarRevealType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.RemoveAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_Player_C::RemoveAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.RemoveAsRepresentation");

	AChar_Player_C_RemoveAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetRealActorRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator AChar_Player_C::GetRealActorRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetRealActorRotation");

	AChar_Player_C_GetRealActorRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.AddAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_Player_C::AddAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.AddAsRepresentation");

	AChar_Player_C_AddAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetActorShouldShowOnMap
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_Player_C::GetActorShouldShowOnMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetActorShouldShowOnMap");

	AChar_Player_C_GetActorShouldShowOnMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.GetRealActorLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector AChar_Player_C::GetRealActorLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetRealActorLocation");

	AChar_Player_C_GetRealActorLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.IsActorStatic
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool AChar_Player_C::IsActorStatic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.IsActorStatic");

	AChar_Player_C_IsActorStatic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Char_Player.Char_Player_C.ToggleCodex
// ()

void AChar_Player_C::ToggleCodex()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ToggleCodex");

	AChar_Player_C_ToggleCodex_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ToggleInventory
// ()

void AChar_Player_C::ToggleInventory()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ToggleInventory");

	AChar_Player_C_ToggleInventory_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ToggleFlashlight
// ()

void AChar_Player_C::ToggleFlashlight()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ToggleFlashlight");

	AChar_Player_C_ToggleFlashlight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.RemovePlayerHUD
// ()
// Parameters:
// class AFGPlayerController*     OldController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::RemovePlayerHUD(class AFGPlayerController* OldController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.RemovePlayerHUD");

	AChar_Player_C_RemovePlayerHUD_Params params;
	params.OldController = OldController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.SetupPlayerHUD
// ()
// Parameters:
// class AFGPlayerController*     PlayerController               (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::SetupPlayerHUD(class AFGPlayerController* PlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.SetupPlayerHUD");

	AChar_Player_C_SetupPlayerHUD_Params params;
	params.PlayerController = PlayerController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.HandleFlashlight
// ()

void AChar_Player_C::HandleFlashlight()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.HandleFlashlight");

	AChar_Player_C_HandleFlashlight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.UpdatePlayerTextVisibility
// ()

void AChar_Player_C::UpdatePlayerTextVisibility()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.UpdatePlayerTextVisibility");

	AChar_Player_C_UpdatePlayerTextVisibility_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.GetHealthPct
// ()
// Parameters:
// float                          healthPct                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::GetHealthPct(float* healthPct)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetHealthPct");

	AChar_Player_C_GetHealthPct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (healthPct != nullptr)
		*healthPct = params.healthPct;
}


// Function Char_Player.Char_Player_C.UpdateDamageIndicator
// ()

void AChar_Player_C::UpdateDamageIndicator()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.UpdateDamageIndicator");

	AChar_Player_C_UpdateDamageIndicator_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.PlayDamageVO
// ()
// Parameters:
// class UDamageType*             Damage_Type                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::PlayDamageVO(class UDamageType* Damage_Type)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.PlayDamageVO");

	AChar_Player_C_PlayDamageVO_Params params;
	params.Damage_Type = Damage_Type;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.PlayDamageCameraShake
// ()

void AChar_Player_C::PlayDamageCameraShake()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.PlayDamageCameraShake");

	AChar_Player_C_PlayDamageCameraShake_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ApplyDamagePP
// ()

void AChar_Player_C::ApplyDamagePP()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ApplyDamagePP");

	AChar_Player_C_ApplyDamagePP_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.PlayImpactEffectSound
// ()
// Parameters:
// class UDamageType*             DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::PlayImpactEffectSound(class UDamageType* DamageType)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.PlayImpactEffectSound");

	AChar_Player_C_PlayImpactEffectSound_Params params;
	params.DamageType = DamageType;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.CalculateOnscreenEffectBlendWeight
// ()
// Parameters:
// float                          BlendWeight                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::CalculateOnscreenEffectBlendWeight(float* BlendWeight)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.CalculateOnscreenEffectBlendWeight");

	AChar_Player_C_CalculateOnscreenEffectBlendWeight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (BlendWeight != nullptr)
		*BlendWeight = params.BlendWeight;
}


// Function Char_Player.Char_Player_C.UpdateWindParticle
// ()

void AChar_Player_C::UpdateWindParticle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.UpdateWindParticle");

	AChar_Player_C_UpdateWindParticle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.TickSprintNoise
// ()

void AChar_Player_C::TickSprintNoise()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.TickSprintNoise");

	AChar_Player_C_TickSprintNoise_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.GetPlayerCameraManager
// ()
// Parameters:
// class APlayerCameraManager*    cameraManager                  (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::GetPlayerCameraManager(class APlayerCameraManager** cameraManager)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.GetPlayerCameraManager");

	AChar_Player_C_GetPlayerCameraManager_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (cameraManager != nullptr)
		*cameraManager = params.cameraManager;
}


// Function Char_Player.Char_Player_C.FadeDamageIndicator
// ()

void AChar_Player_C::FadeDamageIndicator()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.FadeDamageIndicator");

	AChar_Player_C_FadeDamageIndicator_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.TickPlayerNameText
// ()

void AChar_Player_C::TickPlayerNameText()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.TickPlayerNameText");

	AChar_Player_C_TickPlayerNameText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.UserConstructionScript
// ()

void AChar_Player_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.UserConstructionScript");

	AChar_Player_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.InpActEvt_OpenCodex_K2Node_InputActionEvent_6
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void AChar_Player_C::InpActEvt_OpenCodex_K2Node_InputActionEvent_6(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.InpActEvt_OpenCodex_K2Node_InputActionEvent_6");

	AChar_Player_C_InpActEvt_OpenCodex_K2Node_InputActionEvent_6_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.InpActEvt_Flashlight_K2Node_InputActionEvent_5
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void AChar_Player_C::InpActEvt_Flashlight_K2Node_InputActionEvent_5(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.InpActEvt_Flashlight_K2Node_InputActionEvent_5");

	AChar_Player_C_InpActEvt_Flashlight_K2Node_InputActionEvent_5_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_4
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void AChar_Player_C::InpActEvt_PrimaryFire_K2Node_InputActionEvent_4(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_4");

	AChar_Player_C_InpActEvt_PrimaryFire_K2Node_InputActionEvent_4_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.InpActEvt_Inventory_K2Node_InputActionEvent_3
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void AChar_Player_C::InpActEvt_Inventory_K2Node_InputActionEvent_3(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.InpActEvt_Inventory_K2Node_InputActionEvent_3");

	AChar_Player_C_InpActEvt_Inventory_K2Node_InputActionEvent_3_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.InpActEvt_EmoteWheel_K2Node_InputActionEvent_2
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void AChar_Player_C::InpActEvt_EmoteWheel_K2Node_InputActionEvent_2(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.InpActEvt_EmoteWheel_K2Node_InputActionEvent_2");

	AChar_Player_C_InpActEvt_EmoteWheel_K2Node_InputActionEvent_2_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.InpActEvt_EmoteWheel_K2Node_InputActionEvent_1
// ()
// Parameters:
// struct FKey                    Key                            (BlueprintVisible, BlueprintReadOnly, Parm)

void AChar_Player_C::InpActEvt_EmoteWheel_K2Node_InputActionEvent_1(const struct FKey& Key)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.InpActEvt_EmoteWheel_K2Node_InputActionEvent_1");

	AChar_Player_C_InpActEvt_EmoteWheel_K2Node_InputActionEvent_1_Params params;
	params.Key = Key;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.SetFirstPersonMode
// ()

void AChar_Player_C::SetFirstPersonMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.SetFirstPersonMode");

	AChar_Player_C_SetFirstPersonMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.SetThirdPersonMode
// ()

void AChar_Player_C::SetThirdPersonMode()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.SetThirdPersonMode");

	AChar_Player_C_SetThirdPersonMode_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StartFocusAim
// ()

void AChar_Player_C::StartFocusAim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StartFocusAim");

	AChar_Player_C_StartFocusAim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StopFocusAim
// ()

void AChar_Player_C::StopFocusAim()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StopFocusAim");

	AChar_Player_C_StopFocusAim_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StartFreeRotate3P
// ()

void AChar_Player_C::StartFreeRotate3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StartFreeRotate3P");

	AChar_Player_C_StartFreeRotate3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StopFreeRotate3P
// ()

void AChar_Player_C::StopFreeRotate3P()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StopFreeRotate3P");

	AChar_Player_C_StopFreeRotate3P_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.CameraZoomOut
// ()

void AChar_Player_C::CameraZoomOut()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.CameraZoomOut");

	AChar_Player_C_CameraZoomOut_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.CameraZoomIn
// ()

void AChar_Player_C::CameraZoomIn()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.CameraZoomIn");

	AChar_Player_C_CameraZoomIn_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ReceiveDied
// ()

void AChar_Player_C::ReceiveDied()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ReceiveDied");

	AChar_Player_C_ReceiveDied_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.CameraTick
// ()

void AChar_Player_C::CameraTick()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.CameraTick");

	AChar_Player_C_CameraTick_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.PlayPickupEffects
// ()

void AChar_Player_C::PlayPickupEffects()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.PlayPickupEffects");

	AChar_Player_C_PlayPickupEffects_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.SnapSpringArmToDesiredLocation
// ()

void AChar_Player_C::SnapSpringArmToDesiredLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.SnapSpringArmToDesiredLocation");

	AChar_Player_C_SnapSpringArmToDesiredLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnReviveComplete
// ()

void AChar_Player_C::OnReviveComplete()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnReviveComplete");

	AChar_Player_C_OnReviveComplete_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnLanded
// ()
// Parameters:
// struct FHitResult*             Hit                            (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void AChar_Player_C::OnLanded(struct FHitResult* Hit)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnLanded");

	AChar_Player_C_OnLanded_Params params;
	params.Hit = Hit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ClientSetupPlayerHUD
// ()
// Parameters:
// class AController*             InController                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::ClientSetupPlayerHUD(class AController* InController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ClientSetupPlayerHUD");

	AChar_Player_C_ClientSetupPlayerHUD_Params params;
	params.InController = InController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ReceiveUnpossessed
// ()
// Parameters:
// class AController**            OldController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::ReceiveUnpossessed(class AController** OldController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ReceiveUnpossessed");

	AChar_Player_C_ReceiveUnpossessed_Params params;
	params.OldController = OldController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnReceiveRadiationStart
// ()

void AChar_Player_C::OnReceiveRadiationStart()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnReceiveRadiationStart");

	AChar_Player_C_OnReceiveRadiationStart_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnReceiveRadiationStop
// ()

void AChar_Player_C::OnReceiveRadiationStop()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnReceiveRadiationStop");

	AChar_Player_C_OnReceiveRadiationStop_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ReceivePossessed
// ()
// Parameters:
// class AController**            NewController                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::ReceivePossessed(class AController** NewController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ReceivePossessed");

	AChar_Player_C_ReceivePossessed_Params params;
	params.NewController = NewController;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ReceiveDestroyed
// ()

void AChar_Player_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ReceiveDestroyed");

	AChar_Player_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.TakeDamageEvent
// ()
// Parameters:
// class AActor*                  damagedActor                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float                          damageAmount                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UDamageType*             DamageType                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AController*             instigatedBy                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class AActor*                  damageCauser                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::TakeDamageEvent(class AActor* damagedActor, float damageAmount, class UDamageType* DamageType, class AController* instigatedBy, class AActor* damageCauser)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.TakeDamageEvent");

	AChar_Player_C_TakeDamageEvent_Params params;
	params.damagedActor = damagedActor;
	params.damageAmount = damageAmount;
	params.DamageType = DamageType;
	params.instigatedBy = instigatedBy;
	params.damageCauser = damageCauser;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ReceiveBeginPlay
// ()

void AChar_Player_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ReceiveBeginPlay");

	AChar_Player_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ReceiveTick");

	AChar_Player_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Server_PlayClap
// ()

void AChar_Player_C::Server_PlayClap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Server_PlayClap");

	AChar_Player_C_Server_PlayClap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Multicast_PlayClap
// ()

void AChar_Player_C::Multicast_PlayClap()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Multicast_PlayClap");

	AChar_Player_C_Multicast_PlayClap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Server_SetFlashlightOn
// ()
// Parameters:
// bool                           FlashlightOn                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::Server_SetFlashlightOn(bool FlashlightOn)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Server_SetFlashlightOn");

	AChar_Player_C_Server_SetFlashlightOn_Params params;
	params.FlashlightOn = FlashlightOn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnDisabledInputGateChanged
// ()
// Parameters:
// struct FDisabledInputGate*     NewValue                       (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::OnDisabledInputGateChanged(struct FDisabledInputGate* NewValue)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnDisabledInputGateChanged");

	AChar_Player_C_OnDisabledInputGateChanged_Params params;
	params.NewValue = NewValue;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.AudioTickEvent
// ()
// Parameters:
// float                          AudioTick                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::AudioTickEvent(float AudioTick)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.AudioTickEvent");

	AChar_Player_C_AudioTickEvent_Params params;
	params.AudioTick = AudioTick;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.LimitLook
// ()
// Parameters:
// bool                           doLimit                        (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::LimitLook(bool doLimit)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.LimitLook");

	AChar_Player_C_LimitLook_Params params;
	params.doLimit = doLimit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StartCinematic
// ()

void AChar_Player_C::StartCinematic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StartCinematic");

	AChar_Player_C_StartCinematic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.EndCinematic
// ()

void AChar_Player_C::EndCinematic()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.EndCinematic");

	AChar_Player_C_EndCinematic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.DisableGravity
// ()

void AChar_Player_C::DisableGravity()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.DisableGravity");

	AChar_Player_C_DisableGravity_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Server_PlaySpinEmote
// ()

void AChar_Player_C::Server_PlaySpinEmote()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Server_PlaySpinEmote");

	AChar_Player_C_Server_PlaySpinEmote_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Multicast_PlatSpinEmote
// ()

void AChar_Player_C::Multicast_PlatSpinEmote()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Multicast_PlatSpinEmote");

	AChar_Player_C_Multicast_PlatSpinEmote_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ClearEmoteMesh
// ()

void AChar_Player_C::ClearEmoteMesh()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ClearEmoteMesh");

	AChar_Player_C_ClearEmoteMesh_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnSpawnDeathMarker
// ()

void AChar_Player_C::OnSpawnDeathMarker()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnSpawnDeathMarker");

	AChar_Player_C_OnSpawnDeathMarker_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ShowEmote
// ()
// Parameters:
// int                            EmoteIndex                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::ShowEmote(int EmoteIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ShowEmote");

	AChar_Player_C_ShowEmote_Params params;
	params.EmoteIndex = EmoteIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.SkipIntro
// ()

void AChar_Player_C::SkipIntro()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.SkipIntro");

	AChar_Player_C_SkipIntro_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Server_playSignsEmote
// ()

void AChar_Player_C::Server_playSignsEmote()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Server_playSignsEmote");

	AChar_Player_C_Server_playSignsEmote_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.Multicast_PlaySignsEmote
// ()

void AChar_Player_C::Multicast_PlaySignsEmote()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.Multicast_PlaySignsEmote");

	AChar_Player_C_Multicast_PlaySignsEmote_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StartIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_Player_C::StartIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StartIsLookedAt");

	AChar_Player_C_StartIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.StopIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer**     byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState*              State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void AChar_Player_C::StopIsLookedAt(class AFGCharacterPlayer** byCharacter, struct FUseState* State)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.StopIsLookedAt");

	AChar_Player_C_StopIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.OnRadiationIntensityUpdated
// ()
// Parameters:
// float*                         radiationIntensity             (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         radiationImmunity              (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::OnRadiationIntensityUpdated(float* radiationIntensity, float* radiationImmunity)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.OnRadiationIntensityUpdated");

	AChar_Player_C_OnRadiationIntensityUpdated_Params params;
	params.radiationIntensity = radiationIntensity;
	params.radiationImmunity = radiationImmunity;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.ExecuteUbergraph_Char_Player
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::ExecuteUbergraph_Char_Player(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.ExecuteUbergraph_Char_Player");

	AChar_Player_C_ExecuteUbergraph_Char_Player_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.EventFire__DelegateSignature
// ()

void AChar_Player_C::EventFire__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.EventFire__DelegateSignature");

	AChar_Player_C_EventFire__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.EventScroll__DelegateSignature
// ()
// Parameters:
// int                            Index                          (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Player_C::EventScroll__DelegateSignature(int Index)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.EventScroll__DelegateSignature");

	AChar_Player_C_EventScroll__DelegateSignature_Params params;
	params.Index = Index;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.EventScrollDown__DelegateSignature
// ()

void AChar_Player_C::EventScrollDown__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.EventScrollDown__DelegateSignature");

	AChar_Player_C_EventScrollDown__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Player.Char_Player_C.EventScrollUp__DelegateSignature
// ()

void AChar_Player_C::EventScrollUp__DelegateSignature()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Player.Char_Player_C.EventScrollUp__DelegateSignature");

	AChar_Player_C_EventScrollUp__DelegateSignature_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
