#pragma once
#include <string>

enum EventType {
	OnPreInit,
	OnFoliagePickup,
	OnPlayerBeginPlay,
	OnPlayerTakeDamage,
	END
};

class Event {
public:
	virtual ~Event();

	virtual EventType type() const = 0;
	virtual const char* name() const = 0;
};