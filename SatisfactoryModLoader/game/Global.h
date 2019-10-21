#pragma once

#include <HookLoader.h>
#include <util/FString.h>
#include "../SatisfactorySDK/SDK.hpp"
#include "assets/FObjectSpawnParameters.h"
#include "Etc.h"

#pragma warning (push)
#pragma warning (disable: 4667)

namespace SML {
	namespace Objects {

		class IAsyncReadRequest {

		};

		class UWorld {
		public:
			void Tick(enum ELevelTick TickType, float DeltaSeconds);
			AActor* SpawnActor(SDK::UClass *Class, SDK::FVector *Location, SDK::FRotator *Rotation, FActorSpawnParameters *SpawnParameters);
			FString* GetMapName(FString* doesSomethingIThink);
		};

		DEFINE_METHOD(UWorld::Tick);
		DEFINE_METHOD(UWorld::SpawnActor);
		DEFINE_METHOD(UWorld::GetMapName);

		class UGameInstance {
		public:
			UWorld* GetWorld();
		};

		DEFINE_METHOD(UGameInstance::GetWorld);

		class UGameplayStatics {
		public:
			static class APawn* GetPlayerPawn(class UObject* WorldContextObject, int PlayerIndex);
		};

		DEFINE_METHOD(UGameplayStatics::GetPlayerPawn);

		class AFGPlayerController {
		public:
			void BeginPlay();
			void EnterChatMessage(FString *inMessage);
			void OnAttentionPingPressed();
			void Suicide();
		};

		DEFINE_METHOD(AFGPlayerController::BeginPlay);
		DEFINE_METHOD(AFGPlayerController::EnterChatMessage);
		DEFINE_METHOD(AFGPlayerController::OnAttentionPingPressed);
		DEFINE_METHOD(AFGPlayerController::Suicide);

		class FEngineLoop {
		public:
			void Init();
		};

		DEFINE_METHOD(FEngineLoop::Init);
			

		class UFGInventoryComponent {
		public:
			void SortInventory();
		};

		DEFINE_METHOD(UFGInventoryComponent::SortInventory);

		class AFGStorySubsystem {
		public:
			void BeginPlay();
		};

		DEFINE_METHOD(AFGStorySubsystem::BeginPlay);

		class FOutputDevice {
		protected:
			bool bSuppressEventTag;
			bool bAutoEmitLineTerminator;
		};

		class UObject {
		public:
			bool CallFunctionByNameWithArguments(const wchar_t *Str, FOutputDevice *Ar, SDK::UObject *Executor, bool bForceCallWithNonExec);
		};

		DEFINE_METHOD(UObject::CallFunctionByNameWithArguments);

		class AFGGameMode {
		public:
			void InitGameState();
		};

		DEFINE_METHOD(AFGGameMode::InitGameState);
	}
}

#pragma warning (pop)