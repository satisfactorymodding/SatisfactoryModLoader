#include "stdafx.h"
#include "Delegate.h"

#include "UFunction.h"

namespace SML {
	namespace Objects {
		void FMulticastScriptDelegate::bind(UObject * obj, FName func) {
			for (auto d : delegates) if (d.obj == obj && d.funcName == func) return;
			delegates.add({obj, func});
		}
		
		void FMulticastScriptDelegate::invoke(void * params) {
			for (auto d : delegates) {
				if (!d.obj.isValid()) continue; // TODO: unbind
				auto f = d.obj->findFunction(d.funcName);
				if (!f) continue; // TODO: unbind
				f->invoke(d.obj.get(), params);
			}
		}
	}
}
