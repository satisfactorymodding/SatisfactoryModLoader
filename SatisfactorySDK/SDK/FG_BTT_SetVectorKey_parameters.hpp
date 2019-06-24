#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_SetVectorKey_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_SetVectorKey.BTT_SetVectorKey_C.ReceiveExecute
struct UBTT_SetVectorKey_C_ReceiveExecute_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_SetVectorKey.BTT_SetVectorKey_C.ExecuteUbergraph_BTT_SetVectorKey
struct UBTT_SetVectorKey_C_ExecuteUbergraph_BTT_SetVectorKey_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
