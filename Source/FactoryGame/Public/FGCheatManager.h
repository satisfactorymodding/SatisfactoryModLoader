// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/CheatManager.h"
#include "FGGamePhaseManager.h"
#include "Interfaces/OnlineSharedCloudInterface.h"
#include "FGCheatManager.generated.h"


UCLASS( Within = PlayerController, Config = Editor )
class FACTORYGAME_API UFGCheatManager : public UCheatManager
{
	GENERATED_BODY()
public:
	virtual void InitCheatManager() override;

	// Begin UObject interface
	virtual bool IsSupportedForNetworking() const override;
	virtual int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;
	virtual bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;
	// End UObject interface

	// For networking support
	virtual bool ReplicateSubobjects(class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags);

	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	virtual void NoCost( bool enabled );

	UFUNCTION( exec, CheatBoard )
	virtual bool NoCost_Get();

	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	virtual void NoPower( bool enabled );

	UFUNCTION( exec, CheatBoard)
	virtual bool NoPower_Get();

	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	virtual void NoFuel( bool enabled );

	UFUNCTION( exec, CheatBoard )
	virtual bool NoFuel_Get();

	UFUNCTION( exec, CheatBoard, Category = "GUI" )
	virtual void NoMessages( bool enabled );

	UFUNCTION( exec, CheatBoard )
	virtual bool NoMessages_Get();

	UFUNCTION( exec, CheatBoard, Category = "World/Time" )
	virtual void TurboBuildMode( bool enabled );

	UFUNCTION( exec, CheatBoard )
	virtual bool TurboBuildMode_Get();

	UFUNCTION( exec, CheatBoard, Category = "World/Time" )
	virtual void TurboProductionMode( bool enabled );

	UFUNCTION( exec, CheatBoard, Category = "World/Time" )
	virtual bool TurboMode_Get();

	UFUNCTION( exec, CheatBoard, Category = "Resources:-2", meta = ( ToolTip="Give the number of full item stacks specified. Will expand inventory if needed. Becareful with too high numbers.") )
	virtual void GiveItemStacks( TSubclassOf< class UFGItemDescriptor > resource, int32 NumberOfStacks );

	UFUNCTION( exec, CheatBoard, Category = "Resources:-1", meta = ( ToolTip="Give the number of items specified." ))
	virtual void GiveItemsSingle( TSubclassOf< class UFGItemDescriptor > resource, int32 NumberOfItems );

	UFUNCTION( exec, CheatBoard, Category = "Resources", meta = ( ToolTip = "Give the number of coupons specified" ) )
	virtual void GiveResourceSinkCoupons( int32 NumCoupons );

	UFUNCTION( exec, CheatBoard, category = "Player" )
	void DrawSphere( int32 radius );

	UFUNCTION( exec, CheatBoard, Category = "Player/Camera" )
	virtual void PlayerFly( bool flyModeEnabled );
	
	UFUNCTION( exec, CheatBoard, Category = "Cheat Manager" )
	virtual void PlayerAllFly( bool flyModeEnabled);

	UFUNCTION( exec, CheatBoard, Category = "Cheat Manager" )
	virtual bool PlayerAllFly_Get();

	UFUNCTION( exec, CheatBoard, Category = "Player/Camera" )
	virtual bool PlayerFly_Get();

	UFUNCTION( exec, CheatBoard, Category = "Player/Camera" )
	virtual void PlayerNoClipModeOnFly( bool ghostMode );
	UFUNCTION( exec, CheatBoard, Category = "Player/Camera" )
	virtual bool PlayerNoClipModeOnFly_Get();

	UFUNCTION( exec )
	virtual void ClearGiveItemPopularList();
	
	UFUNCTION( exec, CheatBoard, category = "Research" )
	virtual void GiveAllSchematics();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveAllSchematicsAndPhases();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	virtual void GiveAvailableSchematics();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	virtual void GiveActiveMilestoneSchematic();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	virtual void GiveCheatSchematics();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	virtual void GivePrototypeSchematics();

	UFUNCTION( exec, CheatBoard )
	virtual void GiveStorySchematics();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveStartingResearch();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveAllResearchTrees();

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void TriggerNextPrimaryStoryMessageInQueue();

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void TriggerNextSecondaryStoryMessageInQueue( int32 storyQueueIndex = 0 );

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void TriggerNextFloatingMessageInPrimaryQueue();

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void TriggerRandomTriggeredBarksMessage();

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void StartNextStoryQueue();

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void ResetAllStoryQueues();

	UFUNCTION( exec, CheatBoard, category = "Story" )
	void ResetCurrentStoryQueue();
	
	UFUNCTION( exec, CheatBoard, category = "Factory|Uncommon" )
	virtual void RebuildPowerCircuits();

	UFUNCTION( exec, CheatBoard, category = "Factory|Uncommon" )
	void EnableBuildableTick( bool enable );

	UFUNCTION( exec, CheatBoard, category = "Factory|Uncommon" )
	bool EnableBuildableTick_Get();

	/** Cheat for disabling the players fov override if we want to get the fov from cameras in world */
	UFUNCTION( exec, category = "Player/Camera" )
	void EnablePlayerFOV( bool enable );

	UFUNCTION( exec, category = "Player/Camera" )
	bool EnablePlayerFOV_Get();
	
	UFUNCTION( exec, category = "Player/Camera" )
	void DestroyPawn();

	UFUNCTION( exec )
	void RemoveAllFoliage( int32 maxNumInstances = 999999 );

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	virtual void PardonAllPlayers();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	virtual void ClearPardon();

	UFUNCTION( exec, CheatBoard, category = "World/Time" )
	void SetTimeOfDay( int32 hour, int32 minute = 0 );

	UFUNCTION( exec, CheatBoard, category = "World/Time" )
    void SetTimeSpeedMultiplierResetTime( int32 resetHour );

	UFUNCTION( exec, CheatBoard, category = "World/Time" )
	int32 SetTimeOfDay_hour_Get();

	UFUNCTION( exec, CheatBoard, category = "World/Time" )
	int32 SetTimeOfDay_minute_Get();

	UFUNCTION( exec, CheatBoard, category = "World/Planets" )
	void SetPlanetPosition( float value );

	UFUNCTION( exec, CheatBoard, category = "World/Planets" )
	void SetPlanetPositionDeg( int32 value );

	UFUNCTION( exec, CheatBoard, category = "World/Planets" )
	void SetPlanetMovementEnabled( bool enabled );

	UFUNCTION( exec, CheatBoard, category = "World/Planets" )
	void SetPlanetSpeedMultiplier( float multiplier );

	/** Hide everything except the factory */
	UFUNCTION( exec, CheatBoard, category = "Display" )
	void ShowFactoryOnly( bool environmentHidden );

	UFUNCTION( exec, CheatBoard, category = "Display" )
	bool ShowFactoryOnly_Get();

	/** Hide everything the factory */
	UFUNCTION( exec, CheatBoard, category = "Display" )
	void HideFactoryOnly( bool factoryHidden );

	UFUNCTION( exec, CheatBoard, category = "Display" )
	bool HideFactoryOnly_Get();
	
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpAllAvailableRecipes();

	UFUNCTION( exec, CheatBoard, category = "Audio" )
	void EnableAudioDebug(bool isEnabled);

	UFUNCTION( exec, category = "Audio" )
	void ToggleAudioDebug();

	UFUNCTION( exec, CheatBoard, category = "World/Time" )
	void SetSlomo( float slomo );

	UFUNCTION( exec )
	void OpenModMap();

	UFUNCTION( exec, CheatBoard, category = "GUI" )
	void PumpiMode( bool enable );
	UFUNCTION( exec, CheatBoard, category = "GUI" )
	void HiddenHUDMode( bool enable );

	UFUNCTION( exec, CheatBoard, category = "GUI" )
	bool PumpiMode_Get();
	
	UFUNCTION( exec, category = "Factory" )
	void SplitAllConveyors();

	UFUNCTION( exec, category = "Factory" )
	void MergeAllConveyors();

	UFUNCTION( exec, CheatBoard ) 
	void SetTimeSpeedMultiplier( float speed );

	UFUNCTION( exec )
	void SetFactoryDetailReplication( bool enable );

	UFUNCTION( exec )
	bool SetFactoryDetailReplication_Get();

	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void ResetFuses();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void ToggleCameraMode();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_ToggleAdvancedPhotoMode();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_SetManualFocusDistance( float manualFocusDistance );

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_FocusTrackLookedAtObject();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_SetAperture( float aperture );

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_ToggleDebug();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_ResetToDefault();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_AddCurrentPlayerPosAndRot();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_PlaySequence();

	UFUNCTION( exec, CheatBoard, category = "Player/Camera" )
	void Photo_ToggleSequencer();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveSchematicsOfTier( int32 tier );

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetGamePhase( EGamePhase phase );
	
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetNextGamePhase();

	UFUNCTION( exec )
	void TestSharedInventoryPtr();

	/** Forces active spawners to spawn creatures even if the creature isn't set to spawn yet ( because of day/night restrictions etc ) */
	UFUNCTION( exec, CheatBoard, category = "World/Time" )
	void ForceSpawnCreatures();

	UFUNCTION( exec, CheatBoard ,category = "Log" )
	void DumpNonDormantActors();

	UFUNCTION( exec, CheatBoard, category = "Audio" )
	void ToggleAudioLandingDebug();

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpAttachedToSkelMesh( bool detailed = false );

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpTicking( bool detailed = false );
	
	/** Dump all GPU particles systems that's available */
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpActiveGPUParticles();

	/** Starts replaying buildeffects */
	UFUNCTION( exec )
	void ReplayBuildingEffects();

	/** Sets visibility on all buildings */
	UFUNCTION( exec, CheatBoard, category = "Display" )
	void HideAllBuildings( bool inVisibility );

	UFUNCTION( exec, CheatBoard, category = "Display" )
	bool HideAllBuildings_Get();

	/** Randomize building color slot color */
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void RandomizeBuildingsColorSlot( uint8 slotIndex = 0);

	UFUNCTION( exec )
	void UpdateSessionToOSS();

	UFUNCTION( exec )
	void VisitAllMapAreas();

	UFUNCTION( exec, CheatBoard )
	void RevealMap();

	UFUNCTION( exec, CheatBoard )
	void HideMap();

	UFUNCTION( exec, CheatBoard, category = "World/Time" )
	void SetAITickDistance( float distance );

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpPlayerStates();

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpHotbarShortcuts();

	UFUNCTION( exec, CheatBoard, category = "Display" )
	void EnableInstancingOnFactory( bool enabled );

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpActorRepresentations();

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpSignificanceManagedObjects();

	UFUNCTION( exec, CheatBoard, category = "Save/Load" )
	void PurgeInactiveClientsFromSave( bool fetchInventories );

	UFUNCTION( exec, CheatBoard, category = "Save/Load" )
	void PurgeAllBeaconsFromSave();

	UFUNCTION( exec, CheatBoard, category = "Save/Load" )
	void PurgeDeathMarkersFromSave();

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void ListItemPickups();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetTradingPostLevel( int32 inLevel );

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void ListUnlockedRecipesAndSchematics();

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void GetVehicleInfo();

	UFUNCTION( exec )
	void RunDebugMetric();

	UFUNCTION( exec )
	void MCP_Login( FString username, FString password );

	UFUNCTION( exec )
	void MCP_Logout();

	UFUNCTION( exec )
	void MCP_GetOnlineStatus( int32 localPlayerNum = 0 );

	UFUNCTION( exec )
	void MCP_UpdatePresence( FString key, FString value );

	UFUNCTION( exec )
	void MCP_UpdatePresenceString( FString string );

	UFUNCTION( exec )
	void MCP_LogPresence();

	UFUNCTION( exec )
	void MCP_GetFriends();

	UFUNCTION( exec )
	void TriggerPresenceUpdate();

	UFUNCTION( exec )
	void ShowSequenceList();

	UFUNCTION( exec )
	void SendInviteToFriend( FString friendName );

	UFUNCTION( exec )
	void ResetHubTutorial();

	UFUNCTION( exec )
	void ResetSchematics();

	UFUNCTION( exec, CheatBoard, category = "Research" )
	void ResetRecipes();

	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpSchematics();

	UFUNCTION( exec )
	void PrintStaticMeshesHierarchy();

	UFUNCTION( exec )
	void FlipVehicle();

	UFUNCTION( exec )
	void ResetVehicleDeadlocks();

	UFUNCTION( exec )
	void ResetTheChosenWheeledVehicle();

	UFUNCTION( exec )
	void ListDebugStartingPoint();
	
	UFUNCTION( exec )
	void SetDebugStartingPoint( FName startingPoint );
	
	UFUNCTION( exec )
	void SetRandomDebugStartingPoint();

	UFUNCTION( exec )
	void CompleteResearch();

	UFUNCTION( exec )
	void PurgeAllTrainState();

	UFUNCTION( exec )
	void ResetAllFactoryLegsToZero( bool repopulateEmptyLegs );

	UFUNCTION( exec )
	void RebuildFactoryLegsOneTileAroundPlayer();

	UFUNCTION( exec )
	void ResetGamePhases();

	UFUNCTION( exec )
	void DumpGamePhases();

	UFUNCTION( exec )
	void ToggleTrainSelfDriving();

	UFUNCTION( exec )
	void PipeFillFirstInEachNetwork();

	UFUNCTION( exec )
	void PipeEmptyAll();

	UFUNCTION( exec )
	void PipeResetAll();
	
	UFUNCTION( exec )
	void PipePrintMinSizes();

	UFUNCTION( exec )
    void PipeSetVerboseLoggingOnAimedFluidBox( bool enabled );

	UFUNCTION( exec )
	void PipeEnableProbingOnAimedIntegrant();
	
	UFUNCTION( exec )
    void PipeDisableProbingOnAimedIntegrant();

	UFUNCTION( exec )
    void PipeClearProbingOnAllPipe();

	UFUNCTION( exec )
    void PipeAddSelectedNetworkToDisplayDebugList();

	UFUNCTION( exec )
    void PipeClearDisplayDebugList();

	UFUNCTION( exec )
	void PipePrintTweakables();
	
	UFUNCTION( exec )
	void PipeTweakMaximumFlow( float rate );

	UFUNCTION( exec )
    void PipeTweakMinimumMaxContent( float minimumMaxContent, bool keepRelativeContent );
	
	UFUNCTION( exec )
	void PipeTweakPressureLoss( float pressureLoss );

	UFUNCTION( exec )
	void PipeTweakOverfill( float maxOverfillPct, float maxOverfillForPressure );

	UFUNCTION( exec )
    void PipeTweakGravity( float gravity );
	
	UFUNCTION( exec )
	void PipeTweakFluidFriction( float fluidFriction );

	UFUNCTION( exec )
    void PipeTweakFluidDensity( float fluidDensity );

	UFUNCTION( exec )
    void PipeTweakFluidViscosity( float fluidViscosity );

	/** Duplicate a component within a circuit so it contains multiple entries for the same component. */
	UFUNCTION( exec )
	void DupeComponentInCircuit( int32 target );
	/** Duplicate a component from one circuit to another circuit so they contain the same component. */
	UFUNCTION( exec )
	void DupeComponentToAnotherCircuit( int32 source, int32 target );

	UFUNCTION( exec )
	void DumpConnectionString();

	UFUNCTION( exec )
	void FillAllFreightCars( float pct = 1.f );
	UFUNCTION( exec )
    void EmptyAllFreightCars();

	UFUNCTION( exec )
	void DumpCircuitsToLog();

	UFUNCTION( exec )
	void RerailAllTrains();

	UFUNCTION( exec )
	void MarkTrackGraphsAsChanged();

	UFUNCTION( exec )
	void MarkTrackGraphsForRebuild();

private:
	class UActorComponent* GetOuterPlayersUseComponent() const;
	class AActor* GetOuterPlayersUseActor() const;
	class AActor* GetOuterPlayersAimedAtActor( FVector& out_aimLocation ) const;
	class IFGFluidIntegrantInterface* GetOuterPlayerAimedAtFluidInterface() const;
	
public:
	/** This is used to make picking the same classes in the cheat board easier */
	UPROPERTY( Config )
	TArray< UClass* > mPopularUClassChoices;

	FTimerHandle mDebugFocusTimerHandle;
};
