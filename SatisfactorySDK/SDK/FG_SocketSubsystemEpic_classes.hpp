#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_SocketSubsystemEpic_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class SocketSubsystemEpic.EpicNetConnection
// 0x0008 (0x1918 - 0x1910)
class UEpicNetConnection : public UIpConnection
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x1910(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class SocketSubsystemEpic.EpicNetConnection");
		return ptr;
	}

};


// Class SocketSubsystemEpic.EpicNetDriver
// 0x0008 (0x0570 - 0x0568)
class UEpicNetDriver : public UIpNetDriver
{
public:
	bool                                               bIsPassthrough;                                           // 0x0568(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0569(0x0007) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class SocketSubsystemEpic.EpicNetDriver");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
