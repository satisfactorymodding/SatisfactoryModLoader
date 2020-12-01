#pragma once
#include "GameFramework/Actor.h"
#include "SMLInitMod.generated.h"

/** Use AInitGameWorld instead! */
UCLASS(Abstract, Blueprintable)
class SML_API ASMLInitMod : public AActor {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="This function is no longer supported. Use InitGameWorld.Init instead"))
	void PreInit();

	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="Use InitGameWorld.Init instead"))
	void Init();

	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="Use InitGameWorld.PostInit instead"))
	void PostInit();

	void InitDefaultContent();

	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="Use GameModeDelegates and ContentRegistry instead"))
	void PlayerJoined(class AFGPlayerController* Player);
private:
	friend class FModHandler;

	/** Owner mod reference stored in actor */
	FString ModReference;
	
	/** Called very early by mod loader once per game initialization on Actor CDO, intended to register legacy mod subsystems and tooltip providers. Big hack! */
	void RegisterEarlyLoadContent(const FString& ModReference, UGameInstance* GameInstance) const;
	/** Called by registered FGameModeEvents delegate to call PlayerJoined */
	void PostPlayerLogin(class AGameModeBase* GameMode, class APlayerController* PlayerController);
public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = (DeprecatedProperty, DeprecationMessage = "Use InitGameWorld.mSchematics instead"))
	TArray<TSubclassOf<class UFGSchematic>> mSchematics;

	UPROPERTY(VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = (DeprecatedProperty, DeprecationMessage = "Use InitGameWorld.mResearchTrees instead"))
	TArray<TSubclassOf<class UFGResearchTree>> mResearchTrees;

	UPROPERTY(VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = (DeprecatedProperty, DeprecationMessage = "Use InitGameWorld.mChatCommands instead"))
	TArray<TSubclassOf<class AChatCommandInstance>> mChatCommands;

	UPROPERTY(VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = (DeprecatedProperty, DeprecationMessage = "Use InitGameInstance.mModSubsystems instead"))
	TArray<TSubclassOf<class UModSubsystemHolder>> mModSubsystems;

	UPROPERTY(VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = (DeprecatedProperty, DeprecationMessage = "Use InitGameInstance.mGlobalItemTooltipProviders instead"))
	TArray<UClass*> GlobalItemTooltipProviders;

	UPROPERTY(VisibleDefaultsOnly, Category = "Deprecated - To be removed", meta = (DeprecatedProperty, DeprecationMessage = "Use InitGameWorld.mResourceSinkItemPointsTable instead"))
	TSoftObjectPtr<class UDataTable> mResourceSinkItemPointsTable;
};