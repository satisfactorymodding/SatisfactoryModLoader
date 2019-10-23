#include "stdafx.h"
#include "SmartPointer.h"

#include "../Utility.h"
#include "UObject.h"

namespace SML {
	namespace Objects {
		WeakPtr::WeakPtr(UObject * o) {
			index = o->indexInternal;
			serial = UObject::getObjs().get(index).serNum;
		}
		
		bool WeakPtr::isValid() {
			auto p = get();
			return p;
		}

		UObject* WeakPtr::operator*() {
			auto p = get();
			if (!p) throw std::exception("weakpointer is not valid, can't dereference");
			return p;
		}

		UObject* WeakPtr::operator->() {
			auto p = get();
			if (!p) throw std::exception("access invalid weakpointer");
			return p;
		}

		bool WeakPtr::operator==(const WeakPtr & o) const {
			return o.index == index && o.serial == serial;
		}

		void WeakPtr::operator=(const WeakPtr & o) {
			index = o.index;
			serial = o.serial;
		}

		void WeakPtr::operator=(UObject * o) {
			index = o->indexInternal;
			serial = UObject::getObjs().get(index).serNum;
		}

		bool WeakPtr::operator<(const WeakPtr & o) const {
			if (index < o.index) return true;
			if (index > o.index) return true;
			return serial < o.serial;
		}

		UObject* WeakPtr::get() {
			auto oi = UObject::getObjs().getObjPtr(index);
			if (!oi || (oi->serNum != serial) || !oi->obj->isValid()) return nullptr;
			return oi->obj;
		}
	}
}