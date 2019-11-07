#pragma once

#include <Lib.h>

#include "UStruct.h"

namespace SML {
	namespace Objects {
		/**
		* Flag register for function specs
		*/
		enum EFunctionFlags : std::uint32_t {
			FUNC_None = 0x00000000,
			FUNC_Final = 0x00000001,
			FUNC_RequiredAPI = 0x00000002,
			FUNC_BlueprintAuthorityOnly = 0x00000004,
			FUNC_BlueprintCosmetic = 0x00000008,
			FUNC_Net = 0x00000040,
			FUNC_NetReliable = 0x00000080,
			FUNC_NetRequest = 0x00000100,
			FUNC_Exec = 0x00000200,
			FUNC_Native = 0x00000400,
			FUNC_Event = 0x00000800,
			FUNC_NetResponse = 0x00001000,
			FUNC_Static = 0x00002000,
			FUNC_NetMulticast = 0x00004000,
			FUNC_UbergraphFunction = 0x00008000,
			FUNC_MulticastDelegate = 0x00010000,
			FUNC_Public = 0x00020000,
			FUNC_Private = 0x00040000,
			FUNC_Protected = 0x00080000,
			FUNC_Delegate = 0x00100000,
			FUNC_NetServer = 0x00200000,
			FUNC_HasOutParms = 0x00400000,
			FUNC_HasDefaults = 0x00800000,
			FUNC_NetClient = 0x01000000,
			FUNC_DLLImport = 0x02000000,
			FUNC_BlueprintCallable = 0x04000000,
			FUNC_BlueprintEvent = 0x08000000,
			FUNC_BlueprintPure = 0x10000000,
			FUNC_EditorOnly = 0x20000000,
			FUNC_Const = 0x40000000,
			FUNC_NetValidate = 0x80000000,
			FUNC_AllFlags = 0xFFFFFFFF,
		};

		/**
		* UField containg information about a function of a UClass like the function pointer it self
		*/
		class UFunction : public UStruct {
		public:
			EFunctionFlags flags;
			uint8_t parmNum;
			uint16_t parmsSize;
			uint16_t retValOff;
			uint16_t RPCId;
			uint16_t RPCRespID;
			class UProperty* prop2int;
			void* eGraphFunc;
			uint16_t eGraphCallOff;
			void* func;

			/**
			* Returns the UClass instace of UFunctions
			*/
			SML_API static UClass* staticClass() {
				static auto ptr = UObject::findClass("Class CoreUObject.Function");
				return ptr;
			}

			/**
			* prints useful information about this UFunction
			* used for debuging
			*
			* @author Panakotta00
			*/
			SML_API void debug();

			/**
			* Executes the referred UFunction on the given object with the given parameter/return structure.
			*
			* @author Panakotta00
			*/
			SML_API void invoke(UObject* obj, void* parameters = nullptr);
		};
	}
}