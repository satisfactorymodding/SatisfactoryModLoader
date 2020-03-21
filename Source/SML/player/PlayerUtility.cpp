
#include "player/PlayerUtility.h"
#include "FGCharacterPlayer.h"
#include "FGPlayerController.h"
#include "Engine.h"
#include "mod/hooking.h"
#include "player/component/SMLPlayerComponent.h"

namespace SML {
	void initializePlayerComponent() {
		SUBSCRIBE_METHOD("?BeginPlay@AFGPlayerController@@UEAAXXZ", AFGPlayerController::BeginPlay, [](auto& scope, AFGPlayerController* controller) {
			USMLPlayerComponent* component = NewObject<USMLPlayerComponent>(controller, TEXT("SML_PlayerComponent"));
			component->RegisterComponent();
			component->SetNetAddressable();
			component->SetIsReplicated(true);
		});
		SUBSCRIBE_METHOD("?EnterChatMessage@AFGPlayerController@@IEAAXAEBVFString@@@Z", AFGPlayerController::EnterChatMessage, [](auto& scope, AFGPlayerController* player, const FString& message) {
			if (message.StartsWith(TEXT("/"))) {
				const FString commandLine = message.TrimStartAndEnd().RightChop(1);
				USMLPlayerComponent* component = USMLPlayerComponent::Get(player);
				component->HandleChatCommand(commandLine);
				scope.Cancel();
			}
		});
	}
	
    SML_API AFGCharacterPlayer* getPlayerCharacter(const UPlayer* player) {
        return static_cast<AFGCharacterPlayer*>(player->GetPlayerController(nullptr)->GetCharacter());
    }

	SML_API TArray<AFGPlayerController*> getConnectedPlayers(const UWorld* world) {
		TArray<AFGPlayerController*> result;
		//iterate connected players
		for (FConstPlayerControllerIterator iterator = world->GetPlayerControllerIterator(); iterator; iterator++) {
			APlayerController* controller = (*iterator).Get();
			if (controller == nullptr) continue;
			result.Add(static_cast<AFGPlayerController*>(controller));
		}
		return result;
    }

	SML_API AFGPlayerController* GetPlayerByName(const UWorld* world, const FString& playerName) {
		TArray<AFGPlayerController*> connectedPlayers = getConnectedPlayers(world);
    	for (AFGPlayerController* controller : connectedPlayers) {
    		if (controller->PlayerState->GetPlayerName() == playerName) {
				return controller;
    		}
    	}
		return nullptr;
	}
};