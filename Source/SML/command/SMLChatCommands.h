#pragma once
#include "ChatCommandLibrary.h"
#include "SMLChatCommands.generated.h"

UCLASS(MinimalAPI)
class AHelpCommandInstance : public AChatCommandInstance {
	GENERATED_BODY()
public:
	AHelpCommandInstance();
	EExecutionStatus ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) override;
};

UCLASS(MinimalAPI)
class AInfoCommandInstance : public AChatCommandInstance {
	GENERATED_BODY()
public:
	AInfoCommandInstance();
	EExecutionStatus ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) override;
};

UCLASS(MinimalAPI)
class APlayerListCommandInstance : public AChatCommandInstance {
	GENERATED_BODY()
public:
	APlayerListCommandInstance();
	EExecutionStatus ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) override;
};