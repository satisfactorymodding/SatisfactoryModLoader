// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionLeapAttack.h"
#include "FGCreatureActionLeapGrabAttack.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureActionLeapGrabAttack : public UFGCreatureActionLeapAttack
{
	GENERATED_BODY()

public:
	UFGCreatureActionLeapGrabAttack( const FObjectInitializer& ObjectInitializer );

protected:

	// Begin UFGAction Interface
	virtual void CleanupAction_Implementation( bool actionSuccess ) override;
	// End UFGAction Interface
	
	// Begin UFGCreatureActionLeapAttack Interface
	virtual void ProcessHit_Implementation( class AFGCharacterBase* character, const FHitResult& hitResult ) override;
	virtual void OnCreatureLanded_Implementation( const FHitResult& hitResult ) override;
	virtual void OnHitCharacterCleared_Implementation( class AFGCharacterBase* character ) override;
	// End UFGCreatureActionLeapAttack Interface

protected:
	UPROPERTY()
	TArray< class AFGCharacterBase* > mGrabbedCharacters;

private:
	UFUNCTION()
	void OnGrabbedCharacterDied( AActor* characterActor );
	
	void GrabCharacter( class AFGCharacterBase* character );
	void DetachCharacter( class AFGCharacterBase* character );

protected:
	/** How many targets can be grabbed. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Grab" )
	int32 mMaxGrabTargets;
};
