#include "stdafx.h"
#include "UFunction.h"

#include "FFrame.h"

#include <util/Utility.h>
#include "UField.h"
#include "UClass.h"

#include <sstream>

namespace SML {
	namespace Objects {
		void UFunction::invoke(UObject* obj, void * param) {
			obj->processEvent(this, param);
		}

		void UFunction::debug() {
			std::vector<UProperty*> params;

			UField* f = this->childs;
			while (f) {
				//if (f->Class->ClassCastFlags & Objects::EClassCastFlags::CASTCLASS_UProperty && f->Class->ClassCastFlags & Objects::EClassCastFlags::CASTCLASS_UProperty) {
				params.push_back((UProperty*)f);
				//}
				f = f->next;
			}

			std::stringstream str;
			str << "\n" << std::endl;
			str << "### Function - '" << getName() << "' ###" << std::endl;

			str << " Parameters (Name, Offset):" << std::endl;
			for (auto v : params) str << " " << v->getName() << " " << v->internalOffset << std::endl;
			str << std::endl;

			str << std::string(16 + getName().length() + 5, '#') << std::endl;

			SML::Utility::warning(str.str());
		}
	}
}