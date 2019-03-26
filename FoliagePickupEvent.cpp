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

const char* FoliagePickupEvent::name() const {
	return "UFGFoliageLibrary::CheckInventorySpaceAndGetStacks";
}