#pragma once
#include <xkeycheck.h>

#include "CoreMinimal.h"

class SML_API FCrashContextPatch {
public:
    static void ApplyModdedProperties(const struct FGenericCrashContext* CrashContext);
    static void AppendSymbolSearchPaths(FString& OutSearchPaths);
private:
    friend class FSatisfactoryModLoader;
    static TSharedPtr<struct BootstrapAccessors> BootstrapperAccessors;

    /** Setups patch with bootstrapper accessors */
    static void SetupWithAccessors(const BootstrapAccessors& Accessors);

    /** Registers patch */
    static void RegisterPatch();
};