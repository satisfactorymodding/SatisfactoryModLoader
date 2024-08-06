#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SMLExtendedAttributeProvider.generated.h"

/**
* Unreal reflection stub class of ISMLExtendedAttributeProvider.
* Use this instead of ISMLExtendedAttributeProvider for UObject->Implements<ISMLExtendedAttributeProvider>()
*/
UINTERFACE(Blueprintable)
class SML_API USMLExtendedAttributeProvider : public UInterface {
    GENERATED_BODY()
};

/**
* Implement this on an asset to enable it to provide Gameplay Tags to other systems.
* 
* Example: Implement on an FGItemDescriptor and provide the SML.Registry.Item.SpecialItemDescriptor tag
* for the item to be considered "special" and filtered out by default by GetObtainableItemDescriptors
*/
class SML_API ISMLExtendedAttributeProvider {
    GENERATED_BODY()
public:

    /**
      * Gets the set of gameplay tags this UClass wishes to have in the Content Tag Registry.
      * TODO can we say UClass here? since it can be implemented on anything?
      * TODO should this be a const function? probably?
      * 
      * Use UContentTagRegistry::GetGameplayTagContainerFor to get the final tag container.
      */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SML|Tags")
    FGameplayTagContainer GetRequestedGameplayTags();
};
