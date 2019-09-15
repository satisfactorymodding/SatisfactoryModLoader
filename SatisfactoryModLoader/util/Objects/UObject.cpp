#include <stdafx.h>

#include "UObject.h"

#include "UClass.h"

#include <util/Utility.h>

namespace SML {
	namespace Objects {
		/* FChunkedFixedUObjectArray */

		int FChunkedFixedUObjectArray::count() const {
			return countElems;
		}

		FUObjectItem const* FChunkedFixedUObjectArray::getObjPtr(int index) const {
			auto cIndex = index / elemsPerChunk;
			auto inChunk = index % elemsPerChunk;
			auto chunk = objs[cIndex];
			return chunk + inChunk;
		}

		FUObjectItem const& FChunkedFixedUObjectArray::get(int index) const {
			return *getObjPtr(index);
		}

		/* UObject */

		FUObjectArray*	UObject::objs = nullptr;

		FChunkedFixedUObjectArray& UObject::getObjs() {
			return objs->objs;
		}

		std::string UObject::getName() const {
			std::string name(name.getName());
			if (this->name.count > 0) {
				name += '_' + std::to_string(this->name.count);
			}

			auto pos = name.rfind('/');
			if (pos == std::string::npos) {
				return name;
			}

			return name.substr(pos + 1);
		}

		std::string UObject::getFullName() const {
			std::string name;

			if (clazz != nullptr) {
				std::string temp;
				for (auto p = outer; p; p = p->outer) {
					temp = p->getName() + "." + temp;
				}

				name += temp;
				name += getName();
			}

			return name;
		}

		UClass* UObject::findClass(const std::string& name) {
			return findObject<UClass>(name);
		}

		UClass* UObject::staticClass() {
			static auto ptr = UObject::findClass("Class CoreUObject.Object");
			return ptr;
		}

		void UObject::processEvent(class UFunction* function, void* parms) {
			return getVFunc<void(*)(UObject*, class UFunction*, void*)>(this, 64)(this, function, parms);
		}

		void* UObject::findFieldBase(const std::string& name) {
			return this->clazz->findField<void>(name);
		}

		UFunction * UObject::findFunction(const FName & name) {
			return (UFunction*)UClass::findFunction_f(this, name);
		}
	}
}