// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGHardDrive.h"
#include "FGPlayerController.h"
#include "FGRemoteCallObject.h"
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
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnUnclaimedHardDrivesUpdated );
DECLARE_MULTICAST_DELEGATE_OneParam( FOnPopulateResearchTreeListDelegate, TArray< TSubclassOf<class UFGResearchTree> >&);

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

	/** How many rerolls have we executed for this research data. Only applicable to hard drives */
	UPROPERTY( SaveGame )
	int32 PendingRewardsRerollsExecuted = 0;
	
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
};
FORCEINLINE bool IsValidForLoad( const FResearchTime& element );

/**
* Contains data about a researched hard drive. Represented in game by UFGHardDrive
*/
USTRUCT()
struct FACTORYGAME_API FHardDriveData
{
	GENERATED_BODY()

	FHardDriveData(){}

	FHardDriveData( int32 inHardDriveID, TArray<TSubclassOf<class UFGSchematic>> inPendingRewards ) :
		HardDriveID( inHardDriveID ),
		PendingRewards( inPendingRewards )
	{}

	/** The identifier for this hard drive so we can know which one is represented by a UFGHardDrive */
	UPROPERTY( SaveGame )
	int32 HardDriveID = INDEX_NONE;

	/** 
	* The rewards that have been generated for this schematic. 
	* This is used for example to store randomized alternate recipe schematics when analyzing a hard drive 
	* This array can be empty since most schematics use the unlock system except hard drives that generate rewards when research is initialized
	*/
	UPROPERTY( SaveGame )
	TArray<TSubclassOf<class UFGSchematic>> PendingRewards;

	/** How many rerolls have we executed for this research data. Only applicable to hard drives */
	UPROPERTY( SaveGame )
	int32 PendingRewardsRerollsExecuted = 0;

	/** The hard drive connected to this hard drive data. This is just for UI and is only created when hard drive list is requested  */
	UPROPERTY( Transient, NotReplicated )
	class UFGHardDrive* HardDrive = nullptr;

	bool operator==(const FHardDriveData& other) const;
};

UCLASS()
class FACTORYGAME_API UFGResearchManagerRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( Reliable, Server )
	void Server_InitiateResearch( AFGPlayerController* controller, TSubclassOf<class UFGSchematic> schematic,
		TSubclassOf<class UFGResearchTree> initiatingResearchTree );
	
	UFUNCTION( Reliable, Server )
	void Server_ClaimResearchResults( class AFGPlayerController* controller, TSubclassOf<class UFGSchematic> schematic );
	
	UFUNCTION( Reliable, Server )
	void Server_RerollHardDriveRewards( class AFGPlayerController* controller, int32 hardDriveID );
	
	UFUNCTION( Reliable, Server )
	void Server_ClaimHardDrive( class AFGPlayerController* controller, int32 hardDriveID, const TArray< TSubclassOf< UFGSchematic > >& schematics, TSubclassOf<class UFGSchematic> chosenSchematic );
	
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGResearchManagerRemoteCallObject = false;
};

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

	/** Called when the list of unclaimed hard drives is updated */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research" )
	FOnUnclaimedHardDrivesUpdated OnUnclaimedHardDrivesUpdated;

	/** Called after PopulateResearchTreeList has been called and vanilla content has been registered */
	FOnPopulateResearchTreeListDelegate PopulateResearchTreeListDelegate;
public:
	AFGResearchManager();

	// Begin Actor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	// End Actor interface

	static AFGResearchManager* Get( class UWorld* world );

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
	/** Returns true if any research of this tree is being conducted or have finished */
	bool IsResesearchTreeStarted( TSubclassOf<class UFGResearchTree> researchTree ) const;

	/**
	* Initiates research if given player inventory has enough items to cover the cost and research are allowed to start
	* Returns whether research was successfully started.
	* @param playerInventory The inventory where we grab the cost of research from
	* @param initiatingResearchTree The research tree that triggered this schematic research
	* @param schematic The schematic we want to research
	*/
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void InitiateResearch( class AFGPlayerController* controller, TSubclassOf<class UFGSchematic> schematic,
		TSubclassOf<class UFGResearchTree> initiatingResearchTree );

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

	/**
	 * Claims research results for a given schematic.
	 * Special handling for hard drive schematics that calls ProcessCompletedHardDriveResearch.
	 * For other schematics, grants access if research is complete and not yet purchased.
	 */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void ClaimResearchResults( class AFGPlayerController* controller, TSubclassOf<class UFGSchematic> schematic );

	UFUNCTION( Reliable, NetMulticast )
	void NetMulticast_OnResearchResultClaimed( TSubclassOf<class UFGSchematic> schematic );
	
	/** Creates a new hard drive data struct with the completed research and then removes it. */
	void ProcessCompletedHardDriveResearch();
	UFUNCTION( Reliable, NetMulticast )
	void NetMulticast_AddHardDrive( int32 hardDriveID, const TArray< TSubclassOf< UFGSchematic > >& schematics );
	UFGHardDrive* AddHardDriveObject( int32 hardDriveID );
	
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
	
	void GetPendingRewardsForHardDrive( int32 hardDriveID, TArray< TSubclassOf< UFGSchematic > >& out_rewards ) const;
	
	/** Returns true if the number of executed rerolls for the hard drive is less than the maximum allowed rerolls per hard drive. */
	bool HasRerollsLeftForHardDrive( int32 hardDriveID ) const;

	/** Returns true if rerolling of hard drives is currently possible based on a cached value indicating the availability of alternate recipes */
	bool CanRerollHardDrive() const { return mCanRerollHardDrives; }
	
	void RerollHardDriveRewards( class AFGPlayerController* controller, int32 hardDriveID );
	UFUNCTION( Reliable, NetMulticast )
	void NetMulticast_RerollHardDrive( int32 hardDriveID, const TArray< TSubclassOf< UFGSchematic > >& newSchematics );
	
	/**
	 * This function returns an array of alternative schematics. It compiles a list of available, non-purchased alternate schematics,
	 * excluding ongoing/completed research rewards, unclaimed hard drive rewards and the ones specified in excludedSchematics.
	 * out_schematics array is populated with a random selection of these filtered schematics. If the required number isn't met,
	 * we fall back to to excludedSchematics to fill up the list. But we will not fill up the array with just excluded schematics
	 *
	 * @param excludedSchematics List of schematics to be excluded.
	 * @param numSchematics Desired number of schematics to obtain.
	 * @param out_schematics Output array for the selected schematics.
	 * @return true if at least one "new" schematic is obtained, false if none are available.
	 */
	bool GetAvailableAlternateSchematics( TArray< TSubclassOf< UFGSchematic > > excludedSchematics, int32 numSchematics, TArray<TSubclassOf<UFGSchematic>>& out_schematics ) const;
	
	void ClaimHardDrive( class AFGPlayerController* controller, class UFGHardDrive* hardDrive, TSubclassOf<class UFGSchematic> schematic );
	UFUNCTION( Reliable, NetMulticast )
	void NetMulticast_ClaimHardDrive( int32 hardDriveID, TSubclassOf<class UFGSchematic> schematic );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GetUnclaimedHardDrives( TArray<UFGHardDrive*>& out_HardDrives );

	/** Check if any new trees have been unlocked */
	void UpdateUnlockedResearchTrees();

	/** Unlock a research tree */
	void UnlockResearchTree( TSubclassOf<class UFGResearchTree> researchTree );

	/** Returns if all nodes in the given research tree are researched */
	UFUNCTION( BlueprintPure, Category = "Research" )
	static bool IsTreeFullyResearched( UObject* worldContextObject, TSubclassOf<class UFGResearchTree> researchTree, TSubclassOf< class UFGSchematic > schematicToIgnore );

	/** Checks if the system has activated yet */
	UFUNCTION( BlueprintPure, Category = "Research" )
	FORCEINLINE bool IsActivated() const { return mIsActivated; }

	/** Activates subsystem */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetActivated( bool inActivate ) { mIsActivated = inActivate; }

	/**  Unlocks all research trees. Used to show the content of all research trees but don't give any of the schematics in the tree */
	void UnlockAllResearchTrees();
	
protected:
	UFUNCTION()
	void OnRep_OngoingResearch();

	UFUNCTION( Reliable, NetMulticast )
	void Multicast_ResearchCompleted( TSubclassOf< class UFGSchematic > research );

	/** Populates list with all available research trees in the game */
	void PopulateResearchTreeList();

	/** Handles research timers internally and inits research. If research is already started will do nothing. */
	void StartResearch( class AFGPlayerController* controller, TSubclassOf<class UFGSchematic> schematic, TSubclassOf< class UFGResearchTree> initiatingResearchTree );

	/** Generates pending research for any completed research. */
	void GeneratePendingReward( class AFGPlayerController* controller, FResearchData& researchData );

	/** Sets up delegate for building built so that we can check for activation */
	void SetupActivation();

	/** Called when the local player builds anything */
	UFUNCTION()
	void OnBuildingBuiltGlobal( class AFGBuildable* buildable );
	
	/** Checks if a research tree is valid for addition to the available research trees list. */
	bool CanAddToAvailableResearchTrees( TSubclassOf< UFGResearchTree > researchTree ) const;

	/** Whether multiple concurrent research can be conducted, or only one at a time. */
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	bool mCanConductMultipleResearch;

	UPROPERTY( Transient, Replicated )
	TArray<TSubclassOf<class UFGResearchTree>> mAvailableResearchTrees;

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

	/** Returns a hard drive to the given player. Not used at the moment but kept functionality since it might be good to have */
	void GiveHardDriveToPlayer( AFGCharacterPlayer* instigatorPlayer );

	bool AreResearchTreeUnlockDependeciesMet( TSubclassOf <UFGResearchTree> inClass );

	void SubmitResearchCompletedTelemetry( const TArray< TSubclassOf< class UFGSchematic > >& allSchematics, TSubclassOf< UFGSchematic > chosenSchematic ) const;

	/** Checks if we have any available alternative schematics and updates mCanRerollHardDrive */
	UFUNCTION()
    void UpdateCanRerollHardDrive( TSubclassOf< class UFGSchematic > dummySchematic );

	void Internal_ClaimHardDrive( class AFGPlayerController* controller, int32 hardDriveID, const TArray<TSubclassOf<class UFGSchematic>>& schematics , TSubclassOf<class UFGSchematic> chosenSchematic );
	
	UPROPERTY( SaveGame, Replicated )
	bool mIsActivated;

	/** What class the MAM is */
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	TSubclassOf< class AFGBuildable > mMAMClass;

	/** The stored hard drives that we have researched */
	UPROPERTY( SaveGame, Replicated )
	TArray<FHardDriveData> mUnclaimedHardDriveData;

	/** We increment this with one each time we store a hard drive. We could probably reuse indexes when a hard drive is claimed but
	 * this will never grow that big so this felt safer */
	UPROPERTY( SaveGame )
	int32 mLastUsedHardDriveID = 0;

	/** Cached value if we can reroll hard drives. Basically this is true if we have any available alternate recipes that isn't stored
	 * in any hard drive or current/completed research. Replicated since we might not have all relevant data on client to decide this. */
	UPROPERTY( Transient, Replicated )
	bool mCanRerollHardDrives;
	
private:
	friend class UFGResearchManagerRemoteCallObject;
	friend class UFGCheatManager;

};
