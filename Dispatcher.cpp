#include "stdafx.h"
#include "Dispatcher.h"
#include "Connection.h"
#include <algorithm>

Connection Dispatcher::subscribe(const EventType& descriptor, SlotType&& slot) {
	auto id = _nextID;
	SlotHandle handle = { id,slot };

	_observers[descriptor].push_back(handle);
	_nextID++;

	return Connection(this, id);
}

void Dispatcher::unsubscribe(const Connection& connection) {
	for (auto&& pair : _observers) {
		auto&& handles = pair.second;

		handles.erase(std::remove_if(
			handles.begin(), handles.end(),
			[&](SlotHandle& handle) {
				return handle.id == connection.id();
			}),
			handles.end());
	}
}

void Dispatcher::post(const Event& event) const {
	auto type = event.type();

	if (_observers.find(type) == _observers.end()) {
		return;
	}

	auto&& observers = _observers.at(type);

	for (auto&& observer : observers) {
		observer.slot(event);
	}
}