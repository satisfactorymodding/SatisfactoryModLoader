#pragma once

#include <Lib.h>

#include "OutputDevice.h"
#include "UProperty.h"
#include "UFunction.h"
#include "FStack.h"

namespace SML {
	namespace Objects {
		SML_API class FFrame : public OutputDevice {
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
		};
	}
}