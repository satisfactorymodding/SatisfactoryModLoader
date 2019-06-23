// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Beacon_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_Beacon.BP_Beacon_C.ShouldSave
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::ShouldSave()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.ShouldSave");

	ABP_Beacon_C_ShouldSave_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GatherDependencies
// ()
// Parameters:
// TArray<class UObject*>         out_dependentObjects           (Parm, OutParm, ZeroConstructor)

void ABP_Beacon_C::GatherDependencies(TArray<class UObject*>* out_dependentObjects)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GatherDependencies");

	ABP_Beacon_C_GatherDependencies_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_dependentObjects != nullptr)
		*out_dependentObjects = params.out_dependentObjects;
}


// Function BP_Beacon.BP_Beacon_C.NeedTransform
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::NeedTransform()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.NeedTransform");

	ABP_Beacon_C_NeedTransform_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetLookAtDecription
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_Beacon_C::GetLookAtDecription(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetLookAtDecription");

	ABP_Beacon_C_GetLookAtDecription_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.IsUseable
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::IsUseable()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.IsUseable");

	ABP_Beacon_C_IsUseable_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.UpdateUseState
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 atLocation                     (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// class UPrimitiveComponent*     componentHit                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FUseState               out_useState                   (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Beacon_C::UpdateUseState(class AFGCharacterPlayer* byCharacter, const struct FVector& atLocation, class UPrimitiveComponent* componentHit, struct FUseState* out_useState)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.UpdateUseState");

	ABP_Beacon_C_UpdateUseState_Params params;
	params.byCharacter = byCharacter;
	params.atLocation = atLocation;
	params.componentHit = componentHit;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (out_useState != nullptr)
		*out_useState = params.out_useState;
}


// Function BP_Beacon.BP_Beacon_C.SetActorRepresentationText
// ()
// Parameters:
// struct FText                   newText                        (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_Beacon_C::SetActorRepresentationText(const struct FText& newText)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.SetActorRepresentationText");

	ABP_Beacon_C_SetActorRepresentationText_Params params;
	params.newText = newText;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.UpdateRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::UpdateRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.UpdateRepresentation");

	ABP_Beacon_C_UpdateRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorFogOfWarRevealRadius
// ()
// Parameters:
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float ABP_Beacon_C::GetActorFogOfWarRevealRadius()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorFogOfWarRevealRadius");

	ABP_Beacon_C_GetActorFogOfWarRevealRadius_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorFogOfWarRevealType
// ()
// Parameters:
// EFogOfWarRevealType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

EFogOfWarRevealType ABP_Beacon_C::GetActorFogOfWarRevealType()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorFogOfWarRevealType");

	ABP_Beacon_C_GetActorFogOfWarRevealType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationColor
// ()
// Parameters:
// struct FLinearColor            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FLinearColor ABP_Beacon_C::GetActorRepresentationColor()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorRepresentationColor");

	ABP_Beacon_C_GetActorRepresentationColor_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationText
// ()
// Parameters:
// struct FText                   ReturnValue                    (Parm, OutParm, ReturnParm)

struct FText ABP_Beacon_C::GetActorRepresentationText()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorRepresentationText");

	ABP_Beacon_C_GetActorRepresentationText_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationTexture
// ()
// Parameters:
// class UTexture2D*              ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UTexture2D* ABP_Beacon_C::GetActorRepresentationTexture()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorRepresentationTexture");

	ABP_Beacon_C_GetActorRepresentationTexture_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationType
// ()
// Parameters:
// ERepresentationType            ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

ERepresentationType ABP_Beacon_C::GetActorRepresentationType()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorRepresentationType");

	ABP_Beacon_C_GetActorRepresentationType_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorShouldShowInCompass
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::GetActorShouldShowInCompass()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorShouldShowInCompass");

	ABP_Beacon_C_GetActorShouldShowInCompass_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.RemoveAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::RemoveAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.RemoveAsRepresentation");

	ABP_Beacon_C_RemoveAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetRealActorRotation
// ()
// Parameters:
// struct FRotator                ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FRotator ABP_Beacon_C::GetRealActorRotation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetRealActorRotation");

	ABP_Beacon_C_GetRealActorRotation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetRealActorLocation
// ()
// Parameters:
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector ABP_Beacon_C::GetRealActorLocation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetRealActorLocation");

	ABP_Beacon_C_GetRealActorLocation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.GetActorShouldShowOnMap
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::GetActorShouldShowOnMap()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.GetActorShouldShowOnMap");

	ABP_Beacon_C_GetActorShouldShowOnMap_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.IsActorStatic
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::IsActorStatic()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.IsActorStatic");

	ABP_Beacon_C_IsActorStatic_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.AddAsRepresentation
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABP_Beacon_C::AddAsRepresentation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.AddAsRepresentation");

	ABP_Beacon_C_AddAsRepresentation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BP_Beacon.BP_Beacon_C.CloseWidget
// ()
// Parameters:
// class AController*             Controller                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::CloseWidget(class AController* Controller)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.CloseWidget");

	ABP_Beacon_C_CloseWidget_Params params;
	params.Controller = Controller;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.UserConstructionScript
// ()

void ABP_Beacon_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.UserConstructionScript");

	ABP_Beacon_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.PostLoadGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::PostLoadGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.PostLoadGame");

	ABP_Beacon_C_PostLoadGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.PostSaveGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::PostSaveGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.PostSaveGame");

	ABP_Beacon_C_PostSaveGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.PreLoadGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::PreLoadGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.PreLoadGame");

	ABP_Beacon_C_PreLoadGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.PreSaveGame
// ()
// Parameters:
// int                            SaveVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// int                            GameVersion                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::PreSaveGame(int SaveVersion, int GameVersion)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.PreSaveGame");

	ABP_Beacon_C_PreSaveGame_Params params;
	params.SaveVersion = SaveVersion;
	params.GameVersion = GameVersion;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.OnUseStop
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Beacon_C::OnUseStop(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.OnUseStop");

	ABP_Beacon_C_OnUseStop_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.RegisterInteractingPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::RegisterInteractingPlayer(class AFGCharacterPlayer* Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.RegisterInteractingPlayer");

	ABP_Beacon_C_RegisterInteractingPlayer_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.StartIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Beacon_C::StartIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.StartIsLookedAt");

	ABP_Beacon_C_StartIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.StopIsLookedAt
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Beacon_C::StopIsLookedAt(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.StopIsLookedAt");

	ABP_Beacon_C_StopIsLookedAt_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.UnregisterInteractingPlayer
// ()
// Parameters:
// class AFGCharacterPlayer*      Player                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::UnregisterInteractingPlayer(class AFGCharacterPlayer* Player)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.UnregisterInteractingPlayer");

	ABP_Beacon_C_UnregisterInteractingPlayer_Params params;
	params.Player = Player;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.ReceiveBeginPlay
// ()

void ABP_Beacon_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.ReceiveBeginPlay");

	ABP_Beacon_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.OnUse
// ()
// Parameters:
// class AFGCharacterPlayer*      byCharacter                    (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FUseState               State                          (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)

void ABP_Beacon_C::OnUse(class AFGCharacterPlayer* byCharacter, const struct FUseState& State)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.OnUse");

	ABP_Beacon_C_OnUse_Params params;
	params.byCharacter = byCharacter;
	params.State = State;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_Beacon.BP_Beacon_C.ExecuteUbergraph_BP_Beacon
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_Beacon_C::ExecuteUbergraph_BP_Beacon(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_Beacon.BP_Beacon_C.ExecuteUbergraph_BP_Beacon");

	ABP_Beacon_C_ExecuteUbergraph_BP_Beacon_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
