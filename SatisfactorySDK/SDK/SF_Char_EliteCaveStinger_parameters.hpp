#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Char_EliteCaveStinger_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.UserConstructionScript
struct AChar_EliteCaveStinger_C_UserConstructionScript_Params
{
};

// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.ReceiveBeginPlay
struct AChar_EliteCaveStinger_C_ReceiveBeginPlay_Params
{
};

// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.SpawnGas
struct AChar_EliteCaveStinger_C_SpawnGas_Params
{
};

// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.OnTakeAnyDamage_Event_1
struct AChar_EliteCaveStinger_C_OnTakeAnyDamage_Event_1_Params
{
	class AActor*                                      damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_EliteCaveStinger.Char_EliteCaveStinger_C.ExecuteUbergraph_Char_EliteCaveStinger
struct AChar_EliteCaveStinger_C_ExecuteUbergraph_Char_EliteCaveStinger_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
