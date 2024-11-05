// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGRemoteCallObject.h"
#include "FGSaveInterface.h"
#include "FGSubsystem.h"
#include "FGGameRulesSubsystem.generated.h"

class FVariant;

UCLASS()
class FACTORYGAME_API UFGGameRulesRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGGameRulesRemoteCallObject = false;
	
	static UFGGameRulesRemoteCallObject* Get( UWorld* world );

	UFUNCTION( Server, Reliable )
	void Server_UnlockInstantAltRecipes( bool enabled );
	UFUNCTION( Server, Reliable )
	void Server_UnlockAllMileStoneSchematics();
	UFUNCTION( Server, Reliable )
	void Server_UnlockAllResourceSinkSchematics();
	UFUNCTION( Server, Reliable )
	void Server_UnlockAllResearchSchematics();
	UFUNCTION( Server, Reliable )
	void Server_SetNoUnlockCost( bool enabled );
	UFUNCTION( Server, Reliable )
	void Server_SetNoPower( bool enabled );
	UFUNCTION( Server, Reliable )
	void Server_SetArachnidCreaturesDisabled( bool disabled );
	UFUNCTION( Server, Reliable )
	void Server_SetGamePhase( int32 gamePhase );
	
};

/**
 * Handles game rules (session wide game modes) for the game. E.g. NoPower, NoUnlockCost, GiveAllMilestone etc.
 */
UCLASS()
class FACTORYGAME_API AFGGameRulesSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	/// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	/// End AActor Interface
	
	/** Get the game rules subsystem. */
	static AFGGameRulesSubsystem* Get( UWorld* world );

	/** Get the game rules subsystem. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame", DisplayName = "GetGameRulesSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGGameRulesSubsystem* Get( UObject* worldContext );

	void UnlockAllMileStoneSchematics();
	void UnlockAllResourceSinkSchematics();
	void UnlockAllResearchSchematics();
	void UnlockInstantAltRecipes( bool enabled );
	void SetNoUnlockCost( bool enabled );
	void SetNoPower( bool enabled );
	void SetArachnidCreaturesDisabled( bool disabled );
	void SetGamePhase( int32 gamePhase );
	void UnlockPreviouslyUnlockedContent();
	
	void GetDebugOverlayData( TArray<FString>& out_debugOverlayData ) const;

	// This value is only valid if creative mode is enabled.
	FORCEINLINE int32 GetStartingTier() const { return mStartingTier; }
	FORCEINLINE bool GetNoUnlockCost() const { return mNoUnlockCost; }

public:
	UFUNCTION()
	void OnRep_GameRules();
	UFUNCTION()
	void OnRep_NoUnlockCost();
	void SetupGameRules();
	// Setup initial game rules defined when starting a new session. Should only be called on server
	void InitializeGameRules();
	// Listen for changes in advanced game settings
	void SetupBindings();
	// Push current settings to advanced game settings
	void PushGameRulesToAdvancedGameSettings();
	void PushGameRuleToAdvancedGameSettings( const FString& StrID, FVariant value );
	class AFGGameState* GetGameState() const;
	
private:
	// Probably doesn't need to be saved in most cases but if a dedicated server is saved and restarted before a player joins this might be lost 
	UPROPERTY( SaveGame )
	int32 mStartingTier;

	UPROPERTY( SaveGame, Replicated )
	uint8 mHasInitialized : 1 = false;
	
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_GameRules )
	uint8 mUnlockInstantAltRecipes : 1 = false;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_GameRules )
	uint8 mUnlockAllMilestoneSchematics : 1 = false;
	
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_GameRules )
	uint8 mUnlockAllResourceSinkSchematics : 1 = false;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_GameRules )
	uint8 mUnlockAllResearchSchematics : 1 = false;

	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_GameRules  )
	uint8 mDisableArachnidCreatures : 1 = false;

	// Any unlock can be obtained without paying the resource cost.
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_NoUnlockCost )
	uint8 mNoUnlockCost : 1 = false;

	// bool NoPower is handled through AFGGameState::mCheatNoPower
};
