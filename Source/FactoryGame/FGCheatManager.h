// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/CheatManager.h"
#include "FGGameState.h"
#include "Interfaces/OnlineSharedCloudInterface.h"
#include "FGCheatManager.generated.h"

/**
 * 
 */
UCLASS( Within = PlayerController, Config = Editor )
class FACTORYGAME_API UFGCheatManager : public UCheatManager
{
	GENERATED_BODY()
public:
	virtual void InitCheatManager() override;

	UFUNCTION( exec, Category = "Resources" )
	virtual void NoCost( bool enabled );

	UFUNCTION( exec )
	virtual bool NoCost_Get();

	UFUNCTION( exec, Category = "Resources" )
	virtual void NoPower( bool enabled );

	UFUNCTION( exec)
		virtual bool NoPower_Get();

	UFUNCTION( exec, Category = "GUI" )
	virtual void NoMessages( bool enabled );

	UFUNCTION( exec )
	virtual bool NoMessages_Get();

	UFUNCTION( exec, Category = "World/Time" )
	virtual void TurboMode( bool enabled );

	UFUNCTION( exec, Category = "World/Time" )
	virtual bool TurboMode_Get();

	UFUNCTION( exec, Category = "Resources:-2", meta = ( ToolTip="Give the number of full item stacks specified. Will expand inventory if needed. Becareful with too high numbers.") )
	virtual void GiveItemStacks( TSubclassOf< class UFGItemDescriptor > resource, int32 NumberOfStacks );

	UFUNCTION( exec, Category = "Resources:-1", meta = ( ToolTip="Give the number of items specified." ))
	virtual void GiveItemsSingle( TSubclassOf< class UFGItemDescriptor > resource, int32 NumberOfItems );


	

	UFUNCTION( exec, Category = "Player/Camera" )
	virtual void PlayerFly( bool flyModeEnabled );
	UFUNCTION( exec, Category = "Player/Camera" )
	virtual bool PlayerFly_Get();

	UFUNCTION( exec, Category = "Player/Camera" )
	virtual void PlayerNoClipModeOnFly( bool gohstMode );
	UFUNCTION( exec, Category = "Player/Camera" )
	virtual bool PlayerNoClipModeOnFly_Get();
	

	UFUNCTION( exec )
	virtual void ClearGiveItemPopularList();
	
	UFUNCTION( exec, category = "Research" )
	virtual void GiefALLSchematics();

	UFUNCTION( exec, category = "Research" )
	void GiefAllSchematicsAndPhases();

	UFUNCTION( exec, category = "Research" )
	virtual void GiefAvailableSchematics();

	UFUNCTION( exec, category = "Research" )
	virtual void GiefCheatSchematics();

	UFUNCTION( exec)
	virtual void GiefStorySchematics();

	UFUNCTION( exec, category = "Research" )
	void GiefStartingResearch();
	
	UFUNCTION( exec, category = "Factory|Uncommon" )
	virtual void RebuildPowerCircuits();

	UFUNCTION( exec, category = "Factory|Uncommon" )
	void EnableBuildableTick( bool enable );

	UFUNCTION( exec, category = "Factory|Uncommon" )
	bool EnableBuildableTick_Get();

	/** Cheat for disabling the players fov override if we want to get the fov from cameras in world */
	UFUNCTION( exec, category = "Player/Camera" )
	void EnablePlayerFOV( bool enable );

	UFUNCTION( exec, category = "Player/Camera" )
	bool EnablePlayerFOV_Get();
	
	UFUNCTION( exec, category = "Player/Camera|test category" )
	void DestroyPawn();

	UFUNCTION( exec )
	void RemoveAllFoliage( int32 maxNumInstances = 999999 );

	UFUNCTION( exec, category = "Player/Camera" )
	virtual void PardonAllPlayers();

	UFUNCTION( exec, category = "Player/Camera" )
	virtual void ClearPardon();

	UFUNCTION( exec, category = "World/Time" )
	void SetTimeOfDay( int32 hour, int32 minute = 0 );

	UFUNCTION( exec, category = "World/Time" )
	int32 SetTimeOfDay_hour_Get();

	UFUNCTION( exec, category = "World/Time" )
	int32 SetTimeOfDay_minute_Get();

	/** Hide everything except the factory */
	UFUNCTION( exec, category = "Display" )
	void ShowFactoryOnly( bool environmentHidden );

	UFUNCTION( exec, category = "Display" )
	bool ShowFactoryOnly_Get();

	/** Hide everything the factory */
	UFUNCTION( exec, category = "Display" )
	void HideFactoryOnly( bool factoryHidden );

	UFUNCTION( exec, category = "Display" )
	bool HideFactoryOnly_Get();
	
	UFUNCTION( exec, category = "Log" )
	void DumpAllAvailableRecipes();

	UFUNCTION( exec, category = "Audio" )
	void EnableAudioDebug(bool isEnabled);

	UFUNCTION( exec, category = "Audio" )
	void ToggleAudioDebug();

	UFUNCTION( exec, category = "World/Time" )
	void SetSlomo( float slomo );

	UFUNCTION( exec )
	void OpenModMap();

	UFUNCTION( exec, category = "GUI" )
	void PumpiMode( bool enable );

	UFUNCTION( exec, category = "GUI" )
	bool PumpiMode_Get();
	
	UFUNCTION( exec, category = "Factory" )
	void SplitAllConveyors();

	UFUNCTION( exec, category = "Factory" )
	void MergeAllConveyors();

	UFUNCTION( exec) 
	void SetTimeSpeedMultiplier( float speed );

	UFUNCTION( exec )
	void SetFactoryDetailReplication( bool enable );

	UFUNCTION( exec )
	bool SetFactoryDetailReplication_Get();

	UFUNCTION( exec, category = "Factory" )
	void ResetFuses();

	UFUNCTION( exec, category = "Player/Camera" )
	void ToggleCameraMode();

	UFUNCTION( exec, category = "Log" )
	void DumpFactoryStatsToLog();

	UFUNCTION( exec, category = "Research" )
	void GiefSchematicsOfTier( int32 tier );

	UFUNCTION( exec, category = "Research" )
	void SetGamePhase( EGamePhase phase );

	UFUNCTION( exec )
	void TestSharedInventoryPtr();

	/** Forces active spawners to spawn creatures even if the creature isn't set to spawn yet ( because of day/night restrictions etc ) */
	UFUNCTION( exec, category = "World/Time" )
	void ForceSpawnCreatures();

	UFUNCTION( exec ,category = "Log" )
	void DumpNonDormantActors();

	UFUNCTION( exec, category = "Audio" )
	void ToggleAudioLandingDebug();

	UFUNCTION( exec, category = "Log" )
	void DumpAttachedToSkelMesh( bool detailed = false );

	UFUNCTION( exec, category = "Log" )
	void DumpTicking( bool detailed = false );
	
	/** Dump all GPU particles systems that's available */
	UFUNCTION( exec, category = "Log" )
	void DumpActiveGPUParticles();

	/** Starts replaying buildeffects */
	UFUNCTION( exec )
	void ReplayBuildingEffects();

	/** Sets visibility on all buildings */
	UFUNCTION( exec, category = "Display" )
	void HideAllBuildings( bool inVisibility );

	UFUNCTION( exec, category = "Display" )
	bool HideAllBuildings_Get();

	/** Randomize building color slot color */
	UFUNCTION( exec, category = "Factory" )
	void RandomizeBuildingsColorSlot( uint8 slotIndex = 0);

	UFUNCTION( exec )
	void UpdateSessionToOSS();

	UFUNCTION( exec )
	void VisitAllMapAreas();

	UFUNCTION( exec, category = "World/Time" )
	void SetAITickDistance( float distance );

	UFUNCTION( exec, category = "Log" )
	void DumpPlayerStates();

	UFUNCTION( exec, category = "Display" )
	void EnableInstancingOnFactory( bool enabled );

	UFUNCTION( exec, category = "Log" )
	void DumpActorRepresentations();

	UFUNCTION( exec, category = "Log" )
	void DumpSignificanceManagedObjects();

	UFUNCTION( exec, category = "Save/Load" )
	void PurgeInactiveClientsFromSave( bool fetchInventories );

	UFUNCTION( exec, category = "Save/Load" )
	void PurgeAllBeaconsFromSave();

	UFUNCTION( exec, category = "Log" )
	void ListItemPickups();

	UFUNCTION( exec, category = "Research" )
	void SetTradingPostLevel( int32 inLevel );

	UFUNCTION( exec, category = "Log" )
	void ListUnlockedRecipesAndSchematics();

	UFUNCTION( exec, category = "Save/Load" )
	void SaveWithNewSessionName( const FString& saveName, const FString& sessionName );

	UFUNCTION( exec, category = "Log" )
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
	void DebugCrash();

	UFUNCTION( exec )
	void ResetHubTutorial();

	UFUNCTION( exec )
	void ResetSchematics();

	UFUNCTION( exec, category = "Research" )
	void ResetRecipes();

	UFUNCTION( exec, category = "Log" )
	void DumpSchematics();

	UFUNCTION( exec )
	void FixupBuiltByRecipeInOldSave( bool reapplyRecipeIfBetterMatchFound = false );

	UFUNCTION( exec )
	void PrintStatichMeshesHirarchy();

	UFUNCTION( exec )
	void FlipVehicle();

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

public:
	/** This is used to make picking the same classes in the cheat board easier */
	UPROPERTY( Config )
	TArray< UClass* > mPopularUClassChoices;
};
