// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/CheatManager.h"
#include "FGGamePhaseManager.h"
#include "FGCreatureSubsystem.h"
#include "FGCheatManager.generated.h"

/** Will store one per parameter in the function cheat in the cheat board */
USTRUCT()
struct FCheatBoardParamSelectionData
{
	GENERATED_BODY()

	/** Last value that the user has inputted in the input text box */
	UPROPERTY( Config )
	FString LastInputValue;
	
	/** Last value that the user selected as a filter in the filter text box */
	UPROPERTY( Config )
	FString LastFilterValue;

	/** Name of the last item that was selected for this parameter */
	UPROPERTY( Config )
	FString LastItemSelectedName;
};

/** Identifier for a function in a cheat board */
USTRUCT()
struct FCheatBoardFunctionSelectionData
{
	GENERATED_BODY()

	/** Selection data for each parameter of a function */
	UPROPERTY( Config )
	TMap<FName, FCheatBoardParamSelectionData> ParamSelections;
};

/** Implement this on CheatManager of CheatManagerExtension to provide category information to the Cheat Board. */
UINTERFACE( NotBlueprintable )
class FACTORYGAME_API UFGCheatBoardFunctionCategoryProvider : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGCheatBoardFunctionCategoryProvider
{
	GENERATED_BODY()
public:
	/** Returns a map of function names to their Category values. You are supposed to cache them from Metadata during cook time and return the cached values in runtime */
	virtual TMap<FString, FString> GetFunctionCategories() const = 0;
};

/** Allows filtering and visually transforming values of arguments passed to the cheat through the cheat board (currently only supports classes and objects) */
class FACTORYGAME_API IFGCheatBoardParameterFilter
{
public:
	virtual ~IFGCheatBoardParameterFilter() = default;

	virtual FString GetPrettifiedClassName( UClass* InClass ) const;
	virtual bool IsClassFilteredOut( UClass* InClass ) const { return false; }
	virtual FString GetPrettifiedAssetName( UObject* InAsset ) const;
	virtual bool IsAssetFilteredOut( UObject* InAsset ) const { return false; }
};

/** Wraps parameter filter into a struct that can be passed around */
USTRUCT()
struct FACTORYGAME_API FFGCheatBoardParameterFilter
{
	GENERATED_BODY()

	TSharedPtr<IFGCheatBoardParameterFilter> Filter;
};

/** Wraps parameter filter into a struct bound to a specific parameter type */
USTRUCT()
struct FACTORYGAME_API FFGCheatBoardGlobalParameterFilter : public FFGCheatBoardParameterFilter
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UClass> BaseClassType;

	UPROPERTY()
	TObjectPtr<UClass> BaseAssetType;
};

/** Item filter for item descriptors. Exposed here to easily allow taking alternative resource forms on demand. */
class FFGCheatBoardParameterFilter_ItemDescriptor : public IFGCheatBoardParameterFilter
{
public:
	explicit FFGCheatBoardParameterFilter_ItemDescriptor( const EResourceForm InResourceForm ) : mTargetResourceForm( InResourceForm ) {}

	virtual FString GetPrettifiedClassName( UClass* InClass ) const override;
	virtual bool IsClassFilteredOut( UClass* InClass ) const override;
private:
	EResourceForm mTargetResourceForm{};
};

UCLASS( Within = PlayerController, Config = EditorPerProjectUserSettings, ProjectUserConfig )
class FACTORYGAME_API UFGCheatManager : public UCheatManager, public IFGCheatBoardFunctionCategoryProvider
{
	GENERATED_BODY()
public:
	// Begin UCheatManager interface
	virtual void InitCheatManager() override;
	// End UCheatManager interface
	
	// Begin UObject interface
	virtual bool IsSupportedForNetworking() const override;
	virtual int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;
	virtual bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;
	virtual void PreSave( FObjectPreSaveContext saveContext ) override;
	// End UObject interface

	// Begin IFGCheatBoardFunctionCategoryProvider interface
	virtual TMap<FString, FString> GetFunctionCategories() const override { return mFunctionCategories; }
	// End IFGCheatBoardFunctionCategoryProvider interface

	/** Applies default cheats when "EnableCheats" command is triggered. */
	void InitDefaultCheats();

	/** Returns all registered cheat manager extensions */
	FORCEINLINE TArray<TObjectPtr<UCheatManagerExtension>> GetCheatManagerExtensions() const { return CheatManagerExtensions; }

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
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void NoUnlockCost( bool enabled );
	UFUNCTION( exec, CheatBoard )
	bool NoUnlockCost_Get();
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
	UFUNCTION( exec, CheatBoard, Category = "Resources:-1", meta = ( ToolTip="Give the number of full item stacks specified. Will expand inventory if needed. Becareful with too high numbers.") )
	void GiveUploadItemStack( TSubclassOf< class UFGItemDescriptor > resource );
	UFUNCTION( Server, Reliable )
	void Server_GiveUploadItemStack( class AFGCharacterPlayer* character, TSubclassOf< class UFGItemDescriptor > resource );
	UFUNCTION( Exec, CheatBoard, Category = "Resources", meta = ( ToolTip = "Clear the inventory of the player" ) )
	void ClearInventory();
	UFUNCTION( Server, Reliable )
	void Server_ClearInventory();
	UFUNCTION( Server, Reliable )
	void Server_GiveResourceSinkCoupons( int32 numCoupons );
	UFUNCTION( exec, CheatBoard, Category = "Resources:-2", meta = ( ToolTip = "Give the number of coupons specified" ) )
	void GiveResourceSinkCoupons( int32 numCoupons );
	UFUNCTION( exec, CheatBoard, Category = "Resources" )
	void EnableCreativeMode();
	UFUNCTION( Server, Reliable )
	void Server_SetCentralStorageUploadSpeed( float seconds );
	UFUNCTION( exec, CheatBoard, Category = "Resources", meta = ( ToolTip = "This will not save the value. Just for runtime debugging" )  )
	void SetCentralStorageUploadSpeed( float seconds );
	
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
	UFUNCTION( exec, CheatBoard, category = "Time" )
	void SetNumberOfDaysSinceLastDeath( int32 newNumberOfDaysSinceLastDeath );
	UFUNCTION( Server, Reliable )
	void Server_SetNumberOfDaysSinceLastDeath( int32 newNumberOfDaysSinceLastDeath );
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
	UFUNCTION( exec, CheatBoard, category = "World|Debug" )
	void HighlightPickupable( TSubclassOf< AFGItemPickup > pickupClass );
	UFUNCTION( exec, CheatBoard, category = "World|Debug" )
	void HighlightCrashSites();
	UFUNCTION( exec, CheatBoard, category = "World|Debug" )
	void ClearHighlightedActors();
	UFUNCTION()
	void Internal_HighlightPickupables();
	UFUNCTION( Server, Reliable )
	void Server_TriggerRandomWorldEvent();
	UFUNCTION( exec, CheatBoard, category = "World|WorldEvents" )
	void TriggerRandomWorldEvent();
	UFUNCTION( Exec, CheatBoard, Category = "World|Debug" )
	void RunGameplayTest( TSubclassOf<class UFGGameplayTest> gameplayTest );
	UFUNCTION( Server, Reliable )
	void Server_RunGameplayTest( TSubclassOf<class UFGGameplayTest> gameplayTest );
	UFUNCTION( Server, Reliable )
	void Server_SetSAMIntensity( int32 newSAMIntensity );
	UFUNCTION( exec, CheatBoard, category = "World|Alien" )
	void SetSAMIntensity( int32 newSAMIntensity );
	
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
	UFUNCTION( Server, Reliable )
	void Server_Creature_AddCreatureOverride( TSubclassOf< class AFGCreature > creatureClassToReplace, TSubclassOf< class AFGCreature > creatureClassOverride );
	/** Adds a creature class override, so trying to spawn a creature of a certain type will instead spawn another. Override with null to disable the creature, override with the same creature to re-enable it. */
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_AddCreatureOverride( TSubclassOf< class AFGCreature > creatureClassToReplace, TSubclassOf< class AFGCreature > creatureClassOverride );
	UFUNCTION( Server, Reliable )
	void Server_Creature_SetArachnidCreaturesDisabled( bool disabled );
	/** Whether or not to enable / disable arachnid creatures from spawning. */
	UFUNCTION( exec, CheatBoard, category = "Creature" )
	void Creature_SetArachnidCreaturesDisabled( bool disabled );

	/****************************************************************
	 * Vehicles
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
    void Server_Vehicle_SpawnNew( TSubclassOf< class AFGVehicle > vehicleClass, int32 numToSpawn );
    UFUNCTION( exec, CheatBoard, category = "Vehicle" )
    void Vehicle_SpawnNew( TSubclassOf< class AFGVehicle > vehicleClass, int32 numToSpawn = 1 );

	UFUNCTION( Server, Reliable )
	void Server_Vehicle_BringIdleDrones();
	UFUNCTION( exec, CheatBoard, category = "Vehicle" )
	void Vehicle_BringIdleDrones();

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
	/** Makes the player into the server admin. That does not change the admin password, but gives temporarily privileges to the logged in player. Only available in non-Shipping builds */
	UFUNCTION( Exec, CheatBoard, Category = "Player|Server" )
	void PromoteToServerAdmin();
	/** Revokes the admin permissions from the logged in player temporarily. Does not change admin password. Only available in non-Shipping builds */
	UFUNCTION( Exec, CheatBoard, Category = "Player|Server" )
	void DemoteToServerPlayer();
	UFUNCTION( Server, Reliable )
	void Server_PromoteToServerAdmin( bool isAdminNow );
	/** Collects items from all of the crates in the world to the player inventory */
	UFUNCTION( Exec, CheatBoard, Category = "Player" )
	void CollectAllCrates();
	UFUNCTION( Server, Reliable )
	void Server_CollectAllCrates();
	/** Brings all unpossessed player pawns to the player location */
	UFUNCTION( Exec, CheatBoard, Category = "Player" )
	void BringAllUnpossessedPawnsHere();
	UFUNCTION( Server, Reliable )
	void Server_BringAllUnpossessedPawnsHere();
	/** Kills the currently possessed pawn. */
	UFUNCTION( Exec, CheatBoard, Category = "Player" )
	void Die();
	UFUNCTION( Server, Reliable )
	void Server_Die();
	/** Revives the currently possessed pawn */
	UFUNCTION( Exec, CheatBoard, Category = "Player" )
	void ReviveSelf();
	UFUNCTION( Server, Reliable )
	void Server_ReviveSelf();
	/** Ragdolls the character */
	UFUNCTION( Exec, CheatBoard, Category = "Player" )
	void RagdollSelf();
	UFUNCTION( Server, Reliable )
	void Server_RagdollSelf();
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void GodMode( bool enabled );
	UFUNCTION( Server, Reliable )
	void Server_GodMode( bool enabled );
	UFUNCTION( Exec, CheatBoard )
	bool GodMode_Get() const;
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void SetMaxHealth( float newMaxHealth );
	UFUNCTION( Server, Reliable )
	void Server_SetMaxHealth( float newMaxHealth );
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void Heal();
	UFUNCTION( Server, Reliable )
	void Server_Heal();
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void DamageSelf( float damage );
	UFUNCTION( Server, Reliable )
	void Server_DamageSelf( float damage );
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void StopPossessingCharacter();
	UFUNCTION( Server, Reliable )
	void Server_StopPossessingCharacter();
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void PossessCharacterAtIndex( int32 characterIndex );
	UFUNCTION( Server, Reliable )
	void Server_PossessCharacterAtIndex( int32 characterIndex );
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void SetPlayerPrimaryCustomizationColor( const FString& NewColorHex );
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void SetPlayerSecondaryCustomizationColor( const FString& NewColorHex );
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void SetPlayerDetailCustomizationColor( const FString& NewColorHex );
	UFUNCTION( Exec, Category = "Player", CheatBoard )
	void SetPlayerCustomizationHelmetDesc( TSubclassOf<UFGPlayerHelmetCustomizationDesc> NewHelmetDesc );
	/** Fast forwards currently playing intro sequence N seconds forward */
	UFUNCTION( Exec, Category = "Player|Intro", CheatBoard )
	void FastForwardIntroSequence( float SecondsToFastForward );
	
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
	void Server_SetGamePhase( UFGGamePhase* gamePhase );
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SetGamePhase( UFGGamePhase* gamePhase );
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
	void Server_SkipOnboarding();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void SkipOnboarding();
	UFUNCTION( Server, Reliable )
	void Server_GoToNextOnboardingStep();
	UFUNCTION( exec, CheatBoard, category = "Research" )
	void GoToNextOnboardingStep();
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
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockSpecificRecipe( TSubclassOf<class UFGRecipe> recipe );
	UFUNCTION( Server, Reliable )
	void Server_UnlockSpecificRecipe( TSubclassOf<class UFGRecipe> recipe );
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockSpecificEmote( TSubclassOf<class UFGEmote> emote );
	UFUNCTION( Server, Reliable )
	void Server_UnlockSpecificEmote( TSubclassOf<class UFGEmote> emote );
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockSpecificTape( TSubclassOf<class UFGTapeData> tapeData );
	UFUNCTION( Server, Reliable )
	void Server_UnlockSpecificTape( TSubclassOf<class UFGTapeData> tapeData );
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockScannableResource( TSubclassOf< class UFGResourceDescriptor > resourceDescriptor );
	UFUNCTION( Server, Reliable )
	void Server_UnlockScannableResource( TSubclassOf< class UFGResourceDescriptor > resourceDescriptor );
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockInventorySlots( int32 numSlots );
	UFUNCTION( Server, Reliable )
	void Server_UnlockInventorySlots( int32 numSlots );
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockArmSlots( int32 numSlots );
	UFUNCTION( Server, Reliable )
	void Server_UnlockArmSlots( int32 numSlots );
	UFUNCTION( Exec, CheatBoard, Category = "Research" )
	void UnlockSpecificSchematic( TSubclassOf<UFGSchematic> Schematic );
	UFUNCTION( Server, Reliable )
	void Server_UnlockSpecificSchematic( TSubclassOf<UFGSchematic> Schematic );
	
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
	void Online_TriggerPresenceUpdate();
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
	void Trains_EnableSelfDriving( bool requireValidTimeTable );
	UFUNCTION( exec, category = "Trains" )
	void Trains_EnableSelfDrivingForTestCase( FString trainNameTag );
	UFUNCTION( exec, category = "Trains" )
	void Trains_DisableSelfDriving();
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
	 * Narrative/Story
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, category = "Narrative" )
	void ClearMessageCooldown();

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
	
	/****************************************************************
	 * Factory Debug
	 ****************************************************************/
	UFUNCTION( Server, Reliable )
	void Server_ShowFactoryOnly( bool environmentHidden );
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void ShowFactoryOnly( bool environmentHidden );
	UFUNCTION( exec )
	bool ShowFactoryOnly_Get();
	UFUNCTION( Server, Reliable )
	void Server_HideFactoryOnly( bool factoryHidden );
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void HideFactoryOnly( bool factoryHidden );
	UFUNCTION( exec )
	bool HideFactoryOnly_Get();
	UFUNCTION( exec, category = "Factory" )
	void SplitAllConveyors();
	UFUNCTION( exec, category = "Factory" )
	void MergeAllConveyors();
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void SetFactoryDetailReplication( bool enable );
	UFUNCTION( exec )
	bool SetFactoryDetailReplication_Get();
	UFUNCTION( Server, Reliable )
	void Server_HideAllBuildings( bool inVisibility );
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void HideAllBuildings( bool inVisibility );
	UFUNCTION( exec )
	bool HideAllBuildings_Get() const;
	UFUNCTION( Server, Reliable )
	void Server_EnableBuildableTick( bool enable );
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void EnableBuildableTick( bool enable );
	UFUNCTION( exec )
	bool EnableBuildableTick_Get();
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void ReplayBuildingEffects( int32 bucketId, bool playBuildEffect = true );
	UFUNCTION( exec, CheatBoard, category = "Factory" )
	void SetBuildingBucketHidden( int32 bucketId, bool hidden );

	/****************************************************************
	 * Dump
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard ,category = "Log" )
	void DumpNonDormantActors();
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
	void DumpComponentCounts();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpSchematics();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpUnlockedRecipesAndSchematics();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpAllAvailableRecipes();
	UFUNCTION( exec, CheatBoard, category = "Log" )
	void DumpGamePhases();
	UFUNCTION( Exec, CheatBoard, Category = "Log" )
	void DumpPlayerCustomizationData();

	/****************************************************************
	 * Audio
	 ****************************************************************/
	UFUNCTION( exec, CheatBoard, category = "Audio" )
	void Audio_ToggleLandingDebug();
	
	/****************************************************************
	 * Misc
	 ****************************************************************/
	UFUNCTION( exec )
	void RunHardwareBenchmark( int32 WorkScale = 10, float CPUMultiplier = 1.0f, float GPUMultiplier = 1.0f );
	UFUNCTION( exec )
	void RandomizeBuildingsColorSlot( uint8 slotIndex = 0);
	UFUNCTION( exec )
	void ShowSequenceList();
	UFUNCTION( exec )
	void HitchNow( float ms );

	/** Global parameter filters for a few types */
	UFUNCTION( CheatBoard )
	FFGCheatBoardGlobalParameterFilter GlobalParameterFilter_ItemDescriptor() const;
	UFUNCTION( CheatBoard )
	FFGCheatBoardGlobalParameterFilter GlobalParameterFilter_GameplayTest() const;
	UFUNCTION( CheatBoard )
	FFGCheatBoardGlobalParameterFilter GlobalParameterFilter_GamePhase() const;
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
	/** Last remembered values of filter and item name selected for the cheat board */
	UPROPERTY( Config )
	TMap<TSoftObjectPtr<UFunction>, FCheatBoardFunctionSelectionData> mLastRememberedFunctionSelections;

	/** Last remembered filter value on the cheat board */
	UPROPERTY( Config )
	FCheatBoardParamSelectionData mCheatBoardLastFilterValue;
	
	/**
	 * Populated when we save the cheat manager BP. Used to gather metadata from cheat functions. We need to store them since meta data isn't available in packaged builds
	 * Key is a function name and value is a category 
	 */
	UPROPERTY( VisibleDefaultsOnly, Category = "Function Categories" )
	TMap< FString, FString > mFunctionCategories;

	/** Used to check if we have applied the default cheats this game session. */ 
	bool mDefaultCheatsApplied = false;

	/** Tracks with item pickup classes we are tracking */ 
	UPROPERTY( Transient )
	TArray< TSubclassOf< class AActor > > mHighlightedActorClasses;
};
