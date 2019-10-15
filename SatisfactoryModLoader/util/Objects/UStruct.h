#pragma once

#include <Lib.h>

#include "UProperty.h"
#include "TArray.h"

namespace SML {
	namespace Objects {
		class UStruct;

		struct FieldIterator {
			const UStruct* obj;
			UField* field;

			bool useSuperCoder79;
			bool searchForProp = false;

			SML_API FieldIterator(const UStruct* obj, bool searchForProp = false, bool useSuperCoder79 = true);

			SML_API bool operator!=(const FieldIterator& other) const;
			SML_API UField* operator*() const;
			SML_API void operator++();

		private:
			SML_API void iterateToNext();
		};

		/**
		* Representation of UStruct used by Unreal
		*/
		class UStruct : public UField {
		public:
			class UStruct* super;
			UField* childs;
			int32_t propSize;
			int32_t minAlig;
			TArray<uint8_t> script;
			class UProperty* prop;
			class UProperty* ref;
			class UProperty* destructor;
			class UProperty* constructor;
			TArray<UObject*> scriptObjRef;

			/**
			* returns the UClass of UStruct
			*/
			SML_API static UClass* staticClass() {
				static auto ptr = UObject::findClass("Class CoreUObject.Struct");
				return ptr;
			}

			SML_API FieldIterator begin() const;
			SML_API FieldIterator end() const;
		};
	}
}