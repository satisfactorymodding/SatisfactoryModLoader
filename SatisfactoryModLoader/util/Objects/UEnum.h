#pragma once

#include "FString.h"
#include "UField.h"

namespace SML {
	namespace Objects {
		template<typename K, typename V>
		class TTuple {
			K k;
			V v;
		};

		class UEnum : public UField {
		public:
			enum ECppForm {
				Regular,
				Namespaced,
				EnumClass,
			};

			FString type;
			TArray<TTuple<FName, std::int64_t>> names;
			ECppForm form;
			SDK::FText *(*displayNameFunc)(SDK::FText*, int);
		};
	}
}