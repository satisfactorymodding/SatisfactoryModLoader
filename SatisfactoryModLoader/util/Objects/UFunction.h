#pragma once

#include <Lib.h>

#include "UStruct.h"

namespace SML {
	namespace Objects {
		SML_API class UFunction : public UStruct {
		public:
			uint32_t			flags;
			uint16_t			repOff;
			uint8_t				parmNum;
			uint16_t			parmsSize;
			uint16_t			retValOff;
			uint16_t			RPCId;
			uint16_t			RPCRespID;
			class UProperty*	prop2int;
			void*				func;

			SML_API static UClass* staticClass() {
				static auto ptr = UObject::findClass("Class CoreUObject.Function");
				return ptr;
			}

			SML_API void debug();

			SML_API void invoke(UObject* obj, void* parameters = nullptr);
		};
	}
}