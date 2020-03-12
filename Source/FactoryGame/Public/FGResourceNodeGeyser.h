// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Resources/FGResourceNode.h"
#include "FGResourceNodeGeyser.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGResourceNodeGeyser : public AFGResourceNode
{
	GENERATED_BODY()

public:
	/** CTOR, who the hell is that? Some Star Wars robot? */
	AFGResourceNodeGeyser();

	// Begin IFGUseableInterface
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	// End IFGUseableInterface

public:
	FORCEINLINE ~AFGResourceNodeGeyser() = default;
};
