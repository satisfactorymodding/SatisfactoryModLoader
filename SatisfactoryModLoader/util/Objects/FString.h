#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>

#include "TArray.h"

namespace SML {
	namespace Objects {
		SML_API class FString : public TArray<wchar_t> {
		public:
			SML_API FString();
			SML_API FString(const wchar_t* other);
			SML_API FString(const char* message);
			SML_API FString(const FString& other);
			SML_API FString(FString&& other);

			SML_API ~FString();

			SML_API FString& operator=(const FString& other);
			SML_API FString& operator=(FString&& other);

			SML_API bool isValid() const;

			SML_API const wchar_t* c_str() const;

			SML_API std::string toStr() const;
		};
	}
}