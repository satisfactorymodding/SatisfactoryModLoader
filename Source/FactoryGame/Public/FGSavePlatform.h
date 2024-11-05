// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveSystem.h"

class FACTORYGAME_API FFGSavePlatform
{
public:
	static bool CheckSaveInCommon( const UWorld*  world, const FString& saveName );
	static bool IsSaveReadOnly( const FString& savePath );
	static bool WriteSaveGame( const TArray< uint8, TSizedDefaultAllocator< 64 > >& outputData, const FString& savePath, bool bIsAutoSave, bool bAllowSaveBackups );
	static bool ReadSaveGame( const FString& saveFile, TArray< uint8 >& out_rawSaveData );
	static bool DeleteSaveGame( const FString& saveFile );
	static ESaveLocationInfo ResolveSaveLocationForSaveDirectory( const FString& saveDirectory );
	// <FL> [n.tran] Modified to support async
	static void FindSaveGames( const TArray<FString>& saveDirectories, TWeakPtr<FOnEnumerateSaveGamesComplete> onEnumerateSaveGamesComplete );
	/** Synchronous version of the function above. On default platform, the above function just wraps this async */
	static TArray<FSaveHeader> FindSaveGamesSync( const TArray<FString>& saveDirectories );
	static bool SaveExists( const FString& saveFile );
	/** Get the path to the save folder for EPIC user ID, will return path to common directory if it fails to get EPIC user ID */
	static bool GetUserSaveDirectoryPath( const UWorld* world, FString& out_dirPath );
	/** Get the path to the save folder for saves not connected to an EPIC user ID (offline play, PIE, etc) */
	static FString GetCommonSaveDirectoryPath( const UWorld* world );
	/** Convert a filename with a save directory to a filename */
	static FString SaveNameToFileName( const FString& directory, const FString& saveName );
	static bool IsDeprecatedSave( const FString& saveName );

private:
	static inline const FString REL_COMMON_USER = "common/";
	static inline const FString REL_COMMON_SERVER = "server/";
};
