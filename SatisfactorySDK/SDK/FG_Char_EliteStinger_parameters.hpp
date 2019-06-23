#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_EliteStinger_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_EliteStinger.Char_EliteStinger_C.UserConstructionScript
struct AChar_EliteStinger_C_UserConstructionScript_Params
{
};

// Function Char_EliteStinger.Char_EliteStinger_C.ReceiveBeginPlay
struct AChar_EliteStinger_C_ReceiveBeginPlay_Params
{
};

// Function Char_EliteStinger.Char_EliteStinger_C.SpawnGas
struct AChar_EliteStinger_C_SpawnGas_Params
{
};

// Function Char_EliteStinger.Char_EliteStinger_C.OnTakeAnyDamage_Event_1
struct AChar_EliteStinger_C_OnTakeAnyDamage_Event_1_Params
{
	class AActor*                                      damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_EliteStinger.Char_EliteStinger_C.ExecuteUbergraph_Char_EliteStinger
struct AChar_EliteStinger_C_ExecuteUbergraph_Char_EliteStinger_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
