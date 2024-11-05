// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGDSAuthenticationTypes.generated.h"

/** Supported privilege levels for the dedicated server issued tokens */
UENUM( BlueprintType )
enum class EPrivilegeLevel : uint8
{
	// Invalid authentication
	None,
	// This player is not authenticated and may not perform any operations on the server
	NotAuthenticated,
	// This player is authenticated as a client and may only join games on the server
	Client,
	// This player is an administrator and may perform any administration tasks, such as starting new games, saving games, loading games, kicking players aso
	Administrator,
	// This player is an initial administrator. The sole purpose of this privilege level is to allow a player to set an admin password and a server name. No other operations are allowed.
	InitialAdmin,
	// This is a permanent API token that is not bound to a particular player and is instead issued to an application. It cannot be used to log into the game, but for the context of privileges it is equal to initial admin.
	APIToken,
};

/**
 * A Persistent authentication token that a client may hold. It's authenticity can be verified cryptographically by the UFGServerSubsystem class
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FServerAuthenticationToken
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, SaveGame, Category = "Server Authentication Token" )
	EPrivilegeLevel PrivilegeLevel = EPrivilegeLevel::NotAuthenticated;

	UPROPERTY( BlueprintReadWrite, SaveGame, Category = "Server Authentication Token" )
	FString Fingerprint;

	// Attempts to populate the data for this token from the given string. Returns true on success, false and an error message on failure.
	bool FromString( const FString& Authentication, FString& OutErrorMessage );

	// Creates an authentication string from this authentication token.
	FString ToString() const;
};

/**
 * A short lived game entry token that a client needs to provide when actually joining a server game. It's authenticity can be verified cryptographically by the UFGServerSubsystem class
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FServerEntryToken
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "Server Entry Token" )
	EPrivilegeLevel PrivilegeLevel = EPrivilegeLevel::NotAuthenticated;

	UPROPERTY( BlueprintReadWrite, Category = "Server Entry Token" )
	FDateTime IssueDate;

	UPROPERTY( BlueprintReadWrite, Category = "Server Entry Token" )
	FString Fingerprint;

	// Attempts to populate the data for this token from the given string. Returns true on success, false and an error message on failure.
	bool FromString( const FString& Authentication, FString& OutErrorMessage );

	// Creates an authentication string from this authentication token.
	FString ToString() const;
};
