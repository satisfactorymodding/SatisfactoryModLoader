#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>

class SpawnActorEvent : public Event {
public:
	SpawnActorEvent();
	virtual ~SpawnActorEvent();

	static constexpr EventType descriptor = EventType::OnPlayerBeginPlay;

	static constexpr const char* addressName = "UWorld::SpawnActor";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; AActor *__fastcall UWorld::SpawnActor<AActor>(UWorld *this, FActorSpawnParameters *SpawnParameters)
	static void* use(void* c, void* inName, void* location, void* rotation, void* templ, bool bNoCollisionFail, bool bRemoteOwned, void* owner, void* instigator, bool bNoFail, void* overrideLevel, bool bDeferConstruction) {
		log("SpawnActorEvent");
		auto pointer = (SpawnActorEventFunction)originalFunctions[descriptor].Function;
		return pointer(c, inName, location, rotation, templ, bNoCollisionFail, bRemoteOwned, owner, instigator, bNoFail, overrideLevel, bDeferConstruction);
	}

private:
	typedef void*(WINAPI* SpawnActorEventFunction)(VOID*, VOID*, VOID*, VOID*, VOID*, bool, bool, VOID*, VOID*, bool, VOID*, bool);
};

SpawnActorEvent::SpawnActorEvent() {
}


SpawnActorEvent::~SpawnActorEvent() {
}