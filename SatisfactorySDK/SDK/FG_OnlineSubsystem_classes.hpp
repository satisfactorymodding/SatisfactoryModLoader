#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_OnlineSubsystem_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class OnlineSubsystem.NamedInterfaces
// 0x0038 (0x0060 - 0x0028)
class UNamedInterfaces : public UObject
{
public:
	TArray<struct FNamedInterface>                     NamedInterfaces;                                          // 0x0028(0x0010) (ZeroConstructor)
	TArray<struct FNamedInterfaceDef>                  NamedInterfaceDefs;                                       // 0x0038(0x0010) (ZeroConstructor, Config)
	unsigned char                                      UnknownData00[0x18];                                      // 0x0048(0x0018) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class OnlineSubsystem.NamedInterfaces");
		return ptr;
	}

};


// Class OnlineSubsystem.TurnBasedMatchInterface
// 0x0000 (0x0028 - 0x0028)
class UTurnBasedMatchInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class OnlineSubsystem.TurnBasedMatchInterface");
		return ptr;
	}


	void OnMatchReceivedTurn(const class FString& Match, bool bDidBecomeActive);
	void OnMatchEnded(const class FString& Match);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
