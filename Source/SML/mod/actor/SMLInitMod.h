#pragma once

#include "BasicModInit.h"
#include "CoreMinimal.h"
#include "FGSchematic.h"
#include "FGResearchTree.h"
#include "command/ChatCommandLibrary.h"
#include "mod/ModSubsystems.h"
#include "SMLInitMod.generated.h"

enum class ELifecyclePhase : uint8;

/** Use AInitGameWorld instead! */
UCLASS(Abstract, Blueprintable, Deprecated)
class SML_API ASMLInitMod : public ABasicModInit {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="This function is no longer supported. Use InitGameWorld.Init instead"))
	void PreInit();

	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="Use InitGameWorld.Init instead"))
	void Init();

	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="Use InitGameWorld.PostInit instead"))
	void PostInit();

	virtual void InitDefaultContent();

	UFUNCTION(BlueprintImplementableEvent, meta=(DeprecatedFunction, DeprecationMessage="Use GameModeDelegates and ContentRegistry instead"))
	void PlayerJoined(AFGPlayerController* Player);
private:
	friend class FModHandler;
	/** Called very early by mod loader once per game initialization on Actor CDO, intended to register legacy mod subsystems and tooltip providers. Big hack! */
	void RegisterEarlyLoadContent(const FString& ModReference) const;
	/** Called by registered FGameModeEvents delegate to call PlayerJoined */
	void PostPlayerLogin(class AGameModeBase* GameMode, class APlayerController* PlayerController);
	/** Performs initialization of this actor */
    virtual void DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(DeprecatedProperty, DeprecationMessage="Use InitGameWorld.mSchematics instead"))
	TArray<TSubclassOf<UFGSchematic>> mSchematics_DEPRECATED;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(DeprecatedProperty, DeprecationMessage="Use InitGameWorld.mResearchTrees instead"))
	TArray<TSubclassOf<UFGResearchTree>> mResearchTrees_DEPRECATED;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(DeprecatedProperty, DeprecationMessage="Use InitGameWorld.mChatCommands instead"))
	TArray<TSubclassOf<AChatCommandInstance>> mChatCommands_DEPRECATED;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(DeprecatedProperty, DeprecationMessage="Use InitGameInstance.mModSubsystems instead"))
	TArray<TSubclassOf<UModSubsystemHolder>> mModSubsystems_DEPRECATED;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(DeprecatedProperty, DeprecationMessage="Use InitGameInstance.mGlobalItemTooltipProviders instead"))
	TArray<UClass*> GlobalItemTooltipProviders_DEPRECATED;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(DeprecatedProperty, DeprecationMessage="Use InitGameWorld.mResourceSinkItemPointsTable instead"))
	TSoftObjectPtr<UDataTable> mResourceSinkItemPointsTable_DEPRECATED;
};