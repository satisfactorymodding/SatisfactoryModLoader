// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/CheatManager.h"
#include "FGGamePhaseManager.h"
#include "FGCreatureSubsystem.h"
#include "FGCheatManager.generated.h"


UCLASS( Within = PlayerController, Config = Editor )
class FACTORYGAME_API UFGCheatManager : public UCheatManager
{
	GENERATED_BODY()
public:
	// Begin UCheatManager interface
	virtual void InitCheatManager() override;
	// End UCheatManager interface
	
	// Begin UObject interface
	virtual bool IsSupportedForNetworking() const override;
	virtual bool ReplicateSubobjects( class UActorChannel *Channel, class FOutBunch *Bunch, FReplicationFlags *RepFlags );
	virtual int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;
	virtual bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;
	virtual void PreSave( const ITargetPlatform* TargetPlatform ) override;
	// End UObject interface

	/** Applies default cheats when "EnableCheats" command is triggered. */
	void InitDefaultCheats();

	/** Get function categories for populating the UI. */
	FORCEINLINE TMap< FString, FString > GetFunctionCategories() { return mFunctionCategories; }
	
	/** Used to toggle cheat menu from console. Migrated here from the old FGHUD solution and kept the naming */
	UFUNCTION( exec )
	void Cheats();
	
	/****************************************************************
	 * Common
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_NoCost( bool enabled );
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void NoCost( bool enabled );
	UFUNCTION( exec, CheatBoard )
	bool NoCost_Get();
	UFUNCTION( Server, Reliable )
	void Server_NoPower( bool enabled );
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void NoPower( bool enabled );
	UFUNCTION( exec, CheatBoard)
	bool NoPower_Get();
	UFUNCTION( Server, Reliable )
	void Server_NoFuel( bool enabled );
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void NoFuel( bool enabled );
	UFUNCTION( exec, CheatBoard )
	bool NoFuel_Get();
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void TurboBuildMode( bool enabled );
	UFUNCTION( exec, CheatBoard )
	bool TurboBuildMode_Get();
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void TurboProductionMode( bool enabled );
	UFUNCTION( exec, CheatBoard )
	bool TurboProductionMode_Get();
	UFUNCTION( Server, Reliable )
	void Server_GiveItemStacks( class AFGCharacterPlayer* character, TSubclassOf< class UFGItemDescriptor > resource, int32 numberOfStacks );
	UFUNCTION( exec, CheatBoard, Category = "Resources:-4", meta = ( ToolTip="Give the number of full item stacks specified. Will expand inventory if needed. Becareful with too high numbers.") )
	void GiveItemStacks( TSubclassOf< class UFGItemDescriptor > resource, int32 numberOfStacks );
	UFUNCTION( Server, Reliable )
	void Server_GiveItemsSingle( class AFGCharacterPlayer* character, TSubclassOf< class UFGItemDescriptor > resource, int32 numberOfItems );
	UFUNCTION( exec, CheatBoard, Category = "Resources:-3", meta = ( ToolTip="Give the number of items specified." ))
	void GiveItemsSingle( TSubclassOf< class UFGItemDescriptor > resource, int32 numberOfItems );
	UFUNCTION( exec, Category = "Resources" )
	void ClearGiveItemPopularList();
	UFUNCTION( Server, Reliable )
	void Server_GiveResourceSinkCoupons( int32 numCoupons );
	UFUNCTION( exec, CheatBoard, Category = "Resources:-2", meta = ( ToolTip = "Give the number of coupons specified" ) )
	void GiveResourceSinkCoupons( int32 numCoupons );

	/****************************************************************
	 * UI
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, Category = "GUI" )
	void NoMessages( bool enabled );
	UFUNCTION( exec, CheatBoard )
	bool NoMessages_Get();
	UFUNCTION( exec, CheatBoard, category = "GUI" )
	void PumpiMode( bool enable );
	UFUNCTION( exec, CheatBoard )
	bool PumpiMode_Get();
	UFUNCTION( exec, CheatBoard, category = "GUI" )
	void HiddenHUDMode( bool enable );
	UFUNCTION( exec, CheatBoard )
	bool HiddenHUDMode_Get() const;
	
	/****************************************************************
	 * Environment
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_SetTimeOfDay( int32 hour, int32 minute = 0 );
	UFUNCTION( exec, CheatBoard, category = "Time" )
	void SetTimeOfDay( int32 hour, int32 minute = 0 );
	UFUNCTION( Server, Reliable )
	void Server_SetTimeSpeedMultiplier( float speed );
	UFUNCTION( exec, CheatBoard, category = "Time" ) 
	void SetTimeSpeedMultiplier( float speed );
	UFUNCTION( Server, Reliable )
	void Server_SetTimeSpeedMultiplierResetTime( int32 resetHour );
	UFUNCTION( exec, CheatBoard, category = "Time" )
	void SetTimeSpeedMultiplierResetTime( int32 resetHour );
	UFUNCTION( exec, CheatBoard, category = "Time" )
	int32 SetTimeOfDay_hour_Get();
	UFUNCTION( exec, CheatBoard, category = "Time" )
	int32 SetTimeOfDay_minute_Get();
	UFUNCTION( Server, Reliable )
	void Server_SetSlomo( float slomo );
	UFUNCTION( exec, CheatBoard, category = "Time" )
	void SetSlomo( float slomo );
	UFUNCTION( Server, Reliable )
	void Server_SetPlanetPosition( float value );
	UFUNCTION( exec, CheatBoard, category = "World|Planets" )
	void SetPlanetPosition( float value );
	UFUNCTION( Server, Reliable )
	void Server_SetPlanetPositionDeg( int32 value );
	UFUNCTION( exec, CheatBoard, category = "World|Planets" )
	void SetPlanetPositionDeg( int32 value );
	UFUNCTION( Server, Reliable )
	void Server_SetPlanetMovementEnabled( bool enabled );
	UFUNCTION( exec, CheatBoard, category = "World|Planets" )
	void SetPlanetMovementEnabled( bool enabled );
	UFUNCTION( Server, Reliable )
	void Server_SetPlanetSpeedMultiplier( float multiplier );
	UFUNCTION( exec, CheatBoard, category = "World|Planets" )
	void SetPlanetSpeedMultiplier( float multiplier );
	UFUNCTION( exec, CheatBoard, category = "World|Weather" )
	void ForceSetWeatherType( TSubclassOf<class AFGWeatherReaction> Reaction );
	UFUNCTION( exec, CheatBoard, category = "World|Weather" )
	void LockWeather(bool bState);
	
	/****************************************************************
	 * Creatures
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_Creature_CanAttackEachother( bool canAttack );
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_CanAttackEachother( bool canAttack );
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_SetStressEnabled( bool enable );
	UFUNCTION( Server, Reliable )
	void Server_Creature_SpawnNew( TSubclassOf< class AFGCreature > creatureClass, int32 numToSpawn );
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_SpawnNew( TSubclassOf< class AFGCreature > creatureClass, int32 numToSpawn = 1 );
	UFUNCTION( Server, Reliable )
	void Server_Creature_KillAllCreaturesInRadius( float radius );
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_KillAllCreaturesInRadius( float radius );
	UFUNCTION( Server, Reliable )
	void Server_Creature_KillAllCreatures();
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_KillAllCreatures();
	UFUNCTION( Server, Reliable )
	void Server_Creature_ForceSpawnCreatures();
	/** Forces active spawners to spawn creatures even if the creature isn't set to spawn yet (because of day/night restrictions etc) */
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_ForceSpawnCreatures();

	/****************************************************************
	 * Player
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, Category = "Player" )
	void PlayerFly( bool flyModeEnabled );
	UFUNCTION( exec, CheatBoard )
	bool PlayerFly_Get();
	UFUNCTION( Server, Reliable )
	void Server_PlayerAllFly( bool flyModeEnabled);
	UFUNCTION( exec, CheatBoard, Category = "Player" )
	void PlayerAllFly( bool flyModeEnabled );
	UFUNCTION( exec, CheatBoard )
	bool PlayerAllFly_Get();
	UFUNCTION( exec, CheatBoard, Category = "Player" )
	void PlayerNoClipModeOnFly( bool ghostMode );
	UFUNCTION( exec, CheatBoard )
	bool PlayerNoClipModeOnFly_Get();
	UFUNCTION( exec, CheatBoard, category = "Player" )
	void UpdatePlayerNametags();
	UFUNCTION( exec, category = "Player" )
	void EnablePlayerFOV( bool enable );
	UFUNCTION( exec, category = "Player" )
	bool EnablePlayerFOV_Get();
	UFUNCTION( exec, category = "Player" )
	void DestroyPawn();
	UFUNCTION( exec, CheatBoard, category = "Player" )
	void ToggleCameraMode();
	UFUNCTION( exec, category = "Player|Spawn" )
	void ListDebugStartingPoint();
	UFUNCTION( exec, category = "Player|Spawn" )
	void SetDebugStartingPoint( FName startingPoint );
	UFUNCTION( exec, category = "Player|Spawn" )
	void SetRandomDebugStartingPoint();
	UFUNCTION( exec, CheatBoard, category = "Player|Rules" )
	void SetCreatureHostility( EPlayerHostilityMode hostility );

	/****************************************************************
	 * Foliage
	 ****************************************************************/
	UFUNCTION( exec, category = "Foliage" )
	void Foliage_RemoveOneByOne( int32 maxNumInstances = 0 );
	UFUNCTION( Server, Reliable )
	void Server_Foliage_RemoveOneByOne( int32 maxNumInstances );
	UFUNCTION( exec, category = "Foliage" )
	void Foliage_RemoveInBulk( int32 maxNumInstances = 0 );
	UFUNCTION( Server, Reliable )
	void Server_Foliage_RemoveInBulk( int32 maxNumInstances );
	UFUNCTION( exec, category = "Foliage" )
	void Foliage_RemoveByTarget( float radius = 5000.0f );
	UFUNCTION( Server, Reliable )
	void Server_Foliage_RemoveByTarget( float radius );
	
	/****************************************************************
	 * Research
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_GiveAllSchematics();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveAllSchematics();
	UFUNCTION( Server, Reliable )
	void Server_GiveAllSchematicsAndPhases();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveAllSchematicsAndPhases();
	UFUNCTION( Server, Reliable )
	void Server_GiveAvailableSchematics();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveAvailableSchematics();
	UFUNCTION( Server, Reliable )
	void Server_GiveActiveMilestoneSchematic();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveActiveMilestoneSchematic();
	UFUNCTION( Server, Reliable )
	void Server_GiveCheatSchematics();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveCheatSchematics();
	UFUNCTION( Server, Reliable )
	void Server_GivePrototypeSchematics();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GivePrototypeSchematics();
	UFUNCTION( Server, Reliable )
	void Server_GiveStorySchematics();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveStorySchematics();
	UFUNCTION( Server, Reliable )
	void Server_GiveAllResearchTrees();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveAllResearchTrees();
	UFUNCTION( Server, Reliable )
	void Server_GiveSchematicsOfTier( int32 tier );
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GiveSchematicsOfTier( int32 tier );
	UFUNCTION( Server, Reliable )
	void Server_SetGamePhase( EGamePhase phase );
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetGamePhase( EGamePhase phase );
	UFUNCTION( Server, Reliable )
	void Server_SetNextGamePhase();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetNextGamePhase();
	UFUNCTION( Server, Reliable )
	void Server_ResetGamePhases();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void ResetGamePhases();
	UFUNCTION( Server, Reliable )
	void Server_ResetHubTutorial();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void ResetHubTutorial();
	UFUNCTION( Server, Reliable )
	void Server_ResetSchematics();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void ResetSchematics();
	UFUNCTION( Server, Reliable )
	void Server_ResetRecipes();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void ResetRecipes();
	UFUNCTION( Server, Reliable )
	void Server_CompleteResearch();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void CompleteResearch();
	UFUNCTION( Server, Reliable )
	void Server_SetTradingPostLevel( int32 inLevel );
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetTradingPostLevel( int32 inLevel );

	/****************************************************************
	 * Map
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, category = "Map"  )
	void Map_RemoveMarker( int32 index );
	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_Map_Reveal();
	UFUNCTION( Server, Reliable )
	void Server_Map_Reveal();
	UFUNCTION( exec, CheatBoard, category = "Map" )
	void Map_Reveal();
	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_Map_Hide();
	UFUNCTION( Server, Reliable )
	void Server_Map_Hide();
	UFUNCTION( exec, CheatBoard, category = "Map" )
	void Map_Hide();
	
	/****************************************************************
	 * Story
	 ****************************************************************/
	// @todok2 implement client support when we now what to do with story
	// Removed cheatboard tag for now so we don't have them on the cheat board
	UFUNCTION( exec, category = "Story" )
	void Story_TriggerNextPrimaryMessageInQueue();
	UFUNCTION( exec, category = "Story" )
	void Story_TriggerNextSecondaryMessageInQueue( int32 storyQueueIndex = 0 );
	UFUNCTION( exec, category = "Story" )
	void Story_TriggerNextFloatingMessageInPrimaryQueue();
	UFUNCTION( exec, category = "Story" )
	void Story_TriggerRandomTriggeredBarksMessage();
	UFUNCTION( exec, category = "Story" )
	void Story_StartNextStoryQueue();
	UFUNCTION( exec, category = "Story" )
	void Story_ResetAllStoryQueues();
	UFUNCTION( exec, category = "Story" )
	void Story_ResetCurrentStoryQueue();

	/****************************************************************
	 * Photo
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_ToggleAdvancedPhotoMode();
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_SetManualFocusDistance( float manualFocusDistance );
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_FocusTrackLookedAtObject();
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_SetAperture( float aperture );
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_ToggleDebug();
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_ResetToDefault();
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_AddCurrentPlayerPosAndRot();
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_PlaySequence();
	UFUNCTION( exec, CheatBoard, category = "Photo" )
	void Photo_ToggleSequencer();

	/****************************************************************
	 * Online
	 ****************************************************************/
	UFUNCTION( exec, category = "Online" )
	void Online_EpicLogin( FString username, FString password );
	UFUNCTION( exec, category = "Online" )
	void Online_EpicLogout();
	UFUNCTION( exec, category = "Online" )
	void Online_GetOnlineStatus( int32 localPlayerNum = 0 );
	UFUNCTION( exec, category = "Online" )
	void Online_UpdatePresence( FString key, FString value );
	UFUNCTION( exec, category = "Online" )
	void Online_UpdatePresenceString( FString string );
	UFUNCTION( exec, category = "Online" )
	void Online_LogPresence();
	UFUNCTION( exec, category = "Online" )
	void Online_GetFriends();
	UFUNCTION( exec, category = "Online" )
	void Online_TriggerPresenceUpdate();
	UFUNCTION( exec, category = "Online" )
	void Online_SendInviteToFriend( FString friendName );
	UFUNCTION( exec, category = "Online" )
	void Online_UpdateGameSession();
	UFUNCTION( exec, category = "Online" )
	void Online_DumpConnectionString();
	
	/****************************************************************
	 * Wheeled Vehicles
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_Vehicle_FlipDrivenVehicle( class AFGWheeledVehicle* vehicle );
	UFUNCTION( exec, CheatBoard, category = "Vehicle" )
	void Vehicle_FlipDrivenVehicle();
	UFUNCTION( Server, Reliable )
	void Server_Vehicle_ResetDeadlocks();
	UFUNCTION( exec, category = "Vehicle" )
	void Vehicle_ResetDeadlocks();
	UFUNCTION( Server, Reliable )
	void Server_Vehicle_ResetTheChosenVehicle();
	UFUNCTION( exec, category = "Vehicle" )
	void Vehicle_ResetTheChosenVehicle();
	UFUNCTION( exec, CheatBoard, category = "Vehicle" )
	void Vehicle_DumpInfoAboutLookedAtVehicle();
	
	/****************************************************************
	 * Trains
	 ****************************************************************/
	UFUNCTION( exec, category = "Trains" )
	void Trains_ToggleSelfDriving();
	UFUNCTION( Server, Reliable )
	void Server_Trains_FillAllFreightCars( float pct = 1.f );
	UFUNCTION( exec, category = "Trains" )
	void Trains_FillAllFreightCars( float pct = 1.f );
	UFUNCTION( Server, Reliable )
	void Server_Trains_EmptyAllFreightCars();
	UFUNCTION( exec, category = "Trains" )
	void Trains_EmptyAllFreightCars();
	UFUNCTION( Server, Reliable )
	void Server_Trains_RerailAll();
	UFUNCTION( exec, category = "Trains" )
	void Trains_RerailAll();
	UFUNCTION( Server, Reliable )
	void Server_Trains_MarkTrackGraphsAsChanged();
	UFUNCTION( exec, category = "Trains" )
	void Trains_MarkTrackGraphsAsChanged();
	UFUNCTION( Server, Reliable )
	void Server_Trains_MarkTrackGraphsForRebuild();
	UFUNCTION( exec, category = "Trains" )
	void Trains_MarkTrackGraphsForRebuild();

	/****************************************************************
	 * Pipes
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_Pipe_FillFirstInEachNetwork();
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_FillFirstInEachNetwork();
	UFUNCTION( Server, Reliable )
	void Server_Pipe_EmptyAll();
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_EmptyAll();
	UFUNCTION( Server, Reliable )
	void Server_Pipe_ResetAll();
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_ResetAll();
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_PrintMinSizes();
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_SetVerboseLoggingOnAimedFluidBox( bool enabled );
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_EnableProbingOnAimedIntegrant();
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_DisableProbingOnAimedIntegrant();
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_ClearProbingOnAllPipe();
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_AddSelectedNetworkToDisplayDebugList();
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_ClearDisplayDebugList();
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_PrintTweakables();
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_TweakMaximumFlow( float rate );
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_TweakMinimumMaxContent( float minimumMaxContent, bool keepRelativeContent );
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_TweakPressureLoss( float pressureLoss );
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_TweakOverfill( float maxOverfillPct, float maxOverfillForPressure );
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_TweakGravity( float gravity );
	UFUNCTION( exec, category = "Pipes" )
	void Pipe_TweakFluidFriction( float fluidFriction );
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_TweakFluidDensity( float fluidDensity );
	UFUNCTION( exec, category = "Pipes" )
    void Pipe_TweakFluidViscosity( float fluidViscosity );

	/****************************************************************
	 * Circuits
	 ****************************************************************/
	UFUNCTION( exec, category = "Circuit" )
	void Circuit_DumpCircuitsToLog();
	UFUNCTION( Server, Reliable )
	void Server_Circuit_RebuildAll();
	UFUNCTION( exec, category = "Circuit" )
	void Circuit_RebuildAll();
	UFUNCTION( Server, Reliable )
	void Server_Circuit_ResetFuses();
	UFUNCTION( exec, category = "Circuit" )
	void Circuit_ResetFuses();
	UFUNCTION( exec, category = "Circuit" )
	void Circuit_Bug_InsertDupeComponentIntoCircuit( int32 target );
	UFUNCTION( exec, category = "Circuit" )
	void Circuit_Bug_InsertDupeComponentIntoAnotherCircuit( int32 source, int32 target );

	/****************************************************************
	 * Save/Load (Mostly commands to cleanup or fix save issues)
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_PurgeInactiveClientsFromSave( class AFGCharacterPlayer* characterToReceiveInventories, bool fetchInventories );
	UFUNCTION( exec, CheatBoard, category = "Save/Load" )
	void PurgeInactiveClientsFromSave( bool fetchInventories );
	UFUNCTION( Server, Reliable )
	void Server_PurgeAllBeaconsFromSave();
	UFUNCTION( exec, CheatBoard, category = "Save/Load" )
	void PurgeAllBeaconsFromSave();
	UFUNCTION( Server, Reliable )
	void Server_PurgeDeathMarkersFromSave();
	UFUNCTION( exec, CheatBoard, category = "Save/Load" )
	void PurgeDeathMarkersFromSave();
	UFUNCTION( Server, Reliable )
	void Server_PurgeAllTrainState();
	UFUNCTION( exec, category = "Save/Load" )
	void PurgeAllTrainState();
	UFUNCTION( exec, category = "Save/Load" )
	void ResetAllFactoryLegsToZero( bool repopulateEmptyLegs );
	UFUNCTION( exec, category = "Save/Load" )
	void RebuildFactoryLegsOneTileAroundPlayer();
	
	/****************************************************************
	 * Factory Debug
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_ShowFactoryOnly( bool environmentHidden );
	UFUNCTION( exec, category = "Factory" )
	void ShowFactoryOnly( bool environmentHidden );
	UFUNCTION( exec )
	bool ShowFactoryOnly_Get();
	UFUNCTION( Server, Reliable )
	void Server_HideFactoryOnly( bool factoryHidden );
	UFUNCTION( exec, category = "Factory" )
	void HideFactoryOnly( bool factoryHidden );
	UFUNCTION( exec )
	bool HideFactoryOnly_Get();
	UFUNCTION( exec, category = "Factory" )
	void SplitAllConveyors();
	UFUNCTION( exec, category = "Factory" )
	void MergeAllConveyors();
	UFUNCTION( exec, category = "Factory" )
	void SetFactoryDetailReplication( bool enable );
	UFUNCTION( exec )
	bool SetFactoryDetailReplication_Get();
	UFUNCTION( Server, Reliable )
	void Server_HideAllBuildings( bool inVisibility );
	UFUNCTION( exec, category = "Factory" )
	void HideAllBuildings( bool inVisibility );
	UFUNCTION( exec )
	bool HideAllBuildings_Get();
	UFUNCTION( Server, Reliable )
	void Server_EnableBuildableTick( bool enable );
	UFUNCTION( exec, category = "Factory" )
	void EnableBuildableTick( bool enable );
	UFUNCTION( exec )
	bool EnableBuildableTick_Get();
	UFUNCTION( exec, category = "Factory" )
	void ReplayBuildingEffects();

	/****************************************************************
	 * Dump
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard ,category = "Log" )
	void DumpNonDormantActors();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpAttachedToSkelMesh( bool detailed = false );
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpTicking( bool detailed = false );
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpActiveGPUParticles();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpPlayerStates();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpHotbarShortcuts();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpActorRepresentations();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpSignificanceManagedObjects();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpItemPickups();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpStaticMeshesHierarchy();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpComponentCounts();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpSchematics();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpUnlockedRecipesAndSchematics();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpAllAvailableRecipes();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpGamePhases();

	/****************************************************************
	 * Audio
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, category = "Audio" )
	void Audio_EnableDebug(bool isEnabled);
	UFUNCTION( exec, CheatBoard, category = "Audio" )
	void Audio_ToggleLandingDebug();
	
	/****************************************************************
	 * Misc
	 ****************************************************************/
	UFUNCTION( exec )
	void RunHardwareBenchmark( int32 WorkScale = 10, float CPUMultiplier = 1.0f, float GPUMultiplier = 1.0f );
	UFUNCTION( exec )
	void TestSharedInventoryPtr();
	UFUNCTION( exec )
	void RandomizeBuildingsColorSlot( uint8 slotIndex = 0);
	UFUNCTION( exec )
	void ShowSequenceList();

private:
	// Traverse all UFGCheatManager cheat functions and store a mapping so we know what category they belong to since that data isn't available in packaged builds
	void CacheFunctionCategoryMapping();
	
	bool IsClient() const;

	/** Helpers for functionality reused for multiple cheats. */
	class UActorComponent* GetOuterPlayersUseComponent() const;
	class AActor* GetOuterPlayersUseActor() const;
	class AActor* GetOuterPlayersAimedAtActor( FVector& out_aimLocation ) const;
	class IFGFluidIntegrantInterface* GetOuterPlayerAimedAtFluidInterface() const;
	
public:
	/** This is used to make picking the same classes in the cheat board easier */
	UPROPERTY( Config )
	TArray< UClass* > mPopularUClassChoices;
	
	/**
	 * Populated when we save the cheat manager BP. Used to gather metadata from cheat functions. We need to store them since meta data isn't available in packaged builds
	 * Key is a function name and value is a category 
	 */
	UPROPERTY( VisibleDefaultsOnly, Category = "Function Categories" )
	TMap< FString, FString > mFunctionCategories;

	/** Used to check if we have applied the default cheats this game session. */ 
	bool mDefaultCheatsApplied = false;
};
