#pragma once
#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "CoreUObject_classes.hpp"

namespace UE4
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function CoreUObject.Object.ExecuteUbergraph
struct UObject_ExecuteUbergraph_Params
{
	int                                                EntryPoint;                                               // (Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
