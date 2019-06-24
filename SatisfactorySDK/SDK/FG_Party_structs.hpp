#pragma once

// Satisfactory SDK

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

// Enum Party.ECrossplayPreference
enum class ECrossplayPreference : uint8_t
{
	NoSelection                    = 0,
	OptedIn                        = 1,
	OptedOut                       = 2,
	ECrossplayPreference_MAX       = 3
};


// Enum Party.EJoinPartyDenialReason
enum class EJoinPartyDenialReason : uint8_t
{
	NoReason                       = 0,
	Busy                           = 1,
	PartyFull                      = 2,
	GameFull                       = 3,
	NotPartyLeader                 = 4,
	PartyPrivate                   = 5,
	NeedsTutorial                  = 6,
	GameModeRestricted             = 7,
	JoinerCrossplayRestricted      = 8,
	MemberCrossplayRestricted      = 9,
	Banned                         = 10,
	EJoinPartyDenialReason_MAX     = 11
};


// Enum Party.EPartyType
enum class EPartyType : uint8_t
{
	Public                         = 0,
	FriendsOnly                    = 1,
	Private                        = 2,
	EPartyType_MAX                 = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Party.PartyState
// 0x0010
struct FPartyState
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
	EPartyType                                         PartyType;                                                // 0x0008(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bLeaderFriendsOnly;                                       // 0x0009(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bLeaderInvitesOnly;                                       // 0x000A(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bInvitesDisabled;                                         // 0x000B(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
};

// ScriptStruct Party.PartyMemberRepState
// 0x0008
struct FPartyMemberRepState
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
