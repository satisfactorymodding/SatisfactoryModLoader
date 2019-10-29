#pragma once

#include "TArray.h"
#include "FName.h"
#include "SmartPointer.h"

namespace SML {
	namespace Objects {
		struct FScriptDelegate {
			FWeakObjectPtr obj;
			FName funcName;
		};

		struct FMulticastScriptDelegate {
			TArray<FScriptDelegate> delegates;

			SML_API void bind(UObject* obj, FName func);
			SML_API void invoke(void* params);
			SML_API void unbind(UObject* obj, FName func);
		};
	}
}