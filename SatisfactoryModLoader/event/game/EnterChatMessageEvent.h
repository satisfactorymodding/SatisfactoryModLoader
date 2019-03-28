#pragma once
#include <event/Event.h>
#include <util/Utility.h>
#include <event/EventLoader.h>
#include <util/FString.h>
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

	static void create_message(FString* data, const char* message) {
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

		FString msg;
		create_message(&msg, message);

		auto pointer = (EnterChatMessageFunc)originalFunctions[descriptor].Function;

		log("POINTER");
		pointer(player, &msg);
	}

	static void send_messages(void* player, std::vector<const char*> messages) {
		FString msg;
		for (const char* m : messages) {
			create_message(&msg, m);

			auto pointer = (EnterChatMessageFunc)originalFunctions[descriptor].Function;
			pointer(player, &msg);
		}
	}

	//; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
	static void use(void* player, FString* message) {
		log("EnterChatMessage");

		// convert the default message to a readable char*
		char* chars = new char[message->length + 2];
		for (size_t i = 0; i < message->length; i++) {
			chars[i] = message->data[i];
		}

		// convert to a string
		std::string msgString(chars);

		// run mod functions to get and get a return vector
		auto modFunction = (ModFunc)originalFunctions[descriptor].ModFunction;
		std::vector<std::string> returns = {};
		std::vector<void*> args = {
			player, &msgString, &returns
		};

		// get new arguments from the output
		std::vector<void*> newArguments = modFunction(EnterChatMessageEvent(), args);

		// run default function if no return values were given
		if (returns.capacity() == 0) {
			auto pointer = (EnterChatMessageFunc)originalFunctions[descriptor].Function;
			pointer(player, message);
			return;
		}

		// use new data
		for (std::string v : returns) {
			EnterChatMessageEvent::send_message(newArguments[0], v.c_str());
		}
	}

private:
	typedef void(WINAPI* EnterChatMessageFunc)(VOID*, FString*);
};

EnterChatMessageEvent::EnterChatMessageEvent() {
}


EnterChatMessageEvent::~EnterChatMessageEvent() {
}