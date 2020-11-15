#include "Patching/Patch/CrashContextPatch.h"
#include "bootstrapper_exports.h"
#include "GenericPlatformCrashContext.h"
#include "ModHandler.h"
#include "NativeHookManager.h"
#include "SatisfactoryModLoader.h"
#include "WindowsPlatformStackWalk.h"

void FCrashContextPatch::ApplyModdedProperties(const FGenericCrashContext* CrashContext) {
    CrashContext->BeginSection(TEXT("ModdingProperties"));
        
    const FString ModLoaderVersion = FSatisfactoryModLoader::GetModLoaderVersion().ToString();
    CrashContext->AddCrashProperty(TEXT("ModLoaderVersion"), *ModLoaderVersion);

    const TMap<FName, FString> ExtraAttributes = FSatisfactoryModLoader::GetExtraAttributes();
    if (ExtraAttributes.Contains(FModLoaderExtraAttributes::EA_BootstrapperVersion)) {
        const FString BootstrapperVersion = ExtraAttributes.FindChecked(FModLoaderExtraAttributes::EA_BootstrapperVersion);
        CrashContext->AddCrashProperty(TEXT("BootstrapperVersion"), *BootstrapperVersion);
    }

    CrashContext->BeginSection(TEXT("LoadedMods"));
    
    const FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    if (ModHandler != NULL) {
        for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
            CrashContext->AddCrashProperty(*ModContainer->ModInfo.ModReference, *ModContainer->ModInfo.Version.ToString());
        }
    }
    
    CrashContext->EndSection(TEXT("LoadedMods"));
    
    CrashContext->EndSection(TEXT("ModdingProperties"));  
}

void* BootstrapperFMemoryMallocWrapper(uint64 Size) {
    return FMemory::Malloc(Size);
}

void FCrashContextPatch::AppendSymbolSearchPaths(FString& OutSearchPaths) {
    if (BootstrapperAccessors.IsValid()) {
        wchar_t* SymbolFileRoots = BootstrapperAccessors->GetSymbolFileRoots(&BootstrapperFMemoryMallocWrapper);
        OutSearchPaths.AppendChar(';');
        OutSearchPaths.Append(SymbolFileRoots);
        FMemory::Free(SymbolFileRoots);
    }
}

void FCrashContextPatch::SetupWithAccessors(const BootstrapAccessors& Accessors) {
    BootstrapperAccessors = MakeShareable(new BootstrapAccessors(Accessors));
}

void FCrashContextPatch::RegisterPatch() {
    //Hook methods required for providing PDB locations and adding custom information to crash properties
    SUBSCRIBE_METHOD(FWindowsPlatformStackWalk::GetDownstreamStorage, [](auto& Call) {
             FString OriginalResult = Call();
             AppendSymbolSearchPaths(OriginalResult);
             Call.Override(OriginalResult);
    });
    SUBSCRIBE_METHOD_AFTER(FGenericCrashContext::AddPortableCallStack, [](const FGenericCrashContext* CrashContext) {
        ApplyModdedProperties(CrashContext);
    });

    //Flush mod symbols now because by the time it is called are mods are already loaded
    //Ensure StackWalker is initialized before flushing symbols
    ANSICHAR TmpBuffer[100];
    FGenericPlatformStackWalk::StackWalkAndDump(TmpBuffer, ARRAY_COUNT(TmpBuffer), 0);
    
    //Flush bootstrapper cached symbols
    if (BootstrapperAccessors.IsValid()) {
        BootstrapperAccessors->FlushDebugSymbols();
    }
}
