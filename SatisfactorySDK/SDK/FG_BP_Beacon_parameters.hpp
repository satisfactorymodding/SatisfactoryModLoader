#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Beacon_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Beacon.BP_Beacon_C.ShouldSave
struct ABP_Beacon_C_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GatherDependencies
struct ABP_Beacon_C_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function BP_Beacon.BP_Beacon_C.NeedTransform
struct ABP_Beacon_C_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetLookAtDecription
struct ABP_Beacon_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_Beacon.BP_Beacon_C.IsUseable
struct ABP_Beacon_C_IsUseable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.UpdateUseState
struct ABP_Beacon_C_UpdateUseState_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     atLocation;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent*                         componentHit;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Beacon.BP_Beacon_C.SetActorRepresentationText
struct ABP_Beacon_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_Beacon.BP_Beacon_C.UpdateRepresentation
struct ABP_Beacon_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorFogOfWarRevealRadius
struct ABP_Beacon_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorFogOfWarRevealType
struct ABP_Beacon_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationColor
struct ABP_Beacon_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationText
struct ABP_Beacon_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationTexture
struct ABP_Beacon_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorRepresentationType
struct ABP_Beacon_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorShouldShowInCompass
struct ABP_Beacon_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.RemoveAsRepresentation
struct ABP_Beacon_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetRealActorRotation
struct ABP_Beacon_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetRealActorLocation
struct ABP_Beacon_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.GetActorShouldShowOnMap
struct ABP_Beacon_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.IsActorStatic
struct ABP_Beacon_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.AddAsRepresentation
struct ABP_Beacon_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.CloseWidget
struct ABP_Beacon_C_CloseWidget_Params
{
	class AController*                                 Controller;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.UserConstructionScript
struct ABP_Beacon_C_UserConstructionScript_Params
{
};

// Function BP_Beacon.BP_Beacon_C.PostLoadGame
struct ABP_Beacon_C_PostLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.PostSaveGame
struct ABP_Beacon_C_PostSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.PreLoadGame
struct ABP_Beacon_C_PreLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.PreSaveGame
struct ABP_Beacon_C_PreSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.OnUseStop
struct ABP_Beacon_C_OnUseStop_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Beacon.BP_Beacon_C.RegisterInteractingPlayer
struct ABP_Beacon_C_RegisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.StartIsLookedAt
struct ABP_Beacon_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Beacon.BP_Beacon_C.StopIsLookedAt
struct ABP_Beacon_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Beacon.BP_Beacon_C.UnregisterInteractingPlayer
struct ABP_Beacon_C_UnregisterInteractingPlayer_Params
{
	class AFGCharacterPlayer*                          Player;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Beacon.BP_Beacon_C.ReceiveBeginPlay
struct ABP_Beacon_C_ReceiveBeginPlay_Params
{
};

// Function BP_Beacon.BP_Beacon_C.OnUse
struct ABP_Beacon_C_OnUse_Params
{
	class AFGCharacterPlayer*                          byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState                                   State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_Beacon.BP_Beacon_C.ExecuteUbergraph_BP_Beacon
struct ABP_Beacon_C_ExecuteUbergraph_BP_Beacon_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
