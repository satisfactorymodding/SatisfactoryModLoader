#include "stdafx.h"

#include "UClass.h"
#include "UProperty.h"

#include "SatisfactoryModLoader.h"

#include <vector>
#include <sstream>

namespace SML {
	namespace Objects {
		UFunction*(*UClass::findFunction_f)(UObject*, Objects::FName) = nullptr;

		UClass* UClass::staticClass() {
			static auto ptr = UObject::findClass("CoreUObject.Class");
			return ptr;
		}

		UObject* UClass::createDefObj() {
			return getVFunc<UObject*(*)(UClass*)>(this, 103)(this);
		}

		bool UClass::isChild(UClass* super) {
			auto s = this;
			while (s) {
				if (s == super) return true;
				s = (UClass*)s->super;
			}
			return false;
		}

		void UClass::debug() {
			std::vector<UProperty*> vars;

			for (auto f : *this) {
				if ((f->clazz->castFlags & Objects::EClassCastFlags::CAST_UProperty) && (f->clazz->castFlags & Objects::EClassCastFlags::CAST_UProperty)) {
					//vars.push_back((UProperty*)f);
				}
				vars.push_back((UProperty*)f);
			}

			std::stringstream str;
			str << "\n" << std::endl;
			str << "### Class - '" << getName() << "' ###" << std::endl;

			str << " Variables (Name, Offset, property_flags):" << std::endl;
			for (auto v : vars) str << " " << v->getName() << " " << v->internalOffset << " " << v->propFlags << std::endl;
			str << std::endl;

			str << std::string(13 + getName().length() + 5, '#') << std::endl;

			SML::Utility::warning(str.str());
		}

		UObject* UClass::constructObject(UObject* outer, FName name, EObjectFlags flags, EInternalObjectFlags internalFlags, UObject* templ, bool cpyTransient, void* instanceGraph, bool templIsArche) {
			static UObject*(*consObj)(UClass*, UObject*, FName, EObjectFlags, EInternalObjectFlags, UObject*, bool, void*, bool) = nullptr;
			if (!consObj) consObj = (UObject*(*)(UClass*, UObject*, FName, EObjectFlags, EInternalObjectFlags, UObject*, bool, void*, bool)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "StaticConstructObject_Internal");

			return consObj(this, outer, name, flags, internalFlags, templ, cpyTransient, instanceGraph, templIsArche);
		}

		bool UClass::implements(UClass* i) {
			try {
				getImplementation(i);
				return true;
			} catch (...) { return false; }
		}

		FImplementedInterface UClass::getImplementation(UClass* i) {
			if (!this || !i || !(i->classFlags & EClassFlags::CLASS_Interface) || i == (UClass*)SDK::UInterface::StaticClass()) std::exception("no interface class provided");;
			auto super = this;
			while (super) {
				for (FImplementedInterface si : super->interfaces) {
					if (si.clazz && si.clazz->isChild(i)) return si;
				}
				super = (UClass*)super->super;
			}
			throw std::exception("interface not found");
		}
	}
}