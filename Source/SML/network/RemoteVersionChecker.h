#pragma once
#include "Object.h"
#include "mod/SemVersion.h"
#include "RemoteVersionChecker.generated.h"

UCLASS()
class NO_API USMLConnectionMetadata : public UObject {
    GENERATED_BODY()
public:
    bool bIsInitialized;
    TMap<FString, FVersion> InstalledClientMods;    
};

class FRemoteVersionChecker {
public:
    static void Register();
};
