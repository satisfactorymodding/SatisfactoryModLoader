// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGClientRequestBase.h"
#include "FGSaveManagerInterface.h"
#include "FGClientSaveGameRequester.generated.h"

struct FFGPendingClientRequest;

UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientSaveGameRequester : public UFGClientRequestBase
{
	GENERATED_BODY()
public:
	/** Creates and starts a new game on the server using the data provided */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_CreateNewGame( const FFGServerNewGameData& NewGameData ) const;

	/** Called as a response to when new game is created (or failed to be created) */
	UFUNCTION( FGServerResponse )
	void Response_CreateNewGame( const FFGServerErrorResponse& ErrorResponse ) const;

	/** Saves the game on the server to the given save filename */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_SaveGame( const FString& SaveName, UPARAM( FGServerRequestPassThrough ) const FOnSaveMgrInterfaceSaveGameComplete& CompleteDelegate ) const;

	/** Called as a response to when the game is saved */
	UFUNCTION( FGServerResponse )
	static void Response_SaveGame( FFGServerErrorResponse& ErrorResponse, const FOnSaveMgrInterfaceSaveGameComplete& CompleteDelegate );

	/** Deletes the given save filename from the server storage */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_DeleteSaveFile( const FString& SaveName, UPARAM( FGServerRequestPassThrough ) const FOnSaveMgrInterfaceDeleteSaveGameComplete& CompleteDelegate ) const;

	/** Called as a response to when a save game file is deleted */
	UFUNCTION( FGServerResponse )
	static void Response_DeleteSaveFile( FFGServerErrorResponse& ErrorResponse, const FOnSaveMgrInterfaceDeleteSaveGameComplete& CompleteDelegate );

	/** Deletes the entire save session (e.g. all save files from that session) from the server storage */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_DeleteSaveSession( const FString& SessionName, UPARAM( FGServerRequestPassThrough ) const FOnSaveMgrInterfaceDeleteSaveGameComplete& CompleteDelegate ) const;

	/** Called as a response to when a save session is deleted */
	UFUNCTION( FGServerResponse )
	static void Response_DeleteSaveSession( FFGServerErrorResponse& ErrorResponse, const FOnSaveMgrInterfaceDeleteSaveGameComplete& CompleteDelegate );

	/** Enumerates all sessions on the server and returns them as a list */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_EnumerateSessions();

	/** Response to the session enumeration request */
	UFUNCTION( FGServerResponse )
	void Response_EnumerateSessions( const FFGServerErrorResponse& ErrorResponse, const TArray<FSessionSaveStruct>& Sessions, int32 CurrentSessionIndex );

	/** Loads the given save filename on the server */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_LoadGame( const FString& SaveName, bool bEnableAdvancedGameSettings ) const;

	/** Response to the load game request */
	UFUNCTION( FGServerResponse )
	void Response_LoadGame( const FFGServerErrorResponse& ErrorResponse ) const;

	/** Uploads a SaveGame file to the server */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_UploadSaveGame( const FString& SaveName, const FFGMultipartDataWrapper& SaveGameFile, bool bLoadSaveGame, bool bEnableAdvancedGameSettings, UPARAM( FGServerRequestPassThrough ) const FOnSaveManagerTransferCompleted& CompleteDelegate ) const;

	/** Response for when save game upload is complete */
	UFUNCTION( FGServerResponse )
	void Response_UploadSaveGame( FFGServerErrorResponse& ErrorResponse, const FOnSaveManagerTransferCompleted& CompleteDelegate ) const;

	/** Downloads the SaveGame file from the server */
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "Administrator" )
	FFGPendingClientRequest Request_DownloadSaveGame( const FString& SaveName, UPARAM( FGServerRequestPassThrough ) const FOnSaveManagerTransferCompleted& CompleteDelegate ) const;

	/** Response for the SaveGame download request */
	UFUNCTION( FGServerResponse )
	void Response_DownloadSaveGame( FFGServerErrorResponse& ErrorResponse, const FFGFileResponseWrapper& FileResponse, const FOnSaveManagerTransferCompleted& CompleteDelegate ) const;
};
