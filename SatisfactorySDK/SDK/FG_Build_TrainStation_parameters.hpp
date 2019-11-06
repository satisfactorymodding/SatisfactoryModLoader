#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TrainStation_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_TrainStation.Build_TrainStation_C.GetActorCompassViewDistance
struct ABuild_TrainStation_C_GetActorCompassViewDistance_Params
{
	ECompassViewDistance                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.SetActorCompassViewDistance
struct ABuild_TrainStation_C_SetActorCompassViewDistance_Params
{
	ECompassViewDistance                               compassViewDistance;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	ECompassViewDistance                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.AddAsRepresentation
struct ABuild_TrainStation_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorFogOfWarRevealRadius
struct ABuild_TrainStation_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorFogOfWarRevealType
struct ABuild_TrainStation_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorRepresentationColor
struct ABuild_TrainStation_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorRepresentationText
struct ABuild_TrainStation_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorRepresentationTexture
struct ABuild_TrainStation_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorRepresentationType
struct ABuild_TrainStation_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorShouldShowInCompass
struct ABuild_TrainStation_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetActorShouldShowOnMap
struct ABuild_TrainStation_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetRealActorLocation
struct ABuild_TrainStation_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.GetRealActorRotation
struct ABuild_TrainStation_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.IsActorStatic
struct ABuild_TrainStation_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.RemoveAsRepresentation
struct ABuild_TrainStation_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.SetActorRepresentationText
struct ABuild_TrainStation_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_TrainStation.Build_TrainStation_C.UpdateRepresentation
struct ABuild_TrainStation_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.UserConstructionScript
struct ABuild_TrainStation_C_UserConstructionScript_Params
{
};

// Function Build_TrainStation.Build_TrainStation_C.OnNameChanged
struct ABuild_TrainStation_C_OnNameChanged_Params
{
};

// Function Build_TrainStation.Build_TrainStation_C.ReceiveBeginPlay
struct ABuild_TrainStation_C_ReceiveBeginPlay_Params
{
};

// Function Build_TrainStation.Build_TrainStation_C.ReceiveEndPlay
struct ABuild_TrainStation_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Build_TrainStation.Build_TrainStation_C.ExecuteUbergraph_Build_TrainStation
struct ABuild_TrainStation_C_ExecuteUbergraph_Build_TrainStation_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
