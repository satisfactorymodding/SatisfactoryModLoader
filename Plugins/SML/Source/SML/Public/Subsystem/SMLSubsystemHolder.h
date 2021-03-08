#pragma once
#include "CoreMinimal.h"
#include "Subsystem/ModSubsystemHolder.h"
#include "SMLSubsystemHolder.generated.h"

UCLASS()
class SML_API USMLSubsystemHolder : public UModSubsystemHolder {
    GENERATED_BODY()
private:
    UPROPERTY()
    class AChatCommandSubsystem* ChatCommandSubsystem;
    UPROPERTY()
    class AModContentRegistry* ModContentRegistry;
public:
    FORCEINLINE AChatCommandSubsystem* GetChatCommandSubsystem() const { return ChatCommandSubsystem; }
    FORCEINLINE AModContentRegistry* GetModContentRegistry() const { return ModContentRegistry; }
	
    void InitSubsystems() override;
    void InitLocalSubsystems() override;
};
