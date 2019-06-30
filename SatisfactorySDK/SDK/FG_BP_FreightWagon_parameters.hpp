#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_FreightWagon_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_FreightWagon.BP_FreightWagon_C.SetActorRepresentationText
struct ABP_FreightWagon_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_FreightWagon.BP_FreightWagon_C.UpdateRepresentation
struct ABP_FreightWagon_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorFogOfWarRevealRadius
struct ABP_FreightWagon_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorFogOfWarRevealType
struct ABP_FreightWagon_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorRepresentationColor
struct ABP_FreightWagon_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorRepresentationText
struct ABP_FreightWagon_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorRepresentationTexture
struct ABP_FreightWagon_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorRepresentationType
struct ABP_FreightWagon_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorShouldShowInCompass
struct ABP_FreightWagon_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.AddAsRepresentation
struct ABP_FreightWagon_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetActorShouldShowOnMap
struct ABP_FreightWagon_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetRealActorLocation
struct ABP_FreightWagon_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetRealActorRotation
struct ABP_FreightWagon_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.IsActorStatic
struct ABP_FreightWagon_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.RemoveAsRepresentation
struct ABP_FreightWagon_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_FreightWagon.BP_FreightWagon_C.GetLookAtDecription
struct ABP_FreightWagon_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_FreightWagon.BP_FreightWagon_C.UserConstructionScript
struct ABP_FreightWagon_C_UserConstructionScript_Params
{
};

// Function BP_FreightWagon.BP_FreightWagon_C.OnUse
struct ABP_FreightWagon_C_OnUse_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_FreightWagon.BP_FreightWagon_C.ReceiveBeginPlay
struct ABP_FreightWagon_C_ReceiveBeginPlay_Params
{
};

// Function BP_FreightWagon.BP_FreightWagon_C.ReceiveDestroyed
struct ABP_FreightWagon_C_ReceiveDestroyed_Params
{
};

// Function BP_FreightWagon.BP_FreightWagon_C.ExecuteUbergraph_BP_FreightWagon
struct ABP_FreightWagon_C_ExecuteUbergraph_BP_FreightWagon_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
