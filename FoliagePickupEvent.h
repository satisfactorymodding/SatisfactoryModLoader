#pragma once
#include "Event.h"
#include "Utility.h"

class FoliagePickupEvent : public Event {
public:
	FoliagePickupEvent();
	virtual ~FoliagePickupEvent();

	static constexpr EventType descriptor = EventType::OnFoliagePickup;

	virtual EventType type() const;
	virtual const char* name() const;

	static void use(const Event& event) {
		log("FoliagePickupEvent");
	}
};