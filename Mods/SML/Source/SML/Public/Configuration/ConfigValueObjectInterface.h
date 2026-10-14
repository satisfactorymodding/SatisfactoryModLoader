#pragma once
#include "CoreMinimal.h"
#include "Configuration/ConfigProperty.h"
#include "ConfigValueObjectInterface.generated.h"

UINTERFACE(Blueprintable, BlueprintType)
class SML_API UConfigValueObjectInterface : public UInterface {
    GENERATED_BODY()
};

class SML_API IConfigValueObjectInterface {
    GENERATED_BODY()
public:
    /** Returns the child property of this property with the specified key */
    UFUNCTION(BlueprintNativeEvent)
    UConfigProperty* GetChildProperty(const FString& PropertyKey);
};
