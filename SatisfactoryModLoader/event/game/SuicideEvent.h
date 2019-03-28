#pragma once
#include "event/Event.h"
#include "event/EventLoader.h"
#include "util/Utility.h"

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
		auto pointer = (SuicideFunction)originalFunctions[descriptor].Function;
		pointer(character);
	}

private:
	typedef void(WINAPI* SuicideFunction)(VOID*);
};

SuicideEvent::SuicideEvent() {
}


SuicideEvent::~SuicideEvent() {
}