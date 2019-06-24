#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_ClearObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_ClearObject.BTT_ClearObject_C.ReceiveExecute
struct UBTT_ClearObject_C_ReceiveExecute_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_ClearObject.BTT_ClearObject_C.ExecuteUbergraph_BTT_ClearObject
struct UBTT_ClearObject_C_ExecuteUbergraph_BTT_ClearObject_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
