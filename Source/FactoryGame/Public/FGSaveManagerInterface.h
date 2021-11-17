#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGOnlineSessionSettings.h"
#include "FGSaveManagerInterface.generated.h"

namespace SaveSystemConstants
{
	// Several locations require the . in the extension
	static FString SaveExtension( TEXT( ".sav" ) );

	static FString BackupSuffix( TEXT("_BAK" ) );

	// Custom name for the custom version when setting versions of archives
	static const TCHAR CustomVersionFriendlyName[] = TEXT( "SaveVersion" );

	// Custom name for the save header
	static const TCHAR HeaderCustomVersionFriendlyName[] = TEXT( "SaveHeaderVersion" );
}

UENUM( BlueprintType )
enum class ESaveExists : uint8
{
	SE_DoesntExist			UMETA( DisplayName="DoesntExist" ),
	SE_ExistsInSameSession	UMETA( DisplayName="ExistsInSameSession" ),
	SE_ExistsInOtherSession UMETA( DisplayName="ExistsInOtherSession" )
};

UENUM( BlueprintType )
enum class ESaveState : uint8
{
	SS_Unsupported	UMETA( DisplayName="Unsupported" ),
	SS_Volatile		UMETA( DisplayName="Volatile" ),
	SS_Supported	UMETA( DisplayName="Supported"),
	SS_Newer		UMETA( DisplayName="Newer" )
};

UENUM( BlueprintType )
enum class ESaveLocationInfo : uint8
{
	SLI_Default		UMETA( DisplayName = "Default/User Dir" ),
	SLI_Common		UMETA( DisplayName = "Common Dir" ),
	SLI_Server		UMETA( DisplayName = "Server Dir" )
};

/** The header with information about a save game */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FSaveHeader
{
	GENERATED_BODY()

	// if you modify this struct, increment this number
	enum Type
	{
		// First version
		InitialVersion = 0,

		// @2017-01-20: Added BuildVersion, MapName and MapOptions
		PrepareForLoadingMaps,

		// @2017-02-07: Added SessionId for autosaves
		AddedSessionId,

		// @2018-02-23 Added PlayDuration to header
		AddedPlayDuration,

		// @2018-04-10 SessionID from int32 to FString, also added when the save was saved
		SessionIDStringAndSaveTimeAdded,

		// @2019-01-15 Added session visibility to the header so we can set it up with the same visibility
		AddedSessionVisibility,

		// @2019-06-19 This was put in the wrong save version thingy and is now on experimental so can't remove it.
		LookAtTheComment,

		// @2021-01-22 UE4.25 Engine Upgrade. FEditorObjectVersion Changes occurred (notably with FText serialization)
		UE425EngineUpdate,

		// @2021-03-24 Added Modding properties and support
		AddedModdingParams,

		// @2021-04-15 UE4.26 Engine Upgrade. FEditorObjectVersion Changes occurred
		UE426EngineUpdate,

		// -----<new versions can be added above this line>-----
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1 // Last version to use
	};

	FSaveHeader();

	FSaveHeader( int32 saveVersion, int32 buildVersion, FString mapName, FString mapOptions, FString sessionName, int32 playDurationSeconds, FDateTime saveDateTime, ESessionVisibility sessionVisibility, int32 editorObjectVersion, FString metaData, bool isModdedSave ) :
		SaveVersion( saveVersion ),
		BuildVersion( buildVersion ),
		MapName( mapName ),
		MapOptions( mapOptions ),
		SessionName( sessionName ),
		PlayDurationSeconds( playDurationSeconds ),
		SaveDateTime( saveDateTime ),
		SessionVisibility( sessionVisibility ),
		EditorObjectVersion( editorObjectVersion ),
		ModMetadata( metaData ),
		IsModdedSave( isModdedSave )
	{
	}

	/** Version of the save game */
	int32 SaveVersion;

	/** CL the game was on when this was stored */
	int32 BuildVersion;

	/** Name of the save game, not store to disc */
	FString SaveName;

	/** Descriptor for the save game location on the disc at the time of read (not saved to disc) */
	ESaveLocationInfo SaveLocationInfo;

	/** The map this save is valid on  */
	FString MapName;

	/** Options we want to pass to the game mode */
	FString MapOptions;

	/** A unique id for each session, used for generating autosaves that's unique */
	FString SessionName;

	/** How long play time has this save been going on for */
	int32 PlayDurationSeconds;

	/** The time we saved this save */
	FDateTime SaveDateTime;

	/** What was the last visibility of the game when we played it */
	TEnumAsByte<ESessionVisibility> SessionVisibility;

	/** Save the FEditorObjectVersion that this save file was written with */
	int32 EditorObjectVersion;

	/** Generic MetaData - Requested by Mods */
	FString ModMetadata;

	/** Was this save ever saved with mods enabled? */
	bool IsModdedSave;

	// @todosave: Add LastPlayDate as uint64 (Timestamp)
	// @todosave: Add if it's a autosave

	/** Store / load data */
	friend FArchive& operator<< ( FArchive& ar, FSaveHeader& header );

	/** Send/Receive over network */
	bool NetSerialize( FArchive& ar, class UPackageMap* map, bool& out_success );

	// The GUID for this custom version number
	const static FGuid GUID;
};

/** Enable custom net delta serialization for the above struct. */
template<>
struct TStructOpsTypeTraits< FSaveHeader > : public TStructOpsTypeTraitsBase2< FSaveHeader >
{
	enum
	{
		WithNetSerializer = true
	};
};


UENUM()
enum class ESaveSortMode : uint8
{
	SSM_Name UMETA(DisplayName=Name),
	SSM_Time UMETA(DisplayName=Time)
};

UENUM()
enum class ESaveSortDirection : uint8
{
	SSD_Ascending UMETA(DisplayName=Ascending),
	SSD_Descending UMETA(DisplayName=Descending)
};

/**
 * For when a artist/LD has changed the name of a map
 */
USTRUCT()
struct FACTORYGAME_API FMapRedirector
{
	GENERATED_BODY()

	/** Old map name */
	UPROPERTY()
	FString OldMapName;

	/** New map name */
	UPROPERTY()
	FString NewMapName;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSessionSaveStruct
{
	GENERATED_BODY()

	FSessionSaveStruct() :
		SessionName( TEXT( "NO_SESSION_ID" ) )
	{
	}
		
	FSessionSaveStruct( FString sessionName ) :
		SessionName( sessionName )
	{
	}

	/** The name of the session */
	UPROPERTY( BlueprintReadOnly )
	FString SessionName;

	/** The saves that are in this session */
	UPROPERTY( BlueprintReadOnly )
	TArray< FSaveHeader > SaveHeaders;
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams( FOnSaveManagerEnumerateSessionsComplete, bool, Success, const TArray<FSessionSaveStruct>&, Sessions, int32, CurrentSession );
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnSaveMgrInterfaceDeleteSaveGameComplete, bool, Success );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnSaveMgrInterfaceSaveGameComplete, bool, Success, const FText&, ErrorMessage );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnSaveManagerTransferCompleted, bool, Success, const FText&, ErrorMessage );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnSaveManagerTransferProgress, int32, Progress, int32, Total );
DECLARE_DYNAMIC_DELEGATE( FOnSaveManagerRefreshSaves );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSaveManagerRefreshSavesMulti );

/**
 * 
 */
UINTERFACE( BlueprintType, meta=(CannotImplementInterfaceInBlueprint) )
class FACTORYGAME_API UFGSaveManagerInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGSaveManagerInterface
{
	GENERATED_BODY()
	
	UFUNCTION( BlueprintCallable )
	virtual void EnumerateSessions( const FOnSaveManagerEnumerateSessionsComplete& CompleteDelegate ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	virtual bool IsEnumeratingLocalSaves() PURE_VIRTUAL( , return false; );

	UFUNCTION( BlueprintCallable )
	virtual void DeleteSaveSession( const FSessionSaveStruct& Session, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	virtual void DeleteSaveFile( const FSaveHeader& SaveGame, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	virtual void LoadSaveFile( const FSaveHeader& SaveGame, class APlayerController* Player  ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	virtual void SaveGame( const FString& SaveName, FOnSaveMgrInterfaceSaveGameComplete CompleteDelegate ) PURE_VIRTUAL( , );

	UFUNCTION( BlueprintCallable )
	virtual bool IsSaveManagerAvailable() PURE_VIRTUAL( , return false; );

	UFUNCTION( BlueprintCallable )
	virtual void UploadSave( const FSaveHeader& Save, FOnSaveManagerTransferCompleted CompleteDelegate, FOnSaveManagerTransferProgress ProgressDelegate );

	UFUNCTION( BlueprintCallable )
	virtual bool IsTransferInProgress();

	UFUNCTION( BlueprintCallable )
	virtual void BindOnSavesChanged( const FOnSaveManagerRefreshSaves& OnRefreshSaves );

	UFUNCTION( BlueprintCallable )
	virtual void UnbindOnSavesChanged( const FOnSaveManagerRefreshSaves& OnRefreshSaves );

protected:
	FOnSaveManagerRefreshSavesMulti mRefreshSavesDelegate;
};
