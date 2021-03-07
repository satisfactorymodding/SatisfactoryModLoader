#pragma once
#include "Configuration/ConfigManager.h"
#include "Configuration/ConfigValue.h"
#include "RootConfigValueHolder.generated.h"

class UConfigValueSection;

UCLASS(NotBlueprintable)
class SML_API URootConfigValueHolder : public UObject, public IConfigValueDirtyHandlerInterface {
    GENERATED_BODY()

    //Begin IConfigValueDirtyHandlerInterface
    virtual void MarkDirty_Implementation() override;
    //End IConfigValueDirtyHandlerInterface

    FORCEINLINE UConfigValueSection* GetWrappedValue() const { return RootWrappedValue; }
private:
    friend class UConfigManager;
    
    void SetupRootValue(UConfigManager* ConfigManager, const FConfigId& ConfigId, UConfigValueSection* ConfigValue);

    void UpdateWrappedValue(UConfigValueSection* NewWrappedRootValue);
    
    FConfigId ConfigId;
    UPROPERTY()
    UConfigValueSection* RootWrappedValue;
    UPROPERTY()
    UConfigManager* ConfigManager;
};
