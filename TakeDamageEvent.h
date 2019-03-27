#pragma once
#include "Event.h"
#include "Utility.h"
#include "EventLoader.h"

class TakeDamageEvent : public Event {
public:
	TakeDamageEvent();
	virtual ~TakeDamageEvent();

	static constexpr EventType descriptor = EventType::OnPlayerTakeDamage;

	static constexpr const char* addressName = "UFGHealthComponent::TakeDamage";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; void __fastcall UFGHealthComponent::TakeDamage(UFGHealthComponent *this, AActor *damagedActor, float damageAmount, UDamageType *damageType, AController *instigatedBy, AActor *damageCauser)
	static void use(void* healthComponent, void* damagedActor, float damageAmount, void* damageType, void* instigatedBy, void* damageCauser) {
		log("TakeDamageEvent");

		// mod functions
		auto modFunction = (ModFunc)originalFunctions[descriptor].ModFunction;
		std::vector<void*> args = {
			healthComponent, damagedActor, &damageAmount, damageType, instigatedBy, damageCauser
		};
		// std::vector<void*>&
		modFunction(TakeDamageEvent(), args);

		log("Damage:", false, true);
		log(*(float*)args[2], true, false);

		// original function
		auto pointer = (void (WINAPI*)(VOID*, VOID*, float, VOID*, VOID*, VOID*))originalFunctions[descriptor].Function;
		pointer(args[0], args[1], *(float*)args[2], args[3], args[4], args[5]);
	}
};

TakeDamageEvent::TakeDamageEvent() {
}


TakeDamageEvent::~TakeDamageEvent() {
}