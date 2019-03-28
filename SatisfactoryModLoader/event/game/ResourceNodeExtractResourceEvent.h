#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>
#include "EnterChatMessageEvent.h"

class ResourceNodeExtractResourceEvent : public Event {
public:
	ResourceNodeExtractResourceEvent();
	virtual ~ResourceNodeExtractResourceEvent();

	static constexpr EventType descriptor = EventType::OnMinerExtractResource;

	static constexpr const char* addressName = "AFGResourceNode::ExtractResource";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// ; int __fastcall AFGResourceNode::ExtractResource(AFGResourceNode *this, int amount)
	static int use(void* node, int amount) {
		auto pointer = (ResourceNodeExtractResourceEventFunction)originalFunctions[descriptor].Function;
		return pointer(node, 100);
	}

private:
	typedef int(WINAPI* ResourceNodeExtractResourceEventFunction)(VOID*, int);
};

ResourceNodeExtractResourceEvent::ResourceNodeExtractResourceEvent() {
}


ResourceNodeExtractResourceEvent::~ResourceNodeExtractResourceEvent() {
}