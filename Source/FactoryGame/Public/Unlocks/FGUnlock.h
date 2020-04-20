// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGUnlock.generated.h"

/**
 * Base class for unlocks that you get when purchasing/research a schematic
 */
UCLASS( Blueprintable, DefaultToInstanced, abstract, editinlinenew, Meta = ( AutoJSON = true ) )
class FACTORYGAME_API UFGUnlock : public UObject
{
	GENERATED_BODY()

public:
	/** Unlock is only called when you unlock this unlock the first time */
	UFUNCTION( BlueprintImplementableEvent, Category = Unlocks )
	void OnUnlock( class AFGUnlockSubsystem* unlockSubssytem );

	/** Unlock is only called when you unlock this unlock the first time */
	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem );

	/** Apply is called when you unlock this unlock the first time and every time the unlock is reapplied when a game is loaded */
	UFUNCTION( BlueprintImplementableEvent, Category = Unlocks )
	void OnApply( class AFGUnlockSubsystem* unlockSubssytem );

	/** Apply is called when you unlock this unlock the first time and every time the unlock is reapplied when a game is loaded */
	virtual void Apply( class AFGUnlockSubsystem* unlockSubssytem );

	/** Returns true if this unlock is allowed to be purchased more than once */
	UFUNCTION( BlueprintNativeEvent, Category = Unlocks )
	bool IsRepeatPurchasesAllowed() const;

	/** 
	*	To allow the unlock classes to spawn widgets we need to implement GetWorld even if it returns a nullptr 
	*	We use a provided worldcontext in blueprints to spawn widgets in these objects 
	*/
	virtual class UWorld* GetWorld() const override;


public:
	FORCEINLINE ~UFGUnlock() = default;
};
