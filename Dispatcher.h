#pragma once
#include "Event.h"
#include <functional>
#include <map>
#include <vector>

class Connection;

class Dispatcher {
public:
	using SlotType = std::function<void(const Event&)>;

	Connection subscribe(const EventType& descriptor, SlotType&& slot);
	void unsubscribe(const Connection& connection);
	void post(const Event& event) const;

private:
	unsigned int _nextID = 0;

	struct SlotHandle {
		unsigned int id;
		SlotType slot;
	};

	std::map<EventType, std::vector<SlotHandle>> _observers;
};