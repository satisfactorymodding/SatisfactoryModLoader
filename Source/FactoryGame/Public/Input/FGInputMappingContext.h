// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	/** The display name of this input mapping context that will be shown in the UI */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping" )
	FText mDisplayName;

	/** The order in menus is decided by this value. Lower values means earlier in menu. Negative values are allowed. [-N..0..N]*/
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping" )
	float mMenuPriority;

	/**
	 * The parent context for this mapping context
	 * The child contexts will automatically get bound or unbound when their parent context state changes
	 * Main use case of this are extending existing input contexts on the game subsystems for e.g. mods
	 */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Mapping" )
	TSoftObjectPtr<UFGInputMappingContext> mParentContext;
};
