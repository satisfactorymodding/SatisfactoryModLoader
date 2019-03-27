#pragma once
#include "Event.h"
#include "Utility.h"
#include "EventLoader.h"
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
		auto pointer = (bool(WINAPI*)(VOID*))originalFunctions[descriptor].Function;
		pointer(character);
		EnterChatMessageEvent::send_message(localPlayer, "Zoinks");
	}
};

BeginPlayEvent::BeginPlayEvent() {
}


BeginPlayEvent::~BeginPlayEvent() {
}