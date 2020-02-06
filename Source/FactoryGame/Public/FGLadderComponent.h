// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Components/BoxComponent.h"
#include "FGLadderComponent.generated.h"


UCLASS( Blueprintable )
class FACTORYGAME_API UFGLadderComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UFGLadderComponent( const FObjectInitializer& ObjectInitializer );

	// Begin UActorComponent interface
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void TickComponent( float deltaTime, enum ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) override;
	// End UActorComponent interface

private:
	/** Callbacks */
	UFUNCTION()
	void BeginPotentialClimberOverlap( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool isFromSweep, const FHitResult& sweepResult );
	UFUNCTION()
	void EndPotentialClimberOverlap( UPrimitiveComponent* overlappedComp, AActor* other, UPrimitiveComponent* otherComp, int32 otherBodyIndex );

public:
	/** Direction we want to climb */
	FVector mClimbDirection;

	/** This is the way we are facing when climbing */
	FVector mWallDirection;

	/** Climbable angle in degrees. The player must be looking and moving within this angle relative to the ladder to climb it. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mClimbableLookAngle;

	/** Angle in degrees. If the player must be looking and moving within this angle relative to the ladder or else they will hop off. */
	UPROPERTY( EditDefaultsOnly, Category = "Ladder" )
	float mEndClimbingLookAngle;

private:
	/**
	 * List of players that can potentially climb on the ladder, i.e. within grab distance.
	 * Players that do climb on the ladder is also in this list.
	 */
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mPotentialClimbers;
};
