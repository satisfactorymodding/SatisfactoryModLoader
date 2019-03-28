#pragma once
#include "event/Event.h"
#include "event/EventLoader.h"
#include "util/Utility.h"

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
		auto pointer = (InventoryHasAuthorityFunction)originalFunctions[descriptor].Function;
		return pointer(inventory);
	}

private:
	typedef bool(WINAPI* InventoryHasAuthorityFunction)(VOID*);
};

InventoryHasAuthorityEvent::InventoryHasAuthorityEvent() {
}


InventoryHasAuthorityEvent::~InventoryHasAuthorityEvent() {
}