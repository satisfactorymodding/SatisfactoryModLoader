#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "FGChatManager.h"
#include "GameFramework/PlayerController.h"
#include "SMLPlayerComponent.generated.h"

UCLASS(Blueprintable)
class SML_API USMLPlayerComponent : public UActorComponent {
	GENERATED_BODY()
public:
	/** Sends system chat message to the player it is attached*/
	UFUNCTION(BlueprintCallable, Reliable, Client)
	void SendChatMessage(const FString& message, const FLinearColor& color = FLinearColor::Green);

	/** Called client side to process chat command on server */
	UFUNCTION(BlueprintCallable, Reliable, Server, WithValidation = HandleChatCommand_Validate)
	void HandleChatCommand(const FString& commandLine);

	bool HandleChatCommand_Validate(const FString& commandLine);
	
	/*
	 * Returns USMLPlayerComponent instance attached
	 * to the given player controller
	 * Always returns something unless called very very early
	 */
	UFUNCTION(BlueprintPure)
	static USMLPlayerComponent* Get(APlayerController* player);
};