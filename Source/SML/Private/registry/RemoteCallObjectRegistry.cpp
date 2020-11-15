#include "Registry/RemoteCallObjectRegistry.h"


#include "FGGameMode.h"
#include "GameFramework/GameModeBase.h"

void URemoteCallObjectRegistry::RegisterRemoteCallObject(TSubclassOf<UFGRemoteCallObject> RemoteCallObject) {
    URemoteCallObjectRegistry* Registry = GetMutableDefault<URemoteCallObjectRegistry>();
    check(RemoteCallObject);
    Registry->RegisteredRCOs.AddUnique(RemoteCallObject);
}

void URemoteCallObjectRegistry::RegisterRCOsOnGameMode(AGameModeBase* GameMode) {
    const URemoteCallObjectRegistry* Registry = GetDefault<URemoteCallObjectRegistry>();
    AFGGameMode* FactoryGameMode = Cast<AFGGameMode>(GameMode);
    if (FactoryGameMode != NULL) {
        for (const TSubclassOf<UFGRemoteCallObject>& RCO : Registry->RegisteredRCOs) {
            FactoryGameMode->RegisterRemoteCallObjectClass(RCO);
        }
    }
}

void URemoteCallObjectRegistry::InitializeRegistry() {
    FGameModeEvents::GameModeInitializedEvent.AddStatic(URemoteCallObjectRegistry::RegisterRCOsOnGameMode);
}
