#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SMLExtendedAttributeProvider.generated.h"

/**
* Unreal reflection stub class of ISMLExtendedAttributeProvider.
* Use this instead of ISMLExtendedAttributeProvider for checking Implements, ex. use UObject->Implements<USMLExtendedAttributeProvider>()
*/
UINTERFACE(Blueprintable)
class SML_API USMLExtendedAttributeProvider : public UInterface {
    GENERATED_BODY()
};

/**
 * Implement this on an asset to enable it to provide extra data to SML systems
 */
class SML_API ISMLExtendedAttributeProvider {
    GENERATED_BODY()
public:

    /**
      * Gets the set of gameplay tags the implementer wishes to have in the Content Tag Registry.
      * Tags are stored at the class level.
      * 
      * This should rarely be called directly.
      * Use UContentTagRegistry::GetGameplayTagContainerFor to get the final tag container.
      */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SML|Tags")
    const FGameplayTagContainer GetRequestedGameplayTags() const;
};
