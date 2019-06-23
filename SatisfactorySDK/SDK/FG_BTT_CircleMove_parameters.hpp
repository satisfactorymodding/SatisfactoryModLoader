#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_CircleMove_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_CircleMove.BTT_CircleMove_C.ReceiveExecute
struct UBTT_CircleMove_C_ReceiveExecute_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_CircleMove.BTT_CircleMove_C.FinishCircleMove
struct UBTT_CircleMove_C_FinishCircleMove_Params
{
};

// Function BTT_CircleMove.BTT_CircleMove_C.ExecuteUbergraph_BTT_CircleMove
struct UBTT_CircleMove_C_ExecuteUbergraph_BTT_CircleMove_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
