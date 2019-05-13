#pragma once
#include <Windows.h>
#include <cstdint>

namespace SML {
	namespace Objects {
		struct FString {
			int16_t* data;
			int32_t length;

			FString();
			FString(const char* message);

			// TODO implement proper copy / move
			FString(const FString&) = delete;
			FString& operator=(const FString&) = delete;
			FString(FString&&) = delete;
			FString& operator=(FString&&) = delete;
		private:
			void create_message(const char* message);
		};
	}
}