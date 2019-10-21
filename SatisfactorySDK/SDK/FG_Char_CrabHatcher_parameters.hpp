#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_CrabHatcher_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_CrabHatcher.Char_CrabHatcher_C.SpawnTimer
struct AChar_CrabHatcher_C_SpawnTimer_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.PlaySpawnEffects
struct AChar_CrabHatcher_C_PlaySpawnEffects_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.UserConstructionScript
struct AChar_CrabHatcher_C_UserConstructionScript_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.Damaged
struct AChar_CrabHatcher_C_Damaged_Params
{
	class AActor*                                      DamagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 InstigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      DamageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveBeginPlay
struct AChar_CrabHatcher_C_ReceiveBeginPlay_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.SpawnCrabs
struct AChar_CrabHatcher_C_SpawnCrabs_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.StartExpanding
struct AChar_CrabHatcher_C_StartExpanding_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveActorBeginOverlap
struct AChar_CrabHatcher_C_ReceiveActorBeginOverlap_Params
{
	class AActor**                                     OtherActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.GainedSignificance
struct AChar_CrabHatcher_C_GainedSignificance_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.LostSignificance
struct AChar_CrabHatcher_C_LostSignificance_Params
{
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.ReceiveEndPlay
struct AChar_CrabHatcher_C_ReceiveEndPlay_Params
{
	TEnumAsByte<EEndPlayReason>*                       EndPlayReason;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_CrabHatcher.Char_CrabHatcher_C.ExecuteUbergraph_Char_CrabHatcher
struct AChar_CrabHatcher_C_ExecuteUbergraph_Char_CrabHatcher_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
