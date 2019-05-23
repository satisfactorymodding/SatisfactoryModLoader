#pragma once
#include <../SatisfactorySDK/SDK.hpp>
#include <Lib.h>

namespace SML {
	namespace Assets {
		/*
		Current UWorld object.
		*/
		SML_API extern void* CurrentWorld;

		/*
		Single player character
		*/
		SML_API extern SDK::AFGCharacterPlayer* SinglePlayerPawn;
	}
	namespace Mod {
		namespace Functions {
			/*
			Load an object from a pak file. Will crash if the pak is not installed.
			The asset name must be of the following format: \Game\FactoryGame\Path\To\Asset\AssetFile.AssetFile
			If you are loading a blueprint, the name must have a _C appended to the end.
			*/
			SML_API SDK::UObject* loadObjectFromPak(SDK::UClass *ObjectClass, const wchar_t *InName);

			/*
			Spawns an actor at a given location, when given the world.
			*/
			SML_API void* spawnActor(void* UWorld, void* *UClass, void* *FVector, void* *FRotator, void* *FActorSpawnParameters);

			/*
			Get the current world.
			*/
			SML_API void* getWorld();

			/*
			Get the player pawn
			*/
			SML_API SDK::AFGCharacterPlayer* getPlayerPawn();

			SML_API void spawnActorAtPlayer(const wchar_t* name, float x, float y, float z);

			SML_API void spawnActorAtPlayer(const wchar_t* name);

			SML_API void spawnActor(const wchar_t* name, float x, float y, float z, float pitch, float roll, float yaw);
		}
	}
}