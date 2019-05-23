#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum GameAnalyticsModule.EAnalyticsServiceType
enum class EAnalyticsServiceType : uint8_t
{
	EAST_StatHat                   = 0,
	EAST_GoogleAnalytics           = 1,
	EAST_EpicOnlineServices        = 2,
	EAST_MAX                       = 3
};



}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
