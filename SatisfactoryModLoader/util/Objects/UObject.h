#pragma once

#include <cstdint>
#include <string>

#include "FName.h"

namespace SML {
	namespace Objects {
		class UObject;
		class UClass;

		template<typename Fn>
		SML_API inline Fn getVFunc(const void* obj, std::size_t index) {
			auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(obj));
			return reinterpret_cast<Fn>(vtable[index]);
		}

		SML_API class FUObjectItem {
		public:
			UObject* obj;
			int flags;
			int rootIndex;
			int serNum;
		};

		SML_API class FChunkedFixedUObjectArray {
		public:
			SML_API int count() const;

			enum {
				elemsPerChunk = 64 * 1024,
			};

			SML_API FUObjectItem const* getObjPtr(int index) const;
			SML_API FUObjectItem const& get(int index) const;

		private:
			FUObjectItem** objs;
			FUObjectItem* preAllocObjs;
			int maxElems;
			int countElems;
			int maxChunks;
			int countChunks;
		};

		SML_API class FUObjectArray {
		public:
			int objGCIndex;
			int objNGCIndex;
			int maxObjsNConsideredByGC;
			bool open4Disreg4GC;
			FChunkedFixedUObjectArray objs;
		};

		SML_API class UObject {
		private:
			SML_API void* findFieldBase(const std::string& name);

		public:
			static FUObjectArray*	objs;
			void***					vtable;
			std::int32_t			objFlags;
			std::int32_t			indexInternal;
			class UClass*			clazz;
			FName					name;
			class UObject*			outer;

			SML_API static FChunkedFixedUObjectArray& getObjs();
			SML_API std::string getName() const;
			SML_API std::string getFullName() const;

			template<typename T>
			SML_API static inline T* findObject(const std::string& name) {
				for (int i = 0; i < getObjs().count(); ++i) {
					auto object = getObjs().get(i).obj;

					if (object == nullptr) {
						continue;
					}

					if (object->getFullName() == name) {
						return (T*)(object);
					}
				}
				return nullptr;
			}

			SML_API static UClass* findClass(const std::string& name);

			template<typename T>
			SML_API static inline T* getObjCasted(std::size_t index) {
				return static_cast<T*>(getObjs().get(index).obj);
			}

			SML_API bool isA(UClass* cmp) const;

			SML_API static UClass* staticClass();

			SML_API void processEvent(class UFunction* function, void* parms);

			SML_API void execUgraph(int entryPoint);
			SML_API std::string getPName() const;

			template<typename T>
			SML_API inline T* findField(const std::string& name) {
				return (T*)findFieldBase(name);
			}

			SML_API UFunction* findFunction(const FName& name);
		};
	}
}