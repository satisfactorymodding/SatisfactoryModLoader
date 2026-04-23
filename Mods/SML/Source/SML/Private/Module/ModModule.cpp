#include "Module/ModModule.h"

#include "Kismet/BlueprintAssetHelperLibrary.h"
#include "Misc/DataValidation.h"
#include "ModLoading/PluginModuleLoader.h"
#include "Module/GameInstanceModule.h"
#include "Module/GameWorldModule.h"
#include "Module/MenuWorldModule.h"
#include "UObject/Package.h"

#if WITH_EDITOR
EDataValidationResult UModModule::IsDataValid(FDataValidationContext& Context) const {
    EDataValidationResult ValidationResult = EDataValidationResult::Valid;
    
    //Check that we have exactly one module of this type marked as root
    UClass* ModuleClass = nullptr;
    if (IsA(UGameInstanceModule::StaticClass())) {
        ModuleClass = UGameInstanceModule::StaticClass();
    } else if (IsA(UGameWorldModule::StaticClass())) {
        ModuleClass = UGameWorldModule::StaticClass();
    } else if (IsA(UMenuWorldModule::StaticClass())) {
        ModuleClass = UMenuWorldModule::StaticClass();
    }

    if (!ModuleClass) {
        Context.AddError(FText::Format(NSLOCTEXT("ModModule", "RootModuleInvalidType", "Root module {0} has invalid type"), FText::FromString(GetName())));
        ValidationResult = EDataValidationResult::Invalid;
    } else {
        const FString OwnerPluginName = UBlueprintAssetHelperLibrary::FindPluginNameByObjectPath(GetPathName());
    
        //Discover modules by scanning classpath
        const TArray<FDiscoveredModule> DiscoveredModules = FPluginModuleLoader::FindRootModulesOfType(ModuleClass);

        TArray<FDiscoveredModule> ModulesInPlugin;
        for (const FDiscoveredModule& Module : DiscoveredModules) {
            if (Module.OwnerPluginName == OwnerPluginName) {
                ModulesInPlugin.Add(Module);
            }
        }

        if (ModulesInPlugin.Num() > 1) {
            TArray<FText> ModuleNames;
            for (const FDiscoveredModule& Module : ModulesInPlugin) {
                ModuleNames.Add(FText::FromString(Module.ModuleClass->GetPackage()->GetPathName()));
            }
            Context.AddError(FText::Format(NSLOCTEXT("ModModule", "RootModuleMultiple", "Multiple root modules of the same type found in the same mod. Fix by having at maximum only one root module of each type. Detected modules: {0}"), FText::Join(INVTEXT(", "), ModuleNames)));
            ValidationResult = EDataValidationResult::Invalid;
        }

        if (ModulesInPlugin.Num() == 0) {
            Context.AddError(NSLOCTEXT("ModModule", "RootModuleNone", "At least one module of this type was found in this mod, but none were marked as root. Fix by marking at least one as root."));
            ValidationResult = EDataValidationResult::Invalid;
        }
    }

    ValidationResult = FMath::Min(ValidationResult, Super::IsDataValid(Context));
    return ValidationResult;
}
#endif

UModModule* UModModule::SpawnChildModule(FName ModuleName, TSoftClassPtr<UModModule> ModuleClass) {
    //Make sure we are not attempting to spawn same module twice
    checkf(!ChildModules.Contains(ModuleName), TEXT("Module already loaded: %s"), *ModuleName.ToString());
    
    //Create new module, initialize it with data
    UClass* ModuleClassObject = ModuleClass.LoadSynchronous();
    check(ModuleClassObject);
    UModModule* ModModule = NewObject<UModModule>(this, ModuleClassObject, ModuleName);
    ModModule->SetOwnerModReference(GetOwnerModReference());

    //Trigger events that we already received ourselves on spawned module in same order
    for (ELifecyclePhase Phase : EventsReceived) {
        ModModule->DispatchLifecycleEvent(Phase);
    }

    //Add spawned module to the child module map
    ChildModules.Add(ModuleName, ModModule);
    return ModModule;
}

UModModule* UModModule::GetChildModule(FName ModuleName, TSubclassOf<UModModule> ModuleClass) {
    const TObjectPtr<UModModule>* ModModule = ChildModules.Find(ModuleName);
    //Check that module actually exists and its type matches type requested
    if (ModModule != NULL && (*ModModule)->IsA(ModuleClass)) {
        return *ModModule;
    }
    return NULL;
}

void UModModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    //Add event to received events, so later spawned child modules will receive it
    EventsReceived.Add(Phase);
    
    //Process phase event on already spawned child modules
    for (const TPair<FName, TObjectPtr<UModModule>>& ModModule : ChildModules) {
        ModModule.Value->DispatchLifecycleEvent(Phase);
    }
    
    //Trigger kismet OnLifecycleEvent callback
    K2_OnLifecycleEvent(Phase);
}

FString UModModule::LifecyclePhaseToString(ELifecyclePhase Phase) {
    UEnum* LifecyclePhase = StaticEnum<ELifecyclePhase>();
    return LifecyclePhase->GetNameStringByValue((int64) Phase);
}
