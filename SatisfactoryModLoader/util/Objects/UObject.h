#pragma once

#include <cstdint>
#include <string>

#include "FName.h"

namespace SML {
	namespace Objects {
		class UObject;
		class UClass;

		/**
		* Flag register for object specs
		*/
		enum EObjectFlags : unsigned int {
			RF_NoFlags = 0x00000000,
			RF_Public = 0x00000001,
			RF_Standalone = 0x00000002,
			RF_MarkAsNative = 0x00000004,
			RF_Transactional = 0x00000008,
			RF_ClassDefaultObject = 0x00000010,
			RF_ArchetypeObject = 0x00000020,
			RF_Transient = 0x00000040,
			RF_MarkAsRootSet = 0x00000080,
			RF_TagGarbageTemp = 0x00000100,
			RF_NeedInitialization = 0x00000200,
			RF_NeedLoad = 0x00000400,
			RF_KeepForCooker = 0x00000800,
			RF_NeedPostLoad = 0x00001000,
			RF_NeedPostLoadSubobjects = 0x00002000,
			RF_NewerVersionExists = 0x00004000,
			RF_BeginDestroyed = 0x00008000,
			RF_FinishDestroyed = 0x00010000,
			RF_BeingRegenerated = 0x00020000,
			RF_DefaultSubObject = 0x00040000,
			RF_WasLoaded = 0x00080000,
			RF_TextExportTransient = 0x00100000,
			RF_LoadCompleted = 0x00200000,
			RF_InheritableComponentTemplate = 0x00400000,
			RF_DuplicateTransient = 0x00800000,
			RF_StrongRefOnFrame = 0x01000000,
			RF_NonPIEDuplicateTransient = 0x02000000,
			RF_WillBeLoaded = 0x08000000,
		};

		/**
		* Flag enum for internal usage
		*/
		enum class EInternalObjectFlags : std::int32_t {
			None = 0,
			ReachableInCluster = 1 << 23,
			ClusterRoot = 1 << 24,
			Native = 1 << 25,
			Async = 1 << 26,
			AsyncLoading = 1 << 27,
			Unreachable = 1 << 28,
			PendingKill = 1 << 29,
			RootSet = 1 << 30,
			HadReferenceKilled = 1 << 31,
			GarbageCollectionKeepFlags = Native | Async | AsyncLoading,
			AllFlags = ReachableInCluster | ClusterRoot | Native | Async | AsyncLoading | Unreachable | PendingKill | RootSet | HadReferenceKilled
		};

		/**
		* Returns the function pointer by the given index from the given vtable pointer
		*/
		template<typename Fn>
		SML_API inline Fn getVFunc(const void* obj, std::size_t index) {
			auto vtable = *reinterpret_cast<const void***>(const_cast<void*>(obj));
			return reinterpret_cast<Fn>(vtable[index]);
		}

		/**
		* Currently we dont know what this is
		*/
		class __declspec(align(8)) FUObjectItem {
		public:
			UObject* obj;
			EObjectFlags flags;
			int rootIndex;
			int serNum;
		};

		/**
		* Currently we dont know what this is
		*/
		class FChunkedFixedUObjectArray {
		public:
			/**
			* Returns the count of entrys
			*/
			SML_API int count() const;

			enum {
				elemsPerChunk = 64 * 1024,
			};

			/**
			* returns the object pointer by the given index
			*/
			SML_API FUObjectItem* getObjPtr(int index) const;

			/**
			* returns the FUObjectItem by the given index
			*/
			SML_API FUObjectItem& get(int index) const;

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
		*/
		class FUObjectArray {
		public:
			int objGCIndex;
			int objNGCIndex;
			int maxObjsNConsideredByGC;
			bool open4Disreg4GC;
			FChunkedFixedUObjectArray objs;

			/**
			* returns a new serial number
			*
			* @author Panakotta00
			*/
			SML_API int allocSerialnum(int index);
		};

		/**
		* Base class of all Objects useable within the UObjectSystem from unreal
		*/
		class UObject {
		private:
			/**
			* trys to find the UField by the given name in this UObject otherwise returns nullptr
			*/
			SML_API void* findFieldBase(const std::string& name);

		public:
			static FUObjectArray* objs;
			void*** vtable;
			EObjectFlags objFlags;
			std::int32_t indexInternal;
			class UClass* clazz;
			FName name;
			class UObject* outer;

			/**
			* returns all global UObjects
			*/
			SML_API static FChunkedFixedUObjectArray& getObjs();

			/**
			* returns the name of this UObject
			*/
			SML_API std::string getName() const;

			/**
			* returns the name and the path of this UObject
			*/
			SML_API std::string getFullName() const;

			/**
			* trys to find a UObject by the given name otherwise returns nullptr
			*/
			template<typename T>
			static inline T* findObject(const std::string& name) {
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
			*/
			SML_API static UClass* findClass(const std::string& name);

			/**
			* trys to fins a UObject by the given index and cast it to the given type otherwise returns nullptr
			*/
			template<typename T>
			SML_API static inline T* getObjCasted(std::size_t index) {
				return static_cast<T*>(getObjs().get(index).obj);
			}

			/**
			* returns the UClass of Object
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

			/**
			* returns if object is pending for kill
			*
			* @author Panakotta00
			*/
			SML_API bool isPendingKill();

			/**
			* checks if the given object is valid
			*
			* @author Panakotta00
			*/
			SML_API static bool isValid(UObject* obj);

			/**
			* checks if it self is valid (if this pointer is valid)
			*
			* @author Panakotta00
			*/
			SML_API bool isValid();

			/**
			* checks if self is instance of given uclass
			*
			* @author Panakotta00
			*/
			SML_API bool isA(UClass* clazz);


			/**
			* creates and adds a new subobject to the object
			*
			* @author Panakotta00
			*/
			SML_API UObject* createDefaultSubobject(FName name, UClass* type, UClass* retType, bool required = false, bool abstract = false, bool transient = false);

			/**
			* creates and adds a new subobject of given template type to the object
			*
			* @author Panakotta00
			*/
			template<class T>
			inline T* createDefaultSubobject(FName name, bool require = false, bool abstract = false, bool transient = false) {
				return (T*) createDefaultSubobject(name, T::staticClass(), T::staticClass(), require, abstract, transient);
			}

			/**
			* creates and adds a new subobject of given sdk template type
			*
			* @author Panakotta00
			*/
			template<class sdkT>
			inline sdkT* createDefaultSubobjectSDK(FName name, bool require = false, bool abstract = false, bool transient = false) {
				return (sdkT*) createDefaultSubobject(name, (UClass*) sdkT::StaticClass(), (UClass*) sdkT::StaticClass(), require, abstract, transient);
			}

			/**
			* returns the transient package
			*
			* @author Panakotta00
			*/
			SML_API static UObject* getTransientPackage();
		};
	}
}