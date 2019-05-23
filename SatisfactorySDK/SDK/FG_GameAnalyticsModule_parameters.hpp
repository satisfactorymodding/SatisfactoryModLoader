#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GameAnalyticsModule_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function GameAnalyticsModule.AnalyticsService.GetPagePrefix
struct UAnalyticsService_GetPagePrefix_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function GameAnalyticsModule.AnalyticsService.GetBuildPrefix
struct UAnalyticsService_GetBuildPrefix_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function GameAnalyticsModule.StatHatJsonRequest.SendRequest
struct UStatHatJsonRequest_SendRequest_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
