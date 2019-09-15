#pragma once

#ifndef BPINTERFACE_H
#define BPINTERFACE_H

#include <Lib.h>
#include <util/Utility.h>

#include <map>
#include <set>

#include <util/Objects/FName.h>
#include <util/Objects/UObject.h>

namespace SML {
	namespace Paks {
		typedef void(*DelegateFunction)(void*, void*);

		namespace {
			// hooked function for delagte call
			//SML_API void(*delegateCallDetoured)(void*, void*);
		
			// register handlers
			SML_API std::map<void*, std::set<DelegateFunction>> registerdDispatchHandlers;
		}

		SML_API void registerDelegateHandler(void* delegate, DelegateFunction function);
		SML_API void* registerDelegateHandler(Objects::UObject* obj, const std::string& name, DelegateFunction function);
		SML_API void unregisterDelegateHandler(void* delegate, DelegateFunction function);
		SML_API void initBPInterface();
	}
}

#endif