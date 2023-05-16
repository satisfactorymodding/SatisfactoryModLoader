#pragma once
#include "CoreMinimal.h"
#include "Command/CommandSender.h"
#include "PlayerCommandSender.generated.h"

/**
 * Player command sender implementation
 * Requires AFGPlayerController to exist in the object outer chain to work correctly
 * It doesn't need to be immediate outer, though
 */
UCLASS()
class SML_API UPlayerCommandSender : public UCommandSender {
    GENERATED_BODY()
public:
    FString GetSenderName() const override;
    bool IsPlayerSender() const override;
    AFGPlayerController* GetPlayer() const override;
    void SendChatMessage(const FString& Message, const FLinearColor PrefixColor) override;
};
