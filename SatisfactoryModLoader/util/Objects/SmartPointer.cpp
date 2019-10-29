#include "stdafx.h"
#include "SmartPointer.h"

#include "../Utility.h"
#include "UObject.h"

namespace SML {
	namespace Objects {
		FWeakObjectPtr::FWeakObjectPtr(UObject * o) {
			(*this) = o;
		}
		
		bool FWeakObjectPtr::isValid() const {
			auto p = get();
			return p;
		}

		UObject* FWeakObjectPtr::operator*() const {
			auto p = get();
			if (!p) throw std::exception("weakpointer is not valid, can't dereference");
			return p;
		}

		UObject* FWeakObjectPtr::operator->() const {
			auto p = get();
			if (!p) throw std::exception("access invalid weakpointer");
			return p;
		}

		bool FWeakObjectPtr::operator==(const FWeakObjectPtr & o) const {
			return o.index == index && o.serial == serial;
		}

		void FWeakObjectPtr::operator=(const FWeakObjectPtr & o) {
			index = o.index;
			serial = o.serial;
		}

		void FWeakObjectPtr::operator=(UObject * o) {
			index = o->indexInternal;
			serial = UObject::getObjs().get(index).serNum = UObject::objs->allocSerialnum(index);
		}

		bool FWeakObjectPtr::operator<(const FWeakObjectPtr & o) const {
			if (index < o.index) return true;
			if (index > o.index) return true;
			return serial < o.serial;
		}

		UObject* FWeakObjectPtr::get() const {
			auto oi = UObject::getObjs().getObjPtr(index);
			if (!oi || (oi->serNum != serial) || !oi->obj->isValid()) return nullptr;
			return oi->obj;
		}
	}
}