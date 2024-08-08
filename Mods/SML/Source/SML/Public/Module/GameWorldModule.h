#pragma once
#include "CoreMinimal.h"
#include "Module/WorldModule.h"
#include "GameWorldModule.generated.h"

/** World module initialized for normal game world only (e.g skipped for menu world) */
UCLASS(Blueprintable)
class SML_API UGameWorldModule : public UWorldModule {
    GENERATED_BODY()
public:
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(TArray<FText>& ValidationErrors) override;
#endif
	
    /**
    * List of schematics that will be automatically registered
    * by the SML during the loading phase
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<TSubclassOf<class UFGSchematic>> mSchematics;

    /**
    * List of MAM research trees that will be registered
    * by the SML during the loading phase
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<TSubclassOf<class UFGResearchTree>> mResearchTrees;

    /**
    * List of chat commands to register automatically on startup
    */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TArray<TSubclassOf<class AChatCommandInstance>> mChatCommands;

    /**
    * Table to use for obtaining AWESOME resource sink item point values
    * for items added by this mod.
    * 
    * The "Default" track (most factory parts are on this)
    */
    UPROPERTY(EditDefaultsOnly, Category = Advanced)
    TSoftObjectPtr<class UDataTable> mResourceSinkItemPointsTable;

    /**
    * Table to use for obtaining AWESOME resource sink item point values
    * for items added by this mod.
    * 
    * The "Exploration" track (only Alien DNA capsules are on this as of Update 7)
    */
    UPROPERTY(EditDefaultsOnly, Category = Advanced)
    TSoftObjectPtr<class UDataTable> mExplorationResourceSinkItemPointsTable;

    /**
    * Table to use for Content Tag Registry additions.
    * Useful for adding tags to content you don't control, for example,
    * items from the base game and other mods.
    */
    UPROPERTY(EditDefaultsOnly, Category = Advanced)
    TSoftObjectPtr<class UDataTable> mContentTagAdditionsTable;

	/** Mod subsystem actors to be registered automatically during construction phase */
	UPROPERTY(EditDefaultsOnly, Category= Advanced)
	TArray<TSubclassOf<class AModSubsystem>> ModSubsystems;

    /** Register content from properties here.
    Make sure to call super on the C++ side if you have both a C++ and Blueprint implementation. */
    virtual void DispatchLifecycleEvent(ELifecyclePhase Phase) override;
protected:
	/** Registers content at the construction phase */
	void RegisterConstructionPhaseContent();
	
    /** Registers default content from properties specified above */
    void RegisterDefaultContent();
};
