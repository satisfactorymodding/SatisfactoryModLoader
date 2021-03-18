// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once


DECLARE_DELEGATE_RetVal_ThreeParams( class USceneComponent*, FComponentDuplicator, class USceneComponent*, class UActorComponent*, const FName& );

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
	 */
	static void DuplicateComponents( TSubclassOf<class AActor> actorClass, class USceneComponent* defaultRoot, FComponentDuplicator duplicator );
};