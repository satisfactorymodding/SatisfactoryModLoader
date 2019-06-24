// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Lobby_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Lobby.LobbyBeaconClient.ServerSetPartyOwner
// ()
// Parameters:
// struct FUniqueNetIdRepl        InUniqueId                     (ConstParm, Parm, ReferenceParm)
// struct FUniqueNetIdRepl        InPartyOwnerId                 (ConstParm, Parm, ReferenceParm)

void ALobbyBeaconClient::ServerSetPartyOwner(const struct FUniqueNetIdRepl& InUniqueId, const struct FUniqueNetIdRepl& InPartyOwnerId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ServerSetPartyOwner");

	ALobbyBeaconClient_ServerSetPartyOwner_Params params;
	params.InUniqueId = InUniqueId;
	params.InPartyOwnerId = InPartyOwnerId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ServerNotifyJoiningServer
// ()

void ALobbyBeaconClient::ServerNotifyJoiningServer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ServerNotifyJoiningServer");

	ALobbyBeaconClient_ServerNotifyJoiningServer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ServerLoginPlayer
// ()
// Parameters:
// class FString                  InSessionId                    (Parm, ZeroConstructor)
// struct FUniqueNetIdRepl        InUniqueId                     (ConstParm, Parm, ReferenceParm)
// class FString                  UrlString                      (Parm, ZeroConstructor)

void ALobbyBeaconClient::ServerLoginPlayer(const class FString& InSessionId, const struct FUniqueNetIdRepl& InUniqueId, const class FString& UrlString)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ServerLoginPlayer");

	ALobbyBeaconClient_ServerLoginPlayer_Params params;
	params.InSessionId = InSessionId;
	params.InUniqueId = InUniqueId;
	params.UrlString = UrlString;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ServerKickPlayer
// ()
// Parameters:
// struct FUniqueNetIdRepl        PlayerToKick                   (ConstParm, Parm, ReferenceParm)
// struct FText                   Reason                         (ConstParm, Parm, ReferenceParm)

void ALobbyBeaconClient::ServerKickPlayer(const struct FUniqueNetIdRepl& PlayerToKick, const struct FText& Reason)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ServerKickPlayer");

	ALobbyBeaconClient_ServerKickPlayer_Params params;
	params.PlayerToKick = PlayerToKick;
	params.Reason = Reason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ServerDisconnectFromLobby
// ()

void ALobbyBeaconClient::ServerDisconnectFromLobby()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ServerDisconnectFromLobby");

	ALobbyBeaconClient_ServerDisconnectFromLobby_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ServerCheat
// ()
// Parameters:
// class FString                  Msg                            (Parm, ZeroConstructor)

void ALobbyBeaconClient::ServerCheat(const class FString& Msg)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ServerCheat");

	ALobbyBeaconClient_ServerCheat_Params params;
	params.Msg = Msg;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientWasKicked
// ()
// Parameters:
// struct FText                   KickReason                     (ConstParm, Parm, ReferenceParm)

void ALobbyBeaconClient::ClientWasKicked(const struct FText& KickReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientWasKicked");

	ALobbyBeaconClient_ClientWasKicked_Params params;
	params.KickReason = KickReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientSetInviteFlags
// ()
// Parameters:
// struct FJoinabilitySettings    Settings                       (ConstParm, Parm, ZeroConstructor, ReferenceParm, IsPlainOldData)

void ALobbyBeaconClient::ClientSetInviteFlags(const struct FJoinabilitySettings& Settings)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientSetInviteFlags");

	ALobbyBeaconClient_ClientSetInviteFlags_Params params;
	params.Settings = Settings;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientPlayerLeft
// ()
// Parameters:
// struct FUniqueNetIdRepl        InUniqueId                     (ConstParm, Parm, ReferenceParm)

void ALobbyBeaconClient::ClientPlayerLeft(const struct FUniqueNetIdRepl& InUniqueId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientPlayerLeft");

	ALobbyBeaconClient_ClientPlayerLeft_Params params;
	params.InUniqueId = InUniqueId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientPlayerJoined
// ()
// Parameters:
// struct FText                   NewPlayerName                  (ConstParm, Parm, ReferenceParm)
// struct FUniqueNetIdRepl        InUniqueId                     (ConstParm, Parm, ReferenceParm)

void ALobbyBeaconClient::ClientPlayerJoined(const struct FText& NewPlayerName, const struct FUniqueNetIdRepl& InUniqueId)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientPlayerJoined");

	ALobbyBeaconClient_ClientPlayerJoined_Params params;
	params.NewPlayerName = NewPlayerName;
	params.InUniqueId = InUniqueId;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientLoginComplete
// ()
// Parameters:
// struct FUniqueNetIdRepl        InUniqueId                     (ConstParm, Parm, ReferenceParm)
// bool                           bWasSuccessful                 (Parm, ZeroConstructor, IsPlainOldData)

void ALobbyBeaconClient::ClientLoginComplete(const struct FUniqueNetIdRepl& InUniqueId, bool bWasSuccessful)
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientLoginComplete");

	ALobbyBeaconClient_ClientLoginComplete_Params params;
	params.InUniqueId = InUniqueId;
	params.bWasSuccessful = bWasSuccessful;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientJoinGame
// ()

void ALobbyBeaconClient::ClientJoinGame()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientJoinGame");

	ALobbyBeaconClient_ClientJoinGame_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconClient.ClientAckJoiningServer
// ()

void ALobbyBeaconClient::ClientAckJoiningServer()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconClient.ClientAckJoiningServer");

	ALobbyBeaconClient_ClientAckJoiningServer_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconPlayerState.OnRep_PartyOwner
// ()

void ALobbyBeaconPlayerState::OnRep_PartyOwner()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconPlayerState.OnRep_PartyOwner");

	ALobbyBeaconPlayerState_OnRep_PartyOwner_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconPlayerState.OnRep_InLobby
// ()

void ALobbyBeaconPlayerState::OnRep_InLobby()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconPlayerState.OnRep_InLobby");

	ALobbyBeaconPlayerState_OnRep_InLobby_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconState.OnRep_WaitForPlayersTimeRemaining
// ()

void ALobbyBeaconState::OnRep_WaitForPlayersTimeRemaining()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconState.OnRep_WaitForPlayersTimeRemaining");

	ALobbyBeaconState_OnRep_WaitForPlayersTimeRemaining_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Lobby.LobbyBeaconState.OnRep_LobbyStarted
// ()

void ALobbyBeaconState::OnRep_LobbyStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function Lobby.LobbyBeaconState.OnRep_LobbyStarted");

	ALobbyBeaconState_OnRep_LobbyStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
