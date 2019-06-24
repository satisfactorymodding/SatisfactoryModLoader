#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Qos_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class Qos.QosBeaconClient
// 0x0038 (0x03D8 - 0x03A0)
class AQosBeaconClient : public AOnlineBeaconClient
{
public:
	unsigned char                                      UnknownData00[0x38];                                      // 0x03A0(0x0038) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Qos.QosBeaconClient");
		return ptr;
	}


	void ServerQosRequest(const class FString& InSessionId);
	void ClientQosResponse(EQosResponseType Response);
};


// Class Qos.QosBeaconHost
// 0x0010 (0x0360 - 0x0350)
class AQosBeaconHost : public AOnlineBeaconHostObject
{
public:
	unsigned char                                      UnknownData00[0x10];                                      // 0x0350(0x0010) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Qos.QosBeaconHost");
		return ptr;
	}

};


// Class Qos.QosEvaluator
// 0x0058 (0x0080 - 0x0028)
class UQosEvaluator : public UObject
{
public:
	unsigned char                                      UnknownData00[0x20];                                      // 0x0028(0x0020) MISSED OFFSET
	bool                                               bInProgress;                                              // 0x0048(0x0001) (ZeroConstructor, IsPlainOldData)
	bool                                               bCancelOperation;                                         // 0x0049(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x6];                                       // 0x004A(0x0006) MISSED OFFSET
	TArray<struct FDatacenterQosInstance>              Datacenters;                                              // 0x0050(0x0010) (ZeroConstructor, Transient)
	unsigned char                                      UnknownData02[0x20];                                      // 0x0060(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Qos.QosEvaluator");
		return ptr;
	}

};


// Class Qos.QosRegionManager
// 0x0098 (0x00C0 - 0x0028)
class UQosRegionManager : public UObject
{
public:
	int                                                NumTestsPerRegion;                                        // 0x0028(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	float                                              PingTimeout;                                              // 0x002C(0x0004) (ZeroConstructor, Config, IsPlainOldData)
	TArray<struct FQosRegionInfo>                      RegionDefinitions;                                        // 0x0030(0x0010) (ZeroConstructor, Config)
	TArray<struct FQosDatacenterInfo>                  DatacenterDefinitions;                                    // 0x0040(0x0010) (ZeroConstructor, Config)
	struct FDateTime                                   LastCheckTimestamp;                                       // 0x0050(0x0008) (ZeroConstructor)
	class UQosEvaluator*                               Evaluator;                                                // 0x0058(0x0008) (ZeroConstructor, IsPlainOldData)
	EQosCompletionResult                               QosEvalResult;                                            // 0x0060(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0061(0x0007) MISSED OFFSET
	TArray<struct FRegionQosInstance>                  RegionOptions;                                            // 0x0068(0x0010) (ZeroConstructor)
	class FString                                      ForceRegionId;                                            // 0x0078(0x0010) (ZeroConstructor)
	bool                                               bRegionForcedViaCommandline;                              // 0x0088(0x0001) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData01[0x7];                                       // 0x0089(0x0007) MISSED OFFSET
	class FString                                      SelectedRegionId;                                         // 0x0090(0x0010) (ZeroConstructor)
	unsigned char                                      UnknownData02[0x20];                                      // 0x00A0(0x0020) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class Qos.QosRegionManager");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
