
#include "player/PlayerUtility.h"
#include "FGCharacterPlayer.h"
#include "FGPlayerController.h"
#include "Engine.h"
#include "mod/hooking.h"
#include "player/component/SMLPlayerComponent.h"
#include "util/Logging.h"

namespace SML {
	
	void InitializePlayerComponent() {
		SUBSCRIBE_METHOD(AFGPlayerController::BeginPlay, [](auto& Scope, AFGPlayerController* Controller) {
			USMLPlayerComponent* Component = NewObject<USMLPlayerComponent>(Controller, TEXT("SML_PlayerComponent"));
			Component->RegisterComponent();
			Component->SetNetAddressable();
			Component->SetIsReplicated(true);
			
			if (SML::GetSmlConfig().bEnableCheatConsoleCommands) {
				Controller->AddCheats(true);
			}
		});
		
		SUBSCRIBE_METHOD(AFGPlayerController::EnterChatMessage, [](auto& scope, AFGPlayerController* player, const FString& message) {
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
		for (FConstPlayerControllerIterator iterator = World->GetPlayerControllerIterator(); iterator; ++iterator) {
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
