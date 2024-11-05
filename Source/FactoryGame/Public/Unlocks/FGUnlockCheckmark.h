// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGUnlockInfoOnly.h"
#include "FGUnlockCheckmark.generated.h"

USTRUCT(BlueprintType)
struct FGCheckmarkUnlockData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Checkmark")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Checkmark")
	FDateTime UnlockTime;

	FGCheckmarkUnlockData()
	{
		// PlayerName = FString::Empty();
		// UnlockTime = FDateTime::Now();
	}

	FGCheckmarkUnlockData( FString playerName )
	{
		PlayerName = playerName;
		UnlockTime = FDateTime::Now();
	}

	FGCheckmarkUnlockData(FString playerName, FDateTime unlockTime)
	{
		PlayerName = playerName;
		UnlockTime = unlockTime;
	}

	bool IsValid() const
	{
		return !PlayerName.IsEmpty();
	}

	bool operator==(const FGCheckmarkUnlockData& other) const
	{
		return PlayerName == other.PlayerName;
	}
};

/**
 * 
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockCheckmark : public UFGUnlockInfoOnly
{
	GENERATED_BODY()

	// Begin FGUnlock interface
	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem ) override;

	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

	UFUNCTION( BlueprintCallable, Category = Unlocks )
	bool HasPlayerUnlockedCheckmark( class APlayerController* playerController, class AFGUnlockSubsystem* unlockSubsystem );
};
