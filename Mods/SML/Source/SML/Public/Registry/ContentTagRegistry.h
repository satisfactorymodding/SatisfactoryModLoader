#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "ContentTagRegistry.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogContentTagRegistry, Log, All);

/**
  * Row struct for the data table tag assignment registration approach
  */
USTRUCT(BlueprintType)
struct SML_API FContentTagRegistryAddition : public FTableRowBase {
	GENERATED_BODY()

	FContentTagRegistryAddition() :
		Class(nullptr),
		TagContainer(FGameplayTagContainer::EmptyContainer)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer TagContainer;
};

/**
 * Manages Gameplay Tag Containers for content classes.
 * Enables any mod to apply Unreal Gameplay Tags to any mod's content,
 * or the base game's content, at the UClass level.
 * 
 * Add tags to content via this registry's provided avenues,
 * all returned tag containers are const.
 * 
 * Tag associations can only be modified before the subsystem's Begin Play,
 * after that moment the registry is frozen and no changes can be made after that.
 */
UCLASS()
class SML_API UContentTagRegistry : public UWorldSubsystem
{
	GENERATED_BODY()
public:
	UContentTagRegistry();

	/** Retrieves content tag registry instance. */
	UFUNCTION(BlueprintPure, Category = "Content Tag Registry", DisplayName = "GetContentTagRegistry", meta = (WorldContext = "WorldContext"))
	static UContentTagRegistry* Get(const UObject* WorldContext);

	/**
	 * Get the Gameplay Tag container for the supplied class.
	 * Could be an empty container there were no tags registered.
	 * 
	 * Returned container cannot be modified, use the registry's functions for that
	 */
	UFUNCTION(BlueprintPure, Category = "Content Tag Registry")
	const FGameplayTagContainer GetGameplayTagContainerFor(UClass* content);

	/**
	 * Register gameplay tags from the passed container to the passed class.
	 */
	UFUNCTION(BlueprintCallable, Category = "Content Tag Registry", CustomThunk)
	void AddGameplayTagsTo(UClass* content, const FGameplayTagContainer tags);

	/**
	 * Remove gameplay tags in passed container from the passed class if they were present.
	 */
	UFUNCTION(BlueprintCallable, Category = "Content Tag Registry", CustomThunk)
	void RemoveGameplayTagsFrom(UClass* content, const FGameplayTagContainer tags);

	UFUNCTION(BlueprintCallable, Category = "Content Tag Registry", CustomThunk)
	void RegisterTagAdditionTable(FName ModReference, UDataTable* TagTable);

	// Freezes the registry. No new registrations are accepted past this point.
	void FreezeRegistry();

	// Begin USubsystem interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	// virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	// End USubsystem interface

private:
	UPROPERTY()
	TMap<UClass*, FGameplayTagContainer> TagContainerRegistry;

	bool bRegistryFrozen{ false };

	static FString GetCallStackContext();

	/** Pointer to the currently active script callstack frame, used for debugging purposes */
	static FFrame* ActiveScriptFramePtr;

	bool CanModifyTagsOf(const UClass* content, FString& OutMessage);

	void ApplyTagsFromTable(FName ModReference, UDataTable* TagTable);

	/**
	  * Since tags init is delayed until the first add/fetch operation on that class,
	  * the registry itself must be able to add tags disregarding the freeze.
	  */
	void InternalAddGameplayTagsTo(UClass* content, const FGameplayTagContainer tags);
	
	FGameplayTagContainer* GetOrInitContainerFor(UClass* content);

	// Gets tags offered via SML Extended Attribute Provider
	FGameplayTagContainer GetTagsFromExtendedAttributeProvider(UClass* content);

	//Custom Thunks for calling Register functions through Reflection, primary point of which
	//is providing FFrame callstack context to the registration methods for debugging in seamless manner
	DECLARE_FUNCTION(execAddGameplayTagsTo);
	DECLARE_FUNCTION(execRemoveGameplayTagsFrom);
	DECLARE_FUNCTION(execRegisterTagAdditionTable);
};
