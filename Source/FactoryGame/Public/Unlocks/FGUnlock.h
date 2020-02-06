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
UCLASS( DefaultToInstanced, abstract, editinlinenew )
class FACTORYGAME_API UFGUnlock : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintImplementableEvent, Category=Unlocks )
	void OnUnlock( class AFGUnlockSubsystem* unlockSubssytem );

	virtual void Unlock( class AFGUnlockSubsystem* unlockSubssytem );

	/** 
	*	To allow the unlock classes to spawn widgets we need to implement GetWorld even if it returns a nullptr 
	*	We use a provided worldcontext in blueprints to spawn widgets in these objects 
	*/
	virtual class UWorld* GetWorld() const override;

};
