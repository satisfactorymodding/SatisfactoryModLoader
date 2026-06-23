// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"

#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "UObject/NoExportTypes.h"
#include "FGWeatherReaction.generated.h"

/**
 * 
 */
class AFGSkySphere;

/* Weather states for replication.*/
UENUM()
enum class EWeatherInterpState : uint8
{
	EWeatherInterpState_Undefined,
	EWeatherInterpState_Begin,
	EWeatherInterpState_Active,
	EWeatherInterpState_Ending
};

UCLASS(Blueprintable)
class FACTORYGAME_API AFGWeatherReaction : public AInfo
{
	GENERATED_BODY()

	AFGWeatherReaction();
	
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
		
	UFUNCTION(BlueprintPure, Category = "Weather")
	AFGSkySphere* GetSkySphere() const { return mSkySphere; }

	// Begins the weather state, should only be called by server / listen server.
	void ServerBeginWeatherState();
	
	// Called by sky-sphere when interpolation into the weather state is finished, should only be called by server / listen server.
	void ServerFinishedEnterState();
	
	// Ends the weather state, should only be called by server / listen server.
	void ServerEndWeatherState();
	
	EWeatherInterpState GetCurrentState() const			{ return mCurrentState; }
	void ForceSetState( EWeatherInterpState NewState)	{ mCurrentState = NewState; }
	
protected:
	UFUNCTION( BlueprintImplementableEvent )
	void TransitionBeginWeatherState( float Dt, float Percentage );

	/* Blueprint event for updating the weather state. */
	UFUNCTION( BlueprintImplementableEvent )
	void TransitionEndWeatherState( float Dt, float Percentage );

	UFUNCTION( BlueprintNativeEvent )
	void OnTransitionFinished( bool bEventFinished );

	UFUNCTION( BlueprintNativeEvent )
	void StartWeatherState( AFGSkySphere* SkySphere );

	/* Will auto destroy once done. */
	UFUNCTION( BlueprintNativeEvent )
	void EndWeatherState( AFGSkySphere* SkySphere );
	
	/* seconds the transition takes.*/
	UPROPERTY( EditDefaultsOnly,BlueprintReadOnly )
	float TransitionTime;

private:
	UFUNCTION( )
	void OnRep_OnStateUpdated( EWeatherInterpState OldState );

	UPROPERTY( ReplicatedUsing = OnRep_OnStateUpdated )
	EWeatherInterpState mCurrentState = EWeatherInterpState::EWeatherInterpState_Undefined;
		

	/* Outer sky sphere actor.*/
	UPROPERTY() 
	TObjectPtr<AFGSkySphere> mSkySphere = {};

	/* is it stopping? or starting*/
	bool bIsWindingDown;

	// TODO handle replication for this.
	/* Time it spawned in the world*/
	float mSpawnTime = 0;

	/* World time the moment the weather effect started to fade out.*/
	float mEndStartTime = 0;
};
