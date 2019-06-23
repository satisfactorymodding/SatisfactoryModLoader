#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_GameAnalyticsModule_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class GameAnalyticsModule.AnalyticsRequestBase
// 0x0098 (0x00C0 - 0x0028)
class UAnalyticsRequestBase : public UObject
{
public:
	unsigned char                                      UnknownData00[0x98];                                      // 0x0028(0x0098) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class GameAnalyticsModule.AnalyticsRequestBase");
		return ptr;
	}

};


// Class GameAnalyticsModule.AnalyticsService
// 0x0068 (0x0090 - 0x0028)
class UAnalyticsService : public USaveGame
{
public:
	unsigned char                                      UnknownData00[0x48];                                      // 0x0028(0x0048) MISSED OFFSET
	struct FGuid                                       mClientId;                                                // 0x0070(0x0010) (ZeroConstructor, IsPlainOldData)
	class UEOSMetrics*                                 mEOSMetricsHandle;                                        // 0x0080(0x0008) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x8];                                       // 0x0088(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class GameAnalyticsModule.AnalyticsService");
		return ptr;
	}


	class FString GetPagePrefix();
	class FString GetBuildPrefix();
};


// Class GameAnalyticsModule.GoogleAnalytics
// 0x0000 (0x00C0 - 0x00C0)
class UGoogleAnalytics : public UAnalyticsRequestBase
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class GameAnalyticsModule.GoogleAnalytics");
		return ptr;
	}

};


// Class GameAnalyticsModule.AnalyticsRequest
// 0x0000 (0x0028 - 0x0028)
class UAnalyticsRequest : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class GameAnalyticsModule.AnalyticsRequest");
		return ptr;
	}

};


// Class GameAnalyticsModule.StatHat
// 0x0000 (0x00C0 - 0x00C0)
class UStatHat : public UAnalyticsRequestBase
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class GameAnalyticsModule.StatHat");
		return ptr;
	}

};


// Class GameAnalyticsModule.StatHatJsonRequest
// 0x0010 (0x00D0 - 0x00C0)
class UStatHatJsonRequest : public UAnalyticsRequestBase
{
public:
	TArray<class UStatHat*>                            mPendingRequests;                                         // 0x00C0(0x0010) (ZeroConstructor)

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class GameAnalyticsModule.StatHatJsonRequest");
		return ptr;
	}


	bool SendRequest();
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
