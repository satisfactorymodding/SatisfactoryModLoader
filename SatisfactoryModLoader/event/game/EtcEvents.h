#pragma once
#include <Windows.h>
#include <event/FunctionHolder.h>

// ; void __fastcall UFGHealthComponent::TakeDamage(UFGHealthComponent *this, AActor *damagedActor, float damageAmount, UDamageType *damageType, AController *instigatedBy, AActor *damageCauser)
static void player_took_damage(void* healthComponent, void* damagedActor, float damageAmount, void* damageType, void* instigatedBy, void* damageCauser) {
	auto pointer = (void(WINAPI*)(void*, void*, float, void*, void* ,void*))hookedFunctions[EventType::PlayerTookDamage];
	pointer(healthComponent, damagedActor, damageAmount, damageType, instigatedBy, damageCauser);
}