// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "FGInputMappingContext.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGInputMappingContext : public UInputMappingContext
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable, Category = "Mapping" )
	FKey FindKeyForInputAction(const FName& actionName);

	/** The display name of this input mapping context that will be shown in the UI */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping" )
	FText mDisplayName;

	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping" )
	float mMenuPriority;
};
