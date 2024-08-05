#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "ContentTagRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogContentTagRegistry, All, All); // TODO set arg2 to Log once done with feature

/**
 * Manages Gameplay Tag Containers for content classes.
 * Enables any mod to apply Unreal Gameplay Tags to any mod's content,
 * or the base game's content, at the UClass level.
 * 
 * Add tags to content via this registry's provided avenues,
 * all returned tag containers are const.
 * 
 * Tag associations can only be made before save is loaded,
 * after that moment the registry is frozen and no changes can be made after that.
 */
UCLASS()
class SML_API UContentTagRegistry : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UContentTagRegistry();

	/** Retrieves content tag registry instance */
	UFUNCTION(BlueprintPure, Category = "Content Tag Registry", DisplayName = "GetContentTagRegistry", meta = (WorldContext = "WorldContext"))
	static UContentTagRegistry* Get(const UObject* WorldContext);

	/**
	 * Get the Gameplay Tag container for the supplied class.
	 * Could be an empty container there were no tags registered.
	 * 
	 * Returned container cannot be modified, use the registry's functions for that
	 * TODO outvar bool for found/not?
	 */
	UFUNCTION(BlueprintPure, Category = "Content Tag Registry")
	const FGameplayTagContainer GetGameplayTagContainerFor(const UObject* content);

	/**
	 * Register gameplay tags from the passed container to the passed class
	 * TODO do we want arg FName InRegistrationPluginName?
	 */
	UFUNCTION(BlueprintCallable, Category = "Content Tag Registry")
	void AddGameplayTagsTo(UObject* content, const FGameplayTagContainer tags);

	/**
	 * Remove gameplay tags in passed container from the passed class if they were present
	 * TODO do we want arg FName InRegistrationPluginName?
	 */
	UFUNCTION(BlueprintCallable, Category = "Content Tag Registry")
	void RemoveGameplayTagsFrom(UObject* content, const FGameplayTagContainer tags);

	// Used by the Mod Content Registry. Checks the passed content for tags offered via SML Extended Attribute Provider
	// TODO actually call this during mod content registration
	void AddTagsFromExtendedAttributeProvider(UObject* content);

	// Freezes the registry. No new registrations are accepted past this point.
	void FreezeRegistry();

	void OnActorPreSpawnInitialization(AActor* Actor);

	// Begin USubsystem interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	// End USubsystem interface

private:
	UPROPERTY()
	TMap<UObject*, FGameplayTagContainer> TagContainerRegistry;

	bool bRegistryFrozen{ false };

	DECLARE_MULTICAST_DELEGATE(FOnWorldBeginPlay);
	FOnWorldBeginPlay OnWorldBeginPlayDelegate;

	static FString GetCallStackContext();

	/** Pointer to the currently active script callstack frame, used for debugging purposes */
	static FFrame* ActiveScriptFramePtr;

	bool CanModifyTagsOf(UObject* content, FString& OutMessage);

};
