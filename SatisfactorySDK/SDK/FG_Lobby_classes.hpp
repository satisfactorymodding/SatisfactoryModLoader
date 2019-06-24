#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Lobby_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Lobby.LobbyBeaconClient
// 0x0088 (0x0428 - 0x03A0)
class ALobbyBeaconClient : public AOnlineBeaconClient
{
public:
	class ALobbyBeaconState*                           LobbyState;                                               // 0x03A0(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	class ALobbyBeaconPlayerState*                     PlayerState;                                              // 0x03A8(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x1];                                       // 0x03B0(0x0001) MISSED OFFSET
	ELobbyBeaconJoinState                              LobbyJoinServerState;                                     // 0x03B1(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x76];                                      // 0x03B2(0x0076) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Lobby.LobbyBeaconClient");
		return ptr;
	}


	void ServerSetPartyOwner(const struct FUniqueNetIdRepl& InUniqueId, const struct FUniqueNetIdRepl& InPartyOwnerId);
	void ServerNotifyJoiningServer();
	void ServerLoginPlayer(const class FString& InSessionId, const struct FUniqueNetIdRepl& InUniqueId, const class FString& UrlString);
	void ServerKickPlayer(const struct FUniqueNetIdRepl& PlayerToKick, const struct FText& Reason);
	void ServerDisconnectFromLobby();
	void ServerCheat(const class FString& Msg);
	void ClientWasKicked(const struct FText& KickReason);
	void ClientSetInviteFlags(const struct FJoinabilitySettings& Settings);
	void ClientPlayerLeft(const struct FUniqueNetIdRepl& InUniqueId);
	void ClientPlayerJoined(const struct FText& NewPlayerName, const struct FUniqueNetIdRepl& InUniqueId);
	void ClientLoginComplete(const struct FUniqueNetIdRepl& InUniqueId, bool bWasSuccessful);
	void ClientJoinGame();
	void ClientAckJoiningServer();
};


// Class Lobby.LobbyBeaconHost
// 0x0038 (0x0388 - 0x0350)
class ALobbyBeaconHost : public AOnlineBeaconHostObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0350(0x0008) MISSED OFFSET
	TSoftObjectPtr<class UClass>                       LobbyStateClass;                                          // 0x0358(0x0028)
	class ALobbyBeaconState*                           LobbyState;                                               // 0x0380(0x0008) (ZeroConstructor, IsPlainOldData)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Lobby.LobbyBeaconHost");
		return ptr;
	}

};


// Class Lobby.LobbyBeaconPlayerState
// 0x00A8 (0x03D0 - 0x0328)
class ALobbyBeaconPlayerState : public AInfo
{
public:
	struct FText                                       DisplayName;                                              // 0x0328(0x0028) (Net)
	struct FUniqueNetIdRepl                            UniqueId;                                                 // 0x0340(0x0028) (Net)
	struct FUniqueNetIdRepl                            PartyOwnerUniqueId;                                       // 0x0368(0x0028) (Net)
	bool                                               bInLobby;                                                 // 0x0390(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0391(0x0007) MISSED OFFSET
	class AOnlineBeaconClient*                         ClientActor;                                              // 0x0398(0x0008) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x30];                                      // 0x03A0(0x0030) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Lobby.LobbyBeaconPlayerState");
		return ptr;
	}


	void OnRep_PartyOwner();
	void OnRep_InLobby();
};


// Class Lobby.LobbyBeaconState
// 0x0150 (0x0478 - 0x0328)
class ALobbyBeaconState : public AInfo
{
public:
	int                                                MaxPlayers;                                               // 0x0328(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x032C(0x0004) MISSED OFFSET
	class UClass*                                      LobbyBeaconPlayerStateClass;                              // 0x0330(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0338(0x0008) MISSED OFFSET
	bool                                               bLobbyStarted;                                            // 0x0340(0x0001) (Net, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0341(0x0003) MISSED OFFSET
	float                                              WaitForPlayersTimeRemaining;                              // 0x0344(0x0004) (Net, ZeroConstructor, Config, IsPlainOldData)
	struct FLobbyPlayerStateInfoArray                  Players;                                                  // 0x0348(0x00C8) (Net)
	unsigned char                                      UnknownData03[0x68];                                      // 0x0410(0x0068) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Lobby.LobbyBeaconState");
		return ptr;
	}


	void OnRep_WaitForPlayersTimeRemaining();
	void OnRep_LobbyStarted();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
