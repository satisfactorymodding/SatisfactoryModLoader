// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Misc/SecureHash.h"
#include "UObject/Interface.h"
#include "SessionInformation.h"
#include "FGSaveManagerInterface.generated.h"

class USessionMigrationSequence;
class APlayerController;
class IFGAdvancedGameSettingsInterface;

enum class ESessionVisibility: uint8;

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
enum class ESaveModCheckResult : uint8
{
	MCR_Unknown			UMETA( DisplayName="Unknown" ),
	MCR_Supported		UMETA( DisplayName="Supported" ),
	MCR_Volatile		UMETA( DisplayName="Volatile" ),
	MCR_Incompatible	UMETA( DisplayName="Incompatible" )
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

		// @2022-03-22 Added GUID to identify saves, it is for analytics purposes.
		AddedSaveIdentifier,

		// @2022-11-14 Added support for partitioned worlds (UE5)
		AddedWorldPartitionSupport,

		// @2023-03-08 Added checksum to detect save game modifications.
		AddedSaveModificationChecksum,

		// @2023-04-18 Added variable to indicate if creative mode is enabled for this save.
		AddedIsCreativeModeEnabled,

		// -----<new versions can be added above this line>-----
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1 // Last version to use
	};

	FSaveHeader();

	FSaveHeader(
		int32 saveVersion,
		int32 buildVersion,
		FString mapName,
		FString mapOptions,
		FString sessionName,
		int32 playDurationSeconds,
		FDateTime saveDateTime,
		int32 editorObjectVersion,
		FString metaData,
		bool isModdedSave,
		FString saveIdentifier,
		bool isPartitionedWorld,
		bool isCreativeModeEnabled) :
		SaveVersion( saveVersion ),
		BuildVersion( buildVersion ),
		MapName( mapName ),
		MapOptions( mapOptions ),
		SessionName( sessionName ),
		PlayDurationSeconds( playDurationSeconds ),
		SaveDateTime( saveDateTime ),
		EditorObjectVersion( editorObjectVersion ),
		ModMetadata( metaData ),
		IsModdedSave( isModdedSave ),
		SaveIdentifier( saveIdentifier ),
		IsPartitionedWorld( isPartitionedWorld ),
		IsCreativeModeEnabled( isCreativeModeEnabled )
	{
	}

	/** Version of the save game */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	int32 SaveVersion;

	/** CL the game was on when this was stored */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	int32 BuildVersion;

	/** Name of the save game, not store to disc */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	FString SaveName;

	/** Descriptor for the save game location on the disc at the time of read (not saved to disc) */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	ESaveLocationInfo SaveLocationInfo;

	/** The map this save is valid on  */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	FString MapName;

	/** Options we want to pass to the game mode */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	FString MapOptions;

	/** A unique id for each session, used for generating autosaves that's unique */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	FString SessionName;

	/** How long play time has this save been going on for */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	int32 PlayDurationSeconds;

	/** The time we saved this save */
	UPROPERTY(BlueprintReadOnly, Category="SaveHeader")
	FDateTime SaveDateTime;

	/** Save the FEditorObjectVersion that this save file was written with */
	int32 EditorObjectVersion;

	/** Generic MetaData - Requested by Mods */
	FString ModMetadata;

	/** Was this save ever saved with mods enabled? */
	UPROPERTY()
	bool IsModdedSave;

	/**
	 * Hash of the saved data.
	 * This is to detect if the save has been edited outside of the game. Useful for crash report statistics.
	 * Save game editors should leave this property unmodified.
	 */
	FMD5Hash SaveDataHash;

	/**
	 * Was this save modified by an external application?
	 * This is set at load when comparing the hash of the loaded data and the stored hash.
	 */
	UPROPERTY()
	bool IsEditedSave;

	/** A save identifier for analytics. */
	FString SaveIdentifier;

	/** Whether the world that was saved was a partitioned one or not */
	bool IsPartitionedWorld;

	/** Is creative mode enabled for this save */
	UPROPERTY()
	bool IsCreativeModeEnabled;

	// @todosave: Add LastPlayDate as uint64 (Timestamp)
	// @todosave: Add if it's a autosave

	/** Store / load data */
	friend FArchive& operator<< ( FArchive& ar, FSaveHeader& header );

	/** Send/Receive over network */
	bool NetSerialize( FArchive& ar, class UPackageMap* map, bool& out_success );

	// The GUID for this custom version number
	inline static const FGuid GUID = FGuid( 0xC8C4A4F3, 0x3E26BC10, 0x53F8040C, 0x724A7A38 );
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

/** Wraps a FSessionSaveStruct in an UObject. Used for list views since they require an object per item */
UCLASS(BlueprintType)
class UFGSessionSaveStructWrapper : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY( BlueprintReadOnly )
	FSessionSaveStruct SessionSaveStruct;
};

/** Wraps a FSaveHeader in an UObject. Used for list views since they require an object per item */
UCLASS(BlueprintType)
class UFGSaveHeaderWrapper : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY( BlueprintReadOnly )
	FSaveHeader SaveHeader;
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams( FOnSaveManagerEnumerateSessionsComplete, bool, Success, const TArray<FSessionSaveStruct>&, Sessions, int32, CurrentSession );
DECLARE_DYNAMIC_DELEGATE_OneParam( FOnSaveMgrInterfaceDeleteSaveGameComplete, bool, Success );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnSaveMgrInterfaceSaveGameComplete, bool, Success, const FText&, ErrorMessage );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnSaveManagerTransferCompleted, bool, Success, const FText&, ErrorMessage );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FOnSaveManagerTransferProgress, int32, Progress, int32, Total );
DECLARE_DYNAMIC_DELEGATE( FOnSaveManagerRefreshSaves );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSaveManagerRefreshSavesMulti );

/** Parameters struct for IFGSaveManagerInterface::CreateNewGame */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FCreateNewGameParameters
{
	GENERATED_BODY()

	/** Name of the starting location on the map to spawn at */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "New Game Parameters" )
	FString StartingLocation;

	/** True if we should skip onboarding for this game */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "New Game Parameters" )
	bool bSkipOnboarding{false};

	/** Advanced game settings values provider */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "New Game Parameters" )
	TScriptInterface<IFGAdvancedGameSettingsInterface> AdvancedGameSettings;

	// Additional options to be passed as map options for creating a new game
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "New Game Parameters" )
	TMap<FString, FString> ExtraOptions;

	// Custom session settings (session metadata) that should be set immediately on session creation
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "New Game Parameters" )
	TArray< FCustomOnlineSessionSetting > InitialCustomSessionSettings;
};

/** Parameters struct for IFGSaveManagerInterface::LoadSaveFile */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FLoadSaveFileParameters
{
	GENERATED_BODY()

	/** True if we should load this save game with advanced game settings enabled */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Load Save File Parameters" )
	bool bEnableAdvancedGameSettings{false};
};

/**
 * Common entry point to the save system functionality
 */
UINTERFACE( BlueprintType, meta = ( CannotImplementInterfaceInBlueprint ) )
class FACTORYGAME_API UFGSaveManagerInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGSaveManagerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void EnumerateSessions( const FOnSaveManagerEnumerateSessionsComplete& CompleteDelegate ) = 0;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual bool IsEnumeratingLocalSaves() const = 0;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void DeleteSaveSession( const FSessionSaveStruct& Session, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate ) = 0;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void DeleteSaveFile( const FSaveHeader& SaveGame, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate ) = 0;

	/** Creates a new Game with the provided setting values. The implementation might require a player controller to be supplied to allow online travel. */
	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual USessionMigrationSequence* CreateNewGame( const FString& SessionName, const FSoftObjectPath& MapAssetName, const FCreateNewGameParameters& CreateNewGameParameters, APlayerController* Player ) = 0;

	/** Loads a save file with the provided setting values. The implementation might require a player controller to be supplied to allow online travel. */
	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual USessionMigrationSequence* LoadSaveFile( const FSaveHeader& SaveGame, const FLoadSaveFileParameters& LoadSaveFileParameters, APlayerController* Player ) = 0;

	/** True if this save manager supports online session creation settings (dedicated servers do not support the online functionality, for example) */
	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual bool SupportsOnlineSettings() const = 0;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void SaveGame( const FString& SaveName, FOnSaveMgrInterfaceSaveGameComplete CompleteDelegate ) = 0;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual bool IsSaveManagerAvailable() const = 0;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void UploadSave( const FSaveHeader& Save, FOnSaveManagerTransferCompleted CompleteDelegate, FOnSaveManagerTransferProgress ProgressDelegate );

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void DownloadSave( const FSaveHeader& SaveGame, FOnSaveManagerTransferCompleted CompleteDelegate, FOnSaveManagerTransferProgress ProgressDelegate );

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual bool IsTransferInProgress() const;

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void BindOnSavesChanged( const FOnSaveManagerRefreshSaves& OnRefreshSaves );

	UFUNCTION( BlueprintCallable, Category = "Save Manager" )
	virtual void UnbindOnSavesChanged( const FOnSaveManagerRefreshSaves& OnRefreshSaves );

protected:
	FOnSaveManagerRefreshSavesMulti mRefreshSavesDelegate;
};
