#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_CheckValidPath_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BTT_CheckValidPath.BTT_CheckValidPath_C.ReceiveExecute
struct UBTT_CheckValidPath_C_ReceiveExecute_Params
{
	class AActor**                                     OwnerActor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BTT_CheckValidPath.BTT_CheckValidPath_C.ExecuteUbergraph_BTT_CheckValidPath
struct UBTT_CheckValidPath_C_ExecuteUbergraph_BTT_CheckValidPath_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
