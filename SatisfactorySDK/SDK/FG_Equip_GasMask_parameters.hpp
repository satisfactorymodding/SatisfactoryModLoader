#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Equip_GasMask_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Equip_GasMask.Equip_GasMask_C.EnablePostProcessing
struct AEquip_GasMask_C_EnablePostProcessing_Params
{
	bool                                               mEnabled;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_GasMask.Equip_GasMask_C.AdjustDamage
struct AEquip_GasMask_C_AdjustDamage_Params
{
	float*                                             damageAmount;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType**                                DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController**                                instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor**                                     damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Equip_GasMask.Equip_GasMask_C.UserConstructionScript
struct AEquip_GasMask_C_UserConstructionScript_Params
{
};

// Function Equip_GasMask.Equip_GasMask_C.WasUnEquipped
struct AEquip_GasMask_C_WasUnEquipped_Params
{
};

// Function Equip_GasMask.Equip_GasMask_C.ReceiveTick
struct AEquip_GasMask_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Equip_GasMask.Equip_GasMask_C.WasEquipped
struct AEquip_GasMask_C_WasEquipped_Params
{
};

// Function Equip_GasMask.Equip_GasMask_C.ExecuteUbergraph_Equip_GasMask
struct AEquip_GasMask_C_ExecuteUbergraph_Equip_GasMask_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
