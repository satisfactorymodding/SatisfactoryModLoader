#include "Patching/Patch/CrashContextPatch.h"
#include "GenericPlatform/GenericPlatformCrashContext.h"
#include "ModLoading/ModHandler.h"
#include "Patching/NativeHookManager.h"
#include "SatisfactoryModLoader.h"

void FCrashContextPatch::ApplyModdedProperties(const FGenericCrashContext* CrashContext) {
    const FString ModLoaderVersion = FSatisfactoryModLoader::GetModLoaderVersion().ToString();
    CrashContext->AddCrashProperty(TEXT("ModLoaderVersion"), *ModLoaderVersion);
    
    FGenericCrashContext::BeginSection(CrashContext->CommonBuffer, TEXT("LoadedMods"));
    
    const FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    if (ModHandler != NULL) {
        for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
            CrashContext->AddCrashProperty(*ModContainer->ModInfo.ModReference, *ModContainer->ModInfo.Version.ToString());
        }
    }
    
    FGenericCrashContext::EndSection(CrashContext->CommonBuffer, TEXT("LoadedMods"));
}

void FCrashContextPatch::RegisterPatch() {
    //Hook method required for custom information to crash properties
    SUBSCRIBE_METHOD_AFTER(FGenericCrashContext::AddPortableCallStack, [](const FGenericCrashContext* CrashContext) {
        ApplyModdedProperties(CrashContext);
    });
}
