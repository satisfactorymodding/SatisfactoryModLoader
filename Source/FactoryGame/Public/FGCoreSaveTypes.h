#pragma once

#include "FGSaveSystem.h"
#include "Misc/EngineVersion.h"
#include "SaveCustomVersion.h"

/*
* Core save types that need to be accessible outside the save session 
*/

#define SAVE_BUILD_VERSION FEngineVersion::Current().GetChangelist()

#define DISABLE_STRICT_SAVE_CHECKING (UE_BUILD_SHIPPING == 0)
#define STRICT_SAVE_CHECKING (DISABLE_STRICT_SAVE_CHECKING == 0)

#if STRICT_SAVE_CHECKING
#define checkSave(expr) check(expr)
#define checkfSave(expr, format, ...) checkf(expr, format, __VA_ARGS__)
#else
#define checkSave(expr)
#define checkfSave(expr, format, ...)
#endif

namespace SaveSystemConstants
{
	static FString BackupSuffix( TEXT( "_BACK" ) );

	// Several locations require the . in the extension
	static FString SaveExtension( TEXT( ".sav" ) );

	// Custom name for the custom version when setting versions of archives
	static const TCHAR CustomVersionFriendlyName[] = TEXT( "SaveVersion" );

	// Custom name for the save header
	static const TCHAR HeaderCustomVersionFriendlyName[] = TEXT( "SaveHeaderVersion" );

	/// Blueprint Constants
	static inline const FString BlueprintBaseDirectory = "blueprints/"; 
	static inline const FString BlueprintExtension = TEXT(".sbp");
	static inline const FString BlueprintConfigExtension = TEXT(".sbpcfg");
	static const TCHAR BlueprintConfigCustomVersionFriendlyName[] = TEXT("BlueprintConfigVersion");
	static inline const FString PIESessionName = TEXT("_Dev_PIE");
	static inline const FString PIEClientSessionName = TEXT("_Dev_Client_PIE");
	static const TCHAR BlueprintHeaderCustomVersionFriendlyName[] = TEXT("BlueprintHeaderVersion");

}

