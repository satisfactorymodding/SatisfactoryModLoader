// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

class UStaticMeshComponent;
DECLARE_DELEGATE_RetVal_FourParams( class USceneComponent*, FComponentDuplicator, class USceneComponent*, class UActorComponent*, const FName&, const FName& );
DECLARE_DELEGATE_RetVal_TwoParams( class USceneComponent*, FAbstractInstanceDuplicator, class USceneComponent*, const struct FInstanceData& );

class FACTORYGAME_API FGComponentHelpers
{
public:
	/**
	 * Useful helper if you want duplicate the components of a actor class. Supports both native and blueprint components. 
	 * If you chose to not duplicate a component, you won't get the subcomponents of that component, as they don't know where
	 * to be attached correctly
	 *
	 * @param actorClass - the class we want to duplicate components from
	 * @param defaultRoot - when duplicating the native components, what should we attach the to
	 * @param duplicator - the delegate to call for each component that can filter and create new components
	 * @param abstractInstanceDuplicator delegate to handle the duplication of the abstract instance components, optional
	 * @param defaultRootSocketName - Name of the socket to attach to on the default root component, none by default
	 */
	static void DuplicateComponents( TSubclassOf<class AActor> actorClass, class USceneComponent* defaultRoot, FComponentDuplicator duplicator, const FAbstractInstanceDuplicator* abstractInstanceDuplicator = nullptr, FName defaultRootSocketName = NAME_None );
};