// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGResearchRecipe.h"
#include "FGResearchManager.generated.h"

/**
* The current state of research
*/
UENUM( BlueprintType )
enum class EResearchState :uint8
{
	ERS_NotResearching	UMETA( DisplayName = "Not Researching" ),
	ERS_Researching		UMETA( DisplayName = "Researching" ),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchStartedDelegate, TSubclassOf< class UFGSchematic >, schematic );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchCompletedDelegate, TSubclassOf<class UFGSchematic>, schematic );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchStateChangedDelegate, EResearchState, researchState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchResultsClaimed, TSubclassOf<class UFGSchematic>, schematic );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchTreeUnlocked, TSubclassOf<class UFGResearchTree>, researchTree );

/**
* Contains data about the research conducted
*/
USTRUCT()
struct FACTORYGAME_API FResearchData
{
	GENERATED_BODY()

		FResearchData() :
		Schematic( nullptr ),
		InitiatingResearchTree( nullptr )
	{}

	FResearchData( TSubclassOf<class UFGSchematic> schematic, TSubclassOf<class UFGResearchTree> initiatingResearchTree ) :
		Schematic( schematic ),
		InitiatingResearchTree( initiatingResearchTree )
	{}

	/** The schematic that holds the research data */
	UPROPERTY( SaveGame )
	TSubclassOf<class UFGSchematic> Schematic;

	/** The research tree that initiated the research */
	UPROPERTY( SaveGame )
	TSubclassOf<class UFGResearchTree> InitiatingResearchTree;

	/** 
	* The rewards that have been generated for this schematic. 
	* This is used for example to store randomized alternate recipe schematics when analyzing a hard drive 
	* This array can be empty since most schematics use the unlock system except hard drives that generate rewards when research is initialized
	*/
	UPROPERTY( SaveGame )
	TArray<TSubclassOf<class UFGSchematic>> PendingRewards;


public:
	FORCEINLINE ~FResearchData() = default;
};
FORCEINLINE bool IsValidForLoad( const FResearchData& element );

/**
* Keeps track of ongoing research and when it's supposed to be completed.
*/
USTRUCT()
struct FACTORYGAME_API FResearchTime
{
	GENERATED_BODY()

	FResearchTime() :
		ResearchCompleteTimestamp( 0 )
	{}

	FResearchTime( TSubclassOf<class UFGSchematic> schematic, TSubclassOf<class UFGResearchTree> initiatingResearchTree, float researchCompleteTimestamp ) :
		ResearchCompleteTimestamp( researchCompleteTimestamp )
	{
		ResearchData = FResearchData( schematic, initiatingResearchTree );
	}

	FResearchTime( FResearchData researchData, float researchCompleteTimestamp ) :
		ResearchCompleteTimestamp( researchCompleteTimestamp )
	{
		ResearchData = researchData;
	}

	FTimerHandle TimerHandle;

	/** The research entry that contains data about the research conducted */
	UPROPERTY( SaveGame )
	FResearchData ResearchData;

	/** The time stamp for when the research is completed. When saved it represents how much time is left for research */
	UPROPERTY( SaveGame )
	float ResearchCompleteTimestamp;

public:
	FORCEINLINE ~FResearchTime() = default;
};
FORCEINLINE bool IsValidForLoad( const FResearchTime& element );

/**
 * The research manager handles everything research related 
 */
UCLASS( Blueprintable, abstract, HideCategories = ( "Actor Tick", Rendering, Replication, Input, Actor ) )
class FACTORYGAME_API AFGResearchManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	/** Called when a research recipe is started */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchStarted" )
	FResearchStartedDelegate ResearchStartedDelegate;

	/** Called when ongoing research has completed */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchCompleted" )
	FResearchCompletedDelegate ResearchCompletedDelegate;
	
	/** Called when research state has changed */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchStateChanged" )
	FResearchStateChangedDelegate ResearchStateChangedDelegate;

	/** Called when research results are collected from completed research */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchClaimed" )
	FResearchResultsClaimed ResearchResultsClaimedDelegate;
	
	/** Called when research trees are unlocked */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchTreeUnlocked" )
	FResearchTreeUnlocked ResearchTreeUnlockedDelegate;

public:
	AFGResearchManager();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreInitializeComponents() override;

	//MODDING EDIT: forceinline world accessor
	MODDING_SHIPPING_FORCEINLINE static AFGResearchManager* Get(class UWorld* world) { return Get(static_cast<UObject*>(world)); }

	UFUNCTION( BlueprintPure, Category = "Research", DisplayName = "GetResearchManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGResearchManager* Get( class UObject* worldContext );

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/**
	* Returns every possible research tree that is in the game
	* @note Calling this is only valid after PopulateResearchTreeList has been run.
	*/
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GetAllResearchTrees( TArray<TSubclassOf<class UFGResearchTree>>& out_ResearchTrees ) const;

	UFUNCTION( BlueprintPure, Category = "Research" )
	bool IsResesearchTreeUnlocked( TSubclassOf<class UFGResearchTree> researchTree ) const;

	/**
	* Initiates research if given player inventory has enough items to cover the cost and research are allowed to start
	* Returns whether research was successfully started.
	* @param playerInventory The inventory where we grab the cost of research from
	* @param initiatingResearchTree The research tree that triggered this schematic research
	* @param schematic The schematic we want to research

	*/
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool InitiateResearch( UFGInventoryComponent* playerInventory, TSubclassOf<class UFGSchematic> schematic, TSubclassOf<class UFGResearchTree> initiatingResearchTree );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool CanResearchBeInitiated( TSubclassOf<class UFGSchematic> schematic ) const;

	/** Checks whether a piece of research is currently being conducted. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool IsResearchBeingConducted( TSubclassOf<class UFGSchematic> schematic ) const;

	/** Checks whether a specific piece of research has completed (i.e. can be claimed) */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool IsResearchComplete( TSubclassOf<class UFGSchematic> schematic ) const;

	/** Whether or not there is any research that has been completed but not claimed. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool ContainsAnyCompletedResearch() const;

	/** Returns all schematics that have been researched and are ready to be claimed. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Schematic" )
	void GetAllCompletedResearch( TArray< TSubclassOf< UFGSchematic > >& out_schematics ) const;

	/** Returns how much time there is left for a specific research. If the research in question isn't ongoing it will return -1.f */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	float GetOngoingResearchTimeLeft( TSubclassOf<class UFGSchematic> schematic ) const;

	UFUNCTION( BlueprintCallable, Category = "Research" )
	TSubclassOf< class UFGSchematic > GetResearchBeingConducted() const;

	/** Tries to claim rewards from completed research. If rewards have already been claimed then no results will be returned. Returns true if research could be claimed. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool ClaimResearchResults( class AFGCharacterPlayer* instigatorPlayer, TSubclassOf<class UFGSchematic> schematic, int32 selectedRewardIndex );

	UFUNCTION( BlueprintPure, Category = "Research" )
	FORCEINLINE bool IsAnyResearchBeingConducted() const { return mOngoingResearch.Num() > 0; }

	UFUNCTION( BlueprintPure, Category = "Research" )
	bool CanAffordResearch( UFGInventoryComponent* playerInventory, TSubclassOf<class UFGSchematic> schematic ) const;
	
	UFUNCTION( BlueprintPure, Category = "Research" )
	EResearchState GetCurrentResearchState() const { return mOngoingResearch.Num() > 0 ? EResearchState::ERS_Researching : EResearchState::ERS_NotResearching; }
	
	UFUNCTION( BlueprintPure, Category = "Research" )
	bool CanConductMultipleResearch() const { return mCanConductMultipleResearch; }

	/** Return the researchTree that initiated the research of the given schematic */
	UFUNCTION( BlueprintPure, Category = "Research" )
	TSubclassOf<class UFGResearchTree> GetInitiatingResearchTree( TSubclassOf<class UFGSchematic> schematic ) const;

	/** Returns all schematics that have been researched and are ready to be claimed. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Research" )
	void GetPendingRewards( TSubclassOf<class UFGSchematic> schematic, TArray< TSubclassOf< UFGSchematic > >& out_rewards ) const;

	/** Check if any new trees have been unlocked */
	void UpdateUnlockedResearchTrees();

	/** Unlock a research tree */
	void UnlockResearchTree( TSubclassOf<class UFGResearchTree> researchTree );

	/** Checks if the system has activated yet */
	UFUNCTION( BlueprintPure, Category = "Research" )
	FORCEINLINE bool IsActivated() const { return mIsActivated; }

	/** Activates subsystem */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetActivated( bool inActivate ) { mIsActivated = inActivate; }
protected:
	UFUNCTION()
	void OnRep_OngoingResearch();

	UFUNCTION( Reliable, Client )
	void Client_NewResearchStarted( TSubclassOf< class UFGSchematic > research );

	/** Populates list with all available research trees in the game */
	void PopulateResearchTreeList();

	/** Handles research timers internally and inits research. If research is already started will do nothing. */
	void StartResearch( TSubclassOf<class UFGSchematic> schematic, TSubclassOf< class UFGResearchTree> initiatingResearchTree );

	/** Generates pending research for any completed research */
	void GeneratePendingReward( FResearchData& researchData );

	/** Sets up delegate for building built so that we can check for activation */
	void SetupActivation();

	/** Called when the local player builds anything */
	UFUNCTION()
	void OnBuildingBuiltGlobal( class AFGBuildable* buildable );

	/** Whether multiple concurrent research can be conducted, or only one at a time. */
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	bool mCanConductMultipleResearch;

public: // MODDING EDIT
	UPROPERTY( Transient )
	TArray<TSubclassOf<class UFGResearchTree>> mAllResearchTrees;
protected:
	UPROPERTY( SaveGame, Replicated )
	TArray<TSubclassOf<class UFGResearchTree>> mUnlockedResearchTrees;

	/** What research has been conducted and is complete. */
	UPROPERTY( SaveGame, Replicated )
	TArray<FResearchData> mCompletedResearch;

	/** What research that is currently being analyzed. i.e. that has started their timer and is ticking down. */
	UPROPERTY( ReplicatedUsing=OnRep_OngoingResearch )
	TArray<FResearchTime> mOngoingResearch;

	/** Used save the current ongoing research, saved research is restarted on load */
	UPROPERTY( SaveGame )
	TArray<FResearchTime> mSavedOngoingResearch;

private:
	UFUNCTION()
	void OnResearchTimerComplete( TSubclassOf<class UFGSchematic> schematic );

	bool PayForResearch( UFGInventoryComponent* playerInventory, TSubclassOf<class UFGSchematic> schematic ) const;

	/** Claim pending rewards. One alternate recipe or give back one hard drive */
	void ClaimPendingRewards( AFGCharacterPlayer* instigatorPlayer, TSubclassOf<UFGSchematic> schematic, int32 selectedRewardIndex );

	bool AreResearchTreeUnlockDependeciesMet( TSubclassOf <UFGResearchTree> inClass );

	UPROPERTY( SaveGame, Replicated )
	bool mIsActivated;

	/** What class the MAM is */
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	TSubclassOf< class AFGBuildable > mMAMClass;
private:
	friend class UFGCheatManager;


public:
	FORCEINLINE ~AFGResearchManager() = default;
};
