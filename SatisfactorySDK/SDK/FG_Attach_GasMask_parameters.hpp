#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_GasMask_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_GasMask.Attach_GasMask_C.UserConstructionScript
struct AAttach_GasMask_C_UserConstructionScript_Params
{
};

// Function Attach_GasMask.Attach_GasMask_C.ReceiveTick
struct AAttach_GasMask_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_GasMask.Attach_GasMask_C.PlayAttachEffects3P
struct AAttach_GasMask_C_PlayAttachEffects3P_Params
{
};

// Function Attach_GasMask.Attach_GasMask_C.ExecuteUbergraph_Attach_GasMask
struct AAttach_GasMask_C_ExecuteUbergraph_Attach_GasMask_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
