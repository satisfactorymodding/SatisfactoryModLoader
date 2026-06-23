#pragma once
#include "FactoryGame.h"
#include "SaveCustomVersion.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Online/CoreOnline.h"
#include "PlayerInfoCache.generated.h"

/** Represents cached information about the player identity on a particular online platform */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FCachedPlayerPlatformInfo
{
	GENERATED_BODY()

	/** Account ID of the player on this online platform */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "Player Platform Info" )
	FUniqueNetIdRepl UniqueNetId;

	/** Name of the player on this online platform */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "Player Platform Info" )
	FString PlayerName;

	/** URL of the player profile picture on this online platform */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "Player Platform Info" )
	FString DisplayPictureURL;

	friend FArchive& operator<<( FArchive& ar, FCachedPlayerPlatformInfo& playerPlatformInfo )
	{
		ar << playerPlatformInfo.UniqueNetId << playerPlatformInfo.PlayerName << playerPlatformInfo.DisplayPictureURL;
		return ar;
	}

	friend bool operator==( const FCachedPlayerPlatformInfo& A, const FCachedPlayerPlatformInfo& B )
	{
		return A.UniqueNetId == B.UniqueNetId && A.PlayerName == B.PlayerName && A.DisplayPictureURL == B.DisplayPictureURL;
	}
};

template<>
struct TStructOpsTypeTraits<FCachedPlayerPlatformInfo>: TStructOpsTypeTraitsBase2<FCachedPlayerPlatformInfo>
{
	enum
	{
		WithIdenticalViaEquality = true,
	};
};

/** Represents a bundle of all player online identities on all platforms the player is currently logged in on or has been logged in on in the past */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FCachedPlayerInfo
{
	GENERATED_BODY()

	/** Identities of this player for each online platform */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "Player Platform Info" )
	TArray<FCachedPlayerPlatformInfo> PerPlatformInfo;

	/** Name of the online platform on which this player has been seen last */
	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "Player Platform Info" )
	FName LastSeenPlatformName;

	/** Returns the type of platform services that the player was last seen with */
	UE::Online::EOnlineServices GetLastSeenServicesType() const
	{
		UE::Online::EOnlineServices ResultServices = UE::Online::EOnlineServices::None;
		if ( LastSeenPlatformName != NAME_None )
		{
			LexFromString( ResultServices, *LastSeenPlatformName.ToString() );
		}
		return ResultServices;
	}

	/** Returns platform info for the given platform type, or nullptr if not found */
	const FCachedPlayerPlatformInfo* GetForPlatform( const UE::Online::EOnlineServices platformType ) const
	{
		for( const FCachedPlayerPlatformInfo& info : PerPlatformInfo )
		{
			if( info.UniqueNetId.IsV2() && info.UniqueNetId.GetV2().GetOnlineServicesType() == platformType )
			{
				return &info;
			}
		}
		return nullptr;
	}

	/** Returns platform info for the given platform type, or nullptr if not found */
	FCachedPlayerPlatformInfo& FindOrAddForPlatform( const UE::Online::EOnlineServices platformType )
	{
		for( FCachedPlayerPlatformInfo& info : PerPlatformInfo )
		{
			if( info.UniqueNetId.IsV2() && info.UniqueNetId.GetV2().GetOnlineServicesType() == platformType )
			{
				return info;
			}
		}
		return PerPlatformInfo.AddDefaulted_GetRef();
	}

	/** Returns platform info for the given platform name, or nullptr if not found */
	const FCachedPlayerPlatformInfo* GetForPlatformName( const FName platformName ) const
	{
		UE::Online::EOnlineServices platformType = UE::Online::EOnlineServices::None;
		LexFromString( platformType, *platformName.ToString() );
		return GetForPlatform( platformType );
	}

	/** Returns data cached in this player info for the given account ID */
	const FCachedPlayerPlatformInfo* GetForAccountId( const UE::Online::FAccountId accountId ) const
	{
		for( const FCachedPlayerPlatformInfo& info : PerPlatformInfo )
		{
			if( info.UniqueNetId.IsV2() && info.UniqueNetId.GetV2() == accountId )
			{
				return &info;
			}
		}
		return nullptr;
	}

	/** Returns true if this player info contains any player identities also contained in the given platform info */
	bool Intersects( const FCachedPlayerInfo& otherPlayerInfo ) const
	{
		for ( const FCachedPlayerPlatformInfo& otherPlatformInfo : otherPlayerInfo.PerPlatformInfo )
		{
			if ( otherPlatformInfo.UniqueNetId.IsV2() )
			{
				const FCachedPlayerPlatformInfo* localPlatformInfo = GetForPlatform( otherPlatformInfo.UniqueNetId.GetV2().GetOnlineServicesType() );
				if ( localPlatformInfo != nullptr && localPlatformInfo->UniqueNetId == otherPlatformInfo.UniqueNetId )
				{
					return true;
				}
			}
		}
		return false;
	}

	/** Merges this player info with another player info, overwriting data in this player info with the data in the new player info */
	void Merge( const FCachedPlayerInfo& otherPlayerInfo, TArray<UE::Online::EOnlineServices>& outUpdatedPlayerIdentities )
	{
		for ( const FCachedPlayerPlatformInfo& otherPlatformInfo : otherPlayerInfo.PerPlatformInfo )
		{
			if ( otherPlatformInfo.UniqueNetId.IsV2() )
			{
				FCachedPlayerPlatformInfo& localPlatformInfo = FindOrAddForPlatform( otherPlatformInfo.UniqueNetId.GetV2().GetOnlineServicesType() );
				if ( localPlatformInfo != otherPlatformInfo )
				{
					outUpdatedPlayerIdentities.Add( otherPlatformInfo.UniqueNetId.GetV2().GetOnlineServicesType() );
					localPlatformInfo = otherPlatformInfo;
				}
			}
		}

		if ( otherPlayerInfo.LastSeenPlatformName != NAME_None )
		{
			LastSeenPlatformName = otherPlayerInfo.LastSeenPlatformName;
		}
	}

	/** Returns the account ID of the player on the last platform the player was seen on */
	UE::Online::FAccountId GetLastSeenPlatformAccountId() const
	{
		if ( LastSeenPlatformName != NAME_None )
		{
			if ( const FCachedPlayerPlatformInfo* playerPlatformInfo = GetForPlatformName( LastSeenPlatformName ) )
			{
				if ( playerPlatformInfo->UniqueNetId.IsV2() )
				{
					return playerPlatformInfo->UniqueNetId.GetV2();
				}
			}
		}
		return UE::Online::FAccountId{};
	}

	friend FArchive& operator<<( FArchive& ar, FCachedPlayerInfo& cache )
	{
		ar << cache.LastSeenPlatformName;
		ar << cache.PerPlatformInfo;
		return ar;
	}

	friend bool operator==( const FCachedPlayerInfo& A, const FCachedPlayerInfo& B )
	{
		return A.PerPlatformInfo == B.PerPlatformInfo;
	}
};

template<>
struct TStructOpsTypeTraits<FCachedPlayerInfo>: TStructOpsTypeTraitsBase2<FCachedPlayerInfo>
{
	enum
	{
		WithIdenticalViaEquality = true,
	};
};

/** Represents a snapshot of all current player identities and the platform they are currently playing on */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerInfoSnapshot
{
	GENERATED_BODY()

	static inline const TCHAR* URLKey = TEXT("PlayerInfoSnapshot");

	/** All the platform identities the player has with the current login */
	FCachedPlayerInfo CachedPlayerInfo;
	/** The platform the player has logged in from (e.g. primary backend link) */
	FName Platform;

	/** Initializes the snapshot with a single identity constructed from the given account ID */
	void InitializeFromAccountId( const FUniqueNetIdRepl& PlayerNetId, const FString& playerName )
	{
		FCachedPlayerPlatformInfo primaryPlatformInfo{};
		primaryPlatformInfo.UniqueNetId = PlayerNetId;
		primaryPlatformInfo.PlayerName = playerName;
		
		CachedPlayerInfo.PerPlatformInfo.Add( primaryPlatformInfo );

		if ( PlayerNetId.IsV2() )
		{
			UE::Online::EOnlineServices primaryPlatformServices = primaryPlatformInfo.UniqueNetId.GetV2().GetOnlineServicesType();
			CachedPlayerInfo.LastSeenPlatformName = LexToString( primaryPlatformServices );
			Platform = CachedPlayerInfo.LastSeenPlatformName;
		}
	}

	/** Returns the type of platform services for the current platform */
	UE::Online::EOnlineServices GetPlatformServicesType() const
	{
		UE::Online::EOnlineServices ResultServices = UE::Online::EOnlineServices::None;
		if ( Platform != NAME_None )
		{
			LexFromString( ResultServices, *Platform.ToString() );
		}
		return ResultServices;
	}

	/** Returns first valid online services with the data in the order of preference (platform, last seen, any), or null if there are none */
	UE::Online::EOnlineServices FindPreferredOnlineServicesType() const
	{
		const UE::Online::EOnlineServices platformServicesType = GetPlatformServicesType();
		if ( CachedPlayerInfo.GetForPlatform( platformServicesType ) )
		{
			return platformServicesType;
		}
		const UE::Online::EOnlineServices lastSeenServicesType = CachedPlayerInfo.GetLastSeenServicesType();
		if ( CachedPlayerInfo.GetForPlatform( lastSeenServicesType ) )
		{
			return lastSeenServicesType;
		}
		if ( !CachedPlayerInfo.PerPlatformInfo.IsEmpty() && CachedPlayerInfo.PerPlatformInfo[ 0 ].UniqueNetId.IsV2() )
		{
			return CachedPlayerInfo.PerPlatformInfo[ 0 ].UniqueNetId.GetV2().GetOnlineServicesType();
		}
		return UE::Online::EOnlineServices::Null;
	}

	/** Returns the name that the player should have on the current platform */
	FString ResolvePlayerPlatformName() const
	{
		const UE::Online::EOnlineServices targetOnlineServicesType = FindPreferredOnlineServicesType();
		if ( const FCachedPlayerPlatformInfo* platformInfo = CachedPlayerInfo.GetForPlatform( targetOnlineServicesType ) )
		{
			return platformInfo->PlayerName;
		}
		return TEXT("");
	}

	friend FArchive& operator<<( FArchive& ar, FPlayerInfoSnapshot& Snapshot )
	{
		ar << Snapshot.Platform;
		ar << Snapshot.CachedPlayerInfo;
		return ar;
	}
};

/** Represent a handle to the player information for a specific service provider cached on the game state */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPlayerInfoHandle
{
	GENERATED_BODY()
private:
	uint8 ServiceProvider{0};
	int32 PlayerInfoTableIndex{INDEX_NONE};
	friend class AFGGameState;

	/** Internal constructor used to construct a valid player info */
	FORCEINLINE FPlayerInfoHandle( UE::Online::EOnlineServices serviceProvider, const int32 playerInfoTableIndex )
    {
    	ServiceProvider = static_cast<uint8>( serviceProvider );
    	PlayerInfoTableIndex = static_cast<uint8>( playerInfoTableIndex );
    }
public:
	/** Default constructor, constructs invalid player info */
	FPlayerInfoHandle() = default;

	/** Returns true if this player info handle points to a valid player info */
	FORCEINLINE bool IsValid() const
	{
		return PlayerInfoTableIndex != INDEX_NONE;
	}

	/** Returns true if both handles point to the same player account */
	FORCEINLINE bool IsSameAccount( const FPlayerInfoHandle& otherHandle ) const
	{
		return IsValid() && otherHandle.PlayerInfoTableIndex == PlayerInfoTableIndex;
	}

	/** Returns the online services provider this player info handle was created from */
	UE::Online::EOnlineServices GetOnlineServiceProvider() const
	{
		return static_cast<UE::Online::EOnlineServices>( ServiceProvider );
	}

	friend FArchive& operator<<( FArchive& ar, FPlayerInfoHandle& handle )
	{
		ar.UsingCustomVersion( FSaveCustomVersion::GUID );

		// Fix for some assets being saved with a broken format during a short window of time between 16 and 19th of December 2025
		// There was a big merge during that time that touched a lot of UI widgets so quite a few assets got saved with this version
		const int32 saveCustomVersion = ar.CustomVer( FSaveCustomVersion::GUID );
		if ( saveCustomVersion >= FSaveCustomVersion::NewPlayerInfoHandleSerializationFormat && saveCustomVersion < FSaveCustomVersion::FixNewPlayerInfoHandleSerializationFormat )
		{
			ar << handle.ServiceProvider;
			ar << handle.PlayerInfoTableIndex;
		}
		
		if ( ar.CustomVer( FSaveCustomVersion::GUID ) >= FSaveCustomVersion::NewPlayerInfoHandleSerializationFormat )
		{
			ar << handle.ServiceProvider;
			ar << handle.PlayerInfoTableIndex;
		}
		else
		{
			ar << handle.ServiceProvider;
			uint8 LegacyPlayerInfoTableIndex{};
			ar << LegacyPlayerInfoTableIndex;
			handle.PlayerInfoTableIndex = LegacyPlayerInfoTableIndex;

			// Null service provider in legacy serialization format was treated as invalid player info handle
			if ( handle.ServiceProvider == (uint8)UE::Online::EOnlineServices::Null )
			{
				handle.PlayerInfoTableIndex = INDEX_NONE;
			}
		}
		
		return ar;
	}

	bool Serialize( FArchive& ar )
	{
		ar << *this;
		return true;
	}

	bool NetSerialize(FArchive& ar, UPackageMap*, bool& bOutSuccess)
	{ 
		ar << ServiceProvider;
		ar << PlayerInfoTableIndex;
		bOutSuccess = true;
		return true;
	}

	/** Returns true if two player info handles point to the same entry */
	friend bool operator==( const FPlayerInfoHandle& A, const FPlayerInfoHandle& B )
	{
		return A.ServiceProvider == B.ServiceProvider && A.PlayerInfoTableIndex == B.PlayerInfoTableIndex;
	}
};

template<>
struct TStructOpsTypeTraits<FPlayerInfoHandle>: TStructOpsTypeTraitsBase2<FPlayerInfoHandle>
{
	enum
	{
		WithSerializer = true, 
		WithNetSerializer = true,
		WithIdenticalViaEquality = true,
	};
};
