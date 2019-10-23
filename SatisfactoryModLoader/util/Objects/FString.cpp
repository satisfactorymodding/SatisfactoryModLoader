#include <stdafx.h>
#include "FString.h"

namespace SML {
	namespace Objects {
		FString::FString() {
			count = max = 0;
			data = nullptr;
		}

		FString::FString(const wchar_t* other) {
			max = count = other ? static_cast<int32_t>(std::wcslen(other)) + 1: 0;

			if (count) {
				data = (wchar_t*)FMemory::malloc(max * sizeof(wchar_t));
				data = (wchar_t*)std::memcpy(data, other, count * sizeof(wchar_t));
				data[count - 1] = L'\0';
			} else {
				data = nullptr;
			}
		};

		FString::FString(const char* message) {
			max = count = message ? strlen(message) + 1 : 0;
			if (count) {
				int16_t *chars = (int16_t*)FMemory::malloc(max * sizeof(int16_t));
				for (size_t i = 0; i < count; ++i) {
					chars[i] = message[i];
				}
				data = (wchar_t*)chars;
				data[count - 1] = L'\0';
			} else data = nullptr;
		}

		FString::FString(const FString& other) : TArray(other) {}

		FString::FString(FString&& other) : TArray(other) {}

		FString::~FString() {}

		FString& FString::operator=(const FString& other) {
			return (FString&)TArray::operator=(other);
		}

		FString& FString::operator=(FString&& other) {
			return (FString&)TArray::operator=(other);
		}

		bool FString::isValid() const {
			return data != nullptr;
		}

		const wchar_t* FString::c_str() const {
			return (wchar_t*)getData();
		}

		std::string FString::toStr() const {
			if (!count || !data) return "";
			const auto length = std::wcslen(data);

			std::string str(length, '\0');

			std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(data, data + length, '?', &str[0]);

			return str;
		}
	}
}