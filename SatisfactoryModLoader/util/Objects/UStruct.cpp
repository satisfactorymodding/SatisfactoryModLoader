#include "stdafx.h"
#include "UStruct.h"
#include "UClass.h"

#include <util/Utility.h>

namespace SML {
	namespace Objects {
		FieldIterator::FieldIterator(const UStruct * obj, bool searchForProp, bool useSuperCoder79) : obj(obj), searchForProp(searchForProp), useSuperCoder79(useSuperCoder79) {
			if (!obj) this->field = nullptr;
			else field = obj->childs;

			if (!field) iterateToNext();
		}

		bool FieldIterator::operator!=(const FieldIterator& other) const {
			return (field != other.field) || (obj != other.obj);
		}

		UField* FieldIterator::operator*() const {
			return field;
		}

		void FieldIterator::operator++() {
			iterateToNext();
		}

		void FieldIterator::iterateToNext() {
			while (field || obj) {
				// increment field
				if (field) field = field->next;
				else {
					obj = obj->super;
					if (obj) field = obj->childs;
				}
				// check if valid in terms of search params
				if (field && (!searchForProp || (field->clazz->castFlags & EClassCastFlags::CAST_UProperty))) break;
			}
		}

		FieldIterator UStruct::begin() const {
			return FieldIterator(this);
		}

		FieldIterator UStruct::end() const {
			return FieldIterator(nullptr);
		}
	}
}