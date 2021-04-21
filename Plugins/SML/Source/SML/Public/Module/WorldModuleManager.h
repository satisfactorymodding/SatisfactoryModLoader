#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Module/WorldModule.h"
#include "WorldModuleManager.generated.h"

/** Manages registered world modules and their lifecycle events */
UCLASS(NotBlueprintable)
class SML_API UWorldModuleManager : public UWorldSubsystem {
    GENERATED_BODY()
private:
    /** Root map of modules for every registered mod reference */
    UPROPERTY()
    TMap<FName, UWorldModule*> RootModuleMap;

    /** Root module list for fast iteration according to order of registration */
    UPROPERTY()
    TArray<UWorldModule*> RootModuleList;
public:
	UWorldModuleManager();
	
    /** Retrieves world module by provided mod reference */
    UFUNCTION(BlueprintPure)
    UWorldModule* FindModule(const FName& ModReference) const;

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
private:
	bool bPostponeInitializeModules;
	bool bPostponePostInitializeModules;

	/** Called when game state is set on world, used to trigger postponed initialization on remote clients */
	void OnGameStateSet(class AGameStateBase* GameState);

	/** Called when game state is received and fully initialized (e.g on the next frame from OnGameStateSet) */
	void OnGameStateFullyInitialized();
	
	/** Called very early to construct module objects, right after world initialization */
	void ConstructModules();
	
    /** Called when world actors have been initialized */
    void InitializeModules(const UWorld::FActorsInitializedParams& Params);

    /** Called when world post initialization has been completed */
    void PostInitializeModules();

	/** Notifies content registry that modded content registration has been finished */
	void NotifyContentRegistry();
    
    /** Allocates root module object for instance and registers it */
    void CreateRootModule(const FName& ModReference, TSubclassOf<UWorldModule> ObjectClass);

    /** Dispatches lifecycle event to all registered modules */
    void DispatchLifecycleEvent(ELifecyclePhase Phase);
};