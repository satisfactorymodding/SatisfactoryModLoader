
#include "player/PlayerUtility.h"
#include "FGCharacterPlayer.h"
#include "FGPlayerController.h"
#include "Engine.h"
#include "mod/hooking.h"
#include "player/component/SMLPlayerComponent.h"
#include "util/FuncNames.h"

namespace SML {
	void InitializePlayerComponent() {
		SUBSCRIBE_METHOD(PLAYER_CONTROLLER_BEGIN_PLAY_FUNC_DESC, AFGPlayerController::BeginPlay, [](auto& scope, AFGPlayerController* controller) {
			USMLPlayerComponent* Component = NewObject<USMLPlayerComponent>(controller, TEXT("SML_PlayerComponent"));
			Component->RegisterComponent();
			Component->SetNetAddressable();
			Component->SetIsReplicated(true);
		});
		SUBSCRIBE_METHOD(ENTER_CHAT_MESSAGE_FUNC_DESC, AFGPlayerController::EnterChatMessage, [](auto& scope, AFGPlayerController* player, const FString& message) {
			if (message.StartsWith(TEXT("/"))) {
				const FString CommandLine = message.TrimStartAndEnd().RightChop(1);
				USMLPlayerComponent* Component = USMLPlayerComponent::Get(player);
				Component->HandleChatCommand(CommandLine);
				scope.Cancel();
			}
		});
	}
	
    SML_API AFGCharacterPlayer* GetPlayerCharacter(const UPlayer* Player) {
        return static_cast<AFGCharacterPlayer*>(Player->GetPlayerController(nullptr)->GetCharacter());
    }

	SML_API TArray<AFGPlayerController*> GetConnectedPlayers(const UWorld* World) {
		TArray<AFGPlayerController*> Result;
		//iterate connected players
		for (FConstPlayerControllerIterator iterator = World->GetPlayerControllerIterator(); iterator; iterator++) {
			APlayerController* controller = (*iterator).Get();
			if (controller == nullptr) continue;
			Result.Add(static_cast<AFGPlayerController*>(controller));
		}
		return Result;
    }

	SML_API AFGPlayerController* GetPlayerByName(const UWorld* World, const FString& PlayerName) {
		TArray<AFGPlayerController*> ConnectedPlayers = GetConnectedPlayers(World);
    	for (AFGPlayerController* Controller : ConnectedPlayers) {
    		if (Controller->PlayerState->GetPlayerName() == PlayerName) {
				return Controller;
    		}
    	}
		return nullptr;
	}
};
