#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TakeDamage_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TakeDamage.Widget_TakeDamage_C.GetIsHealthCritical
struct UWidget_TakeDamage_C_GetIsHealthCritical_Params
{
	bool                                               IsHealthCritical;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.Construct
struct UWidget_TakeDamage_C_Construct_Params
{
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.SpawnPointer
struct UWidget_TakeDamage_C_SpawnPointer_Params
{
	class AActor*                                      damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Damage;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.OnRadiationDamage
struct UWidget_TakeDamage_C_OnRadiationDamage_Params
{
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.SetPlayerPawn
struct UWidget_TakeDamage_C_SetPlayerPawn_Params
{
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.ShowWarningMessage
struct UWidget_TakeDamage_C_ShowWarningMessage_Params
{
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.UpdateRadiation
struct UWidget_TakeDamage_C_UpdateRadiation_Params
{
	bool                                               RadiationActive;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              amount;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TakeDamage.Widget_TakeDamage_C.ExecuteUbergraph_Widget_TakeDamage
struct UWidget_TakeDamage_C_ExecuteUbergraph_Widget_TakeDamage_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
