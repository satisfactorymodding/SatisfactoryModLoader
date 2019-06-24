#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_OnlineSubsystem_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function OnlineSubsystem.TurnBasedMatchInterface.OnMatchReceivedTurn
struct UTurnBasedMatchInterface_OnMatchReceivedTurn_Params
{
	class FString                                      Match;                                                    // (Parm, ZeroConstructor)
	bool                                               bDidBecomeActive;                                         // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function OnlineSubsystem.TurnBasedMatchInterface.OnMatchEnded
struct UTurnBasedMatchInterface_OnMatchEnded_Params
{
	class FString                                      Match;                                                    // (Parm, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
