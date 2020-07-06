// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSaveInterface.h"
#include "GameFramework/GameState.h"
#include "FGPlayerState.h"
#include "FGGamePhaseManager.h"
#include "FGResearchManager.h"
#include "FGBuildingColorSlotStruct.h"
#include "BuildableColorSlotBase.h"
#include "FGUnlockSubsystem.h"
#include "FGGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FVisitedMapAreaDelegate, TSubclassOf< class UFGMapArea >, mapArea );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRestartTimeNotification, float, timeLeft );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAutoSaveTimeNotification, float, timeLeft );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAutoSaveFinished );

extern const wchar_t STARTUP_TEMP_ID_PREFIX[];
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
	virtual void Tick( float delta ) override;
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
	// End AGameState interface

	/** Init function, for setting up all our subsystems and save system */
	virtual void Init();

	/** Check if subsystems are created or replicated */
	bool AreClientSubsystemsValid();

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
	FORCEINLINE class AFGTimeOfDaySubsystem* GetTimeSubsystem() const { return mTimeSubsystem; }
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

	/** Called on all players when any player enters a new map area. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Map Area", DisplayName = "OnNewMapAreaEntered" )
	FVisitedMapAreaDelegate MapAreaVisistedDelegate;

	/** Getter for Hub Part Class */
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetHubPartClass() { return mHubPartClass;  }

	/** Getter for if the Hub part is needed on spawn */
	FORCEINLINE bool GetForceAddHubPartOnSpawn() { return mForceAddHubPartOnSpawn; }

	/** Setter for force adding Hub part on spawn*/
	FORCEINLINE void SetForceAddHubPartOnSpawn( bool forceAdd ) { mForceAddHubPartOnSpawn = forceAdd;  }

	/** Getter for NoCost */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat" )
	FORCEINLINE bool GetCheatNoCost() { return mCheatNoCost; }

	/** Getter for NoPower */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Cheat" )
	FORCEINLINE bool GetCheatNoPower() { return mCheatNoPower; }

	/** Setter for no power */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat" )
	void SetCheatNoPower( bool noPower ) { mCheatNoPower = noPower; }
	
	/** Setter for no cost */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Cheat" )
	void SetCheatNoCost( bool noCost ) { mCheatNoCost = noCost; }

	UFUNCTION()
	void NotifyPlayerAdded( class AFGCharacterPlayer* inPlayer );

	/** Sends message to all players, will only be called on clients */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Message" )
	void SendMessageToAllPlayers( TSubclassOf< class UFGMessageBase > inMessage );

	/** Sends message to specified player, will only be called on clients */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Message" )
	void SendMessageToPlayer( TSubclassOf< class UFGMessageBase > inMessage, class APlayerController* controller );

	/** The total time that has been played, including previous saves 
	 * @note this will return wrong values between PreSave and PostSave.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	int32 GetTotalPlayDuration() const;
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Session" )
	FORCEINLINE FString GetSessionName() const { return mReplicatedSessionName; }

	void SetSessionName( const FString& inName );
	
	FString GenerateOnlineSessionName();

	UFUNCTION(BlueprintPure, Category = "FactoryGame|Session")
	FString GetOnlineSessionName() const;

	UFUNCTION(BlueprintCallable, Category = "FactoryGame|Session")
	void SetOnlineSessionName( const FString& inName );

	/*
	 * Called from buildable subsystem on load to apply saved color slot data
	 */
	void SetupColorSlots_Linear( const TArray<FLinearColor>& mColorSlotsPrimary, const TArray<FLinearColor>& mColorSlotsSecondary );

	/*
	 * Server - Called to propogate Building Color Changes
	 */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_SetBuildingColorInSlotLinear( uint8 slotIdx, FLinearColor colorPrimary_Linear, FLinearColor colorSecondary_Linear );

	uint8 GetNbColorSlotsExposedToPlayers();

	/** Linear Color Getters */
	FLinearColor GetBuildingColorPrimary_Linear( uint8 slot );
	FLinearColor GetBuildingColorSecondary_Linear( uint8 slot );

	/** Called both on client and server. Apply primary color changes to the buildable subsystem*/
	UFUNCTION()
	void OnRep_BuildingColorSlotPrimary_Linear();

	/** Called both on client and server. Apply secondary color changes to the buildable subsystem*/
	UFUNCTION()
	void OnRep_BuildingColorSlotSecondary_Linear();

	void ClaimPlayerColor( class AFGPlayerState* playerState );
	
	void ReleasePlayerColor( class AFGPlayerState* playerState );

	/** return true if we have picked up and item of the given item class and it is marked to be remembered when picked up */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Item" )
	bool IsItemEverPickedUp( TSubclassOf< class UFGItemDescriptor > itemClass ) const { return mPickedUpItems.Contains( itemClass ); }

	/** If the given item class is marked to be remembered when picked up we store it */
	void ItemPickedUp( TSubclassOf< class UFGItemDescriptor > itemClass );

	/** Set the planned restart in time seconds */
	void SetPlannedServerRestartWorldTime( float worldTimeSeconds );
	
	/** Called both on client and server for syncing session names for connected players*/
	UFUNCTION()
	void OnRep_OnlineSessionName();

	/** Called both on client and server for syncing session visibility for connected players*/
	UFUNCTION()
	void OnRep_OnlineSessionVisibility();
private:
	/** Check the restart time of server and restart it and notify clients of the countdown */
	void CheckRestartTime();

	/** Restart time has been replicated, recheck if the time has been updated */
	UFUNCTION()
	void OnRep_PlannedRestartTime();

	/** Helper to spawn subsystems. */
	template< class C >
	void SpawnSubsystem( C*& out_spawnedSubsystem, TSubclassOf< AFGSubsystem > spawnClass, FName spawnName )
	{
		if( out_spawnedSubsystem )
		{
			UE_LOG( LogGame, Error, TEXT( "AFGGameState::SpawnSubsystem failed for '%s', already spawned or loaded." ), *spawnName.ToString() );
			return;
		}

		if( !IsValid( spawnClass ) )
		{
			UE_LOG( LogGame, Error, TEXT( "AFGGameState::SpawnSubsystem failed for '%s', no class given." ), *spawnName.ToString() );
			return;
		}

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Name = spawnName;

		out_spawnedSubsystem = GetWorld()->SpawnActor< C >( spawnClass, spawnParams );
		check( out_spawnedSubsystem );
	}

public:
	//@todo When was this used last time? Cleanup?
	UPROPERTY( EditDefaultsOnly, Category = "Cheat" )
	float mTurboModeMultiplier;

	/** Message sent when a power fuse is triggered occurs. */
	UPROPERTY( EditDefaultsOnly, Category = "Message" )
	TSubclassOf< class UFGMessageBase > mPowerCircuitFuseTriggeredMessage;

	/** Broadcast a notification when we are about to autosave */
	UPROPERTY( BlueprintAssignable, Category = "Notification" )
	FOnAutoSaveTimeNotification mOnAutoSaveTimeNotification;

	/** Broadcast a notification when we are finished auto saving */
	UPROPERTY( BlueprintAssignable, Category = "Notification" )
	FOnAutoSaveFinished mOnAutoSaveFinished;

private:
	/** Spawned subsystems */
	UPROPERTY( SaveGame, Replicated )
	class AFGTimeOfDaySubsystem* mTimeSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGStorySubsystem* mStorySubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGRailroadSubsystem* mRailroadSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGCircuitSubsystem* mCircuitSubsystem;
	UPROPERTY( SaveGame, Replicated )
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
	UPROPERTY()
	class AFGCentralStorageSubsystem* mCentralStorageSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGPipeSubsystem* mPipeSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGUnlockSubsystem* mUnlockSubsystem;
	UPROPERTY( SaveGame, Replicated )
	class AFGResourceSinkSubsystem* mResourceSinkSubsystem;
	UPROPERTY()
	class AFGItemRegrowSubsystem* mItemRegrowSubsystem;
	UPROPERTY()
	class AFGVehicleSubsystem* mVehicleSubsystem;

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
	
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_OnlineSessionName)
	FString mReplicatedOnlineSessionName = "Auto"; //A value of auto should be evaluated to a generated name on first use/at session creation

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_OnlineSessionVisibility)
	int8 mReplicadedOnlineNumPubliclConnections = 0; 

	/*
	 *	Array of primary building color slots as Linear Colors. Note: This used to be handled with FColor which resulted in unneeded conversions back and forth
	 */
	UPROPERTY( ReplicatedUsing = OnRep_BuildingColorSlotPrimary_Linear, EditDefaultsOnly, Category = "Customization" )
	TArray<FLinearColor> mBuildingColorSlotsPrimary_Linear;

	/*
	 *	Array of secondary building color slots as Linear Colors. Note: This used to be handled with FColor which resulted in unneeded conversions back and forth
	 */
	UPROPERTY( ReplicatedUsing = OnRep_BuildingColorSlotSecondary_Linear, EditDefaultsOnly, Category = "Customization" )
	TArray<FLinearColor> mBuildingColorSlotsSecondary_Linear;

	/** Track whether or not colors have been initialized by the subsystem. This is here to support an old legacy save issue */
	bool mHasInitializedColorSlots;

	/** The different colors to represent players over the network. We keep this if we need to loop back over the colors again*/
	TArray< FSlotData > mPlayerColors;

	/** The remaining colors to represent players over the network */
	TArray< FSlotData > mAvailablePlayerColors;

	/** Next time the server is planned to restart */
	UPROPERTY( VisibleInstanceOnly, Replicated, ReplicatedUsing = OnRep_PlannedRestartTime, Category="Server" )
	float mPlannedRestartTime;

	float mLastRestartTimeCheck;

	/** Called at regular times when the restart time reaches specific thresholds */
	UPROPERTY( BlueprintAssignable, Category="Notification" )
	FOnRestartTimeNotification mOnRestartTimeNotification;

	// @todoadmin: Add delegates to hook up if the player become a administrator

	/** Class used to construct the hub, this is used to guarantee players always have one if they don't have a hub */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UFGItemDescriptor > mHubPartClass;

	/** Track if a hub part is needed for adding to player inventory when they respawn */
	UPROPERTY( SaveGame )
	bool mForceAddHubPartOnSpawn;

	/** Cheat bool for having no cost for stuff  */
	UPROPERTY( SaveGame, Replicated )
	bool mCheatNoCost;

	/** Cheat bool for not requiring power */
	UPROPERTY( SaveGame, Replicated )
	bool mCheatNoPower;
	
	/** There can only be one trading post in the game, so we keep track it here so that we also can replicate it to client */
	UPROPERTY( SaveGame, Replicated )
	bool mIsTradingPostBuilt;

	/** The first time you build a trading post we want the landing animation to play */
	UPROPERTY( SaveGame, Replicated )
	bool mHasInitalTradingPostLandAnimPlayed;

	/** There can only be one tow truck in the game, so we keep track it here so that we also can replicate it to client */
	UPROPERTY( SaveGame, Replicated )
	bool mIsSpaceElevatorBuilt;


public:
	FORCEINLINE ~AFGGameState() = default;
};