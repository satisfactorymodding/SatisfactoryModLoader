#pragma once
#include <string>
#include <iostream>

//enum Event {
//	// Called as soon as SML is finished constructing all mods.
//	OnPreInit,
//	// Called when foliage is picked up by the player. Called once on the server and called once on the client.
//	// (AFGCharacterPlayer character, UHierarchicalInstancedStaticMeshComponent meshComponent, TArray<FInventoryStack,FDefaultAllocator> out_validStacks)
//	OnPickupFoliage,
//	// Called when the player starts playing. Called once on the server and called once on the client.
//	// (void)
//	OnPlayerBeginPlay,
//	// Called when the player takes damage
//	// (AActor damagedActor, FLOAT damageAmount, UDamageType damageType, AController instigatedBy, AController instigatedBy, AActor damageCauser, AActor damageCauser)
//	OnPlayerTakeDamage,
//	OnInventoryHasAuthority
//};

// Provides a colored log with the mod's name
template<typename T>
void log_mod(T msg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "[" + ModName + "] ";

	std::cout << msg;
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}