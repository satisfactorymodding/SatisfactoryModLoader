#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_SpaceElevator_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_SpaceElevator.Build_SpaceElevator_C.SetActorRepresentationText
struct ABuild_SpaceElevator_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.UpdateRepresentation
struct ABuild_SpaceElevator_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationColor
struct ABuild_SpaceElevator_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationText
struct ABuild_SpaceElevator_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationTexture
struct ABuild_SpaceElevator_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorRepresentationType
struct ABuild_SpaceElevator_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorShouldShowInCompass
struct ABuild_SpaceElevator_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.AddAsRepresentation
struct ABuild_SpaceElevator_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorFogOfWarRevealRadius
struct ABuild_SpaceElevator_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorFogOfWarRevealType
struct ABuild_SpaceElevator_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetActorShouldShowOnMap
struct ABuild_SpaceElevator_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetRealActorLocation
struct ABuild_SpaceElevator_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.GetRealActorRotation
struct ABuild_SpaceElevator_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.IsActorStatic
struct ABuild_SpaceElevator_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.RemoveAsRepresentation
struct ABuild_SpaceElevator_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.UserConstructionScript
struct ABuild_SpaceElevator_C_UserConstructionScript_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_01
struct ABuild_SpaceElevator_C_CamShake_01_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_02
struct ABuild_SpaceElevator_C_CamShake_02_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_03
struct ABuild_SpaceElevator_C_CamShake_03_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.CamShake_04
struct ABuild_SpaceElevator_C_CamShake_04_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.UpperlineVisible
struct ABuild_SpaceElevator_C_UpperlineVisible_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.Event_StartSound
struct ABuild_SpaceElevator_C_Event_StartSound_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveBeginPlay
struct ABuild_SpaceElevator_C_ReceiveBeginPlay_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.OnPhaseChanged
struct ABuild_SpaceElevator_C_OnPhaseChanged_Params
{
	TEnumAsByte<EGamePhase>                            gamePhase;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.PlayUpgradeSequence
struct ABuild_SpaceElevator_C_PlayUpgradeSequence_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.Event_SE_SendOff
struct ABuild_SpaceElevator_C_Event_SE_SendOff_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveDestroyed
struct ABuild_SpaceElevator_C_ReceiveDestroyed_Params
{
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.ReceiveEndPlay
struct ABuild_SpaceElevator_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_SpaceElevator.Build_SpaceElevator_C.ExecuteUbergraph_Build_SpaceElevator
struct ABuild_SpaceElevator_C_ExecuteUbergraph_Build_SpaceElevator_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
