#pragma once

#ifndef BPINTERFACE_H
#define BPINTERFACE_H

#include <Lib.h>
#include <util/Utility.h>

#include <map>
#include <set>

#include <util/Objects/FString.h>
#include <util/Objects/FName.h>
#include <util/Objects/UObject.h>
#include <util/Objects/UClass.h>
#include <util/Objects/UProperty.h>
#include <util/Objects/UFunction.h>
#include <util/Objects/FFrame.h>

namespace SDK {
	class UClass;
}

namespace SML {
	namespace Paks {
		struct FClassParams;
		class FObjectInitializer;
		class FReferenceCollector;
		class FVtableHelper;
		class UEnum;
		class UScriptStruct;

		// detour cache
		SML_API extern void(*processNewObjs)();
		SML_API extern void(*constructUClass)(Objects::UClass*&, FClassParams);
		SML_API extern void(*privateStaticClassBody)(const TCHAR*, const TCHAR*, Objects::UClass*&, void(*)(), std::uint32_t, Objects::EClassFlags, Objects::EClassCastFlags, const TCHAR*, void(*)(FObjectInitializer&), Objects::UObject*(*)(FVtableHelper&), void(*)(Objects::UObject*, FReferenceCollector&), Objects::UClass*(*)(), Objects::UClass*(*)(), bool);

		/**
		* Converts the given normal string into a wide one
		* ! WARNING ! No good implementation, does not support utf8! (only ASCII)
		*
		* @author Panakotta00
		*/
		SML_API inline std::wstring stringToW(std::string str) {
			return std::wstring(str.begin(), str.end());
		}

		/**
		* trys to get the size of the given vtable
		*
		* @author Brabb3l
		*/
		SML_API int getVtableSize(void** vtable);

		/**
		* Function declaration for functions able to register for a delegate
		*
		* @author Panakotta00
		*/
		typedef void(*DelegateFunction)(void*, void*);

		namespace {
			/**
			* !!! DO NOT USE !!!
			* refistered delegateFunctions
			*
			* @author Panakotta00
			*/
			SML_API std::map<void*, std::set<DelegateFunction>> registerdDispatchHandlers;
		}

		/**
		* Registers a function so it gets called when the given delegate gets called.
		* 
		* @author Panakotta00
		*/
		SML_API void registerDelegateHandler(void* delegate, DelegateFunction function);

		/**
		* Registers the given function so it gets called when the given delegate gets called.
		* Searches for function by given name in given object.
		*
		* @author Panakotta00
		*/
		SML_API void* registerDelegateHandler(Objects::UObject* obj, const std::string& name, DelegateFunction function);
		
		/**
		* Unregisters the given function from the given delegate
		*
		* @author Panakotta00
		*/
		SML_API void unregisterDelegateHandler(void* delegate, DelegateFunction function);

		/**
		* initializes the BP-Interface
		* gets automaticly called by SML
		*
		* @author Panakotta00
		*/
		SML_API void initBPInterface();



		// --- Enums --- //
		
		enum class ENativeBool {
			NotNative,
			Native
		};

		enum EPropStructParamsType {
			None,
			WithOff,
			Generic,
			Byte,
			Bool,
			Object,
			Class,
			SoftClass,
			Interface,
			Struct,
			Delegate,
			MulticastDelegate,
			Enum
		};
		


		// --- Structs --- //


		class FObjectInitializer {
		public:
			Objects::UObject* obj = nullptr;
			Objects::UObject* arch = nullptr;
			bool copyTransDefaults = false;
			bool shouldInitPropsFromArch = false;
			bool allowSubobjectInit = false;

			inline void finalize() {
				allowSubobjectInit = false;
			}
		};
		class FVtableHelper;
		class FReferenceCollector;

		struct FPropertyParamsBase {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
		};

		struct FPropertyParamsBaseWithOffset {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
		};

		struct FGenericPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
		};

		struct FBytePropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			UEnum* (*enumFunc)();
		};

		struct FBoolPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::uint32_t size;
			ENativeBool nativeBool;
			SIZE_T outerSize;
			void(*setBitFunc)(void*);
		};

		struct FObjectPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			Objects::UClass* (*classFunc)();
		};

		struct FClassPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			Objects::UClass* (*metaClassFunc)();
			Objects::UClass* (*classFunc)();
		};

		struct FSoftClassPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notifyFunc;
			std::int32_t off;
			Objects::UClass* (*metaClassFunc)();
		};

		struct FInterfacePropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			Objects::UClass* (*interfaceClassFunc)();
		};

		struct FStructPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			UScriptStruct* (*scriptStructFunc)();
		};

		struct FDelegatePropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			Objects::UFunction* (*sigFunctionFunc)();
		};

		struct FMulticastDelegatePropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t off;
			Objects::UFunction* (*sigFunctionFunc)();
		};

		struct FEnumPropertyParams {
			Objects::EPropertyClass type;
			const char* name;
			Objects::EObjectFlags objFlags;
			Objects::EPropertyFlags propFlags;
			std::int32_t dim;
			const char* notify;
			std::int32_t offset;
			UEnum* (*enumFunc)();
		};

		/**
		* Describes a function before it gets constructed
		*/
		 struct FFunctionParams {
			Objects::UObject* (*func)() = nullptr;
			const char* name = "";
			Objects::EObjectFlags objFlags = Objects::EObjectFlags::RF_NoFlags;
			Objects::UFunction* (*sFunc)() = nullptr;
			Objects::EFunctionFlags funcFlags = Objects::EFunctionFlags::FUNC_None;
			SIZE_T structSize = 0;
			const FPropertyParamsBase* const* propArr = nullptr;
			std::int32_t propCount = 0;
			std::uint16_t rpcId = 0;
			std::uint16_t rpcRespId = 0;
		};

		/**
		* Describes a connection of a function and class
		*/
		struct FClassFunctionLinkInfo {
			Objects::UFunction* (*func)() = nullptr;
			const char* name = "";
		};

		/**
		* Holds information about the C++ class itself
		*/
		struct FCppClassTypeInfoStatic {
			bool bIsAbstract = false;
		};

		/**
		* Holds information about the interface implementation of a class
		*/
		struct FImplementedInterfaceParams {
			Objects::UClass* (*classFunc)() = nullptr;
			std::int32_t off = 0;
			bool implementedBy2K = false;

			inline FImplementedInterfaceParams(Objects::UClass*(*classFunc)() = nullptr, std::int32_t off = 0, bool implementedBy2K = false)
			:	classFunc(classFunc),
				off(off),
				implementedBy2K(implementedBy2K) {}
		};

		/**
		* Describes a UClass before it gets constructed
		*/
		struct FClassParams {
			Objects::UClass* (*staticClass)() = nullptr;
			Objects::UObject* (*const *deps)() = nullptr;
			std::int32_t depsCount = 0;
			std::uint32_t flags = 0;
			const FClassFunctionLinkInfo* funcs = nullptr;
			std::int32_t funcCount = 0;
			const FPropertyParamsBase* const* props = nullptr;
			std::int32_t propCount = 0;
			const char* config = "";
			const FCppClassTypeInfoStatic* info = nullptr;
			const FImplementedInterfaceParams* interfaces = nullptr;
			std::int32_t interfaceCount = 0;
		};




		// --- Builders --- //

		/**
		* Helps to construct property parameters
		*
		* @author Panakotta00
		*/
		class PropertyBuilder {
		private:

			template<typename T, bool T::* Ptr>
			struct TBitSetFunc {
				static inline void bitSet(void* out) {
					((T*)out)->*Ptr = true;
				}
			};

			EPropStructParamsType structType = EPropStructParamsType::Generic;
			FPropertyParamsBase* params = nullptr;
			std::string pname;
			std::string notify;
			bool manualOff = false;

			inline PropertyBuilder() {};

			SML_API size_t createStructFromType(const Objects::EPropertyClass type);

		public:
			SML_API inline PropertyBuilder(const PropertyBuilder& other) {
				structType = other.structType;
				params = (FPropertyParamsBase*) std::memcpy(params, other.params, createStructFromType(other.params->type));
				pname = other.pname;
				notify = other.notify;
				manualOff = other.manualOff;
			}

			SML_API inline PropertyBuilder(const PropertyBuilder&& other) {
				structType = other.structType;
				params = other.params;
				pname = other.pname;
				notify = other.notify;
				manualOff = other.manualOff;
			}

			SML_API inline PropertyBuilder& operator=(const PropertyBuilder& other) {
				structType = other.structType;
				params = (FPropertyParamsBase*)std::memcpy(params, other.params, createStructFromType(other.params->type));
				pname = other.pname;
				notify = other.notify;
				manualOff = other.manualOff;
				return *this;
			}

			SML_API inline PropertyBuilder& operator=(const PropertyBuilder&& other) {
				structType = other.structType;
				params = other.params;
				pname = other.pname;
				notify = other.notify;
				manualOff = other.manualOff;
				return *this;
			}

			SML_API inline ~PropertyBuilder() {
				if (params) delete params;
			}

			/**
			* Creates a PropertyBuilder with a default setup for return values of functions
			*
			* @author Panakotta00
			*/
			SML_API static PropertyBuilder retVal(Objects::EPropertyClass type, std::string name = "unnamed");

			/**
			* Creates a PropertyBuilder with a default setup for function paramaters
			*
			* @author Panakotta00
			*/
			SML_API static PropertyBuilder param(Objects::EPropertyClass type, std::string name = "unnamed");

			/**
			* Creates a PropertyBuilder with a default setup for class attributes
			*
			* @author Panakotta00
			*/
			SML_API static PropertyBuilder attrib(Objects::EPropertyClass type, std::string name = "unnamed");

			/**
			* Constructs the generic property params and returns a pointer to them
			* It is stored in the builders scope!
			*
			* @author Panakotta00
			*/
			SML_API FPropertyParamsBase* build();

			/**
			* adds object flags
			* 
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& addObjFlags(Objects::EObjectFlags flags);

			/**
			* adds object flags
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& addObjFlags(unsigned int flags);

			/**
			* removes object flags
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& remObjFlags(Objects::EObjectFlags flags);

			/**
			* adds paramter flags
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& addParamFlags(Objects::EPropertyFlags flags);

			/**
			* adds parameter flags
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& addParamFlags(std::uint64_t flags);

			/**
			* removes paramter flags
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& remParamFlags(Objects::EPropertyFlags flags);

			/**
			* sets the propertys name
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& name(std::string name);

			/**
			* if the type hase an offset, it will get set to the given value
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& off(int offset = -1);

			/**
			* returns the offset of property
			* if property has no offset returns -2
			* if offset is not set returns -1
			*
			* @author Panakotta00
			*/
			SML_API std::int32_t getOff();

			/**
			* sets the referenced uclass/interface return function (staticClass) when type needs it
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& classFunc(Objects::UClass*(*func)());
			SML_API PropertyBuilder& classFunc(SDK::UClass*(*func)());

			/**
			* sets the "setBitFunc" of bool property
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& bitFunc(void(*func)(void*));

			/**
			* sets the size of the outer
			*
			* @auhtor Panakotta00
			*/
			SML_API PropertyBuilder& outerSize(size_t size);

			/**
			* other bool property data
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& boolData(size_t size = sizeof(bool), ENativeBool native = ENativeBool::Native);

			/**
			* Helps to setup bool property
			*
			* @author Panakotta00
			*/
			template<class T, bool T::* ptr>
			inline PropertyBuilder& helpBool() {
				boolData();
				outerSize(sizeof(T));
				bitFunc(TBitSetFunc<T, ptr>::bitSet);
				return *this;
			}

			/**
			* sets the metaClassRetFunc of class property
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& metaClassFunc(Objects::UClass*(*func)());

			/**
			* sets the enumRetFunc for the referenced enum
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& enumFunc(void*(*func)());

			/**
			* sets the funcRetFunc for the referenced function
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& funcFunc(void*(*)());

			/**
			* sets the structRetFunc for the referenced structure
			*
			* @author Panakotta00
			*/
			SML_API PropertyBuilder& structFunc(void*(*)());

			/**
			* returns the size of a property type (EPropertyClass)
			*
			* @author Panakotta00
			*/
			SML_API size_t getSize();
			SML_API static size_t getSize(Objects::EPropertyClass type);
		};

		/**
		* Helps to construct, build and register a custom Objects::UFunction
		*
		* @author Panakotta00
		*/
		class FunctionBuilder {
			template <class T>
			friend class ClassBuilder;

		public:
			template<typename T>
			using NativeFunc = void(*)(T*, Objects::FFrame&, void*);

		private:
			FunctionBuilder() {};

			static Objects::UObject* retVal;
			static Objects::UObject* retFunc() {
				return retVal;
			}

			std::vector<PropertyBuilder> props;
			FFunctionParams params;
			std::string fname;
			Objects::UFunction* constructed = nullptr;
			void* func = nullptr;

			SML_API void _registerFunc(Objects::UClass* clazz, void* func = nullptr);
			SML_API Objects::UFunction* _build(Objects::UClass* clazz, void* func = nullptr);
			SML_API void _attach(Objects::UClass* clazz, void* func = nullptr);

		public:
			/**
			* Creates a FunctionBuilder with a default setup for a method with the given name
			*
			* @author Panakotta00
			*/
			SML_API static FunctionBuilder Method(std::string name = "unnamed");

			/**
			* Creates a FunctionBuilder with a default setup for a static function with the given name
			*
			* @author Panakotta00
			*/
			SML_API static FunctionBuilder StaticFunction(std::string name = "unnamed");

			/**
			* constructs the Objects::UFunction and kinda binds it to the given class
			*
			* @author Panakotta00
			*/
			SML_API Objects::UFunction* construct(Objects::UClass* clazz);

			/**
			* registers the given native function or uses the already set native function to the given class and constructed function
			*
			* @author Panakotta00
			*/
			template<typename T>
			inline void registerFunc(Objects::UClass* clazz, NativeFunc<T> func = nullptr) {
				_registerFunc(clazz, func);
			}

			/**
			* constructs the function for the given class and registers the given native function or uses the already set native function
			*
			* @author Panakotta00
			*/
			template<typename T>
			inline Objects::UFunction* build(Objects::UClass* clazz, NativeFunc<T> func = nullptr) {
				return _build(clazz, func);
			}

			/**
			* Builds and attaches the function to the given class with the given native function or uses the already set native function
			*
			* @author Panakotta00
			*/
			template<typename T>
			inline void attach(Objects::UClass* clazz, NativeFunc<T> func = nullptr) {
				_attach(clazz, func);
			}

			/**
			* Sets the native function
			*
			* @author Panakotta00
			*/
			template<typename T>
			inline FunctionBuilder& native(NativeFunc<T> func) {
				this->func = func;
				return *this;
			}

			/**
			* add object flags
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& addObjFlags(Objects::EObjectFlags flags);

			/**
			* adds object flags
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& addObjFlags(unsigned int flags);

			/**
			* removes object flags
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& remObjFlags(Objects::EObjectFlags flags);

			/**
			* adds function flags
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& addFuncFlags(Objects::EFunctionFlags flags);

			/**
			* adds function flags
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& addFuncFlags(unsigned int flags);

			/**
			* removes function flags
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& remFuncFlags(Objects::EFunctionFlags flags);

			/**
			* sets the function namé
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& name(std::string name);

			/**
			* adds a property to the function (parameter or returnValues)
			*
			* @author Panakotta00
			*/
			SML_API FunctionBuilder& param(const PropertyBuilder& prop);
		};
	
		/**
		* Helps to construct, build and register a custom UClass
		*
		* @author Panakotta00
		*/
		template<class T>
		class ClassBuilder {
		public:
			typedef Objects::UClass*(*NativeStaticClass)();
			typedef void(T::*NativeConstructor)();
			typedef void(*NativeRealConstructor)(FObjectInitializer&);
			typedef void(T::*NativeDestructor)();
			typedef Objects::UObject*(*NativeVTHelp)(FVtableHelper&);
			typedef void(*NativeRefCol)(Objects::UObject*, FReferenceCollector&);
			typedef Objects::UClass*(*NativeSuper)();
			typedef Objects::UClass*(*NativeOuter)();
			typedef Objects::UClass*(*NativeGetClass)();
			typedef Objects::UFunction*(*NativeConstFunc)();
			typedef void(*NativeRegFuncs)();

			class UHelper;

		private:
			static inline void vnon() {}
			static inline Objects::UClass* cnon() { return nullptr; }
			static inline void refColNon(Objects::UObject*, FReferenceCollector&) {}
			static inline Objects::UClass* getFGPkg() { return Objects::UObject::staticClass(); }

			// building params
			FClassParams params;
			std::string cname;
			std::wstring cnameni;
			std::string pname = "/Script/FactoryGame";
			std::string cconfig = "Engine";
			Objects::EClassCastFlags cast = Objects::EClassCastFlags::CAST_None;
			NativeConstructor constructorf = nullptr;
			NativeRealConstructor realconstructorf = nullptr;
			NativeDestructor destructorf = nullptr;
			NativeVTHelp vtablehelpf = nullptr;
			NativeRefCol refcolf = &refColNon;
			NativeSuper superf = &cnon;
			NativeOuter outerf = &getFGPkg;
			NativeGetClass getclassf = nullptr;
			NativeConstFunc constFuncf = nullptr;
			NativeRegFuncs regFuncsf = nullptr;
			union {
				/**
				* Function cache for destroing SuperCoder79
				*/
				void(UHelper::*superdestructorf)() = nullptr;
				void* superdestructorfv;
			};

			std::vector<FunctionBuilder> funcs;
			std::vector<PropertyBuilder> props;
			std::vector<FImplementedInterfaceParams> interfaces;
			size_t paramOff = 0;

			// helper params
			Objects::UClass* constructed = nullptr;
			Objects::UClass* staticclass = nullptr;
			int funcI = 0;
			void** vfptr = nullptr;

			// static
			static ClassBuilder<T> active;

			inline ClassBuilder() {}

			static inline std::string remCTIdent(std::string str) {
				switch (str[0]) {
				case 'A':
				case 'U':
				case 'E':
				case 'F':
					return str.erase(0, 1);
				}
				return str;
			}

			template<class C>
			static std::string getClassName() {
				std::string n = typeid(C).name();
				n = n.substr(n.find_last_of(' ') + 1);
				return n.substr(n.find_last_of(':') + 1);
			}

		public:
			inline ~ClassBuilder() {
				vtable(nullptr);
			}

			class UHelper {
			public:
				virtual inline void destructor() {
					auto o = (Objects::UObject*) this;

					if (active.destructorf) (((T*)o)->*(active.destructorf))();
					if (active.superdestructorf) (this->*(active.superdestructorf))();
				}
			};

			/**
			* returns the templated ClassBuilder singelton reference
			*
			* @author Panakotta00
			*/
			inline static ClassBuilder& get() {
				return active;
			}

			/**
			* sets the class name (with prefix like 'U' or 'A')
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& name(std::string name) {
				cname = name;
				cnameni = stringToW(remCTIdent(name));
				return *this;
			}

			/**
			* sets the class containing package name
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& package(std::string package) {
				pname = package;
				return *this;
			}

			/**
			* sets the compile config name
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& config(std::string config) {
				cconfig = config;
				return *this;
			}

			/**
			* sets the static class function of the UClass
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& staticClass(NativeStaticClass func) {
				params.staticClass = func;
				return *this;
			}

			/**
			* sets the real class constructor function of the class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& realconstruct(NativeRealConstructor func) {
				realconstructorf = func;
				return *this;
			}

			/**
			* sets custom class constructor function of the class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& construct(NativeConstructor func) {
				constructorf = func;
				return *this;
			}

			/**
			* sets the destuctor function of the class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& destruct(NativeDestructor func) {
				destructorf = func;
				return *this;
			}

			/**
			* sets the destructor function of the superclass
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& superdestructor(void(*func)()) {
				superdestructorfv = (void*)func;
				return *this;
			}

			/**
			* sets the regerence collector function
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& refcol(NativeRefCol func) {
				refcolf = func;
				return *this;
			}

			/**
			* set the vtable helper function
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& vTableHelp(NativeVTHelp func) {
				vtablehelpf = func;
				return *this;
			}

			/**
			* sets the function to get the outer class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& outer(NativeOuter func) {
				outerf = func;
				return *this;
			}

			/**
			* sets the function to get the super class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& super(NativeSuper func) {
				superf = func;
				return *this;
			}

			/**
			* sets the function to register dependent native functions
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& regFuncs(NativeRegFuncs func) {
				regFuncsf = func;
				return *this;
			}

			/**
			* sets the construct/return UClass "singelton" function
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& constFunc(NativeConstFunc func) {
				constFuncf = func;
				return *this;
			}

			/**
			* sets the bootstraped UClass "singelton" constructor/return function
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& getClass(NativeGetClass func) {
				getclassf = func;
				return *this;
			}

			/**
			* sets base offset for the beginning of the upropertys
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& off(size_t off) {
				paramOff = off;
				return *this;
			}

			/**
			* Copies the given vtable with the given size and uses that one for all new created objects of that class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& vtable(void** vtable, size_t size = 0) {
				if (!vtable) {
					if (this->vfptr) free(this->vfptr);
					this->vfptr = nullptr;
				} else {
					if (!size) size = getVtableSize((void**)vtable);
					size *= sizeof(void*);
					vfptr = (void**)((vfptr) ? realloc(vfptr, size) : malloc(size));
					vfptr = (void**)memcpy(vfptr, vtable, size);
				}
				return *this;
			}

			/**
			* Sets some functions like destructor in stored vtable
			*
			* @auhtor Panakotta00
			*/
			inline void** vtable() {
				return vfptr;
			}

			/**
			* helps to set the superclass (super class needs "UClass* StaticClass" function)
			*
			* @author Panakotta00
			*/
			template<class Super>
			inline ClassBuilder& extendSDK() {
				super((NativeSuper)&Super::StaticClass);
				off(sizeof(Super));
				vtable((void**)((Objects::UClass*)Super::StaticClass())->defaultObj->vtable);
				superdestructor((void(*)())(vfptr)[0]);
				UHelper* h = new UHelper();
				vfptr = (void**)memcpy(vfptr, *(void***)h, sizeof(void*));
				delete h;
				return *this;
			}

			/**
			* helps to set the superclass (super class needs "UClass* staticClass" function)
			*
			* @author Panakotta00
			*/
			template<class Super>
			inline ClassBuilder& extend() {
				super((NativeSuper)&Super::staticClass);
				off(sizeof(Super));
				vtable((void**)((Objects::UClass*)Super::staticClass())->defaultObj->vtable);
				superdestructor((void(*)())(vfptr)[0]);
				UHelper* h = new UHelper();
				vfptr = (void**)memcpy(vfptr, *(void***)h, sizeof(void*));
				delete h;
				return *this;
			}

			/**
			* adds the given UFunction (as FunctionBuilder) to the class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& func(FunctionBuilder fb) {
				funcs.push_back(fb);
				return *this;
			}

			/**
			* adds the given UProperty (as PropertyBuilder) to the class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& prop(PropertyBuilder pb) {
				props.push_back(pb);
				return *this;
			}

			/**
			* add the given interface implementation description to the class
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& interfaceImpl(const FImplementedInterfaceParams&& params) {
				interfaces.push_back(params);
				return *this;
			}

			/**
			* adds the given class flags
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& addFlags(Objects::EClassFlags flags) {
				params.flags = (Objects::EClassFlags)(params.flags | flags);
				return *this;
			}

			/**
			* adds the given class flags
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& addFlags(std::uint64_t flags) {
				params.flags = (Objects::EClassFlags)(params.flags | flags);
				return *this;
			}

			/**
			* removes the given class flags
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& remFlags(Objects::EClassFlags flags) {
				params.flags = (Objects::EClassFlags)(params.flags & ~flags);
				return *this;
			}

			/**
			* adds the given cast flags
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& addCast(Objects::EClassCastFlags flags) {
				params.cast = (Objects::EClassCastFlags)(params.cast | flags);
				return *this;
			}

			/**
			* adds the given cast flags
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& addCast(std::uint64_t flags) {
				params.cast = (Objects::EClassCastFlags)(params.cast | flags);
				return *this;
			}

			/**
			* removes the given cast flags
			*
			* @author Panakotta00
			*/
			inline ClassBuilder& remCast(Objects::EClassCastFlags flags) {
				params.cast = (Objects::EClassCastFlags)(params.cast & ~flags);
				return *this;
			}

			/**
			* builds, compiles and register the class
			*
			* @author Panakotta00
			*/
			inline Objects::UClass* build() {
				auto objCompInDefer = (void(*)(Objects::UClass*(*)(), Objects::UClass*(*)(), const TCHAR*, const TCHAR*, bool, const TCHAR*, void(*)())) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UObjectCompiledInDefer");
				objCompInDefer(getclassf, params.staticClass, stringToW(cname).c_str(), stringToW(pname).c_str(), false, nullptr, nullptr);

				processNewObjs();

				return constructed;
			}

			// helper funcs

			/**
			* default getClass function or helps custom ones
			*
			* @author Panakotta00
			*/
			static inline Objects::UClass* getClass() {
				if (!active.constructed) {
					active.funcI = 0;

					// get funcs
					FClassFunctionLinkInfo* funcs = new FClassFunctionLinkInfo[active.funcs.size()];
					int i = 0;
					for (auto& f : active.funcs) {
						funcs[i++] = {active.constFuncf, f.fname.c_str()};
					}
					active.params.funcs = funcs;
					active.params.funcCount = i;

					// get props
					FPropertyParamsBase** props = new FPropertyParamsBase*[active.props.size()];
					i = 0;
					size_t size = active.paramOff;
					int nextOff = active.paramOff;
					for (auto& p : active.props) {
						auto noff = p.getOff();
						auto nsize = p.getSize();
						if (noff >= 0) nextOff = noff + nsize;
						else {
							if (noff == -1) p.off(nextOff);
							nextOff += nsize;
						}
						
						auto pr = p.build();
						size += nsize;
						props[i++] = pr;
					}
					active.params.props = props;
					active.params.propCount = i;

					active.params.interfaces = active.interfaces.data();
					active.params.interfaceCount = active.interfaces.size();

					// set config
					active.params.config = active.cconfig.c_str();

					// construct
					constructUClass(active.constructed, active.params);

					// reset and delloc
					delete[] funcs;
					delete[] props;
					active.params.funcs = nullptr;
					active.params.props = nullptr;
					active.params.funcCount = 0;
					active.params.propCount = 0;
					active.funcI = 0;
				}
				return active.constructed;
			}

			/**
			* default staticClass function or helps custom ones
			*
			* @author Panakotta00
			*/
			static inline Objects::UClass* staticClass() {
				if (!active.staticclass) {
					privateStaticClassBody(stringToW(active.pname).c_str(), active.cnameni.c_str(), active.staticclass, active.regFuncsf, sizeof(T), (Objects::EClassFlags)active.params.flags, active.cast, stringToW(active.cconfig).c_str(), active.realconstructorf, active.vtablehelpf, active.refcolf, active.superf, active.outerf, false);
				}
				return active.staticclass;
			}

			/**
			* default construct function or helps custom ones
			*
			* @author Panakotta00
			*/
			static inline void construct(FObjectInitializer& objInit) {
				((NativeRealConstructor)active.superf()->ClassConstructor)(objInit);
				if (active.vfptr) {
					(*(void***)objInit.obj) = active.vfptr;
				}
				objInit.obj->clazz = active.params.staticClass();

				if (active.constructorf) (((T*)objInit.obj)->*(active.constructorf))();
			}

			/**
			* default function constructor function or helps custom ones
			*
			* @author Panakotta00
			*/
			static inline Objects::UFunction* constFunc() {
				auto c = active.funcs[active.funcI++].construct(active.constructed);
				return c;
			}

			/**
			* default native function register function or helps custom ones
			*
			* @author Panakotta00
			*/
			static inline void regFuncs() {
				for (auto& f : active.funcs) {
					f.registerFunc<void>(active.params.staticClass());
				}
			}

			/**
			* basic init of class builder
			*
			* @author Panakotta00
			*/
			inline static ClassBuilder& Basic() {
				active.name(getClassName<T>());
				active.staticClass(staticClass);
				active.realconstruct(construct);
				active.getClass(getClass);
				active.regFuncs(regFuncs);
				active.constFunc(constFunc);
				active.addFlags(0x001000A0u);

				return active;
			}
		};
		template<class T>
		ClassBuilder<T> ClassBuilder<T>::active;
	}
}

#endif