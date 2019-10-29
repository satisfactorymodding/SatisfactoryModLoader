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
			for (int i = 0; i < delegates.num(); ++i) {
				auto d = delegates[i];
				if (!d.obj.isValid()) {
					delegates.remove(i);
					--i;
					continue;
				}
				auto f = d.obj->findFunction(d.funcName);
				if (!f) {
					delegates.remove(i);
					--i;
					continue;
				}
				f->invoke(d.obj.get(), params);
			}
		}

		void FMulticastScriptDelegate::unbind(UObject* obj, FName func) {
			for (int i = 0; i < delegates.num(); ++i) {
				auto d = delegates[i];
				if (d.funcName == func && d.obj.get() == obj) {
					delegates.remove(i);
				}
			}
		}
	}
}
