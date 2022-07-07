// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	// End UCharacterMovementComponent Interface

protected:
	UPROPERTY()
	class AFGCreature* mCreature;
};
