// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "FGUnlockEmote.generated.h"

/**
 * Unlocks the specified emotes
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockEmote : public UFGUnlock
{
	GENERATED_BODY()

	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

	UFUNCTION( BlueprintPure, Category="Emote" )
	FORCEINLINE TArray< TSubclassOf< class UFGEmote > > GetEmotesToUnlock() const { return mEmotes; }

protected:
	/** The emotes you get from this unlock */
	UPROPERTY( EditDefaultsOnly )
	TArray< TSubclassOf< class UFGEmote > > mEmotes;
	
};
