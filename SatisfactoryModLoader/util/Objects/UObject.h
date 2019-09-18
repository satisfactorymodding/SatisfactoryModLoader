#pragma once

#include <cstdint>
#include <string>

#include "FName.h"

namespace SML {
	namespace Objects {
		class UObject;
		class UClass;

		/**
		* Returns the function pointer by the given index from the given vtable pointer
		*
		* @author Panakotta00
		*/
		template<typename Fn>
		SML_API inline Fn getVFunc(const void* obj, std::size_t index) {
			auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(obj));
			return reinterpret_cast<Fn>(vtable[index]);
		}

		/**
		* Currently we dont know what this is
		*
		* @author Panakotta00
		*/
		SML_API class FUObjectItem {
		public:
			UObject* obj;
			int flags;
			int rootIndex;
			int serNum;
		};

		/**
		* Currently we dont know what this is
		*
		* @author Panakotta00
		*/
		SML_API class FChunkedFixedUObjectArray {
		public:
			/**
			* Returns the count of entrys
			*
			* @author Panakotta00
			*/
			SML_API int count() const;

			enum {
				elemsPerChunk = 64 * 1024,
			};

			/**
			* returns the object pointer by the given index
			*
			* @author Panakotta00
			*/
			SML_API FUObjectItem const* getObjPtr(int index) const;

			/**
			* returns the FUObjectItem by the given index
			*
			* @author Panakotta00
			*/
			SML_API FUObjectItem const& get(int index) const;

		private:
			FUObjectItem** objs;
			FUObjectItem* preAllocObjs;
			int maxElems;
			int countElems;
			int maxChunks;
			int countChunks;
		};

		/**
		* Currently we dont know what this is
		*
		* @author Panakotta00
		*/
		SML_API class FUObjectArray {
		public:
			int objGCIndex;
			int objNGCIndex;
			int maxObjsNConsideredByGC;
			bool open4Disreg4GC;
			FChunkedFixedUObjectArray objs;
		};

		/**
		* Base class of all Objects useable within the UObjectSystem from unreal
		*
		* @author Panakotta00
		*/
		SML_API class UObject {
		private:
			/**
			* trys to find the UField by the given name in this UObject otherwise returns nullptr
			*
			* @author Panakotta00
			*/
			SML_API void* findFieldBase(const std::string& name);

		public:
			static FUObjectArray* objs;
			void*** vtable;
			std::int32_t objFlags;
			std::int32_t indexInternal;
			class UClass* clazz;
			FName name;
			class UObject* outer;

			/**
			* returns all global UObjects
			*
			* @author Panakotta00
			*/
			SML_API static FChunkedFixedUObjectArray& getObjs();

			/**
			* returns the name of this UObject
			*
			* @author Panakotta00
			*/
			SML_API std::string getName() const;

			/**
			* returns the name and the path of this UObject
			*
			* @author Panakotta00
			*/
			SML_API std::string getFullName() const;

			/**
			* trys to find a UObject by the given name otherwise returns nullptr
			*
			* @author Panakotta00
			*/
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

			/**
			* trys to find a UClass by the given name otherwise returns nullptr
			*
			* @author Panakotta00
			*/
			SML_API static UClass* findClass(const std::string& name);

			/**
			* trys to fins a UObject by the given anem and cast it to the given type otherwise returns nullptr
			*
			* @author Panakotta00
			*/
			template<typename T>
			SML_API static inline T* getObjCasted(std::size_t index) {
				return static_cast<T*>(getObjs().get(index).obj);
			}

			/**
			* returns the UClass of Object
			*
			* @author Panakotta00
			*/
			SML_API static UClass* staticClass();

			/**
			* executes a given event or function with the given parameter/return structure
			*
			* @author Panakotta00
			*/
			SML_API void processEvent(class UFunction* function, void* parms);

			/**
			* trys to find a field with the given name and cast it to the given type otherwise returns nullptr
			*
			* @author Panakotta00
			*/
			template<typename T>
			SML_API inline T* findField(const std::string& name) {
				return (T*)findFieldBase(name);
			}

			/**
			* trys to find a function with the given name and cast it to the given type otherwise returns nullptr
			*
			* @author Panakotta00
			*/
			SML_API UFunction* findFunction(const FName& name);
		};
	}
}