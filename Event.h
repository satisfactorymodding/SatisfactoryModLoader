#pragma once
#include <string>

enum EventType {
	None,
	OnFoliagePickup
};

class Event {
public:
	virtual ~Event();

	virtual EventType type() const = 0;
	virtual void use(const Event& event);
};