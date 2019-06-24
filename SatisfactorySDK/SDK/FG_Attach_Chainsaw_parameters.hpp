#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Attach_Chainsaw_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Attach_Chainsaw.Attach_Chainsaw_C.UserConstructionScript
struct AAttach_Chainsaw_C_UserConstructionScript_Params
{
};

// Function Attach_Chainsaw.Attach_Chainsaw_C.OnAttachmentUseStateUpdated
struct AAttach_Chainsaw_C_OnAttachmentUseStateUpdated_Params
{
	int*                                               newUseState;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Attach_Chainsaw.Attach_Chainsaw_C.PlayAttachEffects3P
struct AAttach_Chainsaw_C_PlayAttachEffects3P_Params
{
};

// Function Attach_Chainsaw.Attach_Chainsaw_C.PlayDetachEffects3P
struct AAttach_Chainsaw_C_PlayDetachEffects3P_Params
{
};

// Function Attach_Chainsaw.Attach_Chainsaw_C.ExecuteUbergraph_Attach_Chainsaw
struct AAttach_Chainsaw_C_ExecuteUbergraph_Attach_Chainsaw_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
