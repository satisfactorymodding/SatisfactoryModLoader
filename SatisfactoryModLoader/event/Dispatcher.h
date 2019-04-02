#pragma once
#include "Event.h"
#include <functional>
#include <map>
#include <vector>

class Connection;
class Dispatcher;

typedef bool(*EventFunc)(std::vector<void*>&);

class Dispatcher {
public:
	Connection subscribe(const EventType& descriptor, EventFunc slot);
	void unsubscribe(const Connection& connection);
	bool post(const EventType type, std::vector<void*>& args) const {
		if (_observers.find(type) == _observers.end()) {
			return true;
		}

		bool run = true;

		auto observers = _observers.at(type);
		for (auto observer : observers) {
			if (!observer.slot(args)) {
				run = false;
			}
		}

		return run;
	}

private:
	unsigned int _nextID = 0;

	struct SlotHandle {
		unsigned int id;
		EventFunc slot;
	};

	std::map<EventType, std::vector<SlotHandle>> _observers;
};