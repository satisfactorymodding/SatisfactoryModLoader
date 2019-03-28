#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>

class IsFlyingEvent : public Event {
public:
	IsFlyingEvent();
	virtual ~IsFlyingEvent();

	static constexpr EventType descriptor = EventType::OnIsFlying;

	static constexpr const char* addressName = "UCharacterMovementComponent::IsFlying";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; bool __fastcall UCharacterMovementComponent::IsFlying(UCharacterMovementComponent *this)
	static bool use(void* movementComponent) {
		log("IsFlyingEvent");
		auto pointer = (IsFlyingEventFunction)originalFunctions[descriptor].Function;
		return true;
	}

private:
	typedef bool(WINAPI* IsFlyingEventFunction)(VOID*);
};

IsFlyingEvent::IsFlyingEvent() {
}


IsFlyingEvent::~IsFlyingEvent() {
}