#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_MamIntegrated_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Build_MamIntegrated.Build_MamIntegrated_C.CanDismantle
struct ABuild_MamIntegrated_C_CanDismantle_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_MamIntegrated.Build_MamIntegrated_C.GetLookAtDecription
struct ABuild_MamIntegrated_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Build_MamIntegrated.Build_MamIntegrated_C.IsUseable
struct ABuild_MamIntegrated_C_IsUseable_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Build_MamIntegrated.Build_MamIntegrated_C.UpdateUseState
struct ABuild_MamIntegrated_C_UpdateUseState_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    atLocation;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent**                        componentHit;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Build_MamIntegrated.Build_MamIntegrated_C.UserConstructionScript
struct ABuild_MamIntegrated_C_UserConstructionScript_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
