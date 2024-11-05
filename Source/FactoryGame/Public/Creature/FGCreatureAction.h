// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGAction.h"

#include "AI/FGCreatureController.h"

#include "FGCreatureAction.generated.h"

UENUM( BlueprintType )
enum class ECreatureActionTargetSelectionType : uint8
{
	/** No target is required by the action. */
	None			UMETA( DisplayName = "None" ),

	/** The action will be used on the closest target. */
	Closest			UMETA( DisplayName = "Closest" ),

	/** The action will be used on a random target. */
	Random			UMETA( DisplayName = "Random" ),

	/** The action will be used on a random target, favoring targets with higher threat. */
	RandomWeighted	UMETA( DisplayName = "Random Weighted" ),

	/** The action will be used on the target with the highest aggro. */
	HighestAggro	UMETA( DisplayName = "Highest Aggro" ),
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FCreatureActionTargetParams
{
	GENERATED_BODY()
	
	/** How the target of the action should be selected. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	ECreatureActionTargetSelectionType TargetType = ECreatureActionTargetSelectionType::None;

	/** What kind of visibility requirement we have in order for a target to be considered. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	ETargetVisibilityRequirement VisibilityRequirement = ETargetVisibilityRequirement::TVR_None;

	/** The minimum amount of aggro a target needs to have in order to be considered. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	float MinimumAggro = 0.f;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FACTORYGAME_API UFGCreatureAction : public UFGAction
{
	GENERATED_BODY()

public:
	UFGCreatureAction( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual bool ExecuteAction() override;
	virtual bool InitializeAction( AController* controller, APawn* pawn ) override;
	virtual void Tick( float DeltaTime ) override;
	virtual bool SetupAction_Implementation() override;
	virtual bool CanPerformAction_Implementation() const override;
	virtual void CleanupAction_Implementation( bool actionSuccess ) override;
	// End UFGAction Interface

	virtual bool IsTickable() const override;

	FORCEINLINE class AActor* GetCurrentTarget() const { return mCurrentTarget.Get(); }

	FORCEINLINE bool ShouldCancelOnStateChange() const { return mCancelsOnStateChange; }

protected:
	virtual bool ExecuteMainAction() override;
	
	/** Whether or not the specified target is valid for this action. */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "Action" )
	bool IsValidTarget( AActor* Target ) const;

	UFUNCTION()
	virtual void OnCreatureStunUpdate( bool isStunned );

	UFUNCTION()
	virtual void OnMovementModeChanged( class ACharacter* character, EMovementMode previousMode, uint8 prevCustomMode );

	UFUNCTION()
	virtual void OnCreatureStateChanged( class AFGCreatureController* creatureController, ECreatureState previousState, ECreatureState newState );

	// Begin UFGAction Interface
	virtual void InternalActionCleanup( bool actionSuccess ) override;
	// End UFGAction Interface

private:
	void SetupTarget();

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_SetTarget( class AActor* target );

protected:

	/** The controller of the creature we belong to. */
	UPROPERTY(BlueprintReadOnly, Category="Action")
	TWeakObjectPtr<AFGCreatureController> mCreatureController;

	/** The creature we belong to. */
	UPROPERTY(BlueprintReadOnly, Category="Action")
	TWeakObjectPtr<AFGCreature> mCreature;

	/** The character movement component of our creature. */
	UPROPERTY( BlueprintReadOnly, Category="Action" )
	TWeakObjectPtr<UCharacterMovementComponent> mCharacterMovement;

	/** Cached value of the current target of the creature controller. */
	UPROPERTY(BlueprintReadOnly, Category="Action")
	TWeakObjectPtr<AActor> mCurrentTarget;
	
	/** Target requirements of the action. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General Settings")
	FCreatureActionTargetParams mTargetRequirements;

	/** Whether or not this action, as a pre / post action, should inherit the target from the parent action. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General Settings")
	bool mShouldInheritTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General Settings")
	bool mCancelsOnStateChange;
	
	UPROPERTY(BlueprintReadOnly)
	bool mReceivedStateChange;
	
	/** Whether or not the creature must be on the ground in order to use the action. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General Settings")
	bool mMustBeGrounded;

	/** Whether or not to cancel the action when we enter water. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="General Settings")
	bool mCancelIfSubmerged;
};
