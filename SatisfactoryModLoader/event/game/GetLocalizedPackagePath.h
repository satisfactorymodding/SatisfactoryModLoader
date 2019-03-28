#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>
#include <util/FString.h>

class GetLocalizedPackagePathEvent : public Event {
public:
	GetLocalizedPackagePathEvent();
	virtual ~GetLocalizedPackagePathEvent();

	static constexpr EventType descriptor = EventType::GetLocalizedPackagePath;

	static constexpr const char* addressName = "FPackageName::GetLocalizedPackagePath";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// FString FPackageName::GetLocalizedPackagePath(const FString& InSourcePackagePath)
	static FString* use(void* packageName, FString* InSourcePackagePath) { // TODO: turn that pointer back to a reference?

		//// mod functions
		auto modFunction = (ModFunc)originalFunctions[descriptor].ModFunction;
		std::vector<void*> args = {
			packageName,
			InSourcePackagePath
		};
		// std::vector<void*>&
		modFunction(GetLocalizedPackagePathEvent(), args);


		auto pointer = (GetLocalizedPackagePathFunction)originalFunctions[descriptor].Function;
		return pointer(packageName, InSourcePackagePath);
	}

private:
	typedef FString*(WINAPI* GetLocalizedPackagePathFunction)(void*, FString*);
};

GetLocalizedPackagePathEvent::GetLocalizedPackagePathEvent() {
}


GetLocalizedPackagePathEvent::~GetLocalizedPackagePathEvent() {
}
