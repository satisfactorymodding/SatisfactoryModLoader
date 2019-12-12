
#include "player/PlayerUtility.h"
#include "FGCharacterPlayer.h"
#include "FGPlayerController.h"
#include "Engine.h"

namespace SML {
    SML_API AFGCharacterPlayer* getPlayerCharacter(const UPlayer* player) {
        return static_cast<AFGCharacterPlayer*>(player->GetPlayerController(nullptr)->GetCharacter());
    }

	SML_API std::vector<AFGPlayerController*> getConnectedPlayers(const UWorld* world) {
		std::vector<AFGPlayerController*> result;
		//iterate connected players
		for (FConstPlayerControllerIterator iterator = world->GetPlayerControllerIterator(); iterator; iterator++) {
			APlayerController* controller = (*iterator).Get();
			if (controller != nullptr) continue;
			result.push_back(static_cast<AFGPlayerController*>(controller));
		}
		return result;
    }

	SML_API AFGPlayerController* GetPlayerByName(const UWorld* world, const FString& playerName) {
		std::vector<AFGPlayerController*> connectedPlayers = getConnectedPlayers(world);
    	for (AFGPlayerController* controller : connectedPlayers) {
    		if (controller->PlayerState->GetPlayerName() == playerName) {
				return controller;
    		}
    	}
		return nullptr;
	}
};