#include <stdafx.h>
#include "FString.h"

namespace SML {
	namespace Objects {
		FString::FString() {}

		FString::FString(const char* message) {
			this->create_message(message);
		}

		void FString::create_message(const char* message) {
			length = strlen(message) + 1;
			int16_t *chars = new int16_t[length + 1];
			for (size_t i = 0; i < length; i++) {
				chars[i] = message[i];
			}
			chars[length] = '\0';
			data = chars;
		}
	}
}