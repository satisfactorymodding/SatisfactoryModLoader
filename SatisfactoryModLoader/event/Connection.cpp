#include "stdafx.h"

#include "event/Connection.h"
#include "event/Dispatcher.h"

Connection::Connection()
{
}

unsigned int Connection::id() const {
	return _id;
}

// shortcut to unsubscribe
void Connection::disconnect() {
	if (_dispatcher) {
		_dispatcher->unsubscribe(*this);
	}
}

Connection::Connection(Dispatcher* dispatcher, unsigned int id)
	: _dispatcher(dispatcher)
	, _id(id) {

}