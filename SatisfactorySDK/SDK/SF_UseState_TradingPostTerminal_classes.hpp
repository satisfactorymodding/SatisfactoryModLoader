#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_UseState_TradingPostTerminal_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// BlueprintGeneratedClass UseState_TradingPostTerminal.UseState_TradingPostTerminal_C
// 0x0000 (0x0030 - 0x0030)
class UUseState_TradingPostTerminal_C : public UFGUseState
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("BlueprintGeneratedClass UseState_TradingPostTerminal.UseState_TradingPostTerminal_C");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
