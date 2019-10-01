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

namespace SML {
	namespace Paks {
		SML_API inline std::wstring stringToW(std::string str) {
			// not good solution (no UTF-8 support)
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

		/**
		* Describes a property before it gets constructed
		*/
		SML_API struct FGenericPropertyParams {
			Objects::EPropertyClass type = (Objects::EPropertyClass)0;
			const char* name = nullptr;
			Objects::EObjectFlags objFlags = Objects::EObjectFlags::RF_NoFlags;
			Objects::EPropertyFlags propFlags = Objects::EPropertyFlags::Prop_None;
			std::int32_t dim = 0;
			const char* repNotStr = nullptr;
			std::int32_t off = 0;
		};

		/**
		* Describes a function before it gets constructed
		*/
		SML_API struct FFunctionParams {
			Objects::UObject* (*func)() = nullptr;
			const char* name = "";
			Objects::EObjectFlags objFlags = Objects::EObjectFlags::RF_NoFlags;
			Objects::UFunction* (*sFunc)() = nullptr;
			Objects::EFunctionFlags funcFlags = Objects::EFunctionFlags::FUNC_None;
			SIZE_T structSize = 0;
			const FGenericPropertyParams* const* propArr = nullptr;
			std::int32_t propCount = 0;
			std::uint16_t rpcId = 0;
			std::uint16_t rpcRespId = 0;
		};

		/**
		* Describes a connection of a function and class
		*/
		SML_API struct FClassFunctionLinkInfo {
			Objects::UFunction* (*func)() = nullptr;
			const char* name = "";
		};

		/**
		* Holds information about the C++ class itself
		*/
		SML_API struct FCppClassTypeInfoStatic {
			bool bIsAbstract = false;
		};

		/**
		* Holds information about the interface implementation of a class
		*/
		SML_API struct FImplementedInterfaceParams {
			Objects::UClass* (*ClassFunc)() = nullptr;
			std::int32_t Offset = 0;
			bool bImplementedByK2 = false;
		};

		/**
		* Describes a UClass before it gets constructed
		*/
		SML_API struct FClassParams {
			Objects::UClass* (*staticClass)() = nullptr;
			Objects::UObject* (*const *deps)() = nullptr;
			std::int32_t depsCount = 0;
			std::uint32_t flags = 0;
			const FClassFunctionLinkInfo* funcs = nullptr;
			std::int32_t funcCount = 0;
			const FGenericPropertyParams* const* props = nullptr;
			std::int32_t propCount = 0;
			const char* config = "";
			const FCppClassTypeInfoStatic* info = nullptr;
			const FImplementedInterfaceParams* interfaces = nullptr;
			std::int32_t interfaceCount = 0;
		};




		// --- Builders --- //

		/**
		* Helps to construct generic property parameters
		*
		* @author Panakotta00
		*/
		SML_API class PropertyBuilder {
		private:
			FGenericPropertyParams params;
			std::string pname;

			PropertyBuilder() {};

		public:
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
			SML_API FGenericPropertyParams* build();

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
			SML_API PropertyBuilder& addParamFlags(unsigned int flags);

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
			* returns the size of a property type (EPropertyClass)
			*
			* @author Panakotta00
			*/
			SML_API size_t getSize();
		};

		/**
		* Helps to construct, build and register a custom Objects::UFunction
		*
		* @author Panakotta00
		*/
		SML_API class FunctionBuilder {
			template <class T>
			friend class ClassBuilder;

		public:
			template<typename T>
			using NativeFunc = void(*)(T*, Objects::FFrame&, void*);

		private:
			FunctionBuilder() {};

			static Objects::UObject* retVal;
			static Objects::UObject* retFunc() {
				Utility::warning("f ret");
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
			typedef void(*NativeConstructor)(FObjectInitializer&);
			typedef void(*NativeDestructor)(T*);
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
			Objects::EClassCastFlags cast = CAST_None;
			NativeConstructor constructorf = nullptr;
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
			class UHelper {
			public:
				virtual inline void dest(void* shit) {
					Utility::warning("shit: ", shit);
					auto o = (Objects::UObject*) this;
					Utility::warning("Dest: ", this, " ", o->clazz, " ", o->clazz->getName(), " ", o->clazz->childs);
					o->clazz->debug();
					Objects::UField* f = o->clazz->childs;
					while (f) {
						auto p = (Objects::UProperty*)f;
						f = p->next;
						if (!(p->clazz->castFlags & Objects::EClassCastFlags::CAST_UProperty)) continue;

						union {
							size_t vptr;
							void(Objects::UProperty::* dest)(void*);
						};
						vptr = (*(size_t**)p)[0x5C];
						//auto dest = reinterpret_cast<void(Objects::UProperty::*)(void*)>(vptrf);
						//(p->*(dest))((void*)(o + p->internalOffset));
					}

					if (active.destructorf) active.destructorf((T*) o);
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
			* sets the constructor function of the class
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

				auto reg = (void(*)()) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "ProcessNewlyLoadedUObjects");
				reg();

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
					FGenericPropertyParams** props = new FGenericPropertyParams*[active.props.size()];
					i = 0;
					size_t size = active.paramOff;
					for (auto& p : active.props) {
						auto pr = p.build();
						pr->off = size;
						size += pr->dim;
						props[i++] = pr;
					}
					active.params.props = props;
					active.params.propCount = i;

					// set config
					active.params.config = active.cconfig.c_str();

					// construct
					auto constructUClass = (void(*)(Objects::UClass*&, FClassParams)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UE4CodeGen_Private::ConstructUClass");
					constructUClass(active.constructed, active.params);

					// reset and delloc
					//delete[] funcs;
					/*delete[] props;
					active.params.funcs = nullptr;
					active.params.props = nullptr;
					active.params.funcCount = 0;
					active.params.propCount = 0;*/
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
					auto gpscb = (void(*)(const TCHAR*, const TCHAR*, Objects::UClass*&, void(*)(), std::uint32_t, Objects::EClassFlags, Objects::EClassCastFlags, const TCHAR*, void(*)(FObjectInitializer&), Objects::UObject*(*)(FVtableHelper&), void(*)(Objects::UObject*, FReferenceCollector&), Objects::UClass*(*)(), Objects::UClass*(*)(), bool)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "GetPrivateStaticClassBody");
					gpscb(stringToW(active.pname).c_str(), active.cnameni.c_str(), active.staticclass, active.regFuncsf, sizeof(T), (Objects::EClassFlags)active.params.flags, active.cast, stringToW(active.cconfig).c_str(), active.constructorf, active.vtablehelpf, active.refcolf, active.superf, active.outerf, false);
				}
				return active.staticclass;
			}

			/**
			* default construct function or helps custom ones
			*
			* @author Panakotta00
			*/
			static inline void construct(FObjectInitializer& objInit) {
				((NativeConstructor)active.superf()->ClassConstructor)(objInit);
				if (active.vfptr) {
					Utility::warning("meep ");
					(*(void***)objInit.obj) = active.vfptr;
				}
				objInit.obj->clazz = active.params.staticClass();

				Objects::UField* f = objInit.obj->clazz->childs;
				while (f) {
					auto p = (Objects::UProperty*)f;
					f = p->next;
					if (!(p->clazz->castFlags & Objects::EClassCastFlags::CAST_UProperty)) continue;

					union {
						size_t vptr;
						void(Objects::UProperty::* init)(void*);
					};
					vptr = (*(size_t**)p)[0x5D];
					//(p->*(init))((void*)(objInit.obj + p->internalOffset));
				}
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
				active.construct(construct);
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