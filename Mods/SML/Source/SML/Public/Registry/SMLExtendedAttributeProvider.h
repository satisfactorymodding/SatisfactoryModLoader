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
    * Get the Gameplay Tags container for this asset.
    * Remember, since it's a BlueprintNativeEvent, to call from C++ you must call via ISMLExtendedAttributeProvider::Execute_GetGameplayTagsContainer
    */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="SML|Tags")
    FGameplayTagContainer GetGameplayTagsContainer();
};
