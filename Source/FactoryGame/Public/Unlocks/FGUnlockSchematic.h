// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Unlocks/FGUnlock.h"
#include "FGUnlockSchematic.generated.h"

/**
 * Unlocks/Purchases the specified schematics
 */
UCLASS( Blueprintable, EditInlineNew, abstract, DefaultToInstanced )
class FACTORYGAME_API UFGUnlockSchematic : public UFGUnlock
{
	GENERATED_BODY()
	
public:
	// Begin FGUnlock interface
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem ) override;
	// End FGUnlock interface

	/** Add schematics to the array of schematics that this unlock gives the player */
	void AddSchematics( TArray< TSubclassOf< class UFGSchematic > > schematics );

	/** Returns the schematic that this schematic unlocks */
	UFUNCTION( BlueprintPure, Category = Unlocks )
	FORCEINLINE TArray< TSubclassOf< class UFGSchematic > > GetSchematicsToUnlock() const { return mSchematics; }

public: // MODDING EDIT: protected -> public
	/** The schematics you get from this unlock */
	UPROPERTY( BlueprintReadWrite, EditDefaultsOnly ) // MODDING EDIT: BPRW
	TArray< TSubclassOf< class UFGSchematic > > mSchematics;


public:
	FORCEINLINE ~UFGUnlockSchematic() = default;
};
