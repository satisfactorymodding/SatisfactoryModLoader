// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "Templates/SubclassOf.h"
#include "FGCalendarSlotUnlockedDependency.generated.h"

UENUM()
enum class EUnlockDependencyType : uint8
{
	// Any Unlock
	Any			UMETA( DisplayName = "Any" ),

	// Random unlocks only
	Random		UMETA( DisplayName = "Random" )
};

UENUM()
enum class EItemUnlockRequirement : uint8
{
	// Any item in the list needs to be unlocked.
	Any		UMETA( DisplayName = "Any" ),

	// All items in the list need to be unlocked.
	All		UMETA( DisplayName = "All" )
};

/**
 * Dependency that's met if a calendar slot is unlocked.
 */
UCLASS()
class FACTORYGAME_API UFGCalendarSlotUnlockedDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	UFGCalendarSlotUnlockedDependency();

	virtual bool AreDependenciesMet( UObject* worldContext ) const override;

	int32 GetSlot() const { return mSlot; }
	EUnlockDependencyType GetUnlockType() const { return mUnlockType; }
	EItemUnlockRequirement GetUnlockedItemClassesRequirement() const { return mUnlockedItemClassesRequirement; }
	const TArray< TSubclassOf< class UFGItemDescriptor > >& GetUnlockedItemClasses() const { return mUnlockedItemClasses; }

#if WITH_EDITOR
    virtual FString ToString() const override;
    virtual void FromString( const FString& inString ) override;
#endif

protected:
	/** If >= 0, requires the specified slot to be unlocked. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	int32 mSlot;

	/** What kind of unlock this dependency requires. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	EUnlockDependencyType mUnlockType;

	/** How to treat the "Unlocked Item Classes" array. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	EItemUnlockRequirement mUnlockedItemClassesRequirement;

	/** What item classes must be part of the unlock for this dependency. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	TArray< TSubclassOf< class UFGItemDescriptor > > mUnlockedItemClasses;
};
