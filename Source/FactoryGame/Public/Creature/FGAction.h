// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Actions/FGActionScorer.h"
#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Tickable.h"
#include "HAL/IConsoleManager.h"
#include "FGAction.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogAction, Log, All );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FActionFinished, bool, Success );

extern TAutoConsoleVariable< int32 > CVarActionDebug;

UENUM(BlueprintType)
enum EFGActionState
{
	EAS_Uninitialized,
	EAS_Initialized,
	EAS_Setup,
	EAS_RunningPreAction,
	EAS_RunningMainAction,
	EAS_RunningPostAction,
	EAS_Cancelled,
	EAS_Finished,
	EAS_Failed
};

/** Actions that can be performed by creatures.
 *	Override ExecuteAction, Tick and FinishAction for custom behaviors.
 *	Can be set to have custom tick behaviors
 */
UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew, AutoExpandCategories=("Action"))
class FACTORYGAME_API UFGAction : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

public:		// PUBLIC FUNC
	/** ctor */
	UFGAction(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitProperties() override;
	virtual bool CallRemoteFunction (UFunction * Function, void * Parms, struct FOutParmRec * OutParms, FFrame * Stack) override;
	virtual int32 GetFunctionCallspace (UFunction* Function, FFrame* Stack) override;
	virtual bool IsSupportedForNetworking () const override { return true; };
	virtual bool IsNameStableForNetworking() const override { return true; }
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category="Action")
	FORCEINLINE TEnumAsByte<EFGActionState> GetActionState() const { return mActionState; }
	
	/** Must be first called before using the action. Sets who the action belongs to. */
	UFUNCTION(BlueprintCallable, Category="Action")
	virtual bool InitializeAction(AController* controller, APawn* pawn);
	
	/** Has the action been initialized? If not, Do not do anything with it and make sure it gets initialized. */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE bool HasBeenInitialized() const { return mActionState != EAS_Uninitialized; }

	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE FString GetActionDescription() const { return GetActionDescription_Native(); }

	// Native version so we can use const ref
	FORCEINLINE const FString& GetActionDescription_Native() const { return mActionDescription; }

	/** Override to perform custom action setup (can be anything that needs to be done everytime before running/scoring the action) */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	bool SetupAction();

	/** Processes and returns the sum of all the action scorers. Must return true if the action is to be considered at all. */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category="Action")
	bool ScoreAction(float& score) const;

	/** Check if the requirements to execute the action are met and return true is they are, false if they aren't. */
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category="Action")
	bool CanPerformAction() const;

	/** Returns true if the action is still ongoing */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE bool IsActionExecuting() const { return mActionState == EAS_RunningMainAction || mActionState == EAS_RunningPreAction || mActionState == EAS_RunningPostAction; }

	/** To start the execution of the action. This function shouldn't be overriden unless you really know what you are doing.
	 *	Will always call PerformAction, which can be overriden for custom behaviors.
	 *	Will call FinishAction if the Action is not set to be Tickable.*/
	UFUNCTION(BlueprintCallable, Category="Action")
	virtual bool ExecuteAction();

	/** Where the actual action is performed. Override to create custom behaviors!
	 * In the case of Actions that last over time, you might want to override ActionTick as well to check for when you want your action to finish.*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void PerformAction();

	/** Called to cancel the execution of the action. Skips Recovery time
	 *	 Broadcasts OnActionFinished*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void CancelAction();

	/** For overriding behavior of actions that should do stuffs while they run. i.e: multi-step action that wait for animation */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Action")
	void ActionTick(float DeltaTime);

	/** Called to finish the execution of the action. Has recovery time, regardless of success.
	 * Broadcasts OnActionFinished.*/
	UFUNCTION(BlueprintCallable, Category="Action")
	void FinishAction(bool ActionSuccess);

	/** Returns cooldown between action execution/finish */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE float GetActionCooldown() const { return mActionCooldown; }

	/** Returns maximum cooldown between action execution/finish */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE float GetActionCooldownMax() const { return mActionCooldownMax; }

	/** Returns when the action last executed in unpaused game seconds. */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE float GetActionLastExecuteTime() const { return mActionLastExecuteTime; }

	/** Manually sets the time the action last executed/performed. Can be used to bypass internal logic or creating custom logic. */
	UFUNCTION(BlueprintCallable, Category="Action")
	void SetActionLastExecuteTime(float executeTime) { mActionLastExecuteTime = executeTime; }

	/** Returns when the action last finished in unpaused game seconds. */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE float GetActionLastFinishTime() const { return mActionLastFinishTime; }

	/** Manually sets the time the action last finished. Can be used to bypass internal logic or creating custom logic. */
	UFUNCTION(BlueprintCallable, Category="Action")
	void SetActionLastFinishTime(float finishTime);

	/** Is it in cooldown? True/False */
	UFUNCTION(BlueprintPure, Category="Action")
	bool IsInCooldown() const;

	UFUNCTION(BlueprintPure, Category="Action")
	bool HasAuthority() const;

	/** How long is left on cooldown? */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE float GetRemainingCooldown() const { return GetWorld() ? FMath::Clamp( mActionLastFinishTime + mCurrentActionCooldown - GetWorld()->GetTimeSeconds(), 0.f, mCurrentActionCooldown ) : -1.f ; }

	/** Returns the pawn the action is being performed on. Can be used for playing montage etc. */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE APawn* GetPawn() const { return mPawn.Get(); }

	/** Returns the controller that this action "belongs" to */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE AController* GetController() const { return mController.Get(); }

	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE UFGAction* GetPreAction() const { return mPreAction; }

	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE UFGAction* GetPostAction() const { return mPostAction; }

	/** If we are a pre or post action this is our parent action. */
	UFUNCTION(BlueprintPure, Category="Action")
	FORCEINLINE UFGAction* GetParentAction() const { return mParentAction; }
	
	/** FTickableGameObject */

	/** Only Internal ticking stuffs here. */
	virtual void Tick( float DeltaTime ) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual bool IsTickableInEditor() const override;
	virtual TStatId GetStatId() const override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual UWorld* GetWorld() const override;						// Needed for world context and KismetLibrary use
	virtual UWorld* GetTickableGameObjectWorld() const override;	// Needed for world context and KismetLibrary use
	/** End FTickableGameObject */

public:		// PUBLIC MEMBERS
	/** Register to this Delegate to be informed of when the action has finished executing. */
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Action")
	FActionFinished OnActionFinished;

protected:	// PROTECTED FUNC

	virtual bool ExecutePreAction();

	virtual bool ExecuteMainAction();

	virtual bool ExecutePostAction();
	
	/** Setter for mActionState. Should only be used in derived classes if you know what you are doing or you will break things.. */
	UFUNCTION(BlueprintCallable, Category="Action|Advanced")
	void SetActionState( EFGActionState newState );
	
	/** Called whenever execution of an action finishes. Either by being finished or cancelled. */
	UFUNCTION(BlueprintNativeEvent, Category="Action")
	void CleanupAction(bool actionSuccess);

	/** Called when the pre-action has been ran and finished. Only used if the pre-action doesn't finish instantly */
	UFUNCTION()
	void OnPreActionFinished(bool success);

	virtual void InternalActionCleanup( bool actionSuccess );

protected:	// PROTECTED MEMBERS
	/** Each scorer gives a weight and they are summed up when called "ScoreAction" */
	UPROPERTY(EditAnywhere, Instanced, Category="Scoring, Interrupt & Filtering")
	TArray<UFGActionScorer*> mActionScorers;

	/** Tests that perform at the beginning of every tick whilst an action runs.
	 * If any of them succeeds, the action gets cancelled.
	 * No tests = no interruption */
	UPROPERTY(EditAnywhere, Instanced, Category="Scoring, Interrupt & Filtering")
	TArray<UFGActionTest*> mActionInterrupts;

	UPROPERTY(EditAnywhere, Category="General Settings")
	FString mActionDescription = "";
	
	/** Action will automatically finish after this amount of time. */
	UPROPERTY(EditAnywhere, Category="General Settings", meta=(ClampMin=0))
	FFloatInterval mActionDuration;

	/** Whether or not the action should successfully finish once its duration is over. */
	UPROPERTY(EditAnywhere, Category="General Settings")
	bool mActionDurationFinishResult;

	/** The start of the action will be delayed by a random time in this range. */
	UPROPERTY(EditAnywhere, Category="General Settings", meta=(ClampMin=0))
	FFloatInterval mActionStartDelay;
	
	/** Minimum time between Actions executions in seconds. Cooldown begins after recovery is done. */
	UPROPERTY(EditAnywhere, Category="General Settings")
	float mActionCooldown = 5.f;

	/** Maximum time between Actions executions in seconds. Cooldown begins after recovery is done. */
	UPROPERTY(EditAnywhere, Category="General Settings")
	float mActionCooldownMax = 0.f;

	/** Time it takes to recover after the action has finished. */
	UPROPERTY(EditAnywhere, Category="General Settings")
	float mActionRecoveryTime = 1.f;

	/** Maximum time it takes to recover after the action has finished*/
	UPROPERTY(EditAnywhere, Category="General Settings")
	float mActionRecoveryTimeMax = 0.f;

	/** Last unpaused game time it got executed at */
	UPROPERTY(BlueprintGetter=GetActionLastExecuteTime, BlueprintSetter=SetActionLastExecuteTime, Category="Action")
	float mActionLastExecuteTime = -1.f;

	/** Last unpaused game time it finished/got cancelled at */
	UPROPERTY(BlueprintGetter=GetActionLastFinishTime, BlueprintSetter=SetActionLastFinishTime, Category="Action")
	float mActionLastFinishTime = -1.f;

	/** Can this action be ticked and run until FinishAction gets called? */
	UPROPERTY(EditAnywhere, Category="Tick")
	bool mIsActionTickable = true;

	/** Can this action tick when the game is paused? */
	UPROPERTY(EditAnywhere, Category="Tick")
	bool mIsActionTickableWhenPaused = false;

	/** Can this Action tick standalone in editor? Could be useful for standalone testing. */
	UPROPERTY(EditAnywhere, Category="Tick")
	bool mIsActionTickableInEditor = false;

	/** Action to run in the same way as post action, but *before* the actual action runs (i.e: Relocate to range) */
	UPROPERTY(EditAnywhere, Instanced, Category="Linked Actions")
	UFGAction* mPreAction = nullptr;

	/** Ability to chain actions. Post action will execute when the current action successfully finishes.
	  * Post Action Setup checks happens at the same as the current action.
	  * Scoring and CanPerform are ignored for post actions, they simply execute if they can perform and their parent (this) executes.*/
	UPROPERTY(EditAnywhere, Instanced, Category="Linked Actions")
	UFGAction* mPostAction = nullptr;

	/** The pawn performing the action */
	UPROPERTY()
	TWeakObjectPtr<APawn> mPawn = nullptr;

	/** The Controller of the pawn performing the action */
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AController> mController = nullptr;

private:	// PRIVATE FUNC
	void ClearTimers();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_RepActionState(EFGActionState newState);

private:	// PRIVATE MEMBERS
	/** State of the action, used to control action flow */
	UPROPERTY()
	TEnumAsByte<EFGActionState> mActionState;

	/** Timer to handle timeout */
	UPROPERTY()
	FTimerHandle mActionTimeoutTimerHandle;

	/** Timer to handle recovery when action ends */
	UPROPERTY()
	FTimerHandle mActionRecoveryTimerHandle;

	/** Timer to handle actions starting with a delay */
	UPROPERTY()
	FTimerHandle mActionStartDelayHandle;

	/** If we are a pre or post action this is our parent action. */
	UPROPERTY()
	UFGAction* mParentAction;

	/** The duration of the current execution of this action, as specified by mActionDuration. */
	float mCurrentActionDuration;

	/** The current cooldown duration, random value between mActionCooldown and mActionCooldownMax. */
	float mCurrentActionCooldown;
};
