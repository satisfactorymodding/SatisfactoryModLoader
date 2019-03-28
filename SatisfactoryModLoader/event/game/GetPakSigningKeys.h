#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>

class GetPakSigningKeysEvent : public Event {
public:
	GetPakSigningKeysEvent();
	virtual ~GetPakSigningKeysEvent();

	static constexpr EventType descriptor = EventType::GetPakSigningKeys;

	static constexpr const char* addressName = "FPakPlatformFile::GetPakSigningKeys";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	// void FPakPlatformFile::GetPakSigningKeys(FEncryptionKey& OutKey)
	static void use(void* OutKey) {
		log("Prevent pak signing keys from being read.");
		// We don't do anything, so that the Unreal Engine thinks it does not need to check the signature of pak files
		// auto pointer = (GetLocalizedPackagePathFunction)originalFunctions[descriptor].Function;
		// pointer(OutKey);
	}

private:
	typedef void(WINAPI* GetLocalizedPackagePathFunction)(void*);
};

GetPakSigningKeysEvent::GetPakSigningKeysEvent() {
}


GetPakSigningKeysEvent::~GetPakSigningKeysEvent() {
}