#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TradingPost_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_TradingPost.Build_TradingPost_C.SetActorRepresentationText
struct ABuild_TradingPost_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_TradingPost.Build_TradingPost_C.UpdateRepresentation
struct ABuild_TradingPost_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorRepresentationColor
struct ABuild_TradingPost_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorRepresentationText
struct ABuild_TradingPost_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorRepresentationTexture
struct ABuild_TradingPost_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorRepresentationType
struct ABuild_TradingPost_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorShouldShowInCompass
struct ABuild_TradingPost_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorFogOfWarRevealRadius
struct ABuild_TradingPost_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorFogOfWarRevealType
struct ABuild_TradingPost_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.RemoveAsRepresentation
struct ABuild_TradingPost_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetRealActorRotation
struct ABuild_TradingPost_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetRealActorLocation
struct ABuild_TradingPost_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.GetActorShouldShowOnMap
struct ABuild_TradingPost_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.AddAsRepresentation
struct ABuild_TradingPost_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.IsActorStatic
struct ABuild_TradingPost_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.UpdateTradingPostVisibility
struct ABuild_TradingPost_C_UpdateTradingPostVisibility_Params
{
};

// Function Build_TradingPost.Build_TradingPost_C.UpdateMainMesh
struct ABuild_TradingPost_C_UpdateMainMesh_Params
{
};

// Function Build_TradingPost.Build_TradingPost_C.UserConstructionScript
struct ABuild_TradingPost_C_UserConstructionScript_Params
{
};

// Function Build_TradingPost.Build_TradingPost_C.ReceiveDestroyed
struct ABuild_TradingPost_C_ReceiveDestroyed_Params
{
};

// Function Build_TradingPost.Build_TradingPost_C.ReceiveBeginPlay
struct ABuild_TradingPost_C_ReceiveBeginPlay_Params
{
};

// Function Build_TradingPost.Build_TradingPost_C.OnTradingPostUpgraded
struct ABuild_TradingPost_C_OnTradingPostUpgraded_Params
{
	int*                                               Level;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool*                                              suppressBuildEffects;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_TradingPost.Build_TradingPost_C.ExecuteUbergraph_Build_TradingPost
struct ABuild_TradingPost_C_ExecuteUbergraph_Build_TradingPost_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
