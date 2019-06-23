#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Party_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Party.Chatroom
// 0x0030 (0x0058 - 0x0028)
class UChatroom : public UObject
{
public:
	class FString                                      CurrentChatRoomId;                                        // 0x0028(0x0010) (ZeroConstructor)
	int                                                MaxChatRoomRetries;                                       // 0x0038(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                NumChatRoomRetries;                                       // 0x003C(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0040(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Party.Chatroom");
		return ptr;
	}

};


// Class Party.Party
// 0x0208 (0x0230 - 0x0028)
class UParty : public UObject
{
public:
	unsigned char                                      UnknownData00[0x70];                                      // 0x0028(0x0070) MISSED OFFSET
	int                                                DefaultMaxPartySize;                                      // 0x0098(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	unsigned char                                      UnknownData01[0x14];                                      // 0x009C(0x0014) MISSED OFFSET
	bool                                               bLeavingPersistentParty;                                  // 0x00B0(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x17F];                                     // 0x00B1(0x017F) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Party.Party");
		return ptr;
	}

};


// Class Party.PartyGameState
// 0x0298 (0x02C0 - 0x0028)
class UPartyGameState : public UObject
{
public:
	class UScriptStruct*                               PartyStateRefDef;                                         // 0x0028(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0030(0x0008) MISSED OFFSET
	struct FUniqueNetIdRepl                            OwningUserId;                                             // 0x0038(0x0028)
	unsigned char                                      UnknownData01[0x58];                                      // 0x0060(0x0058) MISSED OFFSET
	bool                                               bDebugAcceptingMembers;                                   // 0x00B8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x18];                                      // 0x00B9(0x0018) MISSED OFFSET
	bool                                               bStayWithPartyOnDisconnect;                               // 0x00D1(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData03[0x6];                                       // 0x00D2(0x0006) MISSED OFFSET
	class UClass*                                      PartyMemberStateClass;                                    // 0x00D8(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData04[0x108];                                     // 0x00E0(0x0108) MISSED OFFSET
	class UClass*                                      ReservationBeaconClientClass;                             // 0x01E8(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	class APartyBeaconClient*                          ReservationBeaconClient;                                  // 0x01F0(0x0008) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData05[0xC8];                                      // 0x01F8(0x00C8) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Party.PartyGameState");
		return ptr;
	}

};


// Class Party.PartyMemberState
// 0x0060 (0x0088 - 0x0028)
class UPartyMemberState : public UObject
{
public:
	struct FUniqueNetIdRepl                            UniqueId;                                                 // 0x0028(0x0028) (Transient)
	struct FText                                       DisplayName;                                              // 0x0050(0x0028) (BlueprintVisible, BlueprintReadOnly, Transient)
	class UScriptStruct*                               MemberStateRefDef;                                        // 0x0068(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x10];                                      // 0x0070(0x0010) MISSED OFFSET
	bool                                               bHasAnnouncedJoin;                                        // 0x0080(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0081(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Party.PartyMemberState");
		return ptr;
	}


	bool IsPartyLeader();
	bool IsLocalPlayer();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
