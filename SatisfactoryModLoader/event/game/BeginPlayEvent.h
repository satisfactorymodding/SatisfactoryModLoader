#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>
#include "EnterChatMessageEvent.h"

extern void* localPlayer = NULL;

class BeginPlayEvent : public Event {
public:
	BeginPlayEvent();
	virtual ~BeginPlayEvent();

	static constexpr EventType descriptor = EventType::OnPlayerBeginPlay;

	static constexpr const char* addressName = "AFGPlayerController::BeginPlay";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; void __fastcall AFGPlayerController::BeginPlay(AFGPlayerController *this)
	static void use(void* character) {
		log("BeginPlayEvent");
		localPlayer = character;
		auto pointer = (BeginPlayFunction)originalFunctions[descriptor].Function;
		pointer(character);
	}

private:
	typedef void(WINAPI* BeginPlayFunction)(VOID*);
};

BeginPlayEvent::BeginPlayEvent() {
}


BeginPlayEvent::~BeginPlayEvent() {
}