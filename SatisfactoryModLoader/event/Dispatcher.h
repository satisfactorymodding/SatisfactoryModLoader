#pragma once
#include "event/Event.h"

#include <functional>
#include <map>
#include <vector>

class Connection;
class Dispatcher;

typedef void(*EventFunc)(std::vector<void*>&);

class Dispatcher {
public:
	Connection subscribe(const EventType& descriptor, EventFunc slot);
	void unsubscribe(const Connection& connection);
	void post(const Event& event, std::vector<void*>& args) const {
		auto type = event.type();

		if (_observers.find(type) == _observers.end()) {
			return;
		}

		auto observers = _observers.at(type);
		for (auto observer : observers) {
			observer.slot(args);
		}
	}

private:
	unsigned int _nextID = 0;

	struct SlotHandle {
		unsigned int id;
		EventFunc slot;
	};

	std::map<EventType, std::vector<SlotHandle>> _observers;
};