#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DeathMarker_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_DeathMarker.BP_DeathMarker_C.ShouldSave
struct ABP_DeathMarker_C_ShouldSave_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GatherDependencies
struct ABP_DeathMarker_C_GatherDependencies_Params
{
	TArray<class UObject*>                             out_dependentObjects;                                     // (Parm, OutParm, ZeroConstructor)
};

// Function BP_DeathMarker.BP_DeathMarker_C.NeedTransform
struct ABP_DeathMarker_C_NeedTransform_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.SetActorRepresentationText
struct ABP_DeathMarker_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_DeathMarker.BP_DeathMarker_C.UpdateRepresentation
struct ABP_DeathMarker_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorFogOfWarRevealRadius
struct ABP_DeathMarker_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorFogOfWarRevealType
struct ABP_DeathMarker_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorRepresentationColor
struct ABP_DeathMarker_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorRepresentationText
struct ABP_DeathMarker_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorRepresentationTexture
struct ABP_DeathMarker_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorRepresentationType
struct ABP_DeathMarker_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorShouldShowInCompass
struct ABP_DeathMarker_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.AddAsRepresentation
struct ABP_DeathMarker_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetActorShouldShowOnMap
struct ABP_DeathMarker_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetRealActorLocation
struct ABP_DeathMarker_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.GetRealActorRotation
struct ABP_DeathMarker_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.IsActorStatic
struct ABP_DeathMarker_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.RemoveAsRepresentation
struct ABP_DeathMarker_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.UserConstructionScript
struct ABP_DeathMarker_C_UserConstructionScript_Params
{
};

// Function BP_DeathMarker.BP_DeathMarker_C.PostLoadGame
struct ABP_DeathMarker_C_PostLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.PostSaveGame
struct ABP_DeathMarker_C_PostSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.PreLoadGame
struct ABP_DeathMarker_C_PreLoadGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.PreSaveGame
struct ABP_DeathMarker_C_PreSaveGame_Params
{
	int                                                SaveVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                GameVersion;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.ReceiveBeginPlay
struct ABP_DeathMarker_C_ReceiveBeginPlay_Params
{
};

// Function BP_DeathMarker.BP_DeathMarker_C.ReceiveDestroyed
struct ABP_DeathMarker_C_ReceiveDestroyed_Params
{
};

// Function BP_DeathMarker.BP_DeathMarker_C.BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
struct ABP_DeathMarker_C_BndEvt__Sphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params
{
	class UPrimitiveComponent*                         OverlappedComponent;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor*                                      OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent*                         OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                OtherBodyIndex;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bFromSweep;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult                                  SweepResult;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_DeathMarker.BP_DeathMarker_C.ExecuteUbergraph_BP_DeathMarker
struct ABP_DeathMarker_C_ExecuteUbergraph_BP_DeathMarker_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
