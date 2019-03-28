#include "stdafx.h"
#include "Dispatcher.h"
#include "Connection.h"
#include <algorithm>

// add a new function to the event
Connection Dispatcher::subscribe(const EventType& descriptor, EventFunc slot) {
	auto id = _nextID;
	SlotHandle handle = { id,slot };

	_observers[descriptor].push_back(handle);
	_nextID++;

	return Connection(this, id);
}

// remove a function from the event by connection
void Dispatcher::unsubscribe(const Connection& connection) {
	for (auto pair : _observers) {
		auto handles = pair.second;

		handles.erase(std::remove_if(
			handles.begin(), handles.end(),
			[&](SlotHandle& handle) {
			return handle.id == connection.id();
		}),
			handles.end());
	}
}