#pragma once
#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"

class SML_API FOfflinePlayerHandler {
public:
    static FString GetOfflineUsernameOverride();
    static FUniqueNetIdRepl GenerateUniqueNetIdFromUsername(const FString& Username);
private:
    friend class FSatisfactoryModLoader;

    static void RegisterHandlerPatches();
};
