#pragma once
#include "Event.h"
#include <util/Utility.h>
#include "EventLoader.h"

class FoliagePickupEvent : public Event {
public:
	FoliagePickupEvent();
	virtual ~FoliagePickupEvent();

	static constexpr EventType descriptor = EventType::OnFoliagePickup;

	static constexpr const char* addressName = "UFGFoliageLibrary::CheckInventorySpaceAndGetStacks";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; bool __fastcall UFGFoliageLibrary::CheckInventorySpaceAndGetStacks(AFGCharacterPlayer *character, UHierarchicalInstancedStaticMeshComponent *meshComponent, TArray<FInventoryStack,FDefaultAllocator> *out_validStacks)
	static bool use(void* character, void* meshComponent, void* out_validStacks) {
		log("FoliagePickupEvent");
		auto pointer = (bool(WINAPI*)(VOID*, VOID*, VOID*))originalFunctions[descriptor].Function;
		return pointer(character, meshComponent, out_validStacks);
	}
};

FoliagePickupEvent::FoliagePickupEvent() {
}


FoliagePickupEvent::~FoliagePickupEvent() {
}