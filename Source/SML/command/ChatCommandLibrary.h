#pragma once
#include "CoreTypes.h"
#include "Delegates/Delegate.h"
#include "FGPlayerController.h"
#include "ChatCommandLibrary.generated.h"

UENUM(BlueprintType)
enum class EExecutionStatus : uint8 {
	/** command executed successfully */
	COMPLETED,
	/** command not executed, or had no effect */
	UNCOMPLETED,
	/** command not executed, user permissions are too low */
	INSUFFICIENT_PERMISSIONS,
	/** command failed due to user providing invalid arguments */
	BAD_ARGUMENTS
};

/**
 * Generic object representing abstract command source
 */
UCLASS(Abstract, BlueprintType)
class SML_API UCommandSender : public UObject {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	virtual FString GetSenderName() const;
	
	/**
	 * Returns true if this command sender represents player, false otherwise
	 */
	UFUNCTION(BlueprintPure)
	virtual bool IsPlayerSender() const;

	/**
	 * If this command sender is player, returns player controller instance
	 */
	UFUNCTION(BlueprintPure)
	virtual AFGPlayerController* GetPlayer() const;

	/**
	 * Sends chat message to this command sender
	 */
	UFUNCTION(BlueprintCallable)
	virtual void SendChatMessage(const FString& Message, const FLinearColor PrefixColor = FLinearColor::Green);
};

UCLASS(Abstract, Blueprintable)
class SML_API AChatCommandInstance : public AInfo {
	GENERATED_BODY()
public:
	AChatCommandInstance();
	
	/**
	 * Whenever this command can only be used by player sender
	 * Trying to run it from non-player sender will print error message
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	uint8 bOnlyUsableByPlayer: 1;

	/**
	 * Minimum number of arguments to enforce before
	 * actually giving execution control to the command
	 * Providing less will instead print command usage
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	int32 MinNumberOfArguments;
	
	/**
	* ModId of the mod registering the command
	* Assigned automatically by call stack analysis for both blueprints and C++ code
	*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString ModId;

	/**
	 * Name of the command
	 * Not limited in any way, but consider using only ASCII chars there
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString CommandName;

	/**
	 * List of the additional names command can be referenced by
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TArray<FString> Aliases;
	/**
	 * Usage of the command
	 * Example:
	 * msg <username> <message>
	 * give <username> <item> [amount] [extra_data]
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FString Usage;

	/**
	 * Command handler function to be called when command is executed
	 *
	 * @param Sender Command Sender caused execution of this command
	 * @param Arguments Additional arguments passed to command
	 * @param Label Command Alias used for calling this command
	 * @return Execute Status describing what command actually did
	 */
	UFUNCTION(BlueprintNativeEvent)
	EExecutionStatus ExecuteCommand(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label);

	/**
	* Prints usage of this command to the given player
	*
	* @param CommandSender ICommandSenderInterface implementing object
	*/
	UFUNCTION(BlueprintCallable)
	void PrintCommandUsage(UCommandSender* CommandSender) const;
};

UCLASS(NotBlueprintable)
class SML_API AChatCommandSubsystem : public AFGSubsystem {
	GENERATED_BODY()
private:
	//Array of registered command actors
	UPROPERTY()
	TArray<AChatCommandInstance*> RegisteredCommands;
	//Map to lookup command instances fast
	TMap<FString, AChatCommandInstance*> CommandByNameMap;
public:
	/**
	 * Retrieves Chat Command Subsystem instance for a given world
	 * Will always return something unless called really early
	 */
	UFUNCTION(BlueprintPure)
	static AChatCommandSubsystem* Get(UObject* WorldContext);
	
	/**
	 * Initializes builtin commands for the command subsystem
	 */
	void Init();
	
	/**
	 * Searches command register entry by given command name
	 *
	 * @param Name Name to search for, can be command name or one of aliases. Accepts both full and short names
	 * @return Found entry, or nullptr if not found
	 */
	UFUNCTION(BlueprintPure, Category = "Utilities|ChatCommand")
	AChatCommandInstance* FindCommandByName(const FString& Name);

	/*
	 * Returns array of all registered commands
	 */
	UFUNCTION(BlueprintPure, Category = "Utilities|ChatCommand")
	const TArray<AChatCommandInstance*>& GetRegisteredCommands() const;
	
	/**
	* Registers a chat command to a chat command subsystem
	* Will return silently if command with same qualified name already exists
	*
	* @param Command Command data to register
	*/
	UFUNCTION(BlueprintCallable, Category = "Utilities|ChatCommand")
	void RegisterCommand(TSubclassOf<AChatCommandInstance> Command);

	/**
	* Parses command line and executes given command from the face of the given player
	* Characters enclosed in "" are considered a single argument
	* If command is not found, returns bad_arguments
	*
	* @param CommandLine Command line to execute, without prefix slash
	* @param Sender Sender which caused command execution. Should implement ICommandSenderInterface
	* @param WorldContext Object used to retrieve UWorld context
	*/
	UFUNCTION(BlueprintCallable, Category = "Utilities|ChatCommand")
	EExecutionStatus RunChatCommand(const FString& CommandLine, UCommandSender* Sender);
	
	/**
	* Parses given player name, returning all players matching
	*
	* It supports multiple target selectors:
	* @s(elf) - targets player who executed this command
	* @a(ll) - targets all players on the server
	* otherwise - treated as player nickname
	*
	* @param Caller caller of the original command
	* @param Name Name to parse against selectors
	* @param WorldContext World Context
	* @return Array of players matching given name
	*/
	UFUNCTION(BlueprintPure, Category = "Utilities|ChatCommand", meta = (WorldContext = "WorldContext"))
	static TArray<AFGPlayerController*> ParsePlayerName(UCommandSender* Caller, const FString& Name, UObject* WorldContext);
};