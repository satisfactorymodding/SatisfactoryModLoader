#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>

class FlyEvent : public Event {
public:
	FlyEvent();
	virtual ~FlyEvent();

	static constexpr EventType descriptor = EventType::OnFly;

	static constexpr const char* addressName = "UCheatManager::Fly";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; void __fastcall UCheatManager::Fly(UCheatManager *this)
	static void use(void* cheats) {
		log("FlyEvent");
		auto pointer = (FlyEventFunction)originalFunctions[descriptor].Function;
		pointer(cheats);
	}

private:
	typedef void(WINAPI* FlyEventFunction)(VOID*);
};

FlyEvent::FlyEvent() {
}


FlyEvent::~FlyEvent() {
}