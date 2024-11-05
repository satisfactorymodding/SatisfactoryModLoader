// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGFactoryColoringTypes.h"
#include "FGGamePhaseManager.h"
#include "FGPlayerState.h"
#include "FGRemoteCallObject.h"
#include "FGResearchManager.h"
#include "FGSaveInterface.h"
#include "FGSchematic.h"
#include "FGSwatchGroup.h"
#include "FGUnlockSubsystem.h"
#include "GameFramework/GameState.h"
#include "LatentActions.h"
#include "FGGameState.generated.h"

class UOnlineUserInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FVisitedMapAreaDelegate, TSubclassOf< class UFGMapArea >, mapArea );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRestartTimeNotification, float, timeLeft );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAutoSaveTimeNotification, float, timeLeft );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAutoSaveFinished );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnTetrominoLeaderBoardUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPlayerStateSlotDataUpdated, class AFGPlayerState*, playerState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnClientSubsystemsIsValid );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnSessionNameChanged, const FString&, sessionName );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnCreativeModeEnabled, bool );

// Minigame struct for minigames like tetromino packaging game 
USTRUCT( BlueprintType )
struct FMiniGameResult
{
	GENERATED_BODY()
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	FString LevelName = {};
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	FString PlayerName = {};
	
	UPROPERTY( SaveGame, BlueprintReadWrite )
	int32 Points = 0;
};

// Handled RPC for game state. Previous RPCed Functions we're moved away from game state so this is empty now but leaving it here
// since I plan to use it for other things -K2
UCLASS()
class FACTORYGAME_API UFGGameStateRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGGameStateRemoteCallObject = false;

	static UFGGameStateRemoteCallObject* Get( UWorld* world );
	
	UFUNCTION( Server, Reliable )
	void Server_SetCreativeModeEnabled();

	UFUNCTION( Client, Reliable )
	void Client_SendAutoSaveTimeNotification( float timeLeft );

	UFUNCTION( Client, Reliable )
	void Client_SendAutoSaveFinishedNotification();

	UFUNCTION( Client, Reliable )
	void Client_SendRestartTimeNotification( float timeLeft );
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGGameState : public AGameState, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGGameState();

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject Interface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	// Begin AGameState interface
	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void AddPlayerState( class APlayerState* playerState ) override;
	virtual void RemovePlayerState( class APlayerState* playerState ) override;
	// End AGameState interface

	UFUNCTION()
	void OnPlayerStateSlotDataUpdated( class AFGPlayerState* playerState );
	
	/** Init function, for setting up all our subsystems and save system */
	virtual void Init();

	/** Check if subsystems are created or replicated */
	UFUNCTION( BlueprintPure, Category = "Subsystems" )
	bool AreClientSubsystemsValid() const;

	UFUNCTION()
	void CheckClientSubsystemsValid();

	/** Finds a free slot for a new player state */
	int32 FindFreeSlot( class AFGPlayerState* playerState );
	
	/** Is a trading post built? Works on both client and server */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trading Post" )
	bool IsTradingPostBuilt() const;

	/** Set if the trading post is built or not */
	FORCEINLINE void SetIsTradingPostBuilt( bool isTradingPostBuilt) { mIsTradingPostBuilt = isTradingPostBuilt; }

	/** Have we played the initial trading post land anim? */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Trading Post" )
	bool HasInitalTradingPostLandAnimPlayed() const;

	/** Set if the trading post is built or not */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Trading Post" )
	void SetHasInitalTradingPostLandAnimPlayed();

	/** Is a towtruck built? Works on both client and server */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Tow Truck" )
	bool IsSpaceElevatorBuilt() const;

	/** Set if the trading post is built or not */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Tow Truck" )
	void SetIsSpaceElevatorBuilt( bool isSpaceElevatorBuilt ) { mIsSpaceElevatorBuilt = isSpaceElevatorBuilt; }

	void SetProjectAssembly( class AFGProjectAssembly* projectAssembly );
	
	/** Returns the schematic manager */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Schematic", meta = ( DeprecatedFunction, DeprecationMessage = "Use global getter instead" ) )
	FORCEINLINE class AFGSchematicManager* GetSchematicManager() { return mSchematicManager; }

	/** Returns the game phase manager */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Game Phase", meta = ( DeprecatedFunction, DeprecationMessage = "Use global getter instead" ) )
	FORCEINLINE class AFGGamePhaseManager* GetGamePhaseManager() { return mGamePhaseManager; }

	/** Returns the research manager */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Research", meta = ( DeprecatedFunction, DeprecatedMessage = "Use global getter instead" ) )
	FORCEINLINE class AFGResearchManager* GetResearchManager() { return mResearchManager; }

	/** Returns the tutorial intro manager */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Tutorial Intro", meta = ( DeprecatedFunction, DeprecationMessage = "Use global getter instead" ) )
	FORCEINLINE class AFGTutorialIntroManager* GetTutorialIntroManager() { return mTutorialIntroManager; }

	// Native subsystem getters.
	FORCEINLINE class AFGRailroadSubsystem* GetRailroadSubsystem() const { return mRailroadSubsystem; }
	FORCEINLINE class AFGVehicleSubsystem* GetVehicleSubsystem() const { return mVehicleSubsystem; }
	FORCEINLINE class AFGCircuitSubsystem* GetCircuitSubsystem() const { return mCircuitSubsystem; }
	FORCEINLINE class AFGStorySubsystem* GetStorySubsystem() const { return mStorySubsystem; }
	FORCEINLINE class AFGRadioactivitySubsystem* GetRadioactivitySubsystem() const { return mRadioactivitySubsystem; }
	FORCEINLINE class AFGChatManager* GetChatManager() const { return mChatManager; }
	FORCEINLINE class AFGCentralStorageSubsystem* GetCentralStorageSubsystem() const { return mCentralStorageSubsystem; }
	FORCEINLINE class AFGRecipeManager* GetRecipeManager() const { return mRecipeManager; }
	FORCEINLINE class AFGMapManager* GetMapManager() const { return mMapManager; }
	FORCEINLINE class AFGUnlockSubsystem* GetUnlockSubsystem() const { return mUnlockSubsystem; }
	FORCEINLINE class AFGPipeSubsystem* GetPipeSubsystem() const { return mPipeSubsystem; }
	FORCEINLINE class AFGResourceSinkSubsystem* GetResourceSinkSubsystem() const { return mResourceSinkSubsystem; }
	FORCEINLINE class AFGItemRegrowSubsystem* GetItemRegrowSubsystem() const { return mItemRegrowSubsystem; }
	FORCEINLINE class AFGEventSubsystem* GetEventSubsystem() const { return mEventSubsystem; }
	FORCEINLINE class AFGWorldGridSubsystem* GetWorldGridSubsystem() const { return mWorldGridSubsystem; }
	FORCEINLINE class AFGDroneSubsystem* GetDroneSubsystem() const { return mDroneSubsystem; }
	FORCEINLINE class AFGStatisticsSubsystem* GetStatisticsSubsystem() const { return mStatisticsSubsystem; }
	FORCEINLINE class AFGSignSubsystem* GetSignSubsystem() const { return mSignSubsystem; }
	FORCEINLINE class AFGCreatureSubsystem* GetCreatureSubsystem() const { return mCreatureSubsystem; }
	FORCEINLINE class AFGScannableSubsystem* GetScannableSubsystem() const { return mScannableSubsystem; }
	FORCEINLINE class AFGBlueprintSubsystem* GetBlueprintSubsystem() const { return mBlueprintSubsystem; }
	FORCEINLINE class AFGGameRulesSubsystem* GetGameRulesSubsystem() const { return mGameRulesSubsystem; }
	FORCEINLINE class AFGIconDatabaseSubsystem* GetIconDatabaseSubsystem() const { return mIconDatabaseSubsystem; }
	FORCEINLINE class AFGWorldEventSubsystem* GetWorldEventSubsystem() const { return mWorldEventSubsystem; }
	FORCEINLINE class AFGTestManager* GetTestManager() const { return mTestManager; }
	
	FORCEINLINE class AFGProjectAssembly* GetProjectAssembly() const { return mProjectAssembly; }
	FORCEINLINE class AFGConveyorChainSubsystem* GetConveyorChainSubsystem() const { return mConveyorChainSubsystem; }

	/** Helper to access the actor representation manager */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Representation", meta = ( DeprecatedFunction, DeprecationMessage = "Use global getter instead" ) )
	FORCEINLINE class AFGActorRepresentationManager* GetActorRepresentationManager() const { return mActorRepresentationManager; }

	/** Gives you all the visited map areas on the current level */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Map Area" )
	void GetVisitedMapAreas( UPARAM( ref ) TArray< TSubclassOf< UFGMapArea > >& out_VisitedAreas );

	/** Returns true if any of the players has visited the passed area */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Map Area" )
	bool IsMapAreaVisisted( TSubclassOf< UFGMapArea > inArea );

	/** Adds a new map area if it previously was unvisited */
	void AddUniqueVisistedMapArea( TSubclassOf< UFGMapArea > mapArea );

	/** Called when a new map area has been added */
	UFUNCTION()
	void OnRep_MapAreaVisited();

	UFUNCTION()
	void OnRep_SessionName();

	/** Called on all players when any player enters a new map area. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Map Area", DisplayName = "OnNewMapAreaEntered" )
	FVisitedMapAreaDelegate MapAreaVisistedDelegate;

	/** Getter for NoCost */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat" )
	FORCEINLINE bool GetCheatNoCost() { return mCheatNoCost; }

	/** Getter for NoPower */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat" )
	FORCEINLINE bool GetCheatNoPower() { return mCheatNoPower; }

	/** Getter for NoFuel */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat" )
	FORCEINLINE bool GetCheatNoFuel() { return mCheatNoFuel; }

	/** Setter for no power */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat" )
	void SetCheatNoPower( bool noPower );
	
	/** Setter for no cost */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat" )
	void SetCheatNoCost( bool noCost );
	
	/** Setter for no fuel */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat" )
	void SetCheatNoFuel( bool noFuel );
	
	UFUNCTION()
	void NotifyPlayerAdded( class AFGCharacterPlayer* inPlayer );

	/** The total time that has been played, including previous saves 
	 * @note this will return wrong values between PreSave and PostSave.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	int32 GetTotalPlayDuration() const;
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Session" )
	FORCEINLINE FString GetSessionName() const { return mReplicatedSessionName; }

	void SetSessionName( const FString& inName );
	
	/*
	 * Called from buildable subsystem on load to apply saved color slot data
	 */
	void SetupColorSlots_Data( const TArray< FFactoryCustomizationColorSlot >& colorSlotsPrimary_Data );

	/*
	 * Server - Called to propogate Building Color Changes
	 */
	UFUNCTION( Reliable, Server )
	void Server_SetBuildingColorDataForSlot( uint8 slotIdx, FFactoryCustomizationColorSlot colorData );

	
	//////////////////////////////////////////////////////////////////////////
	/// Global Color Presets (Unrelated to color swatches / building colors

	/** Returns the color presets defined by CSS. These are not modifiable. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|GlobalColorPresets" )
	TArray< FGlobalColorPreset > GetStaticColorPresets() { return mStaticGlobalColorPresets; }

	/** Returns the colors preset array created by players. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|GlobalColorPresets" )
	TArray< FGlobalColorPreset > GetPlayerColorPresets() { return mPlayerGlobalColorPresets; }

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|GlobalColorPresets" )
	void RemovePlayerColorPresetAtIndex( int32 index );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|GlobalColorPresets" )
	void AddPlayerColorPreset( FText presetName, FLinearColor color );

	/// End Global Color Presets
	//////////////////////////////////////////////////////////////////////////

	/** Linear Color Getters */
	FLinearColor GetBuildingColorPrimary_Linear( uint8 slot );
	FLinearColor GetBuildingColorSecondary_Linear( uint8 slot );

	/* Server - Called to propogate building lighting color changes to buildable subsystem */
	UFUNCTION(BlueprintCallable, Server, Reliable, Category="FactoryGame|Buildable|Light")
	void Server_SetBuildableLightColorSlot( uint8 slotIdx, FLinearColor color );

	/** Color Data Getter */
	FFactoryCustomizationColorSlot GetBuildingColorDataForSlot( uint8 slot );

	/** Swatch Group Helper */
	UFUNCTION( BlueprintPure, Category="SwatchGroup" )
	TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch > GetCurrentSwatchForSwatchGroup( TSubclassOf< UFGSwatchGroup > swatchGroup );

	/** Called both on client and server. Apply primary color changes to the buildable subsystem*/
	UFUNCTION()
	void OnRep_BuildingColorSlot_Data();

	/** Called both on client and server when the buildable light color slots have been updated. Relays changes to buildable subsystem */
	UFUNCTION()
	void OnRep_BuildableLightColorSlots();

	void ClaimPlayerColor( class AFGPlayerState* playerState );
	
	void ReleasePlayerColor( class AFGPlayerState* playerState );

	/** return true if we have picked up and item of the given item class and it is marked to be remembered when picked up */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Item" )
	bool IsItemEverPickedUp( TSubclassOf< class UFGItemDescriptor > itemClass ) const { return mPickedUpItems.Contains( itemClass ); }

	/** If the given item class is marked to be remembered when picked up we store it */
	void ItemPickedUp( TSubclassOf< class UFGItemDescriptor > itemClass );

	/** Gets the Local date and time on the server */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|DateTime" )
    FDateTime GetServerLocalDateTime() const;
	
	/** Called both on client and server for syncing session visibility for connected players*/
	UFUNCTION()
	void OnRep_OnlineSessionVisibility();

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	bool IsCustomizerRecipeUnlocked();

	UFUNCTION( BlueprintPure, Category="FactoryGame|Customization" )
	TArray< FSwatchGroupData > GetSwatchGroupData() const { return mSwatchGroupDatum; }
	
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Customization" )
	void SetDefaultSwatchForBuildableGroup( TSubclassOf< class UFGSwatchGroup > swatchGroup, TSubclassOf< class UFGFactoryCustomizationDescriptor_Swatch> swatch );

	UFUNCTION( BlueprintCallable, Category = "Tetromino" )
	FORCEINLINE TArray< FMiniGameResult > GetTetrominoLeaderBoard() const {return mTetrominoLeaderBoard; }

	/** Add a tetromino result. If it's a new highscore on the given level it will be added to the leaderboard. */
	UFUNCTION( BlueprintCallable, Category = "Tetromino" )
	void AddTetrominoResult( const FMiniGameResult& newResult );

	UFUNCTION()
	void OnRep_TetrominoLeaderBoard();

	UFUNCTION()
	void OnRep_RecipeManager();
	
	FORCEINLINE FString GetPublicTodoList() const { return mPublicTodoList; }

	// No server RPC call per se but used with server rpc from player state to update server value and spread to clients so figuerd the naming was good to separate from the other SetPublicTodoList. 
	void Server_SetPublicTodoList( const FString& newTodoList );
	
	void SetPublicTodoList( const FString& newTodoList ) { mPublicTodoList = newTodoList; }

	UFUNCTION( BlueprintPure, Category = "Creative" )
	bool IsCreativeModeEnabled() const { return mIsCreativeModeEnabled; }

	// We only allow a one way transiton here. We can only go to creative mode from vanilla. Not the other way around. 
	UFUNCTION( BlueprintCallable, Category = "Creative" )
	void SetCreativeModeEnabled();

	UFUNCTION( BlueprintCallable, Category = "Players" )
	AFGPlayerState* FindPlayerStateForOnlineUser( UOnlineUserInfo* userInfo );

	void BroadcastAutoSaveTimeNotification( float timeLeft ) const;
	void BroadcastAutoSaveFinishedNotification() const;
	void BroadcastServerRestartTimeNotification( float timeLeft ) const;
private:
	UFUNCTION()
	void OnRep_CheatNoPower();

	UFUNCTION()
	void OnRep_CreativeModeEnabled();

	/** Helper to spawn subsystems. */
	template< class C >
	void SpawnSubsystem( C*& out_spawnedSubsystem, TSoftClassPtr< AFGSubsystem > spawnClass, FName spawnName )
	{
		if( out_spawnedSubsystem )
		{
			UE_LOG( LogGame, Error, TEXT( "AFGGameState::SpawnSubsystem failed for '%s', already spawned or loaded." ), *spawnName.ToString() );
			return;
		}

		if( spawnClass.IsNull() )
		{
			UE_LOG( LogGame, Error, TEXT( "AFGGameState::SpawnSubsystem failed for '%s', no class given." ), *spawnName.ToString() );
			return;
		}

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Name = spawnName;

		out_spawnedSubsystem = GetWorld()->SpawnActor< C >( spawnClass.LoadSynchronous(), spawnParams );
		fgcheck( out_spawnedSubsystem );
	}

	void SubmitNumPlayersTelemetry() const;
	void SubmitCheatTelemetry() const;

	void TryGiveStartingRecipes( class AFGCharacterPlayer* inPlayer );

public:
	//@todo When was this used last time? Cleanup?
	UPROPERTY( EditDefaultsOnly, Category = "Cheat" )
	float mTurboModeMultiplier;

	/** Broadcast a notification when we are about to autosave */
	UPROPERTY( BlueprintAssignable, Category = "Notification" )
	FOnAutoSaveTimeNotification mOnAutoSaveTimeNotification;

	/** Broadcast a notification when we are finished auto saving */
	UPROPERTY( BlueprintAssignable, Category = "Notification" )
	FOnAutoSaveFinished mOnAutoSaveFinished;

	/** Called at regular times when the restart time reaches specific thresholds */
	UPROPERTY( BlueprintAssignable, Category="Notification" )
	FOnRestartTimeNotification mOnRestartTimeNotification;

	/** Broadcast a notification when the tetromino leader board is updated */
	UPROPERTY( BlueprintAssignable, Category = "Tetromino" )
	FOnTetrominoLeaderBoardUpdated mOnTetrominoLeaderBoardUpdated;

	/** Broadcast a notification when a player state have updated the slot data (color) */
	UPROPERTY( BlueprintAssignable, Category = "SlotData")
	FOnPlayerStateSlotDataUpdated mOnPlayerStateSlotDataUpdated;

	/** Broadcast a notification when the session name changes. Works on server and client. */
	UPROPERTY( BlueprintAssignable )
	FOnSessionNameChanged OnSessionNameChanged;

	FOnCreativeModeEnabled OnCreativeModeEnabled;

	/** Broadcast a notification when all subssytems are valid on client */
	UPROPERTY()
	FOnClientSubsystemsIsValid mOnClientSubsystemsValid;

private:
	/** Spawned subsystems */
	UPROPERTY( SaveGame, Replicated )
	class AFGStorySubsystem* mStorySubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGRailroadSubsystem* mRailroadSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGCircuitSubsystem* mCircuitSubsystem;
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_RecipeManager )
	class AFGRecipeManager* mRecipeManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGSchematicManager* mSchematicManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGGamePhaseManager* mGamePhaseManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGResearchManager* mResearchManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGTutorialIntroManager* mTutorialIntroManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGActorRepresentationManager* mActorRepresentationManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGMapManager* mMapManager;
	UPROPERTY()
	class AFGRadioactivitySubsystem* mRadioactivitySubsystem;
	UPROPERTY( Replicated )
	class AFGChatManager* mChatManager;
	UPROPERTY( SaveGame, Replicated )
	class AFGCentralStorageSubsystem* mCentralStorageSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGPipeSubsystem* mPipeSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGUnlockSubsystem* mUnlockSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGResourceSinkSubsystem* mResourceSinkSubsystem;
	UPROPERTY()
	class AFGItemRegrowSubsystem* mItemRegrowSubsystem;
	UPROPERTY( Replicated )
	class AFGVehicleSubsystem* mVehicleSubsystem;
	UPROPERTY( Replicated )
	class AFGEventSubsystem* mEventSubsystem;
	UPROPERTY()
	class AFGWorldGridSubsystem* mWorldGridSubsystem;
	UPROPERTY( Replicated )
	class AFGDroneSubsystem* mDroneSubsystem;
	UPROPERTY( SaveGame )
	class AFGStatisticsSubsystem* mStatisticsSubsystem;
	UPROPERTY( Replicated )
	class AFGSignSubsystem* mSignSubsystem;
	UPROPERTY( Replicated )
	class AFGCreatureSubsystem* mCreatureSubsystem;
	UPROPERTY( Replicated )
	class AFGScannableSubsystem* mScannableSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGBlueprintSubsystem* mBlueprintSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGGameRulesSubsystem* mGameRulesSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGIconDatabaseSubsystem* mIconDatabaseSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGWorldEventSubsystem* mWorldEventSubsystem;
	UPROPERTY()
	class AFGTestManager* mTestManager;

	UPROPERTY( SaveGame, Replicated )
	class AFGProjectAssembly* mProjectAssembly;
	UPROPERTY( Replicated )
	class AFGConveyorChainSubsystem* mConveyorChainSubsystem;
	
	/** This array keeps track of what map areas have been visited this game */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_MapAreaVisited )
	TArray< TSubclassOf< UFGMapArea > > mVisitedMapAreas;
	
	/** All items we have picked up that also are relevant to know if we picked up */
	UPROPERTY( SaveGame, Replicated )
	TArray<TSubclassOf< class UFGItemDescriptor>> mPickedUpItems;

	/** The total play time when loaded this save */
	UPROPERTY( SaveGame, Replicated )
	int32 mPlayDurationWhenLoaded;

	UPROPERTY( SaveGame, Replicated )
	FString mReplicatedSessionName;
	
	UPROPERTY( ReplicatedUsing = OnRep_BuildingColorSlot_Data, EditDefaultsOnly, Category = "Customization" )
	TArray< FFactoryCustomizationColorSlot > mBuildingColorSlots_Data;

	/** The player adjustable color slots used by the buildable lights. We store it here instead of buildable subsystem since that subsystem isn't replicated */ 
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_BuildableLightColorSlots )
	TArray< FLinearColor > mBuildableLightColorSlots;

	/** Predefined Colors by CSS. These cannot be modified. Allow players to quickly retrieve popular colors */
	UPROPERTY( EditDefaultsOnly )
	TArray< FGlobalColorPreset > mStaticGlobalColorPresets;

	/** Customizable Global Color Presets. Players can add / remove */
	UPROPERTY( SaveGame, EditDefaultsOnly, Replicated )
	TArray< FGlobalColorPreset > mPlayerGlobalColorPresets;
	
	/** Data to map a SwatchGroup to the Color Swatch it should use when building buildables of that type */
	UPROPERTY( SaveGame, EditDefaultsOnly, Replicated )
	TArray< FSwatchGroupData > mSwatchGroupDatum;

	/** Data to use if mSwatchGroupDatum is found to be corrupted on PostLoadGame. This is mainly for use to fix an Experimental crash happening before BU5 release. */
	UPROPERTY( EditDefaultsOnly )
	TArray< FSwatchGroupData > mSwatchGroupFallbackDatum;

	/** 
	 * The schematic that allows for the opening of the customizer menu.
	 * This is a special input gate lock so its not done through the input gate locking and will just check against this recipe
	 */
	UPROPERTY( EditDefaultsOnly, Category="Customization")
	TSoftClassPtr< class UFGSchematic > mUnlockCustomizerSchematic;

	/** Track whether or not colors have been initialized by the subsystem. This is here to support an old legacy save issue */
	bool mHasInitializedColorSlots;

	/** The different colors to represent players over the network. We keep this if we need to loop back over the colors again*/
	TArray< FPlayerColorData > mPlayerColors;

	/** The remaining colors to represent players over the network */
	TArray< FPlayerColorData > mAvailablePlayerColors;

	// @todoadmin: Add delegates to hook up if the player become a administrator

	/** Cheat bool for having no cost for stuff  */
	UPROPERTY( SaveGame, Replicated )
	bool mCheatNoCost;

	/** Cheat bool for not requiring power */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_CheatNoPower )
	bool mCheatNoPower;

	/** Cheat bool for not requiring fuel */
	UPROPERTY( SaveGame, Replicated )
	bool mCheatNoFuel;
	
	/** There can only be one trading post in the game, so we keep track it here so that we also can replicate it to client */
	UPROPERTY( SaveGame, Replicated )
	bool mIsTradingPostBuilt;

	/** The first time you build a trading post we want the landing animation to play */
	UPROPERTY( SaveGame, Replicated )
	bool mHasInitalTradingPostLandAnimPlayed;

	/** There can only be one tow truck in the game, so we keep track it here so that we also can replicate it to client */
	UPROPERTY( SaveGame, Replicated )
	bool mIsSpaceElevatorBuilt;

	/** The local date and time on the server represented in ticks at the time of the init of this game state. */
	UPROPERTY( Replicated )
	int64 mServerLocalDateTimeTicksAtInit;

	// @todok2 Might want to move this to a separate system like statistics subsystem or something.
	/** The leaderboard for tetromino mini game */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_TetrominoLeaderBoard )
	TArray< FMiniGameResult > mTetrominoLeaderBoard;

	/** The public todo list. Only replicated on initial send. Then RPCed through FGPlayerState. */
	UPROPERTY( SaveGame, Replicated )
	FString mPublicTodoList;
	
	/** If we have given the first player that joins the starting recipes or not. Based on which tier you start on */
	UPROPERTY( SaveGame )
	bool mHasGivenStartingRecipes = false;

	/** If the player have enabled creative mode for this game. This means they can change settings in advanced game settings menu */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CreativeModeEnabled )
	bool mIsCreativeModeEnabled = false;
	
};
