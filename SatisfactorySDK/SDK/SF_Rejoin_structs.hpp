#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Basic.hpp"
#include "SF_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum Rejoin.ERejoinStatus
enum class ERejoinStatus : uint8_t
{
	NoMatchToRejoin                = 0,
	RejoinAvailable                = 1,
	UpdatingStatus                 = 2,
	NeedsRecheck                   = 3,
	NoMatchToRejoin_MatchEnded     = 4,
	ERejoinStatus_MAX              = 5
};



}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
