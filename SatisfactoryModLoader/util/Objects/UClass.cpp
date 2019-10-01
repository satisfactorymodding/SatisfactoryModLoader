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

		void UClass::debug() {
			std::vector<UProperty*> vars;

			Utility::warning((std::uint64_t)&castFlags - (std::uint64_t)this);

			UField* f = childs;
			while (f) {
				if ((f->clazz->castFlags & Objects::EClassCastFlags::CAST_UProperty) && (f->clazz->castFlags & Objects::EClassCastFlags::CAST_UProperty)) {
					//vars.push_back((UProperty*)f);
				}
				vars.push_back((UProperty*)f);
				f = f->next;
			}

			std::stringstream str;
			str << "\n" << std::endl;
			str << "### Class - '" << getName() << "' ###" << std::endl;

			str << " Variables (Name, Offset):" << std::endl;
			for (auto v : vars) str << " " << v->getName() << " " << v->internalOffset << std::endl;
			str << std::endl;

			str << std::string(13 + getName().length() + 5, '#') << std::endl;

			SML::Utility::warning(str.str());
		}
	}
}