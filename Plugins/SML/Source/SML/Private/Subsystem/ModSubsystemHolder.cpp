#include "Subsystem/ModSubsystemHolder.h"
#include "FGGameState.h"
#include "Engine/World.h"

void UModSubsystemHolder::InitSubsystems()
{
}

void UModSubsystemHolder::InitLocalSubsystems()
{
}

AFGSubsystem* UModSubsystemHolder::K2_SpawnSubsystem(TSubclassOf<AFGSubsystem> SpawnClass, FName SpawnName) {
    if (!IsValid(SpawnClass)) {
        UE_LOG(LogTemp, Error, TEXT("ModSubsystems::SpawnSubsystem failed for '%s', no class given."), *SpawnName.ToString());
        return nullptr;
    }
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    SpawnParams.Name = SpawnName;

    return GetWorld()->SpawnActor<AFGSubsystem>(SpawnClass, SpawnParams);
}

UModSubsystemHolder* UModSubsystemHolder::K2_GetModSubsystemHolder(TSubclassOf<UModSubsystemHolder> HolderClass, UObject* WorldContextObject) {
    UWorld* World = WorldContextObject->GetWorld();
    checkf(World, TEXT("GetWorld not implemented for passed WorldContext object"));
    AFGGameState* GameState = World->GetGameState<AFGGameState>();
    if (GameState == nullptr)
        return nullptr;
    return Cast<UModSubsystemHolder>(GameState->FindComponentByClass(HolderClass));
}
