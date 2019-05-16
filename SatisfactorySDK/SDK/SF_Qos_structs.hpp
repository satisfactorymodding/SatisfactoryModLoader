#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Basic.hpp"
#include "SF_OnlineSubsystemUtils_classes.hpp"
#include "SF_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Enums
//---------------------------------------------------------------------------

// Enum Qos.EQosResponseType
enum class EQosResponseType : uint8_t
{
	NoResponse                     = 0,
	Success                        = 1,
	Failure                        = 2,
	EQosResponseType_MAX           = 3
};


// Enum Qos.EQosCompletionResult
enum class EQosCompletionResult : uint8_t
{
	Invalid                        = 0,
	Success                        = 1,
	Failure                        = 2,
	Canceled                       = 3,
	EQosCompletionResult_MAX       = 4
};


// Enum Qos.EQosRegionResult
enum class EQosRegionResult : uint8_t
{
	Invalid                        = 0,
	Success                        = 1,
	Incomplete                     = 2,
	EQosRegionResult_MAX           = 3
};



//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct Qos.QosSearchPass
// 0x0008
struct FQosSearchPass
{
	int                                                RegionIdx;                                                // 0x0000(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                CurrentSessionIdx;                                        // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
};

// ScriptStruct Qos.QosPingServerInfo
// 0x0018
struct FQosPingServerInfo
{
	class FString                                      Address;                                                  // 0x0000(0x0010) (ZeroConstructor)
	int                                                Port;                                                     // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x0014(0x0004) MISSED OFFSET
};

// ScriptStruct Qos.QosDatacenterInfo
// 0x0040
struct FQosDatacenterInfo
{
	struct FText                                       DisplayName;                                              // 0x0000(0x0028)
	class FString                                      RegionId;                                                 // 0x0018(0x0010) (ZeroConstructor)
	bool                                               bEnabled;                                                 // 0x0028(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bVisible;                                                 // 0x0029(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bBeta;                                                    // 0x002A(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x5];                                       // 0x002B(0x0005) MISSED OFFSET
	TArray<struct FQosPingServerInfo>                  Servers;                                                  // 0x0030(0x0010) (ZeroConstructor)
};

// ScriptStruct Qos.QosRegionInfo
// 0x0078
struct FQosRegionInfo
{
	struct FQosDatacenterInfo                          Region;                                                   // 0x0000(0x0040) (Transient)
	EQosRegionResult                                   Result;                                                   // 0x0040(0x0001) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0041(0x0003) MISSED OFFSET
	int                                                AvgPingMs;                                                // 0x0044(0x0004) (ZeroConstructor, Transient, IsPlainOldData)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0048(0x0010) MISSED OFFSET
	TArray<int>                                        PingResults;                                              // 0x0058(0x0010) (ZeroConstructor, Transient)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0068(0x0008) MISSED OFFSET
	struct FDateTime                                   LastCheckTimestamp;                                       // 0x0070(0x0008) (Transient)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
