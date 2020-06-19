#include "ChatCommandLibrary.h"

#include "mod/ModHandler.h"
#include "util/Utility.h"
#include "player/PlayerControllerHelper.h"
#include "player/component/SMLPlayerComponent.h"
#include "SMLChatCommands.h"
#include "mod/ModSubsystems.h"
#include "util/Logging.h"

AFGPlayerController* UCommandSender::GetPlayer() const {
	checkf(false, TEXT("GetPlayer not implemented by this CommandSource"));
	return nullptr;
}

FString UCommandSender::GetSenderName() const {
	return TEXT("Unspecified");
}

bool UCommandSender::IsPlayerSender() const {
	return false;
}

void UCommandSender::SendChatMessage(const FString& Message, const FLinearColor PrefixColor) {
}

const TArray<AChatCommandInstance*>& AChatCommandSubsystem::GetRegisteredCommands() const {
	return RegisteredCommands;
}

AChatCommandInstance* AChatCommandSubsystem::FindCommandByName(const FString& Name) {
	AChatCommandInstance** Entry = CommandByNameMap.Find(Name.ToLower());
	return Entry == nullptr ? nullptr : *Entry;
}

AChatCommandInstance::AChatCommandInstance() {
	bOnlyUsableByPlayer = false;
	MinNumberOfArguments = 0;
}

//Default implementation that will call CommandExecuted if it is bound
EExecutionStatus AChatCommandInstance::ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) {
	return EExecutionStatus::UNCOMPLETED;
}

void AChatCommandInstance::PrintCommandUsage(UCommandSender* Player) const {
	Player->SendChatMessage(FString::Printf(TEXT("Usage: %s"), *Usage), FLinearColor::Red);
}

void PrintCommandNotFound(UCommandSender* Player) {
	Player->SendChatMessage(TEXT("Unknown command. Type /help for a list of commands."), FLinearColor::Red);
}

void PrintCommandOnlyUsableByPlayer(UCommandSender* Player) {
	Player->SendChatMessage(TEXT("This command is only usable by players."), FLinearColor::Red);
}

AChatCommandSubsystem* AChatCommandSubsystem::Get(UObject* WorldContext) {
	USMLSubsystemHolder* Holder = GetSubsystemHolder<USMLSubsystemHolder>(WorldContext);
	if (Holder == nullptr)
		return nullptr;
	return Holder->GetChatCommandSubsystem();
}

void AChatCommandSubsystem::Init() {
	RegisterCommand(AHelpCommandInstance::StaticClass());
	RegisterCommand(AInfoCommandInstance::StaticClass());
	RegisterCommand(APlayerListCommandInstance::StaticClass());
}

TArray<AFGPlayerController*> AChatCommandSubsystem::ParsePlayerName(UCommandSender* Caller, const FString& Name, UObject* WorldContext) {
	check(WorldContext->ImplementsGetWorld());
	const UWorld* WorldObject = WorldContext->GetWorld();
	AFGPlayerController* CallerPlayer = Caller->IsPlayerSender() ? Caller->GetPlayer() : nullptr;
	if (Name == TEXT("@self") || Name == TEXT("@s")) 
		return SML::ArrayOfNullable<AFGPlayerController*>(CallerPlayer);
	
	if (Name == TEXT("@all") || Name == TEXT("@a"))
		return FPlayerControllerHelper::GetConnectedPlayers(WorldObject);

	AFGPlayerController* FoundPlayer = FPlayerControllerHelper::GetPlayerByName(WorldObject, Name);
	return SML::ArrayOfNullable<AFGPlayerController*>(FoundPlayer);
}

FString MakeFQCommandName(const FString& ModId, const FString& Name) {
	return FString::Printf(TEXT("%s:%s"), *ModId, *Name);
}

void AChatCommandSubsystem::RegisterCommand(TSubclassOf<AChatCommandInstance> CommandClass) {
	const FModHandler& ModHandler = SML::GetModHandler();
	//Ensure that mod with specified ModId is loaded and active

	AChatCommandInstance* CommandCDO = CommandClass->GetDefaultObject<AChatCommandInstance>();
	checkf(ModHandler.IsModLoaded(CommandCDO->ModId), TEXT("Invalid ModId provided for RegisterCommand: %s"), *CommandCDO->ModId);
	const FString FqCommandName = MakeFQCommandName(CommandCDO->ModId, CommandCDO->CommandName);
	//Only register command if it's not already registered
	if (!CommandByNameMap.Contains(FqCommandName)) {
		const FString ActorName = FString::Printf(TEXT("ChatCommand_%s_%s"), *CommandCDO->ModId, *CommandCDO->CommandName);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = *ActorName;
		AChatCommandInstance* Command = GetWorld()->SpawnActor<AChatCommandInstance>(CommandClass, SpawnParams);
		check(Command);
		TArray<FString> AllCommandNames;
		AllCommandNames.Add(Command->CommandName);
		AllCommandNames.Append(Command->Aliases);
		//register all command aliases
		for (const FString& CommandAlias : AllCommandNames) {
			const FString FqCommandAlias = MakeFQCommandName(CommandCDO->ModId, CommandAlias);
			CommandByNameMap.Add(CommandAlias.ToLower(), Command);
			CommandByNameMap.Add(FqCommandAlias.ToLower(), Command);
			SML::Logging::info(TEXT("Registering chat command with name "), *FqCommandAlias, TEXT(" from mod "), *CommandCDO->ModId);
		}
		//Register command entry
		RegisteredCommands.Add(Command);
	}
}

FString ParseCommandArgument(const FString& Line, int32& Off);

EExecutionStatus AChatCommandSubsystem::RunChatCommand(const FString& CommandLine, UCommandSender* Sender) {
	SML::Logging::info(TEXT("[CHAT CMD] "), *Sender->GetSenderName(), TEXT(": /"), *CommandLine);
	if (CommandLine.IsEmpty()) {
		PrintCommandNotFound(Sender);
		return EExecutionStatus::BAD_ARGUMENTS;
	}
	TArray<FString> ResultArgArray;
	int32 Offset = 0;
	while (CommandLine.Len() > Offset) {
		FString resultArg = ParseCommandArgument(CommandLine, Offset);
		ResultArgArray.Add(resultArg);
		Offset++; //skip argument separator
	}
	const FString CommandAliasUsed = ResultArgArray[0];
	//Remove command name from arguments array
	ResultArgArray.RemoveAt(0);
	AChatCommandInstance* CommandEntry = FindCommandByName(CommandAliasUsed);
	if (CommandEntry == nullptr) {
		PrintCommandNotFound(Sender);
		return EExecutionStatus::BAD_ARGUMENTS;
	}
	const FString CommandFQName = MakeFQCommandName(CommandEntry->ModId, CommandEntry->CommandName);
	if (SML::GetSmlConfig().DisabledCommands.Contains(CommandFQName) && Sender->IsPlayerSender()) {
		Sender->SendChatMessage(TEXT("This command has been disabled by server owner."), FLinearColor::Red);
		return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
	}
	if (CommandEntry->bOnlyUsableByPlayer && !Sender->IsPlayerSender()) {
		PrintCommandOnlyUsableByPlayer(Sender);
		return EExecutionStatus::UNCOMPLETED;
	}
	if (CommandEntry->MinNumberOfArguments > ResultArgArray.Num()) {
		CommandEntry->PrintCommandUsage(Sender);
		return EExecutionStatus::BAD_ARGUMENTS;
	}
	return CommandEntry->ExecuteCommand(Sender, ResultArgArray, CommandAliasUsed);
}

FString ParseCommandArgument(const FString& Line, int32& Off) {
	if (Off >= Line.Len()) return TEXT("");
	const wchar_t EscapeChar = TEXT('\\');
	const wchar_t FirstChar = Line[Off++];
	bool bPreviousCharIsEscape = FirstChar == EscapeChar;
	const bool bIsQuoted = FirstChar == TEXT('"');
	const wchar_t breakCharacter = bIsQuoted ? TEXT('"') : TEXT(' ');
	FString Result;
	//if first char is not a quote, append it too!
	if (!bIsQuoted && !bPreviousCharIsEscape) {
		Result.AppendChar(FirstChar);
	}
	while (Line.Len() > Off) {
		const wchar_t Character = Line[Off];
		if (!bPreviousCharIsEscape) {
			//break on the control character
			if (Character == breakCharacter) break;
			//set last character as escape
			if (Character == EscapeChar) {
				bPreviousCharIsEscape = true;
				//continue here to skip resetting prevIsEscape
				//and adding character to the result
				continue;
			}
		}
		Result.AppendChar(Character);
		bPreviousCharIsEscape = false;
		Off++;
	}
	return Result;
}