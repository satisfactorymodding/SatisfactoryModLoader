#pragma once
#include "Event.h"
#include "Utility.h"
#include "EventLoader.h"

class InventoryHasAuthorityEvent : public Event {
public:
	InventoryHasAuthorityEvent();
	virtual ~InventoryHasAuthorityEvent();

	static constexpr EventType descriptor = EventType::OnInventoryHasAuthority;

	static constexpr const char* addressName = "UFGInventoryComponent::HasAuthority";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; bool __fastcall UFGInventoryComponent::HasAuthority(UFGInventoryComponent *this)
	static bool use(void* inventory) {
		log("InventoryHasAuthorityEvent");
		auto pointer = (bool (WINAPI*)(VOID*))originalFunctions[descriptor].Function;
		return pointer(inventory);
	}
};

InventoryHasAuthorityEvent::InventoryHasAuthorityEvent() {
}


InventoryHasAuthorityEvent::~InventoryHasAuthorityEvent() {
}