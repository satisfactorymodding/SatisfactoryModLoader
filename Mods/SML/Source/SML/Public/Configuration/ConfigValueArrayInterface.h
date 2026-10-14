#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigProperty.h"
#include "ConfigValueArrayInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class SML_API UConfigValueArrayInterface : public UInterface {
    GENERATED_BODY()
};

class SML_API IConfigValueArrayInterface {
    GENERATED_BODY()
public:
    /** Returns the child property of this property at the specified index */
    UFUNCTION(BlueprintNativeEvent)
    UConfigProperty* GetChildProperty(const int32 PropertyIndex);
};
