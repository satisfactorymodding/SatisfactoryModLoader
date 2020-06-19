#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "command/ChatCommandLibrary.h"
#include "mod/SemVersion.h"

#include "SMLPlayerComponent.generated.h"

UCLASS()
class SML_API UPlayerCommandSender : public UCommandSender {
	GENERATED_BODY()
public:
	FString GetSenderName() const override;
	bool IsPlayerSender() const override;
	AFGPlayerController* GetPlayer() const override;
	void SendChatMessage(const FString& Message, const FLinearColor PrefixColor) override;
};

UCLASS(BlueprintType)
class SML_API USMLPlayerComponent : public UActorComponent {
	GENERATED_BODY()
public:
	/* Command sender used for given player */
	UPROPERTY(BlueprintReadOnly)
	UCommandSender* CommandSender;
	/* List of mods installed on the client side */
	UPROPERTY()
	TMap<FString, FVersion> ClientInstalledMods;

	/** Returns true whenever provided mod is installed on client side */
	UFUNCTION(BlueprintPure)
	bool IsClientModInstalled(const FString& ModId) const;

	/** Returns version of the mod installed on client side. Returns 0.0.0 if mod is not installed */
	UFUNCTION(BlueprintPure)
	FVersion GetClientModVersion(const FString& ModId) const;
	
	USMLPlayerComponent();
	
	/** Sends system chat message to the player it is attached to */
	UFUNCTION(BlueprintCallable, Reliable, Client)
	void SendChatMessage(const FString& Message, const FLinearColor& Color);

	/** Called client side to process chat command on server */
	UFUNCTION(BlueprintCallable, Reliable, Server, WithValidation = HandleChatCommand_Validate)
	void HandleChatCommand(const FString& CommandLine);

	bool HandleChatCommand_Validate(const FString& CommandLine);

	/*
	 * Returns USMLPlayerComponent instance attached
	 * to the given player controller
	 * Always returns something unless called very very early
	 */
	UFUNCTION(BlueprintPure)
	static USMLPlayerComponent* Get(APlayerController* Player);

	/* Internal usage only */
	static void Register();
};