#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>
#include "SuicideEvent.h"

class EnterChatMessageEvent : public Event {
public:
	EnterChatMessageEvent();
	virtual ~EnterChatMessageEvent();

	static constexpr EventType descriptor = EventType::OnPlayerEnterChatMessage;

	static constexpr const char* addressName = "AFGPlayerController::EnterChatMessage";

	virtual EventType type() const {
		return descriptor;
	}

	virtual const char* name() const {
		return addressName;
	}

	struct s2 {
		int16_t* data;
		int32_t length;
	};

	static void create_message(s2* data, const char* message) {
		data->length = strlen(message) + 1;
		int16_t *chars = new int16_t[data->length + 1];
		for (size_t i = 0; i < data->length; i++) {
			chars[i] = message[i];
		}
		chars[data->length] = '\0';
		data->data = chars;
	}

	static void send_message(void* player, const char* message) {
		if (player != NULL) {
			log("player != NULL");
		}

		s2 msg;
		create_message(&msg, message);

		auto pointer = (void(WINAPI*)(VOID*, s2*))originalFunctions[descriptor].Function;

		log("POINTER");
		pointer(player, &msg);
	}

	static void send_messages(void* player, std::vector<const char*> messages) {
		s2 msg;
		for (const char* m : messages) {
			create_message(&msg, m);

			auto pointer = (void(WINAPI*)(VOID*, s2*))originalFunctions[descriptor].Function;
			pointer(player, &msg);
		}
	}

	//; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
	static void use(void* player, s2* message) {
		log("EnterChatMessage");

		char* chars = new char[message->length + 2];
		for (size_t i = 0; i < message->length; i++) {
			chars[i] = message->data[i];
		}

		const char* msg = (const char*)chars;

		std::string msgString(msg);

		auto modFunction = (ModFunc)originalFunctions[descriptor].ModFunction;
		std::vector<std::string> returns = {};
		std::vector<void*> args = {
			player, &msgString, &returns
		};

		std::vector<void*> newArguments = modFunction(EnterChatMessageEvent(), args);

		if (returns.capacity() == 0) {
			auto pointer = (void(WINAPI*)(VOID*, s2*))originalFunctions[descriptor].Function;
			pointer(player, message);
			return;
		}

		// use new data
		for (std::string v : returns) {
			EnterChatMessageEvent::send_message(newArguments[0], v.c_str());
		}
	}
};

EnterChatMessageEvent::EnterChatMessageEvent() {
}


EnterChatMessageEvent::~EnterChatMessageEvent() {
}