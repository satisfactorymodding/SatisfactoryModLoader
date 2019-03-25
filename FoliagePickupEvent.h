#pragma once
#include "Event.h"

class FoliagePickupEvent : public Event
{
public:
	FoliagePickupEvent();
	virtual ~FoliagePickupEvent();

	static constexpr EventType descriptor = EventType::OnFoliagePickup;

	virtual EventType type() const;

	virtual void use(const Event& event);
};