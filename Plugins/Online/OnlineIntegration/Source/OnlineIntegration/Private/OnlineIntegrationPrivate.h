#pragma once

#include "OnlineFriend.h"
#include "User/OnlineUserPresence.h"
#include "Auth.h"
#include "Online/Presence.h"
#include "OnlineIntegrationBackendPrivate.h"
#include "OnlineIntegrationStatePrivate.h"
#include "OnlineIntegrationSubsystem.h"
#include "Sessions.h"
#include "Social.h"

inline UE::Online::EUserPresenceStatus MapOnlineUserPresenceStatus(EOnlineUserPresenceStatus OnlineUserPresenceStatus)
{
	switch (OnlineUserPresenceStatus)
	{
		case EOnlineUserPresenceStatus::Offline:
			return UE::Online::EUserPresenceStatus::Offline;

		case EOnlineUserPresenceStatus::Online:
			return UE::Online::EUserPresenceStatus::Online;

		case EOnlineUserPresenceStatus::Away:
			return UE::Online::EUserPresenceStatus::Away;

		case EOnlineUserPresenceStatus::ExtendedAway:
			return UE::Online::EUserPresenceStatus::ExtendedAway;

		case EOnlineUserPresenceStatus::DoNotDisturb:
			return UE::Online::EUserPresenceStatus::DoNotDisturb;

		case EOnlineUserPresenceStatus::Unknown:
			return UE::Online::EUserPresenceStatus::Unknown;
		// Intentionally omitted default clause so we can get feedback when the enum changes.
	}
	return UE::Online::EUserPresenceStatus::Unknown;
}

inline EOnlineUserPresenceStatus MapOnlineUserPresenceStatus(UE::Online::EUserPresenceStatus OnlineUserPresenceStatus)
{
	switch (OnlineUserPresenceStatus)
	{
		case UE::Online::EUserPresenceStatus::Offline:
			return EOnlineUserPresenceStatus::Offline;

		case UE::Online::EUserPresenceStatus::Online:
			return EOnlineUserPresenceStatus::Online;

		case UE::Online::EUserPresenceStatus::Away:
			return EOnlineUserPresenceStatus::Away;

		case UE::Online::EUserPresenceStatus::ExtendedAway:
			return EOnlineUserPresenceStatus::ExtendedAway;

		case UE::Online::EUserPresenceStatus::DoNotDisturb:
			return EOnlineUserPresenceStatus::DoNotDisturb;

		case UE::Online::EUserPresenceStatus::Unknown:
			return EOnlineUserPresenceStatus::Unknown;
		// Intentionally omitted default clause so we can get feedback when the enum changes.
	}
	return EOnlineUserPresenceStatus::Unknown;
}


inline UE::Online::EUserPresenceJoinability MapOnlineUserPresenceJoinability(EOnlineUserPresenceJoinability OnlineUserPresenceJoinability)
{
	switch (OnlineUserPresenceJoinability)
	{
		case EOnlineUserPresenceJoinability::Public:
			return UE::Online::EUserPresenceJoinability::Public;
		case EOnlineUserPresenceJoinability::FriendsOnly:
			return UE::Online::EUserPresenceJoinability::FriendsOnly;
		case EOnlineUserPresenceJoinability::InviteOnly:
			return UE::Online::EUserPresenceJoinability::InviteOnly;
		case EOnlineUserPresenceJoinability::Private:
			return UE::Online::EUserPresenceJoinability::Private;
		case EOnlineUserPresenceJoinability::Unknown:
			return UE::Online::EUserPresenceJoinability::Unknown;
		// no default clause
	}
	return UE::Online::EUserPresenceJoinability::Unknown;
}

inline EOnlineUserPresenceJoinability MapOnlineUserPresenceJoinability(UE::Online::EUserPresenceJoinability OnlineUserPresenceJoinability)
{
	switch (OnlineUserPresenceJoinability)
	{
		case UE::Online::EUserPresenceJoinability::Public:
			return EOnlineUserPresenceJoinability::Public;
		case UE::Online::EUserPresenceJoinability::FriendsOnly:
			return EOnlineUserPresenceJoinability::FriendsOnly;
		case UE::Online::EUserPresenceJoinability::InviteOnly:
			return EOnlineUserPresenceJoinability::InviteOnly;
		case UE::Online::EUserPresenceJoinability::Private:
			return EOnlineUserPresenceJoinability::Private;
		case UE::Online::EUserPresenceJoinability::Unknown:
			return EOnlineUserPresenceJoinability::Unknown;
		// no default clause
	}
	return EOnlineUserPresenceJoinability::Unknown;
}

inline UE::Online::EUserPresenceGameStatus MapOnlineUserPresenceGameStatus(EOnlineUserPresenceGameStatus OnlineUserPresenceGameStatus)
{
	switch (OnlineUserPresenceGameStatus)
	{
		case EOnlineUserPresenceGameStatus::PlayingThisGame:
			return UE::Online::EUserPresenceGameStatus::PlayingThisGame;
		case EOnlineUserPresenceGameStatus::PlayingOtherGame:
			return UE::Online::EUserPresenceGameStatus::PlayingOtherGame;
		case EOnlineUserPresenceGameStatus::Unknown:
			return UE::Online::EUserPresenceGameStatus::Unknown;
		// no default
	}
	return UE::Online::EUserPresenceGameStatus::Unknown;
}

inline EOnlineUserPresenceGameStatus MapOnlineUserPresenceGameStatus(UE::Online::EUserPresenceGameStatus OnlineUserPresenceGameStatus)
{
	switch (OnlineUserPresenceGameStatus)
	{
		case UE::Online::EUserPresenceGameStatus::PlayingThisGame:
			return EOnlineUserPresenceGameStatus::PlayingThisGame;
		case UE::Online::EUserPresenceGameStatus::PlayingOtherGame:
			return EOnlineUserPresenceGameStatus::PlayingOtherGame;
		case UE::Online::EUserPresenceGameStatus::Unknown:
			return EOnlineUserPresenceGameStatus::Unknown;
		// no default
	}
	return EOnlineUserPresenceGameStatus::Unknown;
}

inline UE::Online::ERelationship MapOnlineRelationship(EOnlineRelationship OnlineRelationship)
{
	switch (OnlineRelationship)
	{
		case EOnlineRelationship::Friend:
			return UE::Online::ERelationship::Friend;
		case EOnlineRelationship::NotFriend:
			return UE::Online::ERelationship::NotFriend;
		case EOnlineRelationship::InviteSent:
			return UE::Online::ERelationship::InviteSent;
		case EOnlineRelationship::InviteReceived:
			return UE::Online::ERelationship::InviteReceived;
		case EOnlineRelationship::Blocked:
			return UE::Online::ERelationship::Blocked;
		// no default
	}
	return UE::Online::ERelationship::NotFriend;
}

inline EOnlineRelationship MapOnlineRelationship(UE::Online::ERelationship Relationship)
{
	switch (Relationship)
	{
		case UE::Online::ERelationship::Friend:
			return EOnlineRelationship::Friend;
		case UE::Online::ERelationship::NotFriend:
			return EOnlineRelationship::NotFriend;
		case UE::Online::ERelationship::InviteSent:
			return EOnlineRelationship::InviteSent;
		case UE::Online::ERelationship::InviteReceived:
			return EOnlineRelationship::InviteReceived;
		case UE::Online::ERelationship::Blocked:
			return EOnlineRelationship::Blocked;
		// no default
	}
	return EOnlineRelationship::NotFriend;
}

inline ECommonSessionJoinPolicy MapJoinPolicy(UE::Online::ESessionJoinPolicy JoinPolicy)
{
	switch (JoinPolicy)
	{
		case UE::Online::ESessionJoinPolicy::Public:
			return ECommonSessionJoinPolicy::Public;
		case UE::Online::ESessionJoinPolicy::FriendsOnly:
			return ECommonSessionJoinPolicy::FriendsOnly;
		case UE::Online::ESessionJoinPolicy::InviteOnly:
			return ECommonSessionJoinPolicy::InviteOnly;
		// no default
	}
	// Need a sane default in case someone does anything funny
	return ECommonSessionJoinPolicy::InviteOnly;
}

inline UE::Online::EUserPresenceJoinability PresenceJoinabilityFromJoinPolicy(UE::Online::ESessionJoinPolicy JoinPolicy)
{
	switch (JoinPolicy)
	{
		case UE::Online::ESessionJoinPolicy::Public:
			return UE::Online::EUserPresenceJoinability::Public;
		case UE::Online::ESessionJoinPolicy::FriendsOnly:
			return UE::Online::EUserPresenceJoinability::FriendsOnly;
		case UE::Online::ESessionJoinPolicy::InviteOnly:
			return UE::Online::EUserPresenceJoinability::InviteOnly;
		// no default
	}
	return UE::Online::EUserPresenceJoinability::Unknown;
}

inline UE::Online::ESessionJoinPolicy MapJoinPolicy(ECommonSessionJoinPolicy JoinPolicy)
{
	switch (JoinPolicy)
	{
		case ECommonSessionJoinPolicy::Public:
			return UE::Online::ESessionJoinPolicy::Public;
		case ECommonSessionJoinPolicy::FriendsOnly:
			return UE::Online::ESessionJoinPolicy::FriendsOnly;
		case ECommonSessionJoinPolicy::InviteOnly:
			return UE::Online::ESessionJoinPolicy::InviteOnly;
		// no default
	}
	return UE::Online::ESessionJoinPolicy::InviteOnly;
}

inline ECommonUserLoginStatus MapLoginStatus(UE::Online::ELoginStatus LoginStatus)
{
	switch(LoginStatus)
	{
		/** Player has not logged in or chosen a local profile. */
		case UE::Online::ELoginStatus::NotLoggedIn:
			return ECommonUserLoginStatus::NotLoggedIn;
		/** Player is using a local profile but is not logged in. */
		case UE::Online::ELoginStatus::UsingLocalProfile:
			return ECommonUserLoginStatus::UsingLocalProfile;
		/** Player is logged in but may have reduced functionality with online services. */
		case UE::Online::ELoginStatus::LoggedInReducedFunctionality:
			return ECommonUserLoginStatus::LoggedInReducedFunctionality;
		/** Player has been validated by the platform specific authentication service. */
		case UE::Online::ELoginStatus::LoggedIn:
			return ECommonUserLoginStatus::LoggedIn;
		// no default
	}
	return ECommonUserLoginStatus::NotLoggedIn;
}

inline EOnlineBackendConnectionStatus MapConnectionStatus(UE::Online::EOnlineServicesConnectionStatus ConnectionStatus)
{
	switch (ConnectionStatus)
	{
		case UE::Online::EOnlineServicesConnectionStatus::Connected:
			return EOnlineBackendConnectionStatus::Connected;
		case UE::Online::EOnlineServicesConnectionStatus::NotConnected:
			return EOnlineBackendConnectionStatus::NotConnected;
		// no default
	}
	return EOnlineBackendConnectionStatus::NotConnected;
}

inline UE::Online::EOnlineServicesConnectionStatus MapConnectionStatus(EOnlineBackendConnectionStatus ConnectionStatus)
{
	switch (ConnectionStatus)
	{
		case EOnlineBackendConnectionStatus::Connected:
			return UE::Online::EOnlineServicesConnectionStatus::Connected;
		case EOnlineBackendConnectionStatus::NotConnected:
			return UE::Online::EOnlineServicesConnectionStatus::NotConnected;
	}
	return UE::Online::EOnlineServicesConnectionStatus::NotConnected;
}

inline const FName GameSessionIdPresenceKey = "CommonSessionId";
inline const FName SessionBackendKey = "SessionBackend";
inline constexpr TCHAR SessionIdKeyFormat[] = TEXT("SessionId-%s");
inline const FName LastGameSessionUpdateTimestampUTC = "LastGameSessionUpdateTimestampUTC";

inline UOnlineIntegrationStatePrivate* GetViewModelPrivate(const UOnlineIntegrationSubsystem* Subsystem)
{
	return Cast<UOnlineIntegrationStatePrivate>(Subsystem->GetOnlineIntegrationState());
}


DECLARE_STATS_GROUP(TEXT("OnlineIntegration"), STATGROUP_OnlineIntegration, STATCAT_Advanced);