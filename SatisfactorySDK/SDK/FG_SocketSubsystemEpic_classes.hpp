#pragma once

// Satisfactory SDK

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
// 0x0008 (0x1980 - 0x1978)
class UEpicNetConnection : public UIpConnection
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x1978(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class SocketSubsystemEpic.EpicNetConnection");
		return ptr;
	}

};


// Class SocketSubsystemEpic.EpicNetDriver
// 0x0008 (0x06E0 - 0x06D8)
class UEpicNetDriver : public UIpNetDriver
{
public:
	bool                                               bIsPassthrough;                                           // 0x06D8(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x06D9(0x0007) MISSED OFFSET

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
