#include "GameInstanceInitSubsystem.h"

TArray<UInitGameInstance*> UGameInstanceInitSubsystem::GetInitGameInstanceList() const {
    return GameInstanceInitList;
}

UInitGameInstance* UGameInstanceInitSubsystem::GetInitGameInstanceByModReference(const FString& ModReference) const {
    UInitGameInstance* const* InitGameInstance = GameInstanceInitByModRef.Find(ModReference);
    return InitGameInstance ? *InitGameInstance : NULL;
}

void UGameInstanceInitSubsystem::CreateInitObjectForMod(const FString& ModReference, TSubclassOf<UInitGameInstance> ObjectClass) {
    UFGGameInstance* GameInstance = Cast<UFGGameInstance>(GetGameInstance());
    checkf(GameInstance, TEXT("Outer GameInstance is not UFGGameInstance"));
    
    const FString ObjectName = FString::Printf(TEXT("InitGameInstance_%s"), *ModReference);
    UInitGameInstance* InitGameInstance = NewObject<UInitGameInstance>(this, ObjectClass, *ObjectName);
    checkf(InitGameInstance, TEXT("Couldn't create InitGameInstance for %s"), *ModReference);

    //Initialize primary object information, register object in collections
    InitGameInstance->OwnerModReference = ModReference;
    InitGameInstance->OwnerGameInstance = GameInstance;
    GameInstanceInitList.Add(InitGameInstance);
    GameInstanceInitByModRef.Add(ModReference, InitGameInstance);
}

void UGameInstanceInitSubsystem::InitializeInitObjects() {
    for (UInitGameInstance* InitGameInstance : GameInstanceInitList) {
        InitGameInstance->DispatchInitialize();
    }
}
