#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>

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
			&damageAmount
		};
		// std::vector<void*>&
		modFunction(TakeDamageEvent(), args);

		log("Damage:", false, true);
		log(*(float*)args[0], true, false);

		// original function
		auto pointer = (TakeDamageFunction)originalFunctions[descriptor].Function;
		pointer(healthComponent, damagedActor, *(float*)args[0], damageType, instigatedBy, damageCauser);
	}

private:
	typedef void(WINAPI* TakeDamageFunction)(VOID*, VOID*, float, VOID*, VOID*, VOID*);
};

TakeDamageEvent::TakeDamageEvent() {
}


TakeDamageEvent::~TakeDamageEvent() {
}