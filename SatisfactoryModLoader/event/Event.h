#pragma once
#include <string>
#include <vector>

enum EventType {
	PlayerSuicide,
	PlayerTookDamage,
	PlayerBeginPlay,
	PlayerSentMessage,
	END
};

class Event {
public:
	virtual ~Event();

	virtual EventType type() const = 0;
	virtual const char* name() const = 0;
};

typedef std::vector<void*>(WINAPI* ModFunc)(const Event&, std::vector<void*>&);