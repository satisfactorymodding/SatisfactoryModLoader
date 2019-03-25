#include "stdafx.h"
#include "DemoEvent.h"
#include "Utility.h"

constexpr EventType DemoEvent::descriptor;

DemoEvent::DemoEvent(){
}

DemoEvent::~DemoEvent(){
}

EventType DemoEvent::type() const {
	return descriptor;
}

void DemoEvent::use(const Event& event) {
	log("DemoEvent");
}