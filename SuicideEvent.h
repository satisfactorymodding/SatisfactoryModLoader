#pragma once
#include "Event.h"
#include "Utility.h"
#include "EventLoader.h"

class SuicideEvent : public Event {
public:
	SuicideEvent();
	virtual ~SuicideEvent();

	static constexpr EventType descriptor = EventType::OnFoliagePickup;

	static constexpr const char* addressName = "AFGPlayerController::Suicide";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; void __fastcall AFGPlayerController::Suicide(AFGPlayerController *this)
	static void use(void* character) {
		log("Suicided");
		auto pointer = (bool(WINAPI*)(VOID*))originalFunctions[descriptor].Function;
		pointer(character);
	}
};

SuicideEvent::SuicideEvent() {
}


SuicideEvent::~SuicideEvent() {
}