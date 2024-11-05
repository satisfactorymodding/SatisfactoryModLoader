// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FGCreatureMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;

	// Begin UCharacterMovementComponent Interface
	virtual void OnCharacterStuckInGeometry( const FHitResult* Hit ) override;
	virtual void OnMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode ) override;
	virtual bool ResolvePenetrationImpl( const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation ) override;
	virtual bool ShouldRemainVertical() const override;
	// End UCharacterMovementComponent Interface

protected:
	UPROPERTY()
	class AFGCreature* mCreature;
};
