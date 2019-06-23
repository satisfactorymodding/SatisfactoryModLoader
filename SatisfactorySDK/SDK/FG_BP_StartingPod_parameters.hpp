#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_StartingPod_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_StartingPod.BP_StartingPod_C.GatherDependencies
struct ABP_StartingPod_C_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function BP_StartingPod.BP_StartingPod_C.NeedTransform
struct ABP_StartingPod_C_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.ShouldSave
struct ABP_StartingPod_C_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.SetActorRepresentationText
struct ABP_StartingPod_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_StartingPod.BP_StartingPod_C.UpdateRepresentation
struct ABP_StartingPod_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorFogOfWarRevealRadius
struct ABP_StartingPod_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorFogOfWarRevealType
struct ABP_StartingPod_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorRepresentationColor
struct ABP_StartingPod_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorRepresentationText
struct ABP_StartingPod_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorRepresentationTexture
struct ABP_StartingPod_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorRepresentationType
struct ABP_StartingPod_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorShouldShowInCompass
struct ABP_StartingPod_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.AddAsRepresentation
struct ABP_StartingPod_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetActorShouldShowOnMap
struct ABP_StartingPod_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetRealActorLocation
struct ABP_StartingPod_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.GetRealActorRotation
struct ABP_StartingPod_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.IsActorStatic
struct ABP_StartingPod_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.RemoveAsRepresentation
struct ABP_StartingPod_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.UserConstructionScript
struct ABP_StartingPod_C_UserConstructionScript_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.PostLoadGame
struct ABP_StartingPod_C_PostLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.PostSaveGame
struct ABP_StartingPod_C_PostSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.PreLoadGame
struct ABP_StartingPod_C_PreLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.PreSaveGame
struct ABP_StartingPod_C_PreSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.StartIsLookedAtForDismantle
struct ABP_StartingPod_C_StartIsLookedAtForDismantle_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.StopIsLookedAtForDismantle
struct ABP_StartingPod_C_StopIsLookedAtForDismantle_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.ReceiveTick
struct ABP_StartingPod_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_StartingPod.BP_StartingPod_C.SetupPodForOwner
struct ABP_StartingPod_C_SetupPodForOwner_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.SetupPodForObserver
struct ABP_StartingPod_C_SetupPodForObserver_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.EndCinematic
struct ABP_StartingPod_C_EndCinematic_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.StartMovie
struct ABP_StartingPod_C_StartMovie_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.AK_StopDucking
struct ABP_StartingPod_C_AK_StopDucking_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.AK_HalveDucking
struct ABP_StartingPod_C_AK_HalveDucking_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.ReceiveDestroyed
struct ABP_StartingPod_C_ReceiveDestroyed_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.StartCinematic
struct ABP_StartingPod_C_StartCinematic_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.OnPlayerSkipIntroSequence
struct ABP_StartingPod_C_OnPlayerSkipIntroSequence_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.AllowSkipIntro
struct ABP_StartingPod_C_AllowSkipIntro_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.BlockSkipIntro
struct ABP_StartingPod_C_BlockSkipIntro_Params
{
};

// Function BP_StartingPod.BP_StartingPod_C.ExecuteUbergraph_BP_StartingPod
struct ABP_StartingPod_C_ExecuteUbergraph_BP_StartingPod_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
