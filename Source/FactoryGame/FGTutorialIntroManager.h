// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGTutorialSubsystem.h"
#include "Resources/FGResourceDescriptor.h"
#include "FGTutorialIntroManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FIntroSequenceStateUpdate );

//Steps in the intro tutorial
UENUM( BlueprintType )
enum class EIntroTutorialSteps :uint8
{
	ITS_NONE			UMETA( DisplayName = "No tutorial" ),
	ITS_INTRO			UMETA( DisplayName = "Intro state with message" ),
	ITS_DISMANTLE_POD	UMETA( DisplayName = "Dismantle drop pod" ),
	ITS_STUN_SPEAR		UMETA( DisplayName = "Equip stun spear" ),
	ITS_IRON_ORE		UMETA( DisplayName = "Pick up iron ore" ),
	ITS_HUB				UMETA( DisplayName = "Build a hub" ),
	ITS_HUB_LVL1		UMETA( DisplayName = "Upgrade Hub to lvl 1" ),
	ITS_HUB_LVL2		UMETA( DisplayName = "Upgrade Hub to lvl 2" ),
	ITS_HUB_LVL3		UMETA( DisplayName = "Upgrade Hub to lvl 3" ),
	ITS_HUB_LVL4		UMETA( DisplayName = "Upgrade Hub to lvl 4" ),
	ITS_HUB_LVL5		UMETA( DisplayName = "Upgrade Hub to lvl 5" ),
	ITS_DONE			UMETA( DisplayName = "Done with intro" )
};

USTRUCT( BlueprintType )
struct FTutorialHintData
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	EIntroTutorialSteps ID;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	FText Title;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	TArray< FText > HintTexts;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial" )
	TSubclassOf< class UFGMessageBase > Message;
};

struct FFindByIntroID
{
	EIntroTutorialSteps TutorialStep;

	FFindByIntroID( EIntroTutorialSteps InTutorialStep ) : TutorialStep( InTutorialStep ) { }

	bool operator() ( const FTutorialHintData Element ) const
	{
		return ( TutorialStep == Element.ID );
	}
};

UCLASS( abstract )
class FACTORYGAME_API AFGTutorialIntroManager : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	/** Get the tutorial intro manager, this should always return something unless you call it really early. */
	static AFGTutorialIntroManager* Get( UWorld* world );

	/** Get thetutorial intro manager from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "TutorialIntroManager", DisplayName = "GetTutorialIntroManager", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGTutorialIntroManager* Get( UObject* worldContext );

public:	
	AFGTutorialIntroManager();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaTime ) override;
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

	/** A player was added to the game */
	void AddPlayer( class AFGCharacterPlayer* inPlayer );

	/** Gamestate tells us what resource was just scanned for */
	void OnResourceScannedFor( TSubclassOf< UFGResourceDescriptor > resourceScannedFor );

	/** Called when the drop pod is dismantled. */
	void OnDismantleDropPod();

	UFUNCTION( BlueprintPure, Category = "Tutorial" )
	FORCEINLINE bool GetIsIntroSequenceDone() const { return mHasCompletedIntroSequence; }

	/** Are we done with the tutorial? */
	UFUNCTION( BlueprintPure, Category = "Tutorial" )
	FORCEINLINE bool GetIsTutorialCompleted() const { return mHasCompletedIntroTutorial; }

	/** Gets the current step we are at */
	UFUNCTION( BlueprintPure, Category = "Tutorial" )
	FORCEINLINE EIntroTutorialSteps GetCurrentTutorialStep() const { return mCurrentLocalTutorial; }

	/** Sets the tradingpost level to new value */
	void SetTradingPostLevel( int32 newLevel );

	/** Based on tutorial progression set player input gates */
	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void SetInputGatesFromTutorialLevel( class AFGPlayerController* playerController );

	struct FDisabledInputGate* GetInputGatesFromTutorialLevel();

	/** Spawns and sets up necessary stuff for the drop pod sequence */
	void SetupDropPod( class AFGCharacterPlayer* forPlayer );

	/** Do stuff when acknowledging that the tradingpost was build */
	void TradingPostWasBuilt();

	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void StartSkipIntroSequence();

	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void CancelSkipIntroSequence();

	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void EndSkipIntroSequence();

	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	float GetNormalizedProgressToSkip();

	UFUNCTION( BlueprintPure, Category = "Tutorial" )
	FORCEINLINE int32 GetTradingPostLevel() const { return mTradingPostLevel; }

	/** Completes the tutorial */
	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void CompleteTutorial();

	/** Called when the intro cinematic is done @SERVERONLY */
	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void IntroDone();

	/** Resets the tutorial progression from the ITS_HUB step. */
	void ResetHubTutorial();

	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void SetCanSkipTutorialIntro( bool canSkip );

	UFUNCTION( BlueprintPure, Category = "Tutorial" )
	FORCEINLINE bool GetCanSkipTutorial() const { return mCanIntroBeSkipped; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called when the local player builds anything */
	UFUNCTION()
	void OnBuildingBuiltGlobal( class AFGBuildable* buildable );

	/** Called when a schematic is unlocked */
	UFUNCTION()
	void OnSchematicPurchased( TSubclassOf< UFGSchematic > newSchematic );

	/** Updates progress in the tutorial to next step specified */
	UFUNCTION( BlueprintCallable, Category = "Tutorial" )
	void UpdateTutorial( EIntroTutorialSteps nextTutorialStep );

	/** Checks if it is time to push out the pending tutorial step */
	void HandlePendingTutorials();

	/** Clears the currently displayed hint widget in hud for when a tutorial step is completed */
	void ClearActiveTutorialHint();

	/** Called when a player gets an item in its inventory */
	UFUNCTION()
	void OnPlayerAddedItemToInventory( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	/** Called when a player gets an item in its arm slot */
	UFUNCTION()
	void OnPlayerAddedItemToArmSlot( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	/** Sets the status of mTradingPostBuilt */
	void SetTradingpostBuilt( bool hasbuilt );

	/** Checks if a tradingpost has ever been built */
	UFUNCTION( BlueprintPure, Category = "Tutorial" )
	FORCEINLINE bool HasTradingpostBeenBuilt() const{ return mTradingPostBuilt; }

	/** Called from IntroDone and only once per session */
	void OnIntroDone();

	UFUNCTION()
	void OnRep_TradingPostLevel();

public:
	/** Called when mHasCompletedIntroSequence updates */
	UPROPERTY(BlueprintAssignable,Category="Tutorial")
	FIntroSequenceStateUpdate mOnIntroSequenceStateUpdated;

protected:
	/** Has a trading post been built */
	UPROPERTY( SaveGame )
	bool mTradingPostBuilt;

	/** Returns true if we should skip the tutorial as we are in PIE */
	bool ShouldSkipTutorialDueToPIE() const;

	/** Set when the player force skips the intro sequence (landing of the pod up until full player control is regained) */
	bool mIsSkippingIntro;

	/** This is ensures we can only skip during certain parts of the intro sequence */
	bool mCanIntroBeSkipped;

private:	
	/** Array of pending tutorial IDs that should be shown when possible ( no other widgets on screen etc ) */
	UPROPERTY( Replicated, SaveGame )
	EIntroTutorialSteps mPendingTutorial;

	/** Array of pending tutorial IDs that should be shown when possible ( no other widgets on screen etc ) */
	EIntroTutorialSteps mCurrentLocalTutorial;

	/** Indicates if the player has completed the introduction tutorial */
	UPROPERTY( Replicated, EditDefaultsOnly, SaveGame, Category = "Tutorial" )
	bool mHasCompletedIntroTutorial;

	/** Indicates that the introduction sequence is done (right now, drop pod sequence) */
	UPROPERTY( SaveGame )
	bool mHasCompletedIntroSequence;

	/** The class of the trading post */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGBuildingDescriptor > mTradingPostDescriptor;

	/** Cached reference of trading post */
	UPROPERTY( SaveGame, Replicated )
	class AFGBuildableTradingPost* mTradingPost;

	/** Data used for the intro tutorial */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TArray< FTutorialHintData > mIntroTutorialData;

	/** Class of Iron Resource Descriptor */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGItemDescriptor > mIronOreDescriptor;

	UPROPERTY( SaveGame )
	bool mDidPickUpIronOre;

	/** An item you receive when dismantling the drop pod so we can identify it */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGItemDescriptor > mDropPodItemClass;
	
	/** Checks if we have dismantled the drop pod */
	UPROPERTY( SaveGame )
	bool mDidDismantleDropPod;

	/** class to identify the stun spear */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGItemDescriptor > mStunSpearItemClass;

	/** Checks if we equipped the stun spear */
	UPROPERTY( SaveGame )
	bool mDidEquipStunSpear;

	/** Reference to the class step 1 tutorial schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGSchematic > mStep1UpgradeSchematic;

	/** Bool for the step 1 schematic */
	UPROPERTY( SaveGame )
	bool mDidStep1Upgrade;

	/** Reference to the class step 2 tutorial schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGSchematic > mStep2UpgradeSchematic;

	/** Bool for the step 2 schematic */
	UPROPERTY( SaveGame )
	bool mDidStep2Upgrade;

	/** Reference to the class step 3 tutorial schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGSchematic > mStep3UpgradeSchematic;

	/** Bool for the step 3 schematic */
	UPROPERTY( SaveGame )
	bool mDidStep3Upgrade;

	/** Reference to the class step 4 tutorial schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGSchematic > mStep4UpgradeSchematic;

	/** Bool for the step 4 schematic */
	UPROPERTY( SaveGame )
	bool mDidStep4Upgrade;

	/** Reference to the class step 5 tutorial schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class UFGSchematic > mStep5UpgradeSchematic;

	/** Bool for the step5 schematic */
	UPROPERTY( SaveGame )
	bool mDidStep5Upgrade;

	/** Class of drop pod to spawn */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	TSubclassOf< class AFGStartingPod > mStartingPodClass;

	/** Reference to starting pod ( server only ) */
	UPROPERTY( Replicated )
	class AFGStartingPod* mStartingPod;

	/** Override for skipping the tutorial when playing in PIE */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" ) 
	bool mSkipTutorialInPIE;

	/** The upgrade level we have on our trading post */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_TradingPostLevel )
	int32 mTradingPostLevel;

	/** Time to wait after completing a minor tutorial step and displaying the next */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	float mWaitTimeAfterCompletingMinorStep;

	/** Time to wait after completing a trading post step and displaying the next */
	UPROPERTY( EditDefaultsOnly, Category = "Tutorial" )
	float mWaitTimeAfterCompletingHubStep;

	/** Time required to */
	UPROPERTY ( EditDefaultsOnly, Category = "Tutorial" )
	float mHoldTimeToSkipIntro;

	UPROPERTY ()
	FTimerHandle mHoldToSkipTimerHandle;

	/** Tracks the remaining time until we can start the next step */
	float mCurrentStepWaitTime;

	uint8 mStartupFrameCounter = 0; //[DavalliusA:Wed/03-04-2019] a way to stop initilization of the start value to trigger effect from changes
};
