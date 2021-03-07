#pragma once
#include <xkeycheck.h>

#include "CoreMinimal.h"

class SML_API FCrashContextPatch {
public:
    static void ApplyModdedProperties(const struct FGenericCrashContext* CrashContext);
private:
    friend class FSatisfactoryModLoader;

    /** Registers patch */
    static void RegisterPatch();
};