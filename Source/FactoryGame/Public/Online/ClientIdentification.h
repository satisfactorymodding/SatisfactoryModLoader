// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Online/CoreOnline.h"
#include "ClientIdentification.generated.h"


USTRUCT()
struct FClientIdentityInfo
{
	GENERATED_BODY()

	/**
	 * Checks if two given client identities match. When no online ids are available, the offline id is used. Otherwise, if one online
	 * id matches, the identities are considered to match. This operation is not commutative.
	 */
	static float CalcClientIdentityMatchQuality(const FClientIdentityInfo& first, const FClientIdentityInfo& second);

	/**
	 * @return the result of merging @Second into @First. Everything in @First will be preserved, but if there are any online ids in @Second
	 * they will be added to @First. If there are any online ids in @First that are not in @Second, they will be preserved.
	 */
	static FClientIdentityInfo MergeIdentities(const FClientIdentityInfo& first, const FClientIdentityInfo& second);

	/**
	 * Substracts the identity in @substractThis from @substractFrom. If the offline id matches, it will be removed. If any online id
	 * matches, they will also be removed. The goal is to create a new identity that will not match the identity in @substractThis.
	 */
	static FClientIdentityInfo SubstractIdentity( const FClientIdentityInfo& substractFrom, const FClientIdentityInfo& substractThis );

	/**
	 * Key used to store the client identity in a URL.
	 */
	static const FString URLKey;

	/**
	 * An offline identifier for the client. Used when no online ids are available.
	 */
	UPROPERTY(SaveGame)
	FString OfflineId;

	/**
	 * Online identity for the client for each service. Stored as a map so we can only have one identity per service even though the service
	 * id is also embedded in the account id.
	 */
	TMap<UE::Online::EOnlineServices, UE::Online::FAccountId> AccountIds;
	bool operator==(const FClientIdentityInfo&) const;
	
	bool Serialize(FArchive& ar);
};

template<>
struct TStructOpsTypeTraits<FClientIdentityInfo> : public TStructOpsTypeTraitsBase2<FClientIdentityInfo>
{
	enum
	{
		WithSerializer = true
	};
};

FArchive& operator<<(FArchive& ar, FClientIdentityInfo& info);
