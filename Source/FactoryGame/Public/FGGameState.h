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

	FORCEINLINE void SetSessionName( const FString& inName ) { mReplicatedSessionName = inName; }

	/*
	 *	No need to be a ufunction, as it is only used to set a start state from loading so far, when the game loads on the server.
	 */
	void SetupColorSlots( const FColor *mColorSlotsPrimary, const FColor *mColorSlotsSecondary, const  uint8 startINdex, const uint8 writeCount );

	UFUNCTION( Reliable, Server, WithValidation )
	void SetAndReplicateBuildingColorInSlot( uint8 slot, FColor pColor, FColor sColor );
	FColor GetBuildingColorPrimary( uint8 slot );
	FColor GetBuildingColorSecondary( uint8 slot );
	uint8 GetNbColorSlotsExposedToPlayers();

	UFUNCTION()
	void OnRep_BuildingColorSlot();

	void ClaimPlayerColor( class AFGPlayerState* playerState );
	
	void ReleasePlayerColor( class AFGPlayerState* playerState );

	/** return true if we have picked up and item of the given item class and it is marked to be remembered when picked up */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Item" )
	bool IsItemEverPickedUp( TSubclassOf< class UFGItemDescriptor > itemClass ) const { return mPickedUpItems.Contains( itemClass ); }

	/** If the given item class is marked to be remembered when picked up we store it */
	void ItemPickedUp( TSubclassOf< class UFGItemDescriptor > itemClass );

	/** Set the planned restart in time seconds */
	void SetPlannedServerRestartWorldTime( float worldTimeSeconds );
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
	
	/** @todo @save 2019-02-26 If this is cleaned up alpha saves will lose recipes unlocked by other means than through schematics, i.e. probably alternate recipes. */
	UPROPERTY( SaveGame )
	TArray< TSubclassOf< UFGRecipe > > mAvailableRecipes; //_DEPRECATED

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

	/*
	 *	System to keep track of color slot changes and comapre to buildable system to update and mark dirty
	 */
	UPROPERTY( Replicated, ReplicatedUsing = OnRep_BuildingColorSlot, EditDefaultsOnly, Category = "Customization" )
	FFGBuildingColorSlotStruct mBuildingColorSlots[ BUILDABLE_COLORS_MAX_SLOTS ];

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