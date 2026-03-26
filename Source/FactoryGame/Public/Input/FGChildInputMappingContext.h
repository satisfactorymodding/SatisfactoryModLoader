// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Input/FGInputMappingContext.h"
#include "FGChildInputMappingContext.generated.h"

/**
 * Child mapping contexts are input mapping contexts that are automatically bound when their parent input context is bound
 * They can be used for extending existing mapping contexts in a modular fashion, e.g. from game feature plugins or mods
 * Child mapping contexts, unlike their parent contexts, are primary data assets and are discovered automatically through Asset Manager
 */
UCLASS()
class FACTORYGAME_API UFGChildInputMappingContext : public UFGInputMappingContext
{
	GENERATED_BODY()
public:
	// Begin UObject interface
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	// End UObject interface

	/**
	 * The parent context for the given mapping context
	 * The child contexts will automatically get bound or unbound when their parent context state changes
	 * Main use case of this are extending existing input contexts on the game subsystems for e.g. mods
	 */
	UPROPERTY( EditAnywhere, Category = "Mapping" )
	TSoftObjectPtr<UFGInputMappingContext> mParentContext;
};
