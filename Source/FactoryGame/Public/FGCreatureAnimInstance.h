// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGCharacterAnimInstance.h"
#include "FGCreatureAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureAnimInstance : public UFGCharacterAnimInstance
{
	GENERATED_BODY()
public:
	UFGCreatureAnimInstance();

	/** Caching stuff */
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

public:
	/** Caching the creature */
	UPROPERTY( BlueprintReadOnly, Category = "Anim" )
	class AFGCreature* mCachedCreature;

	/** Whether or not the creature is threatened. Specifically being in Alert / Fight state. */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Anim" )
	bool mIsThreatened;
};
