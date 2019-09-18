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
	}
}

#endif