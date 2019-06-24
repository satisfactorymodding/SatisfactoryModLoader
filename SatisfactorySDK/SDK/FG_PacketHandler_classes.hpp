#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_PacketHandler_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class PacketHandler.HandlerComponentFactory
// 0x0000 (0x0028 - 0x0028)
class UHandlerComponentFactory : public UObject
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class PacketHandler.HandlerComponentFactory");
		return ptr;
	}

};


// Class PacketHandler.NetAnalyticsAggregatorConfig
// 0x0010 (0x0038 - 0x0028)
class UNetAnalyticsAggregatorConfig : public UObject
{
public:
	TArray<struct FNetAnalyticsDataConfig>             NetAnalyticsData;                                         // 0x0028(0x0010) (ZeroConstructor, Config)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class PacketHandler.NetAnalyticsAggregatorConfig");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
