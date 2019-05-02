#pragma once

#pragma once

#include <HookLoader.h>
#include <util/FString.h>

#pragma warning (push)
#pragma warning (disable: 4667)

namespace Classes {
	class UWorld {
	public:
		void Tick(enum ELevelTick TickType, float DeltaSeconds);
	};
}

DEFINE_METHOD(Classes::UWorld::Tick);

namespace Classes {
	class UGameInstance {
	public:
		UWorld* GetWorld();
	};
}

DEFINE_METHOD(Classes::UGameInstance::GetWorld);

namespace Classes {
	class UGameplayStatics {
	public:
		static class APawn* GetPlayerPawn(class UObject* WorldContextObject, int PlayerIndex);
	};
}

DEFINE_METHOD(Classes::UGameplayStatics::GetPlayerPawn);

namespace Classes {
	class AFGPlayerController {
	public:
		void BeginPlay();
		void EnterChatMessage(FString *inMessage);
		void OnAttentionPingPressed();
		void Suicide();
	};
}

DEFINE_METHOD(Classes::AFGPlayerController::BeginPlay);
DEFINE_METHOD(Classes::AFGPlayerController::EnterChatMessage);
DEFINE_METHOD(Classes::AFGPlayerController::OnAttentionPingPressed);
DEFINE_METHOD(Classes::AFGPlayerController::Suicide);

namespace Classes {
	class UFGInventoryComponent {
	public:
		void SortInventory();
	};
}

DEFINE_METHOD(Classes::UFGInventoryComponent::SortInventory);

namespace Classes {
	class FPakPlatformFile {
	public:
		void GetPakSigningKeys(void* OutKey);
	};
}

DEFINE_METHOD(Classes::FPakPlatformFile::GetPakSigningKeys);

#pragma warning (pop)