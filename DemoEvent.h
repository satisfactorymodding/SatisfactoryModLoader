#pragma once
#include "Event.h"

class DemoEvent : public Event
{
public:
	DemoEvent();
	virtual ~DemoEvent();

	static constexpr EventType descriptor = EventType::None;

	virtual EventType type() const;

	virtual void use(const Event& event);
};