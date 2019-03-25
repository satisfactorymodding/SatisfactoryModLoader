#pragma once
#include <string>
#include <iostream>

enum Event {
	// Called as soon as SML is finished constructing all mods.
	OnPreInit,
	// Called when foliage is picked up by the player. Called once on the server and called once on the client.
	// (AFGCharacterPlayer character, UHierarchicalInstancedStaticMeshComponent meshComponent, TArray<FInventoryStack,FDefaultAllocator> out_validStacks)
	OnPickupFoliage,
	// Called when the player starts playing. Called once on the server and called once on the client.
	// (void)
	OnPlayerBeginPlay
	};

void log(std::string msg);