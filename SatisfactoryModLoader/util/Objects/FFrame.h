#pragma once

#include <Lib.h>

#include <Windows.h>
#include <detours.h>

#include <util/Utility.h>

#include "FOutputDevice.h"
#include "UProperty.h"
#include "UFunction.h"
#include "FStack.h"

namespace SML {
	namespace Objects {
		/**
		* Object that holds information about the current execution/stack/scope of the BP VM.
		* Used f.e. for reading/writing data in UFunctions
		*/
		class FFrame : public FOutputDevice {
		public:
			UFunction* node;
			UObject* obj;
			std::uint8_t* code;
			std::uint8_t* locals;
			UProperty* prop;
			std::uint8_t* propAddr;
			FStack flow;
			FFrame* prevFrame;
			void* outParms;
			UField* propChain;
			UFunction* nativeFunc;
			bool failed;
			
			SML_API FFrame(UObject* obj, UFunction* node, void* locals, FFrame* prevFrame = nullptr, UField* propChain = nullptr) :
				node(node),
				obj(obj),
				code((std::uint8_t*)(node->script.getData())),
				locals((std::uint8_t*)locals),
				prop(nullptr),
				propAddr(nullptr),
				prevFrame(prevFrame),
				outParms(nullptr),
				propChain(propChain),
				nativeFunc(nullptr),
				failed(false) {}

			/**
			* Steps to the next scope/code entry/statement
			*
			* @author Panakotta00
			*/
			inline void step(UObject* obj, void* params) {
				auto stepFunc = (void(*)(FFrame*, UObject*, void*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FFrame::Step");
				stepFunc(this, obj, params);
			}

			/**
			* Steps to the next scope/code entry/statement with eventually extractrs/inserts the given data
			*
			* @author Panakotta00
			*/
			inline void stepProp(void* params, UProperty* prop) {
				auto stepFunc = (void(*)(FFrame*, void*, UProperty*))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FFrame::StepExplicitProperty");
				stepFunc(this, params, prop);
			}

			/**
			* General step execution based on current code/scope. Sets the given value to the next value on stack.
			*
			* @author Panakotta00
			*/
			inline void stepCompIn(void*const res) {
				if (code) {
					step(obj, res);
				} else {
					UProperty* prop = (UProperty*)propChain;
					propChain = prop->next;
					stepProp(res, prop);
				}
			}

			/**
			* General step execution based on current code/scope. Uses the given value to set the next value on stack.
			*
			* @author Panakotta00
			*/
			template<typename Type>
			inline Type& stepCompInRef(void*const temp) {
				propAddr = NULL;

				if (code) {
					step(obj, temp);
				} else {
					UProperty* prop = (UProperty*)propChain;
					propChain = prop->next;
					stepProp(temp, prop);
				}

				return (propAddr != NULL) ? *(Type*)(propAddr) : *(Type*)temp;
			}
		};
	}
}