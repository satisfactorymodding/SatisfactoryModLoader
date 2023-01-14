// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"

struct FRecentAccountId
{
	/** Registers the last launcher account id that successfully logged in on this machine. */
	static void Set( const FString& socialId );

	/** Retrieves the last launcher account id that was registered from the game on this machine. */
	static bool Get( FString& out_registeredId );
};
