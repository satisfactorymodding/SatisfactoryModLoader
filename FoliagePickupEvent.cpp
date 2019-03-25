#include "stdafx.h"
#include "FoliagePickupEvent.h"
#include "Utility.h"

FoliagePickupEvent::FoliagePickupEvent(){
}


FoliagePickupEvent::~FoliagePickupEvent(){
}

EventType FoliagePickupEvent::type() const {
	return descriptor;
}

void FoliagePickupEvent::use(const Event& event) {
	log("FoliagePickupEvent");
}