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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchStartedDelegate, TSubclassOf< class UFGResearchRecipe >, researchRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FPaidOffResearchDelegate, TSubclassOf<class UFGResearchRecipe>, researchRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchCompletedDelegate, TSubclassOf<class UFGResearchRecipe>, researchRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchResultsClaimed, TSubclassOf<class UFGResearchRecipe>, researchRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FResearchNewAvailable, TSubclassOf<class UFGResearchRecipe>, researchRecipe );

/**
* Keeps track of research that is in a state of being paid off.
*/
USTRUCT( BlueprintType )
struct FResearchCost
{
	GENERATED_BODY()

		FResearchCost()
	{
	}

	FResearchCost( TSubclassOf<class UFGResearchRecipe> researchRecipeClass )
	{
		ResearchRecipe = researchRecipeClass;

		class UFGResearchRecipe* research = researchRecipeClass->GetDefaultObject<class UFGResearchRecipe>();
		Cost = research->GetIngredients();
	}

	bool HasValidRecipe() const
	{
		if( ResearchRecipe && ResearchRecipe->IsValidLowLevel() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	UPROPERTY( EditDefaultsOnly, SaveGame )
	TSubclassOf<class UFGResearchRecipe> ResearchRecipe;

	UPROPERTY( EditDefaultsOnly, SaveGame )
	TArray<FItemAmount> Cost;
};
FORCEINLINE bool IsValidForLoad( const FResearchCost& element ){ return element.ResearchRecipe != nullptr; }

/**
* Keeps track of ongoing research and when it's supposed to be completed.
*/
USTRUCT()
struct FResearchTime
{
	GENERATED_BODY()

	FResearchTime()
	{
	}

	FTimerHandle TimerHandle;

	UPROPERTY( EditDefaultsOnly, SaveGame )
	TSubclassOf<class UFGResearchRecipe> ResearchRecipe;

	UPROPERTY( EditDefaultsOnly, SaveGame )
	float ResearchCompleteTimestamp;
};
FORCEINLINE bool IsValidForLoad( const FResearchTime& element ){ return element.ResearchRecipe != nullptr; }

/**
* This struct defines data related to any research that has been completed. Once research is complete
* the player can choose to collect the rewards affiliated with research. This struct keep track of
* whether the rewards have been claimed.
*/
USTRUCT( BlueprintType )
struct FCompletedResearch
{
	GENERATED_BODY()

	FCompletedResearch()
	{
		RewardHasBeenClaimed = false;
	}

	FCompletedResearch( TSubclassOf<class UFGResearchRecipe> research ) :
		ResearchRecipe( research ),
		RewardHasBeenClaimed( false ),
		SelectedRewardIndex( -1 )
	{
	}


	UPROPERTY( BlueprintReadWrite )
	bool RewardRequiresSelection;

	UPROPERTY( EditDefaultsOnly, SaveGame )
	TSubclassOf<class UFGResearchRecipe> ResearchRecipe;

	UPROPERTY( EditDefaultsOnly, SaveGame )
	bool RewardHasBeenClaimed;

	UPROPERTY( BlueprintReadOnly )
	TArray<FResearchRecipeReward> PendingRewards;

	bool HasValidPendingRewards()
	{
		if( PendingRewards.Num() > 0 )
		{
			bool isValid = true;

			for( FResearchRecipeReward reward : PendingRewards )
			{
				if( !reward.IsValid() )
				{
					isValid = false;
					break;
				}
			}

			// if the list was invalid, clear it so that it doesn't contain broken data
			if( !isValid )
			{
				PendingRewards.Empty();
			}

			return isValid;
		}

		return false;
	}

	void GetUnlockedResearch( TArray<TSubclassOf<UFGResearchRecipe>>& out_rewardRecipes ) const
	{
		if( ResearchRecipe )
		{
			UFGResearchRecipe* researchRecipeCDO = ResearchRecipe->GetDefaultObject<UFGResearchRecipe>();
			for( TSubclassOf<UFGResearchRecipe> rewardResearch : researchRecipeCDO->GetRewardedResearchRecipes() )
			{
				if( rewardResearch )
				{
					out_rewardRecipes.Add( rewardResearch );
				}
			}
		}
	}

	bool HasRewardBeenSelected() const
	{
		if( RewardRequiresSelection == false || ( RewardRequiresSelection && PendingRewards.IsValidIndex( SelectedRewardIndex ) ) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool CanBeClaimed() const
	{
		return !RewardHasBeenClaimed && PendingRewards.Num() > 0;
	}

	int GetSelectedRewardIndex()
	{
		if( !RewardRequiresSelection && PendingRewards.IsValidIndex(0) )
		{
			SelectedRewardIndex = 0;
		}

		return SelectedRewardIndex;
	}

	void SetSelectedRewardIndex(int32 index)
	{
		if(PendingRewards.IsValidIndex(index))
		{
			SelectedRewardIndex = index;
		}
	}

	bool HasValidRecipe() const
	{
		if( ResearchRecipe && ResearchRecipe->IsValidLowLevel() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	
	// When a reward does require selection, this tracks the selected index of the reward from the pending
	// rewards list. If it is not selectable, then this value is not used.
	int32 SelectedRewardIndex = -1;
};
FORCEINLINE bool IsValidForLoad( const FCompletedResearch& element ){ return element.ResearchRecipe != nullptr; }

/**
 *
 */
UCLASS( Blueprintable, abstract, HideCategories = ( "Actor Tick", Rendering, Replication, Input, Actor ) )
class FACTORYGAME_API AFGResearchManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	/** Called when a research recipe is started */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchStarted" )
	FResearchStartedDelegate ResearchStartedDelegate;

	/** Called when a piece of research has been payed off in full */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnPaidOffResearch" )
	FPaidOffResearchDelegate PaidOffResearchDelegate;

		/** Called when ongoing research has completed */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchCompleted" )
	FResearchCompletedDelegate ResearchCompletedDelegate;

		/** Called when research results are collected from completed research */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchClaimed" )
	FResearchResultsClaimed ResearchResultsClaimedDelegate;

	/** Called when new research is available */
	UPROPERTY( BlueprintAssignable, Category = "Events|Research", DisplayName = "OnResearchAvailable" )
	FResearchNewAvailable ResearchNewAvailableDelegate;

public:
	AFGResearchManager();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreInitializeComponents() override;

	static AFGResearchManager* Get( class UWorld* world );

	UFUNCTION( BlueprintPure, Category = "Research", DisplayName = "GetResearchManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGResearchManager* Get( class UObject* worldContext );

		// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Tries to unlock research with item. If no research is affiliated with the item or already unlocked, nothing happens.. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void UnlockResearchWithItem( TSubclassOf<class UFGItemDescriptor> itemClass );

	/** Pays off a specific type of research. Durp. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	int32 PayOffOnResearch( FItemAmount payOff, TSubclassOf<class UFGResearchRecipe> researchRecipe );

	/** Attempts to pay off research from inventory slot at given index */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	int32 PayOffFromInventory( TSubclassOf<class UFGResearchRecipe> researchRecipe, UFGInventoryComponent* inventory, int32 inventorySlotIndex );

	/**
	* Returns how much is left to pay off for a specific type of research (if available).
	*/
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GetPayOffBalanceForResearch( TSubclassOf<class UFGResearchRecipe> researchRecipe, TArray<FItemAmount>& out_cost );

	/**
	* Returns every possible research recipe that is in the game
	* @note Calling this is only valid after PopulateResearchLists has been run.
	*/
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GetAllResearchRecipes( TArray<TSubclassOf<class UFGResearchRecipe>>& out_ResearchRecipes ) const;

	/** Returns all available research in the M.A.M. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GetAllAccessibleResearch( TArray<TSubclassOf<class UFGResearchRecipe>>& out_ResearchRecipes ) const;

	/** Returns all research that has both been completed and have had their rewards claimed. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GetAllCompletedAndClaimedResearch( TArray<TSubclassOf<class UFGResearchRecipe>>& out_ResearchRecipes ) const;

	/** Gives access to a research recipe in the M.A.M. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void GiveAccessToResearch( TSubclassOf<class UFGResearchRecipe> researchRecipeClass, bool accessedViaCheats = false );

	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool CanResearchBeInitiated( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	/** Returns whether a piece of research available/unlocked for the player? */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool IsResearchRecipeAccessible( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	/** Checks whether a piece of research is accessible and paid off (i.e. can be initiated/conducted). */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool IsResearchAccessibleAndPaidOff( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	/** Checks whether a piece of research is currently being conducted. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool IsResearchBeingConducted( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	/** Checks whether a specific piece of research has completed (i.e. can be claimed) */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool IsResearchComplete( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	/** Whether or not there is any research that has been completed but not claimed. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool ContainsAnyCompletedButUnclaimedResearch() const;

	/** Returns how much time there is left for a specific research. If the research in question isn't ongoing it will return -1.f */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	float GetOngoingResearchTimeLeft( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	UFUNCTION( BlueprintPure, Category = "Research" )
	FORCEINLINE float GetResearchDuration( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const { return UFGResearchRecipe::GetResearchTime( researchRecipe ); }

	UFUNCTION( BlueprintCallable, Category = "Research" )
	TSubclassOf< class UFGResearchRecipe > GetResearchBeingConducted() const;

	UFUNCTION( BlueprintPure, Category = "Research" )
	bool IsCompletedResearchResultSelectable( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	/** Tries to claim rewards from completed research. If rewards have already been claimed then no results will be returned. Returns true if research could be claimed. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool ClaimResearchResults( class AFGCharacterPlayer* instigatorPlayer, TSubclassOf<class UFGResearchRecipe> completedResearch, int32 selectedRewardIndex );

	/** Get the research reward package from a given completed recipe */
	UFUNCTION( BlueprintPure, Category = "Research" )
	const FCompletedResearch GetCompletedResearchRewardByRecipe( TSubclassOf<class UFGResearchRecipe> completedResearch );

	/** Set the selected reward index for a given researchRecipe */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	void SetSelectedRewardIndexByRecipe( TSubclassOf<class UFGResearchRecipe> completedResearch, int32 selectedIndex );

	/** Get the rewards associated with a completed research */
	UFUNCTION( BlueprintPure, Category = "Research" )
	const TArray<FResearchRecipeReward> GetRewardsFromCompletedResearch( FCompletedResearch completedResearch );

	/** Checks to see if rewards can be claimed for research. Will also return false if research hasn't been completed. */
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool CanResearchRewardBeClaimed( TSubclassOf<class UFGResearchRecipe> researchRecipe ) const;

	UFUNCTION( BlueprintPure, Category = "Research" )
	FORCEINLINE bool IsAnyResearchBeingConducted() const { return mOngoingResearch.Num() > 0; }

	/**
	* Initiates research if the given research has been payed off and ready to start
	* Returns whether research was successfully started.
	*/
	UFUNCTION( BlueprintCallable, Category = "Research" )
	bool InitiateResearch( TSubclassOf<class UFGResearchRecipe> researchRecipe );

	//////////////////////////////////////////////////////////////////////////
	// Decor points

	/** Returns the amount of decor points the ResearchManager currently has. */
	UFUNCTION( BlueprintPure, Category = "Decor" )
	FORCEINLINE int32 GetDecorPoints() const { return mDecorPoints; }

	/** Adds decor points to the ResearchManager */
	UFUNCTION( BlueprintCallable, Category = "Decor" )
	void AddDecorPoints( int32 amount ) { mDecorPoints = FMath::Max( 0, mDecorPoints + FMath::Abs( amount ) ); }

	/** Tries to consume the amount of decor points that is inputed. Returns the amount of points that were actually consumed. */
	UFUNCTION( BlueprintCallable, Category = "Decor" )
	int32 ConsumeDecorPoints( int32 amount );

	/** Returns whether or not the amount of decor points can be fully consumed. */
	UFUNCTION( BlueprintPure, Category = "Decor" )
	FORCEINLINE bool CanConsumeDecorPoints( int32 amount ) const { return mDecorPoints >= amount; }


	//////////////////////////////////////////////////////////////////////////
	// Structure points

	/** Returns the amount of structure points the ResearchManager currently has. */
	UFUNCTION( BlueprintPure, Category = "Structure" )
	FORCEINLINE int32 GetStructurePoints() const { return mStructurePoints; }

	/** Adds structure points to the ResearchManager */
	UFUNCTION( BlueprintCallable, Category = "Structure" )
	void AddStructurePoints( int32 amount ) { mStructurePoints = FMath::Max( 0, mStructurePoints + amount ); }

	/** Tries to consume the amount of structure points that is inputed. Returns the amount of points that were actually consumed. */
	UFUNCTION( BlueprintCallable, Category = "Structure" )
	int32 ConsumeStructurePoints( int32 amount );

	/** Returns whether or not the amount of structure points can be fully consumed. */
	UFUNCTION( BlueprintPure, Category = "Structure" )
	FORCEINLINE bool CanConsumeStructurePoints( int32 amount ) const { return mStructurePoints >= amount; }


protected:
	/** Populates list with all available research in the game */
	void PopulateResearchLists();

	/** Gives access to the default available research. Is called at start after PopulateResearchLists */
	void GiveAccessToDefaultResearch();

	/** Handles research timers internally and inits research. If research is already started will do nothing. */
	void StartResearch( TSubclassOf<class UFGResearchRecipe> researchRecipe, float researchTime );

	/** Generates pending research for any completed research */
	void GeneratePendingReward( FCompletedResearch& completedResearch );

	/** Whether multiple concurrent research can be conducted, or only one at a time. */
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	bool mCanConductMultipleResearch;

	/** What research that is available at start of the game. */
	UPROPERTY( EditDefaultsOnly, Category = "Research" )
	TArray<TSubclassOf<class UFGResearchRecipe>> mDefaultStartingResearch;

	UPROPERTY()
	TArray<TSubclassOf<class UFGResearchRecipe>> mAllResearchRecipes;

	/** Keeps track of what research is available to be conducted by the player and how much they've been paid off */
	UPROPERTY( SaveGame, Replicated )
	TArray<FResearchCost> mResearchCosts;

	/** What research has been conducted and is complete. */
	UPROPERTY( SaveGame, Replicated )
	TArray<FCompletedResearch> mCompletedResearch;

	/** What research that is currently being analyzed. i.e. that has started their timer and is ticking down. */
	UPROPERTY( Replicated )
	TArray<FResearchTime> mOngoingResearch;

	/** Used to track timestamps during saving */
	UPROPERTY( SaveGame )
	TArray<FResearchTime> mSavedOngoingResearch;

	UPROPERTY( SaveGame )
	int32 mDecorPoints;

	UPROPERTY( SaveGame )
	int32 mStructurePoints;

private:
	friend class UFGCheatManager;

	UFUNCTION()
	void OnResearchTimerComplete( TSubclassOf<class UFGResearchRecipe> researchRecipe );

	TMap<TSubclassOf<class UFGItemDescriptor>, TArray<TSubclassOf<class UFGResearchRecipe>>> mItemAffiliatedResearch;
};
