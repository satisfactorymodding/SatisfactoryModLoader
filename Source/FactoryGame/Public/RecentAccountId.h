// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Online/CoreOnline.h"

struct FRecentAccountId
{
	/** Registers the last launcher account id that successfully logged in on this machine. */
	static void SetUserSaveDirectory( const FString& socialId );

	/** Retrieves the last launcher account id that was registered from the game on this machine. */
	static bool GetUserSaveDirectory( FString& out_registeredId );

	static void SetLastUsedAccountIdForPlatform( const UE::Online::FAccountId accountId, UObject* worldContextObject );

	static UE::Online::FAccountId GetLastUsedAccountIdForPlatform( UObject* worldContextObject );
};
