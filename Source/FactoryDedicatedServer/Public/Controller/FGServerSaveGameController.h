// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Controller/FGServerControllerBase.h"
#include "FGServerSaveGameController.generated.h"

struct FFGFileResponseWrapper;
struct FFGMultipartDataWrapper;
class UFGServerSubsystem;
struct FFGRequestHandlerContextWrapper;

/**
 * Handles SaveGame related operations such as:
 *  - Enumerating Save Sessions
 *  - Loading Save Sessions to the Dedicated Server
 *  - Starting New Games
 *  - Deleting/Downloading Saves
 *
 * Most operations require Administrator privilege level.
 */
UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerSaveGameController : public UFGServerControllerBase
{
	GENERATED_BODY()

public:
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_CreateNewGame( const FFGServerNewGameData& NewGameData ) const;
	
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	void Handler_SaveGame( const FString& SaveName, const FFGRequestHandlerContextWrapper& Context ) const;

	UFUNCTION( FGServerAsyncCompleteRequest )
	static void CompleteRequest_SaveGame( const FFGRequestHandlerContextWrapper& Context, const FFGServerErrorResponse& ErrorResponse );
	
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	void Handler_DeleteSaveFile( const FString& SaveName, const FFGRequestHandlerContextWrapper& Context );

	UFUNCTION( FGServerAsyncCompleteRequest )
	static void CompleteRequest_DeleteSaveFile( const FFGRequestHandlerContextWrapper& Context, const FFGServerErrorResponse& ErrorResponse );

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	void Handler_DeleteSaveSession( const FString& SessionName, const FFGRequestHandlerContextWrapper& Context );

	UFUNCTION( FGServerAsyncCompleteRequest )
	static void CompleteRequest_DeleteSaveSession( const FFGRequestHandlerContextWrapper& Context, const FFGServerErrorResponse& ErrorResponse );

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator", FGServerRequestHandlerEnableCompression )
	void Handler_EnumerateSessions( const FFGRequestHandlerContextWrapper& Context );

	UFUNCTION( FGServerAsyncCompleteRequest )
	static void CompleteRequest_EnumerateSessions( const FFGRequestHandlerContextWrapper& Context, const FFGServerErrorResponse& ErrorResponse, const TArray<FSessionSaveStruct>& Sessions, int32 CurrentSessionIndex );

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_LoadGame( const FString& SaveName, bool bEnableAdvancedGameSettings ) const;

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_UploadSaveGame( const FString& SaveName, const FFGMultipartDataWrapper& SaveGameFile, bool bLoadSaveGame, bool bEnableAdvancedGameSettings ) const;

	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGServerErrorResponse Handler_DownloadSaveGame( const FString& SaveName, FFGFileResponseWrapper& OutFileResponse ) const;
};