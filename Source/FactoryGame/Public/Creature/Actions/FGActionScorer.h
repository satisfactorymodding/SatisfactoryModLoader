// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "FGActionScorer.generated.h"

class UFGAction;

UCLASS( BlueprintType, Blueprintable, EditInlineNew )
class FACTORYGAME_API UFGActionTest : public UObject
{
	GENERATED_BODY()

public:
	UFGActionTest();
	
	UFUNCTION( BlueprintCallable )
	bool ExecuteTest();
	
	UFUNCTION(BlueprintCallable)
	virtual void Initialize( APawn* pawn, AController* controller, UFGAction* ownerAction );

	UFUNCTION(BlueprintImplementableEvent)
	void Initialize_Blueprint( APawn* pawn, AController* controller, UFGAction* ownerAction );
	
	UFUNCTION(BlueprintPure)
	APawn* GetPawn() const { return mPawn; }

	UFUNCTION(BlueprintPure)
	AController* GetController() const { return mController; }

	UFUNCTION(BlueprintPure)
	UFGAction* GetAction() const { return mOwnerAction; }

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Creature|Action|Interrupt")
    bool ExecuteCheck();

protected:
	/** Whether or not to invert the result of the test. */
	UPROPERTY( EditDefaultsOnly, Category = "Interrupt")
	bool mInvertCondition;
	
private:
	UPROPERTY()
	APawn* mPawn;
	UPROPERTY()
	AController* mController;

	UPROPERTY()
	UFGAction* mOwnerAction;
};

/**
 * 
 */
UCLASS(Blueprintable, EditInlineNew)
class FACTORYGAME_API UFGActionScorer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintNativeEvent, Category = "Scorer" )
	bool GetScore( float& out_score ) const;

	/** Initializes the action. Should be called by the action the scorer belongs to before use. */
	virtual void Initialize_Native( UFGAction* action );

	/* UObject **/
	virtual UWorld* GetWorld() const override;
	virtual void PostInitProperties() override;
	/* End of UObject **/

protected:
	/** Used to initialize the action scorer. Runs once.*/
	UFUNCTION( BlueprintNativeEvent, Category = "Scorer" )
	void InitializeScorer();

protected:
	UPROPERTY( BlueprintReadOnly, Category = "Scorer" )
	UFGAction* mAction;
};
