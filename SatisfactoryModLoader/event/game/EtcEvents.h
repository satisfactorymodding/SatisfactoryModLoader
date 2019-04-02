#pragma once
#include <Windows.h>
#include <event/FunctionHolder.h>
#include <util/FKey.h>
#include <util/FString.h>
#include <inttypes.h>
#include <conio.h>

void int64ToChar(char a[], int64_t n) {
	memcpy(a, &n, 8);
}

// ; void __fastcall UFGHealthComponent::TakeDamage(UFGHealthComponent *this, AActor *damagedActor, float damageAmount, UDamageType *damageType, AController *instigatedBy, AActor *damageCauser)
static void player_took_damage(void* healthComponent, void* damagedActor, float damageAmount, void* damageType, void* instigatedBy, void* damageCauser) {
	std::vector<void*> args = {
		healthComponent,
		damagedActor,
		&damageAmount,
		damageType,
		instigatedBy,
		damageCauser
	};
	if (!run_mods(modList, EventType::PlayerTookDamage, args)) {
		return;
	}
	auto pointer = (void(WINAPI*)(void*, void*, float, void*, void* ,void*))hookedFunctions[EventType::PlayerTookDamage];
	pointer(healthComponent, damagedActor, damageAmount, damageType, instigatedBy, damageCauser);
}

// ; void __fastcall UFGItemDescriptor::UFGItemDescriptor(UFGItemDescriptor *this)
void item_descriptor_constructor(void* item) {
	auto args = std::vector<void*>{
		item
	};
	if (!run_mods(modList, EventType::ItemDescriptorConstructor, args)) {
		return;
	}
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::ItemDescriptorConstructor];
	pointer(item);
}

// ; bool __fastcall UPlayerInput::InputKey(UPlayerInput *this, FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad)
bool input_key(void* input, void* key, void* event, float amountDepressed, bool gamepad) {
	auto args = std::vector<void*>{
		input,
		key,
		event,
		&amountDepressed,
		&gamepad
	};
	if (!run_mods(modList, EventType::InputKey, args)) {
		return false;
	}
	auto pointer = (bool(WINAPI*)(void*, void*, void*, float, bool))hookedFunctions[EventType::InputKey];
	bool down = pointer(input, key, event, amountDepressed, gamepad);
	return down;
}

// ; void __fastcall AActor::GetComponents<UFGInventoryComponent,FDefaultAllocator>(AActor *this, TArray<UFGInventoryComponent *,FDefaultAllocator> *OutComponents, bool bIncludeFromChildActors)
void get_inventories(void* actor, void* outComponents, bool includeChildren) {
	auto args = std::vector<void*>{
		actor,
		outComponents,
		&includeChildren

	};
	if (!run_mods(modList, EventType::InventoryRegister, args)) {
		return;
	}
	auto pointer = (bool(WINAPI*)(void*, void*, bool))hookedFunctions[EventType::InventoryRegister];
	pointer(actor, outComponents, includeChildren);
}