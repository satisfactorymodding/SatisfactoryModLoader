// Satisfactory SDK

#include <stdafx.h>

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CoreUObject_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
TNameEntryArray* FName::GNames = nullptr;
FUObjectArray* UObject::GObjects = nullptr;
UWorld** UWorld::GWorld = nullptr;
}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
